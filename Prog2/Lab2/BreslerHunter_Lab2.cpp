/*
    Author: Hunter Bresler
    Date: 3/16/2023
    Lab2: Money class object
*/

#include <iostream>
#include <string>


using namespace std;


//Keeps track of money as if everything was pennies
class Money
{

    private:
        int money;

    public:
        //*Constructors
        Money(long dollars, int cents);
        Money(long dollars);
        Money();

        //*Get/Set Functions
        int getMoney();
        void setMoney(int new_money);

        //*Calculations
        Money add(Money add);
        Money subtract(Money subtract);
        bool equal(Money compare);

        //*IO Functions
        void output();
        void output(ostream& out);
        void input(istream& ins);

};


//*MAIN
int main() {


    //*Test Money Class Constructor
    cout << "\nTesting negative constructor input\n";
    Money neg(-10, 35), neg2 (-10, -35);

    neg.output();
    neg2.output();


    //*Test Money Class functions
    cout << "\nTesting Money class functions (excluding IO stream)\n";
    Money expenses(100.00), revenue(150, 23), profit, result;

    //Test subtract
    profit = revenue.subtract(expenses);
    profit.output();

    //Test add
    result = result.add(profit);

    //Test equal
    if (result.equal(profit))
    {
        cout << "\nAdd worked: " << result.getMoney() << endl;
    }
    else
    {
        cout << "\nAdd failed" << result.getMoney() << endl;
    }

    //Test set
    result.setMoney(100);
    cout << "\nResult should be 100.";
    result.output();

    //Test get
    int cents = result.getMoney();
    cout << "\nCents should be 100. Cents: " << cents;
    

    //*Test IO streams
    //Test output stream
    cout << "\n\nOutput result to screen:";
    profit.output(cout);

    //Test input stream
    cout << "\n\nInput cash amount in $00.00/-$00.00 form: ";
    result.input(cin);
    result.output();

    return 0;

}

/*
    !This is the list of functions in the Money Class 
    !The functions will be folded below
*/
//*Constructors
Money::Money(long dollars, int cents)
{
    money = dollars*100;

    //Makes sure if amount is negative, that cents is added properly
    if (money < 0)
    {
        if (cents < 0)
        {
            money += cents;
        }
        else
        {
            money -= cents;
        }
    }
    else
    {
        money += cents;
    }
}

Money::Money(long dollars)
{
    money = dollars*100;
}

Money::Money()
{
    money = 0;
}


//*Get/Set Functions
int Money::getMoney()
{
    return money;
}

void Money::setMoney(int new_money)
{
    money = new_money;
}


//*Calculations
Money Money::add(Money add) //Add 2 Money objects: return Money object
{
    add.money += money;
    return add;
}

Money Money::subtract(Money sub) //Subtract 2 Money objects: return Money object
{
    sub.money = money - sub.money;
    return sub;
}

bool Money::equal(Money compare) //Compare 2 Money objects: return bool
{
    return money == compare.money;
}


//*IO Functions
void Money::output() //cout
{
    cout << "\nThe Money object has a value of " << money << " cents.\n";
}

void Money::output(ostream& out) //parameter ostream
{
    out << "\nThe Money object has a value of " << money << " cents.\n";
}

void Money::input(istream& ins) //parameter istream
{
    string input;
    ins >> input;

    //Get the money value of a string in $00.00 form
    money = stod(input.substr(input.find("$")+1))*100;

    //Check if input id negative
    if (input[0] == '-')
    {
        money *= -1;
    }
}
