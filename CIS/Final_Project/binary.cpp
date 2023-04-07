//*binary Implementation
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "binary.h"

//*Constructors
binary::binary()
{
    number = "0";
}

binary::binary(string num)
{
    number = num;
}

binary::binary(char num)
{
    number = num;
}

//* Getter/Setter Functions
string binary::get_Number()
{
    return number;
}

void binary::set_Number(string newNum)
{
    number = newNum;
}


//*Binary Overload Operations
string operator+(const binary& num1, const binary& num2)
{
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    string sum = "";
    int carry = 0; //Carry for bit addition

    while (i >= 0 || j >= 0 || carry == 1)
    {
        carry += ((i >= 0) ? num1.number[i] - '0': 0);
        carry += ((j >= 0) ? num2.number[j] - '0': 0);
        
        sum = char(carry%2 + '0') + sum;

        carry /= 2;

        //Decrement i and j
        i--;
        j--;
    }

    return sum;
}

string operator-(const binary& minuend, const binary& subtrahend)
{
    binary result;

    //Short circuit if minuend  and subtrahend are equal
    if (minuend == subtrahend)
    {
        return "0";
    }

    //Make sure minuend is greater than subtrahend
    if (minuend > subtrahend)
    {
        //cout << "\nError: ELGAMAL::minuend must be larger than subtrahend";
        //return "0";
    }

    //Make sure they are equal in size
    result = subtrahend.PadLeft(minuend.size() - subtrahend.size()); 


    //Replace subtrahend with it's 1s complement
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = ((result[i] == '1') ? '0': '1');
    }

    //Add minuend and the 1s complement for subtraction
    result += minuend;

    //Check for carry and add it back into sum
    if (result.size() > minuend.size())
    {
        result.erase(result.begin()); //Remove the first element
        result += '1';
    }

    //Remove excess 0s
    while (result[0] == '0')
    {
        result.erase(result.begin()); //Remove the first element
    }

    return result.number;
}

string operator*(const binary& num1, const binary& num2)
{
    binary result, shifted;
    int len = num2.size();

    //Add 
    for (int i = len-1; i >= 0; i--)
    {
        if (num2[i] == '1')
        {
            //Uses repeated addition to multiply
            shifted = num1.PadRight(len - (i+1));
            result += shifted;
        }
        else
        {
            continue;
        }
    }

    return result.number;
}

string operator/(const binary& divadend, const binary& divisor)
{

}

string operator%(const binary& divadend, const binary& divisor)
{

}

bool operator>(const binary& num1, const binary& num2)
{

}

bool operator<(const binary& num1, const binary& num2)
{

}

bool operator>=(const binary& num1, const binary& num2)
{
    return num1 > num2 || num1 == num2;
}

bool operator<=(const binary& num1, const binary& num2)
{
    return num1 < num2 || num1 == num2;
}

bool operator==(const binary& num1, const binary& num2)
{
    return num1.number == num2.number;
}

binary& binary::operator=(const binary& num2)
{
    number = num2.number;
    return *this;
}

binary& binary::operator=(const string& num2)
{
    number = num2;
    return *this;
}

binary& binary::operator+=(const binary& num2)
{
    number = number + num2;
    return *this;
}

binary& binary::operator-=(const binary& num2)
{
    number = number - num2.number;
    return *this;
}

binary& binary::operator*=(const binary& num2)
{
    number = number * num2;
    return *this;
}

binary& binary::operator/=(const binary& num2)
{
    number = number / num2;
    return *this;
}

binary& binary::operator%=(const binary& num2)
{
    number = number % num2.number;
    return *this;
}


char binary::operator[](const int& index) const
{
    if (index > number.size() || index < 0)
    {
        cout << "\nError:Index Out of Bounds";
        exit(0);
    }
    return number[index];
}

char& binary::operator[](const int& index)
{
    if (index > number.size() || index < 0)
    {
        cout << "\nError:Index Out of Bounds";
        exit(0);
    }
    return number[index];
}


istream& operator >>(istream &ins, binary &num)
{
    ins >> num.number;
    return ins;
}

ostream& operator <<(ostream &outs, const binary &num)
{
    outs << num.number;
    return outs;
}


//*Binary Calc Functions
string binary::PadRight(int PadCount) const
{
    string shifted = number;

    for (int i = 0; i < PadCount; i++)
    {
        shifted += "0";
    }
    return shifted;
}

string binary::PadLeft(int PadCount) const
{
    string shifted = number;

    for (int i = 0; i < PadCount; i++)
    {
        shifted = "0" + shifted;
    }
    return shifted;
}

binary ModExpo(const binary& base, const binary& exponent, const binary& modulo);
binary Xor(const binary& num1, const binary& num2);
binary getRandom(const binary& min, const binary& max);


//*String overload functions
int binary::size() const
{
    return number.size();
}

void binary::erase(const string::iterator& it)
{
    number.erase(it);
}

string::iterator binary::begin()
{
    return number.begin();
}

