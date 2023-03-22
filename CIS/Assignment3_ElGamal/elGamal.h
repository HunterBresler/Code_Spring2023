//*Header file for ELGAMAL class
#ifndef ELGAMAL_H
#define ELGAMAL_H

using namespace std;

//Contains all functions and variables to encrypt AND decrypt elgamal
//IO from file
//uses vector<char> for binary representation
class ELGAMAL
{

    private:
        //vector<char> prime;
        //vector<char> generator;
        //vector<char> generator_pow_private_key;
        //vector<char> private_key;
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

        //*Calc Functions
        void MakeEqualSize(vector<char> &first, vector<char> &second);
        vector<char> ModExpo(vector<char> base, vector<char> modulo, vector<char> exponent);
        vector<char> BinaryAdd(vector<char> add1, vector<char> add2);
        vector<char> BinaryMultiply(vector<char> multi1, vector<char> multi2);

};

#endif