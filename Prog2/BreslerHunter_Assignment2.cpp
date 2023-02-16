/*
    Author: Hunter Bresler
    Date: 2/15/2023
    Assignment2: Loan Calculator
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

//Function Definitions
double amortization(double P, double rate, int n);
void monthlyMath(double *balance , double *monthlyInterest, double *principalPayment, double r , double M);
void totalMath(double *totalPaid, double *totalInterest, double monthlyInterest, double M);
void getInput(double *P, double *rate, int *n);
void outputTable(double *PLoanBalance, double *totalPaid, double *totalInterest, double r, double M, int n);



//*Calculatles amortization
double amortization(double P, double r, int n)
{
    //declare variables for different parts of the amortization equation
    double num, den, power;

    //Calculations for amortization
    power = pow(1 + r, n);
    num = P*r*power;
    den = power - 1;
    
    return num/den;
}



//*Calculates the monthly interest, principal pay, and balance
void monthlyMath(double *balance , double *monthlyInterest, double *principalPayment, double r , double M)
{
    *monthlyInterest = (*balance)*r;
    *principalPayment = M - *monthlyInterest;

    //Make sure the balance isn't overpaid
    if (*balance - *principalPayment < 0)
    {
        *principalPayment = *balance;
        *balance = 0;
    }
    else
    {
        *balance -= *principalPayment;
    }
}



//*Keeps track of totals paid
void totalMath(double *totalPaid, double *totalInterest, double monthlyInterest, double M)
{
    *totalPaid += M;
    *totalInterest += monthlyInterest;
}



//*Get input for P, r, and n
void getInput(double *P, double *rate, int *n)
{

    cout << "\n\nEnter the principal loan amount: ";
    cin >> *P;

    //Divide by number of months in a year
    cout << "Enter the annual interest rate: ";
    cin >> *rate;
    *rate /= 12;

    cout << "Enter the number of months until the loan is paid off: ";
    cin >> *n;

    //Make space
    cout << endl << endl;

}



//*Make and Display output table and write it into a file
void outputTable(double *PLoanBalance, double *totalPaid, double *totalInterest, double r, double M, int n)
{

    //Declare variables for the table
    double oldBalance, monthlyInterest, principalPayment;


    //Trying out string streams
    //Formating string stream
    ostringstream sout;
    sout << fixed << showpoint << setprecision(2);



    //Table Heading
    sout << setw(20) << "Beginning Balance" << setw(15) << "Interest" 
              << setw(15) << "Principal" << setw(20) << "Ending Balance" << endl;
    
    //Loop to make the table in the file
    for (int i = 1; i <= n; i++)
    {
            //Keep track of balance before monthly payments
            oldBalance = *PLoanBalance;

            //Get monthly values and calculate total values
            monthlyMath(PLoanBalance, &monthlyInterest, &principalPayment, r, M);
            totalMath(totalPaid, totalInterest, monthlyInterest, M);

            //Table display
            sout << setw(5) << left << i << right << setw(15) << oldBalance << setw(15) <<  monthlyInterest
                      << setw(15) << principalPayment << setw(20) << *PLoanBalance << endl;

            
            //Add year# end in table
            if (i%12 == 0)
            {
                sout << setw(25) << " " << "-----Year #" << i/12 << " End-----" << endl;
            }
    }


        //Open file
        ofstream tableFile;
        tableFile.open("amortizationTable.txt");

        //Finish by streaming to cout and file
        tableFile << sout.str();
        cout << sout.str();
        sout.str(string());
        tableFile.close();
}



//* Main
int main(){

    //Declare variables
    double PLoanBalance, rRate, MPayment, totalPaid, totalInterest;
    int nMonths, quit;

    //Formatting cout
    cout << fixed << showpoint << setprecision(2);



    //Welcome statement
    cout << "\n\nWelcome to the amortization program!";

    //Loop until user quits
    do
    {
        //reset values
        quit = 0;
        totalPaid = 0;
        totalInterest = 0;


        getInput(&PLoanBalance, &rRate, &nMonths);

        //Get monthly payment
        MPayment = amortization(PLoanBalance, rRate, nMonths);



        //Output table will make an amortization table
        //It will also call the functions to do the math for the table
        outputTable(&PLoanBalance, &totalPaid, &totalInterest, rRate, MPayment, nMonths);



        //Print totals
        cout << "\n\nPayment Every Month: " << MPayment
             << "\n\nTotal of " << nMonths << " Payments: " << totalPaid
             << "\n\nTotal Interest: " << totalInterest;


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