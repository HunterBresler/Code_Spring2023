//*Implementation for rationals class
#include <iostream>
#include "rationals.h"


using namespace std;


//*Constructors
rationals::rationals()
{
    numerator = 0;
    denominator = 0;
}


rationals::rationals(int first)
{
    numerator = first;
    denominator = 0;
}


rationals::rationals(int first, int second)
{
    numerator = first;
    denominator = second;
}



//*Friend Functions
rationals operator +(const rationals &first, const rationals &second)
{
    rationals result(first.numerator + second.numerator, first.denominator + second.denominator);
    return result;
}


rationals operator -(const rationals &first, const rationals &second)
{
    rationals result(first.numerator - second.numerator, first.denominator - second.denominator);
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

