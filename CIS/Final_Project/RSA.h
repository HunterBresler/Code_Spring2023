//*Header file for RSA class
#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <fstream>
#include <vector>
#include "binary.h"

using namespace std;
using namespace binary_HB;

namespace RSA_HB
{
    //const int BLOCK_SIZE = 4194304;

    // Performs RSA using binary data type
    // Plaintext and ciphertext are "sent" through .txt files
    class RSA
    {

        private:
            //*Primes
            binary p;
            binary q;

            //*Public Key
            binary n;   // p*q
            binary phi; // n-1
            binary e;   // random number

            //*Private Key
            binary d;

            //*Texts
            //vector<binary> plain_text;
            //vector<binary> cipher_text;
            binary plain_text;
            binary cipher_text;

        public:
            //*Constructors
            RSA();
            RSA(int size);

            //* Getter/"Setter" Functions
            // Gets public key from file
            void get_Public_Key_fromFile();
            void get_Private_Key_fromFile();
            // Precondition: n must already have been generated
            // fills plain_text from file in n-1 size blocks
            void get_Plain_Text_fromFile();
            // Precondition: n must already have been obtained through a public key
            // fills cipher_text from file in n-1 size blocks
            void get_Cipher_Text_fromFile();
            // Generates size bit primes p and q
            void generate_RSA_Primes(const int &size);
            // Precondition: p and q must already have been generated
            // Generates public/private key values with p and q
            // Also writes keys to file
            void generate_Keys();

            //*Encryption/Decription
            void encryption();
            void decryption();
            void encrypt_fromFile();
            void encrypt_fromGeneration(const int& size);
            void decrypt_fromFile();

            //*Helper functions
            void generate_e();
            void generate_d();
            void write_Public_Key_toFile();
            void write_Private_Key_toFile();
            void write_Plain_Text_toFile();
            void write_Cipher_Text_toFile();
    };
}//end RSA_HB

#endif