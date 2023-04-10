//*Header for rationals class
#ifndef ELGAMAL_H
#define ELGAMAL_H


using namespace std;


class Pairs
{
    public:

        //*Constructors
        Pairs();
        Pairs(int first);
        Pairs(int first, int second);

        //*Friend Functions
        friend Pairs operator +(const Pairs &first, const Pairs &second);
        //add pairs according to the rule (a, b) + (c, d) = (a + c, b + d)
        friend Pairs operator -(const Pairs &first, const Pairs &second);
        //subtract pairs according to the rule (a, b) - (c, d) = (a - c, b - d)
        friend Pairs operator -(const Pairs &negate);
        //negates pairs according to the rule a = -a
        friend Pairs operator *(const Pairs &pair, int scalar);
        //multiplies a pair by a scalar according to the rule (a, b) * c = (a * c, b * d)
        friend istream& operator >>(istream &ins, Pairs &pair);
        //inputs a pairs object using >>
        friend ostream& operator <<(ostream &outs, const Pairs &pair);
        //Outputs a pairs object using <<

    private:
        int f;
        int s;
};

#endif