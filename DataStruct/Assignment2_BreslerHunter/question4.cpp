/*
    Author: Hunter Bresler
    Date: 2/23/2023
    question4: modular exponentiation
*/

#include <iostream>
#include <vector>

using namespace std;



//*Binary K conversion
void BinaryK(vector<int> &K, int k)
{
    //Declare variable
    int i = 0;

    //Loop to convert k to binary
    while (k > 0)
    {
        K.push_back(k%2);
        k = (k - K[i])/2;
        i++;
    }

}



//*Modular Exponentiation
int ModularExpo(int a, int n, vector<int> &K)
{

    //Any number mod 1 is 0
    if (n == 1)
    {
        return 0;
    }
    
    //Declare variable for return  value
    int b = 1;

    
    //Short circuit to prevent error with the next if statement
    if (K.size() == 0)
    {
        return b;
    }

    
    if (K[0] == 1)
    {
        b = a;
    }


    
    for (int i = 1; i < K.size(); i++)
    {

        a = (a*a) % n;

        if (K[i] == 1)
        {
            b = (a*b) % n;
        }

    }

    return b;
}



//*MAIN
int main(){

    //Declare variables
    //Where a^k mod n
    int a, k, n, solution;
    vector<int> K = {};

    //Get user inputs
    cout << "\nEnter the base: ";
    cin >> a;

    cout << "Enter the exponent: ";
    cin >> k;

    cout << "Enter the modulus: ";
    cin >> n;


    
    //Call Binary K
    BinaryK(K, k);
    
    //Call Modular Exponentiation
    solution = ModularExpo(a, n, K);


    //Print the modular exponentiation
    cout << "\n\n" << a << "^" << k << " mod " << n << " = " << solution;
    
    return 0;
}