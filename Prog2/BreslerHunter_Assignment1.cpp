/*
 * Author: Hunter Bresler
 * Date: 1/21/2022
 * Assignment1: Coin dispenser/Coin counter
*/

#include <iostream>
#include <vector>

using namespace std;

//Declare functions
void CashToCoins(vector<int> coinVec, double cashInput);
void CoinsToCash(vector<int> coinVec);
void menu(vector<int> coinVec);


//Menu for program 
void menu(vector<int> coinVect)
{

    int userSelection;
    double cashInput;

    //Loop the menu until the user quits
    while(true)
    {
        //Menu prompt
        cout << "\n\nChoose an option by typing an integer (0, 1, or 2)\n\n"
                "Change cash into coins: Select 1\n"
                "Change your coins into cash: Select 2\n"
                "End the program: Select 0\n";
        cin >> userSelection;

        //Check input
        if (userSelection ==  1)
        {
            cout << "\nHow much would you like to convert into coins?\n";
            cin >> cashInput;

            CashToCoins(coinVect, cashInput);
        }
        else if(userSelection == 2)
        {
            CoinsToCash(coinVect);
        }
        else
        {
            break;
        }
        
    }
    
    cout << "\nThank you for using this program";

}



//
void CashToCoins(vector<int> coinVec, double cashInput)
{

    //Declare variables
    //coinCount counts # of quarters, dimes, etc.
    vector<int> coinCount = {};
    int cashInt = cashInput * 100;

    
    //Calculate change to give
    for (int i = 0; i < coinVec.size(); i++)
    {
        coinCount.push_back(cashInt / coinVec[i]);
        cashInt %= coinVec[i];
    }
    

    // Print Change
    cout << "\nThe change for $" << cashInput << " is:\n"
         << coinCount[0] << " Quarters\n"
         << coinCount[1] << " Dimes\n"
         << coinCount[2] << " Nickels\n"
         << coinCount[3] << " Pennies\n";

}



void CoinsToCash(vector<int> coinVec)
{
    //Declare variables
    vector<int> coinCount(4);
    double cashValue = 0;

    //Get user input
    cout << "\nEnter the number of quarters: \n";
    cin >> coinCount[0];
    cout << "\nEnter the number of dimes: \n";
    cin >> coinCount[1];
    cout << "\nEnter the number of nickels: \n";
    cin >> coinCount[2];
    cout << "\nEnter the number of pennies: \n";
    cin >> coinCount[3];

    //Calculate the cash value
    for (int i = 0; i < coinVec.size(); i++)
    {
        cashValue += coinCount[i] * coinVec[i];
    }

    cashValue /= 100;

    //Print cash value
    cout << "\nYou have $" << cashValue << " in coins";
}



int main(){

    //List for coin values
    vector<int> coinVec = {25, 10, 5, 1};

    menu(coinVec);

    return 0;
}