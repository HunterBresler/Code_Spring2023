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
        string prime;
        string generator;
        string generator_pow_private_key;
        string private_key;
        string plain_text;
        string cipher_text;
        ofstream fout;
        ifstream fin;

    public:
        //*Constructors
        ELGAMAL();

        //* Getter/Setter Functions
        void getPublicKey_fromFile();
        void getPlainText_fromFile();
        void getCipherText_fromFile();

        //*Binary Calc Functions
        void MakeEqualSize(string &first, string &second);
        string MakeShiftedString(string shiftStr, int shiftCount);
        string ModExpo(string base, string modulo, string exponent);
        string Add(string add1, string add2);
        string Sub(string sub1, string sub2);
        string Xor(string a, string b);
        string Multiply(string X, string Y);
        string Modulus(string divadend, string divisor);

        //*ELGAMAL Functions
        void generatePrivateKey();

};

#endif