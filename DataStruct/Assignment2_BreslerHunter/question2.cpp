/*
    Author: Hunter Bresler
    Date: 2/22/2023
    question2: Extended Euclidian Algorithm
*/

#include <iostream>

using namespace std;



//*Extended Euclidian Algorithm
void EEA(int a, int b, int* c1, int* c2)
{

    //Declare variables
    int q, s = 0, old_s = 1, t = 1, old_t = 0, r = b, old_r = a, temp;

    while (r!=0)
    {
        q = old_r/r;
        temp = old_r;
        old_r = r;
        r = temp - q*r;
        temp = old_s;
        old_s = s;
        s = temp - q*s;
        temp = old_t;
        old_t = t;
        t = temp - q*t;
    }

    cout << "\nGCD = " << old_r;

    *c1 = old_s;
    *c2 = old_t;
}



//*MAIN
int main(){

    //Declare variables
    int num1, num2, gcd, c1, c2;

    //Get user inputs
    cout << "\nEnter the first number: ";
    cin >> num1;

    cout << "Enter the second number: ";
    cin >> num2;

    
    //Call Extended Euclidian Algorithm
    EEA(num1, num2, &c1, &c2);


    //Print Bezout coefficients
    cout << "\n\nThe first coefficient is " << c1 << " and the second is " << c2;
    
    return 0;
}