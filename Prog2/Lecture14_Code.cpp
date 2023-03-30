/*Lecture 14: Friend Functions
Code taken from: "Problem-Solving with C++", by W. Savitch
Instructor: Sareh Taebi, PhD
Date: 03/023/2023
*/

#include <iostream>

using namespace std;

//Purpose of this class: store a date (whether it's a birthday or an event)
class DayOfYear
{
    public:
        const int DaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //How many days are in each month
        DayOfYear();    //initializes day and month to 01/01
        DayOfYear(int the_month, int the_day);
        void input( );
        void output( );
        void set_date(int new_month, int new_day);  //setter function or mutator function
        //Precondition: new_month and new_day form a possible date.
        //Postcondition: The date is reset according to the arguments.
        int get_month( );   //getter function or accessor function
        //Returns the month, 1 for January, 2 for February, etc.
        int get_day( );
        //Returns the day of the month.
        friend bool equal(DayOfYear date1,DayOfYear date2);
        //checks for equality of two dates
    private:
        void check_date( );
        int month;
        int day;
};


DayOfYear::DayOfYear()
{
    month = 1;
    day = 1;
}

DayOfYear::DayOfYear(int the_month, int the_day)
{
    month = the_month;
    day = the_day;
}

void DayOfYear::input( )
{
    cout << "Enter the month as a number: ";
    cin >> month;
    cout << "Enter the day of the month: ";
    cin >> day;
    check_date( );
}


void DayOfYear::output( )
{
    cout << "month = " << month << ", day = " << day << endl;
}


void DayOfYear::set_date(int new_month, int new_day)
{
    month = new_month;
    day = new_day;
    check_date();
}

void DayOfYear::check_date( )
{
if ((month < 1) || (month > 12) || (day < 1) || (day > 31))
{   //input();
cout << "Illegal date. Aborting program.\n";
exit(1);
}
}

int DayOfYear::get_month( )
{
    return month;
}

int DayOfYear::get_day( )
{
    return day;
}

bool equal(DayOfYear date1,DayOfYear date2)
{
    return (date1.day == date2.day && date1.month == date2.month);
}
