#include <iostream> // Allows for simple input and output functions
#include <fstream>  // Allows for simple file controls
#include <filesystem>   // Allows for more advanced file controls
#include <string>   // Allows the use of strings
#include <map>  // Allows the use of maps (dictionaries)
#include <vector>   // Allows the use of vectors (can be dynamically edited unlike arrays)
#include <algorithm>    // Allows the sorting and such of items
#include <windows.h> // For sleep function windows only :) it was the easy way to do it
#include <mutex> // Mutex for thread safety
// Not including using namespace std to avoid conflicts with other libraries if I ever use them

// This is here for thread safety (From what I have understood it will lock so if another thread wants to "talk" it cannot, thus keeping it safe)
std::mutex mtx;

// This is so I can change the save location easier
std::string highScoreFile = "HighScore.txt";

// Money you start with
int money = 100;

// Map of prices for items you can buy
std::map<std::string, int> prices = {{"car", 50}, {"house", 100}, {"boat", 150}, {"plane", 200}, {"spaceship", 250}};

// Array of items you own
std::vector<std::string> items;

//Function to convert a string to lowercase - it loops through the given string and converts each character to lowercase
std::string convertStringToLower(std::string str)
{
    for (auto &c : str)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

// Function to clear the console as safe as I can
void clearConsole()
{
    std::lock_guard lock(mtx); // Locks the mutex
    system("cls");  // NOLINT(concurrency-mt-unsafe) This is because I am using mutex to be thread safe :D
}

// Function to make the program wait until the user presses the enter key
void wait()
{
    std::cout << "Press the 'Enter' key to continue... ";
    std::cin.get();
}

// Function to buy an item
void buyItem() {

    //////////////////////////////////// I have no idea how this works :/ ////////////////////////////////////

    // Lambda function to sort the vector of pairs by the second element of the pair

    // Copy items to a vector of pairs
    std::vector<std::pair<std::string, int>> itemsToBuy(prices.begin(), prices.end());

    // Sort the vector by price (second element of the pair)
    std::sort(itemsToBuy.begin(), itemsToBuy.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second < b.second;
    });

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Asks the user what they want to do with their money
    std::cout << "You have £" << money << " on you. Here are some options to do with it:\n";
    for (auto &item : itemsToBuy)
    {
        std::cout << item.first << " for £" << item.second << "\n";
    }
    
    // Gets the user's response
    std::string response;
    getline(std::cin, response);

    // Converts the user's response to lowercase here, so I don't have to do it every time I check the response
    response = convertStringToLower(response);

    // Checks if the response is in prices. It compares the result to an invalid end of prices as prices.find() is a bool
    if (prices.find(response) == prices.end())
    {
        clearConsole();
        std::cout << "That is not a valid item to buy\n";
        wait();
        clearConsole();
        buyItem();
    }
    else if (money < prices[response])
    {
        clearConsole();
        std::cout << "You do not have enough money to buy that item\n";
        wait();
        clearConsole();
    }
    else
    {
        // Money is subtracted from the user's wallet by setting the money variable
        money -= prices[response];
        clearConsole();
        std::cout << "You have bought a " << response << " for £" << prices[response] << ". You now have £" << money << " left in your wallet\n";
        // Adds the item to the user's inventory (using a vector because an array is not dynamic and a vector is much easier :D)
        items.push_back(response);
        // Loops this section until the user gives a valid response
        while (response != "no"){
            std::cout << "Do you want to buy something else? Yes or No\n";
            getline(std::cin, response);

            //Converts the response to lowercase
            response = convertStringToLower(response);

            if (response == "yes")
            {   
                clearConsole();
                buyItem();
                break;
            }
            else if (response == "no")
            {
                clearConsole();
                std::cout << "You have finished buying items\n";
                wait();
                clearConsole();
            }
            else
            {
                clearConsole();
                std::cout << "That is not a valid response\n";
                wait();
                clearConsole();
            }
        }
    }
}

// Function to update the money you have basically an idle game.
void updateMoney(){
    //This updates every second to see which item will add money.
    std::cout << "You will make money every 5 seconds, the money varies on what item you buy\n";
    std::cout << "You have £" << money << " in your wallet (Exit to buy more items using the 'ESC' key.)\n";
    int currentTime = 0;
    while (true)
    {
        // A map for the items and how much they pay each 5 seconds
        std::map<std::string, int> itemsMap = {{"car", 5},{"house", 15},{"boat", 25},{"plane", 35},{"spaceship", 45}};

        // This for loop will loop through the items you own. When the time is divisible by 5 and not 0 (so each 5 seconds) it will add an amount that the item generates to your wallet
        for (auto &item : items)
        {
            if ((currentTime % 5) == 0 && currentTime != 0 && std::find(items.begin(), items.end(), item) != items.end())
            {
                // Gets the matched money per 5 seconds
                money += itemsMap[item];
                std::cout << "You have gained £" << itemsMap[item] << " from the " << item << " you now have £" << money << " in your wallet\n";
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE)) {
            std::cout << "Exiting\n";
            Sleep(500); // Add a small delay to prevent immediate re-trigger
            clearConsole();
            break;
        }
        Sleep(1000); // Sleeps for 1 second (1000 milliseconds)

        currentTime++;
    }
}

void highScore()
{
    // Uses filesystem to see if a score exists is, so it will show the user
    if (std::filesystem::exists(highScoreFile))
    {
        // Gets the score from the file, and then shows it to the user. If there is no score it will tell the user the high score does not exist
        std::ifstream readHighScore(highScoreFile);
        std::string score;
        getline(readHighScore, score);
        std::cout << "Your high score is £" << score << "\n";
        readHighScore.close();
    }
    else
    {
        std::cout << "High score does not exist\n";
    }
    wait();
    clearConsole();
}

// Main function to run the shop after any of the functions end
int main()
{
    // Some stupid stuff to get £ to show up, if there is a better way I don't know it
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int responseInt = 0;
    // Loops the shop until the user gives a valid response
    while (responseInt != 4)
    {
        // Prints the shop menu
        std::cout << "Welcome to the shop\n1. Buy an item\n2. Make Money\n3. High score\n4. Exit\n";
        std::string response;
        getline(std::cin, response);
        responseInt = std::stoi(response);
        switch (responseInt)
        {
            case 1:
                // Calls the buyItem function to send the user to buy an item
                clearConsole();
                buyItem();
                break;
            case 2:
                // Calls the updateMoney function to send the user to make money
                clearConsole();
                updateMoney();
                break;
            case 3:
                // Calls the high score function to show the current high score
                clearConsole();
                highScore();
                break;
            case 4:
                // Exits the program
                std::cout << "Exiting\n";
                clearConsole();
                break;
            default:
                // If the user gives an invalid response it will be none of the cases and be the default, it will then tell them that it is invalid and loop the shop again
                std::cout << "That is not a valid response\n";
        }
    }
    // Prints a thank-you message when the user exits the shop
    std::cout << "Thank you for shopping\n";
    // Checks if the user has bought any items
    if (items.empty())
    {
        std::cout << "You have not bought any items\n";
    }
    else
    {
        // Loops through the items the user has bought and prints them
        std::cout << "You have bought the following item(s):\n";
        for (auto item = items.begin(); item != items.end(); ++item)
        {
            // This checks if the for loop is at the correct index, items.size() counts the numbers starting at 1, so I - 1, so it is inline with the index
            if (item != items.end() - 1)
            {
                std::cout << *item << ", ";
            }
            else
            {
                std::cout << *item << "\n";
            }
        }
    }

    // Checks if the file exists
    if (std::filesystem::exists(highScoreFile))
    {
        // Opens the file and reads it. Converts the string into an int, so I can use operators on the score
        std::ifstream readHighScore(highScoreFile);
        std::string score;
        getline(readHighScore, score);
        int scoreNum = std::stoi(score);

        if (scoreNum > money)
        {
            std::cout << "Your high score for money was £" << scoreNum << " you got £" << money << " try again next time!\n";
        }
        // Remember "=" != "==" ffs
        else if (scoreNum == money)
        {
            std::cout << "Your high score for money was £" << money << " This is the same as what you gained this round. Try again next time!\n";
        }
        else
        {
            std::cout << "Your high score for money was £" << money << " This is more than what was saved! Well done!\n";
            std::ofstream newHighScore(highScoreFile);
            newHighScore << money;
            newHighScore.close();
        }
        
        readHighScore.close();
    }
    else
    {
        std::cout << "Your high score for money was £" << money << " This is more than what was saved! Well done!\n";
        std::ofstream newHighScore(highScoreFile);
        newHighScore << money;
        newHighScore.close();
    }

    // This will pause the program and display press the enter key to continue...
    wait();
    return 0;
}