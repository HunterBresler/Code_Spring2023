//*Header file for RSA class
#ifndef RSA_H
#define RSA_H
#include "binary.h"
#include "binary.cpp"
#include "vector"

using namespace std;

//Performs RSA using binary data type
//Plaintext and ciphertext are "sent" through .txt files
class RSA: public binary
{

    private:

        //*Primes
        binary p;
        binary q;

        //*Public Key
        binary n;
        binary phi;
        binary e;

        //*Private Key
        binary d;

        //*Texts
        vector<binary> plain_text;
        vector<binary> cipher_text;
        

    public:

        //*Constructors
        RSA();

        //* Getter/"Setter" Functions
        //Gets public key from file
        binary get_public_key();
        //Generates size bit primes p and q
        void generatePrimes(const int& size);
        //Precondition: p and q must already have been generated
        //Generates public/private key values with p and q
        void generateKeys();
        //Precondition: n must already have been generated
        //fills plain_text from file in n-1 size blocks
        void fill_plain_text();
        //Precondition: n must already have been obtained through a public key
        //fills cipher_text from file in n-1 size blocks
        void fill_cipher_text();

        //*Helper functions
        void generate_e();
        void generate_d();

        

};

#endif