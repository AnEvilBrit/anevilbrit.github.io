﻿#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <windows.h> // For sleep function windows only :) it was the easy way to do it
// Not including using namespace std to avoid conflicts with other libraries if I ever use them

// This is so I can change the save location easier
std::string highscorefile = "Highscore.txt";

// Money you start with
int money = 100;

// Map of prices for items you can buy
std::map<std::string, int> prices = {{"car", 50}, {"house", 100}, {"boat", 150}, {"plane", 200}, {"spaceship", 250}};

// Array of items you own
std::vector<std::string> items;

//Function to convert a string to lowercase - it loops through the given string and converts each character to lowercase
std::string convertStringToLower(std::string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Function to buy an item
void buyItem() {

    //////////////////////////////////// I have no idea how this works :/ ////////////////////////////////////
    
    // I have no idea what this does but it's needed for the sort function to work

    // Lambda function to sort the vector of pairs by the second element of the pair

    // Copy items to a vector of pairs
    std::vector<std::pair<std::string, int>> itemstobuy(prices.begin(), prices.end());

    // Sort the vector by price (second element of the pair)
    std::sort(itemstobuy.begin(), itemstobuy.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second < b.second;
    });

    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Asks the user what they want to do with their money
    std::cout << "You have £" << money << " on you. Here are some options to do with it:\n";
    for (auto &item : itemstobuy)
    {
        std::cout << item.first << " for £" << item.second << "\n";
    }
    
    // Gets the user's response
    std::string response;
    getline(std::cin, response);

    // Converts the user's response to lowercase here so I don't have to do it every time I check the response
    response = convertStringToLower(response);

    // Checks if the user's response is in the map of prices if not it will return 0
    if (prices[response] == 0)
    {
        std::cout << "That is not a valid item to buy\n";
        buyItem();
    }
    else if (money < prices[response])
    {
        std::cout << "You do not have enough money to buy that item\n";
    }
    else
    {
        // Money is subtracted from the user's wallet by settting the money variable
        money -= prices[response];
        std::cout << "You have bought a " << response << " for £" << prices[response] << ". you now have £" << money << " left in your wallet\n";
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
                buyItem();
                break;
            }
            else if (response == "no")
            {
                std::cout << "You have finished buying items\n";
            }
            else
            {
                std::cout << "That is not a valid response\n";
            }
        }
    }
}

// Function to update the money you have basicly an idle game.
void updateMoney(){
    //This updates every second to see which item will add money.
    std::cout << "You will make money every 5 seconds for a car, 15 seconds for a house, 25 seconds for a boat, 35 seconds for a plane and 45 seconds for a spaceship\n";
    std::cout << "You have £" << money << " in your wallet (Exit to buy more items using the 'ESC' key.)\n";
    int currentTime = 0;
    while (true)
    {
        // When the time is divisible by 5 and not 0 (so each 5 seconds) it will add £10 to your wallet
        // It also checks if the user has bought a car if so it will add £10 to your wallet each 5 seconds
        if ((currentTime % 5) == 0 && currentTime != 0 && std::find(items.begin(), items.end(), "car") != items.end())
        {
            money += 5;
            std::cout << "You have gained £5 from the car you now have £" << money << " in your wallet\n";
        }
        if ((currentTime % 15) == 0 && currentTime != 0 && std::find(items.begin(), items.end(), "house") != items.end())
        {
            money += 20;
            std::cout << "You have gained £20 from the house you now have £" << money << " in your wallet\n";
        }
        if ((currentTime % 25) == 0 && currentTime != 0 && std::find(items.begin(), items.end(), "boat") != items.end())
        {
            money += 35;
            std::cout << "You have gained £35 from the boat you now have £" << money << " in your wallet\n";
        }
        if ((currentTime % 35) == 0 && currentTime != 0 && std::find(items.begin(), items.end(), "plane") != items.end())
        {
            money += 50;
            std::cout << "You have gained £50 from the plane you now have £" << money << " in your wallet\n";
        }
        if ((currentTime % 45) == 0 && currentTime != 0 && std::find(items.begin(), items.end(), "spaceship") != items.end())
        {
            money += 65;
            std::cout << "You have gained £65 from the spaceship you now have £" << money << " in your wallet\n";
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            std::cout << "Exiting\n";
            Sleep(500); // Add a small delay to prevent immediate re-trigger
            break;
        }
        Sleep(1000); // Sleeps for 1 second (1000 milliseconds)

        currentTime++;
    }
}

void highscore()
{
    // Uses filesystem to see if a score exists is so it will show the user
    bool isFileThere = std::filesystem::exists(highscorefile);
    if (isFileThere)
    {
        // Gets the score from the file, and then shows it to the user. If there is no score it will tell the user the highscore does not exist
        std::ifstream ReadHighscore(highscorefile);
        std::string score;
        getline(ReadHighscore, score);
        std::cout << "Your highscore is £" << score << "\n";
        ReadHighscore.close();
    }
    else
    {
        std::cout << "Highscore does not exist\n";
    }
    system("pause");
}

// Main function to run the shop after any of the functions end
int main()
{
    std::string response;
    // Loops the shop until the user gives a valid response
    while (response != "4")
    {
        // Prints the options for the user
        std::cout << "Welcome to the shop\n" << "1. Buy an item\n" << "2. Make Money\n" << "3. Highscore\n" << "4. Exit\n";
        std::string response;
        getline(std::cin, response);
        int responseint = std::stoi(response);
        switch (responseint)
        {
            case 1:
                // Calls the buyItem function to send the user to buy an item
                buyItem();
                break;
            case 2:
                // Calls the updateMoney function to send the user to make money
                updateMoney();
                break;
            case 3:
                // Calls the highscore function to show the current highscore
                highscore();
                break;
            case 4:
                // Exits the program
                std::cout << "Exiting\n";
                break;
            default:
                // If the user gives an invalid response it will be none of the cases and be the default, it will then tell them that it is invalid and loop the shop again
                std::cout << "That is not a valid response\n";
        }

    }
    // Prints a thank you message when the user exits the shop
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
        for (auto &item : items)
        {
            std::cout << item << "\n";
        }
    }

    // Checks if the file exists
    bool isFileThere = std::filesystem::exists(highscorefile);
    if (isFileThere)
    {
        // Opens the file and reads it. Converts the string into an int so I can use operators on the score
        std::ifstream ReadHighscore(highscorefile);
        std::string score;
        getline(ReadHighscore, score);
        int scoreNum = std::stoi(score);

        if (scoreNum > money)
        {
            std::cout << "Your highscore for money was £" << scoreNum << " you got £" << money << " try again next time!\n";
        }
        else
        {
            std::cout << "Your highscore for money was £" << money << " This is more than what was saved! Well done!\n";
            std::ofstream NewHighscore(highscorefile);
            NewHighscore << money;
            NewHighscore.close();
        }

        ReadHighscore.close();
    }
    else
    {
        std::cout << "Your highscore for money was £" << money << " This is more than what was saved! Well done!\n";
        std::ofstream NewHighscore(highscorefile);
        NewHighscore << money;
        NewHighscore.close();
    }


    // This will pause the program and display a press any key to continue...
    system("pause");
    return 0;
}