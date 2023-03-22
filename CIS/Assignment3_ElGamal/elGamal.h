//*Header file for ELGAMAL class
#ifndef ELGAMAL_H
#define ELGAMAL_H

using namespace std;

//Contains all functions and variables to encrypt AND decrypt elgamal
//IO from file
//uses string for binary representation
class ELGAMAL
{

    private:
        //string prime;
        //string generator;
        //string generator_pow_private_key;
        //string private_key;
        //ostream& send;
        //istream& receive;


    public:
        //*Constructors
        ELGAMAL();

        //* Getter/Setter Functions
        void getPublicKey_fromFileStream();
        void setPrime();
        void setGenerator();
        void setGen_PowA();

        //*Binary Calc Functions
        void MakeEqualSize(string &first, string &second);
        string MakeShiftedString(string shiftStr, int shiftCount);
        string ModExpo(string base, string modulo, string exponent);
        string Add(string add1, string add2);
        string Multiply(string X, string Y);

};

#endif