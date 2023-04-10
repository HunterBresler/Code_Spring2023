//*Implementation for rationals class
#include <iostream>
#include "rationals.h"


using namespace std;


//*Constructors
rationals::rationals()
{
    numerator = 0;
    denominator = 1;
}


rationals::rationals(int numerator)
{
    numerator = numerator;
    denominator = 1;
}


rationals::rationals(int numerator, int denominator)
{
    numerator = numerator;
    denominator = denominator;
}



//*Friend Functions
rationals operator +(const rationals &numerator, const rationals &denominator)
{
    rationals result;
    result.numerator = 
    return result;
}


rationals operator -(const rationals &numerator, const rationals &denominator)
{
    rationals result(numerator.numerator - denominator.numerator, numerator.denominator - denominator.denominator);
    return result;
}


rationals operator -(const rationals &negate)
{
    rationals result(-negate.numerator, -negate.denominator);
    return result;
}


rationals operator *(const rationals &pair, int scalar)
{
    rationals result(pair.numerator * scalar, pair.denominator * scalar);
    return result;
}


istream& operator >>(istream &ins, rationals &pair)
{
    ins >> pair.numerator >> pair.denominator;
    return ins;
}


ostream& operator <<(ostream &outs, const rationals &pair)
{
    outs << "(" << pair.numerator << "," << pair.denominator << ")";
    return outs;
}

