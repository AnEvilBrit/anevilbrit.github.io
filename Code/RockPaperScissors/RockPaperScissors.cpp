#include <iostream> // Simple input and output functions
#include <string> // Allows for string usage
#include <ctime> // Allows for time() usage and more
#include <map> // Allows for the usage of maps (dictionaries)
#include <mutex>
// Not using namespace std just in case I need to use other libraries and to not conflict with them 

std::mutex mtx;

// Variable for the computers choice
std::string computer;

// Variable for the users choice
std::string userChoice;

// Function to clean the users input to make it much easier to compare
std::string stringToLower(std::string str)
{
    for (auto &c : str)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

void clearConsole()
{
    // This works without (in namespace std) because of C++17 and beyond. They don't require this
    std::lock_guard lock(mtx);
    system("cls");  // NOLINT(concurrency-mt-unsafe) I am using protection :)
}

void wait()
{
    std::cout << "Press the 'Enter' key to continue... ";
    std::cin.get();
}

// Main function and game
int main()
{   
    // Creates a map (dictionary) to see what lose condition will be paired up with the win condition, e.g. rock beats scissors
    std::map<std::string, std::string> conditions = {{"paper", "rock"},{"scissors", "paper"},{"rock", "scissors"}};
    
    // Uses ctime for a random seed this seed is used for true random numbers if it was the same seed each time it would output the same random numbers, time() gives the current timestamp which will be different every time you run this program
    std::srand(std::time(nullptr));  // NOLINT(clang-diagnostic-shorten-64-to-32, cert-msc51-cpp) This is because it should be fine as it is an RNG generator
    
    // This makes a random number from 0 to 2. This is because rand() % 3 = 0 - 2
    // Switch for choosing the computers hand. This is better than if statements because it is more manageable
    switch (rand() % 3)  // NOLINT(concurrency-mt-unsafe) It will be safe (Even though I am using mutex earlier :D)
    {
    case 0:
        computer = "rock";
        break;
    case 1:
        computer = "paper";
        break;
    case 2:
        computer = "scissors";
        break;
    // It should never reach this default case but if it does it will output an error message
    default:
        std::cout << "Random number generator failed\n";
        break;
    }

    // Repeats the program until a correct input is written. This makes it so wrong inputs are not passed through which would create errors
    while (userChoice != "rock" || userChoice != "paper" || userChoice != "scissors")
    {
        // Asks the user for rock paper or scissors converts the input to lower so the input is case-insensitive
        std::cout << "Rock, Paper or Scissors?\n";
        std::cin >> userChoice;
        userChoice = stringToLower(userChoice);
        clearConsole();

        // Made this area of code more dynamic, so it only needs one if statement
        if (userChoice == "rock" || userChoice == "paper" || userChoice == "scissors")
        {
            std::cout << "You chose " << userChoice << "\n" << "The computer chose " << computer << "\n";
            break;
        }
        // This else statement will loop back to the beginning as there is no break and the while conditions will not be met
        else
        {
            std::cout << "That input is not in the rock paper scissors game\n";
        }
    }

    // If computer equals the losing conditions you lose
    if (computer == conditions[userChoice])
    {
        std::cout << "You won!\n";
    }
    else if (userChoice == conditions[computer])
    {
        std::cout << "You lost\n";
    }
    else
    {
        std::cout << "It's a draw\n";
    }

    // This allows the user to see the output of the program and when they want to exit they can press any key to do so
    wait();
    return 0;
}