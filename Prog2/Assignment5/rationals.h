//*Header for rationals class
#ifndef ELGAMAL_H
#define ELGAMAL_H


using namespace std;


class rationals
{
    public:

        //*Constructors
        rationals();
        rationals(int first);
        rationals(int first, int second);

        //*Friend Functions
        friend rationals operator +(const rationals &first, const rationals &second);
        //add rationals according to the rule (a, b) + (c, d) = (a + c, b + d)
        friend rationals operator -(const rationals &first, const rationals &second);
        //subtract rationals according to the rule (a, b) - (c, d) = (a - c, b - d)
        friend rationals operator -(const rationals &negate);
        //negates rationals according to the rule a = -a
        friend rationals operator *(const rationals &pair, int scalar);
        //multiplies a pair by a scalar according to the rule (a, b) * c = (a * c, b * d)
        friend istream& operator >>(istream &ins, rationals &pair);
        //inputs a rationals object using >>
        friend ostream& operator <<(ostream &outs, const rationals &pair);
        //Outputs a rationals object using <<

    private:
        int numerator;
        int denominator;
};

#endif