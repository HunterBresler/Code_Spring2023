//*Implementation for rationals class
#include <iostream>
#include "rationals.h"


using namespace std;


//*Constructors
Pairs::Pairs()
{
    f = 0;
    s = 0;
}


Pairs::Pairs(int first)
{
    f = first;
    s = 0;
}


Pairs::Pairs(int first, int second)
{
    f = first;
    s = second;
}



//*Friend Functions
Pairs operator +(const Pairs &first, const Pairs &second)
{
    Pairs result(first.f + second.f, first.s + second.s);
    return result;
}


Pairs operator -(const Pairs &first, const Pairs &second)
{
    Pairs result(first.f - second.f, first.s - second.s);
    return result;
}


Pairs operator -(const Pairs &negate)
{
    Pairs result(-negate.f, -negate.s);
    return result;
}


Pairs operator *(const Pairs &pair, int scalar)
{
    Pairs result(pair.f * scalar, pair.s * scalar);
    return result;
}


istream& operator >>(istream &ins, Pairs &pair)
{
    ins >> pair.f >> pair.s;
    return ins;
}


ostream& operator <<(ostream &outs, const Pairs &pair)
{
    outs << "(" << pair.f << "," << pair.s << ")";
    return outs;
}

