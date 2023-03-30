/*
    Author: Hunter Bresler
    Date: 2/16/2023
    Lab1: Measurements calculator
*/

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


//function definitions
void getInput(double *height, double *weight, int *age);
void output(double hatSize, double jacketSize, double waistSize, double futureHatSize, double futureJacketSize, double futureWaistSize);
double getHatSize(double height, double weight, double *futureHatSize);
double getJacketSize(double height, double weight, int age, double *futureJacketSize);
double getWaistSize(double height, double weight, int age, double *futureWaistSize);



//*Gets input
void getInput(double *height, double *weight, int *age)
{
    cout << "\n\nEnter your height (in inches): ";
    cin >> *height;

    cout << "Enter your weight (in pounds): ";
    cin >> *weight;

    cout << "Enter your age: ";
    cin >> *age;

    //Make space
    cout << endl << endl;

}



//*Displays output
void output(double hatSize, double jacketSize, double waistSize, double futureHatSize, double futureJacketSize, double futureWaistSize)
{

    //output to terminal
    cout << "Your hat size is " << hatSize
         << "\nYour jacket size is " << jacketSize
         << "\nYour waist size is " << waistSize 
         << "\n\nYour hat size in 10 years will be " << futureHatSize
         << "\nYour jacket in 10 years will be " << futureJacketSize
         << "\nYour waist size in 10 years will be " << futureWaistSize
         << "\n\nAll sizes are in inches and rounded to the nearest hundreth" << endl << endl;



    //output to file
    ofstream sizeFile;
    sizeFile.open("sizes.txt");


    //Format file
    sizeFile << fixed << showpoint << setprecision(2);

    sizeFile << "Your hat size is " << hatSize
             << "\nYour jacket size is " << jacketSize
             << "\nYour waist size is " << waistSize
             << "\n\nYour hat size in 10 years will be " << futureHatSize
             << "\nYour jacket in 10 years will be " << futureJacketSize
             << "\nYour waist size in 10 years will be " << futureWaistSize 
             << "\n\nAll sizes are in inches and rounded to the nearest hundreth" << endl << endl;


    sizeFile.close();

    

}



//*Calculates hat size
double getHatSize(double height, double weight, double *futureHatSize)
{
    //Constant for calculations
    const double hatMATH = 2.9;


    //Calculate size for 10 years in the future
    *futureHatSize = (weight/height)*hatMATH;

    return (weight/height)*hatMATH;
}



//*Calculates jacket size (Chest in inches)
double getJacketSize(double height, double weight, int age, double *futureJacketSize)
{
    //Constants for calculations
    const double jacketMATH = 288, ageINCREMENT = .125;
    const int ageMATH = 10, ageMIN = 3, futureMATH = 10;


    //Calculate size for 10 years in the future
    *futureJacketSize = (height*weight)/jacketMATH + ageINCREMENT*((age + futureMATH)/ageMATH - ageMIN);
    
    //Math for increment
    if (age/ageMATH > ageMIN)
    {
        return (height*weight)/jacketMATH + ageINCREMENT*(age/ageMATH - ageMIN);
    }
    else
    {
        return (height*weight)/jacketMATH;
    }
}



//*Calculattes waist size (in inches)
double getWaistSize(double height, double weight, int age, double *futureWaistSize)
{
    //Constants for calculations
    const double waistMATH = 5.7, ageINCREMENT = .1;
    const int ageMATH = 2, ageMIN = 14, futureMATH = 10;


    //Calculate size for 10 years in the future
    *futureWaistSize = weight/waistMATH + ageINCREMENT*((age + futureMATH)/ageMATH - ageMIN);


    //Math for increment
    if (age/ageMATH > ageMIN)
    {
        return weight/waistMATH + ageINCREMENT*(age/ageMATH - ageMIN);
    }
    else
    {
        return weight/waistMATH;
    }
}



//*MAIN
int main(){

    //variable declaration
    double height, weight, hatSize, jacketSize, waistSize, futureHatSize, futureJacketSize, futureWaistSize;
    int age, quit;

    //Format cout
    cout << fixed << showpoint << setprecision(2);



    //Loop until user quits
    do
    {
        //reset quit value
        quit = 0;


        //Call functions
        getInput(&height, &weight, &age);
        hatSize = getHatSize(height, weight, &futureHatSize);
        jacketSize = getJacketSize(height, weight, age, &futureJacketSize);
        waistSize = getWaistSize(height, weight, age, &futureWaistSize);
        output(hatSize, jacketSize, waistSize, futureHatSize, futureJacketSize, futureWaistSize);
        


        //Ask if the user wants to continue
        cout << "\n\n\nIf you'd like to end the program, Enter '0'.\n"
                "If you'd like to run the program again, Enter '1' : ";
        cin >> quit;

    } 
    while (quit);


    //Goodbye
    cout << "\nThank you for using the amortization program!\n\n";
    return 0;
}