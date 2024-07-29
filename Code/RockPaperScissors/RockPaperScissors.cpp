#include <iostream> // Simple input and output functions
#include <string> // Allows for string usage
#include <ctime> // Allows for time() usage and more
#include <map> // Allows for the usage of maps (dictionaries)
// Not using namespace std just in case I need to use other libraries and to not conflict with them 

// Function to clean the users input to make it much easier to compare
std::string stringToLower(std::string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Main function and game
int main()
{   
    // Creates a map (dictionary) to see what lose condition will be paried up with the win condition, e.g. rock beats scissors
    std::map<std::string, std::string> conditions = {{"paper", "rock"},{"scissors", "paper"},{"rock", "scissors"}};

    // Random number gen for the computer
    // Uses ctime for a random seed time() gives the current timestamp which will be different every time you run this program
    std::srand(std::time(nullptr));
    
    // This makes a random number from 0 - 2. This is because rand() % 3 = 0 - 2
    int randomNum = rand() % 3;

    std::string computer;
    // Switch for choosing the computers hand. This is better than if statements because it is more manageable
    switch (randomNum)
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
    }

    std::string userChoice;

    // Repeats the program until a correct input is written. This makes it so wrong inputs are not passed through which would create errors
    while (userChoice != "rock" || userChoice != "paper" || userChoice != "scissors")
    {
        // Asks the user for rock paper or scissors
        std::cout << "Rock, Paper or Scissors?\n";
        std::cin >> userChoice;
        
        userChoice = stringToLower(userChoice);
        system("cls");

        // Made this area of code more dynamic so it only needs one if statement
        if (userChoice == "rock" || userChoice == "paper" || userChoice == "scissors")
        {
            std::cout << "You chose " << userChoice << "\n" << "The computer chose " << computer << "\n";
            break;
        }
        // This else statement will loop back to the begining as there is no break and the while conditions will not be met
        else
        {
            std::cout << "That input is not in the rock paper scissors game\n";
        }
    }

    // If computer equals the losing conditons you lose
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
    system("pause");
    return 0;
}