#include <iostream>
#include "rationals.h"
#include "rationals.cpp"


using namespace std;


//*MAIN: tests rationals class
int main(){

    //Test class
    rationals X(2, 3), Y(2);

    //Test >> << operators
    cout << "\nEnter an oredered pair (x,y) in the form (x y): ";
    cin >> Y;
    cout << "The ordered pair is " << Y << endl;

    //Test + and - with Pair types
    cout << "\nX - Y = " << X - Y;
    cout << "\nX + Y = " << X + Y;
    cout << endl;

    //Test + and - with int types
    cout << "\nX + 2 = " << X + 2;
    cout << "\nX - 2 = " << X - 2;
    cout << endl;

    //Test scalar multiplications
    cout << "\nX * 2 = " << X * 2;
    cout << endl;

    return 0;

}