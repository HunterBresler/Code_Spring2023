//*Header for pairs class
#include <iostream>
#ifndef ELGAMAL_H
#define ELGAMAL_H


using namespace std;


class Pairs
{
    public:

        //*Constructors
        Pairs();
        Pairs(int first, int second);

        //*Friend Functions
        friend Pairs operator +(const &Pair first, const &Pair second);
        friend Pairs operator -(const &Pair first, const &Pair second);
        friend Pairs operator -(const &Pair negate);
        friend Pairs operator *(const &Pair pair, int scalar);
        friend istream& operator >>(istream &ins, Pairs &second);
        friend ostream& operator <<(ostream &outs, const Pairs &second);

    private:
        int f;
        int s;
};

#endif