/*
    Author: Hunter Bresler
    Date: 3/29/2023
    Assignment4: DateYear child class implementation
*/

#include <iostream>
#include "DayOfYear.cpp"


using namespace std;



class DateYear: public DayOfYear
{

    private:
        
        int year;

    public:

        //*Constructors
        DateYear();
        DateYear(int new_year, int new_month, int new_day);

        //*Getter/Setter Functions
        int getYear();
        void setYear(int new_year);

        //*IO Functions
        void inputDateFull();
        void outputDateFull();

        //*Class Functions
        int BDCountdown(DayOfYear& birthday); //Takes class type DayOfYear and returns how many days until that date
        //Precondition: the DateYear calling this function is today's date
        //Does not have leap year functionality

        //*Friend functions
        friend bool DateCompare(const DateYear& date1, const DateYear& date2); //Compares two years from class types DateYear

};



//*MAIN
int main(){

    //Test DateYear
    DateYear today(2023, 3, 29), compare;

    //Get today's date and display it
    //today.inputDateFull();
    cout << "\nToday's date is ";
    today.outputDateFull();
    
    //Get a date and compare it to today's date
    compare.inputDateFull();
    if (DateCompare(today, compare) && equal(today, compare))
    {
        cout << "\nThe two dates are the same.";
    }
    else
    {
        cout << "\nThe two dates are different.";
    }
    
    //Get a birthday
    DayOfYear birthday(6, 28);
    cout << "\n\nYour birthday is on ";
    birthday.output();

    //Calc how many days until that birthday
    int daysTillBD = today.BDCountdown(birthday);
    cout << "\nThere are " << daysTillBD << " days until your birthday!";


    return 0;
}



//*Constructors
DateYear::DateYear(): DayOfYear()
{
    year = 2023;
}


DateYear::DateYear(int new_year, int new_month, int new_day): DayOfYear(new_month, new_day)
{
    year = new_year;
}


//*Getter/Setter Functions
int DateYear::getYear()
{
    return year;
}


void DateYear::setYear(int new_year)
{
    year = new_year;
}


//*IO Functions
void DateYear::inputDateFull()
{
    cout << "\nEnter the year as a number: ";
    cin >> year;
    input(); //Calls input() from DayOfYear to input the day and month
}


void DateYear::outputDateFull()
{
    cout << "year = " << year << ", ";
    output(); //Calls output() from DayOfYear to output the day and month
}


//*Class Functions
bool DateCompare(const DateYear& date1, const DateYear& date2)
{
    return (date1.year == date2.year);
}


int DateYear::BDCountdown(DayOfYear& birthday)
{
    //Gets the amount of days till the day of the birthday
    int daysTillBirthday = birthday.get_day() - get_day(); 


    //Gets the amount of days till the month of the birthday
    //reset month to 1 if it goes out of bounds aka set to january
    //Subtract month by 1 to get the corresponding index
    for (int month = get_month(); month != birthday.get_month() || daysTillBirthday < 0; month = ((month < 12) ? month + 1: 1)) 
    {
        daysTillBirthday += DaysInMonth[month-1];
    }

    return daysTillBirthday;

}
