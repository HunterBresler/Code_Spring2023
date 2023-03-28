//*Header file for ELGAMAL class
#include <vector>
#ifndef ELGAMAL_H
#define ELGAMAL_H

using namespace std;

//Contains all functions and variables to encrypt AND decrypt elgamal
//IO from file
//uses string for binary representation
class ELGAMAL
{

    private:

        //*Public Key
        string prime;
        string generator;
        string generator_pow_private_key;

        //*Private Key
        string private_key;

        //*Plain Text
        string plain_text;

        //*Cipher Text
        string gamma;
        string delta;

        //*User
        //string name;

    public:
        //*Constructors
        ELGAMAL();
        ELGAMAL(string user);
        ELGAMAL(int test); //For testing

        //* Getter/Setter Functions
        void getPublicKey_fromFile();
        void getPrivateKey_fromFile();
        void getPlainText_fromFile();
        void getCipherText_fromFile();
        string getPrime();
        string getGenerator();
        string getGeneratorpPowPrivateKey();
        string getPrivateKey();
        

        //*Binary Calc Functions
        void MakeEqualSize(string &first, string &second);
        string MakeShiftedString(string shiftStr, int shiftCount);
        string ModExpo(string base, string exponent, string modulo);
        string Add(string add1, string add2);
        string Sub(string sub1, string sub2);
        bool IsGreaterThan(string large, string small);
        string Xor(string a, string b);
        string Multiply(string X, string Y);
        string Modulus(string divadend, string divisor);
        string Div(string divadend, string divisor);
        string getRandom(string min, string max);
        string generateGenerator(string prime);

        //*ELGAMAL Functions
        void generateKeys(int keySize);
        bool isPrime(string num, int k);
        bool millerTest(string num, string d);
        string generateSafePrime(int Size);
        void encrypt();
        void decrypt();

        //*Driver Function
        void Drive();

};

#endif