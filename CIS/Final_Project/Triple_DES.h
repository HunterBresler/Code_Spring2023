//*Header file for Triple_DES class
#ifndef Triple_DES_H
#define Triple_DES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "binary.h"

using namespace std;
using namespace binary_HB;

namespace Triple_DES_HB
{

    // Performs Triple_DES using binary data type
    // Plaintext and ciphertext are "sent" through .txt files
    class Triple_DES
    {

        private:
            //*Private Keys
            binary key_1;
            binary key_2;
            binary key_3;
            binary sub_keys_1[16];
            binary sub_keys_2[16];
            binary sub_keys_3[16];


            //*Texts
            vector<binary> plain_text;
            vector<binary> cipher_text;

        public:
            //*Constructor
            Triple_DES();

            //*Getter/Setter functions
            // gets private key from file (3 DES keys)
            void get_Private_Key_fromFile();
            // fills plain_text from file in BLOCK_SIZE sized blocks
            void get_Plain_Text_fromFile();
            // fills cipher_text from file in BLOCK_SIZE sized blocks
            void get_Cipher_Text_fromFile();

            //*Key generation
            // Generates the 3 keys used for 3DES
            void generate_all_keys();
            //Generates and returns one DES key
            binary generate_key();
            // Precondition: keys 1-3 must have values
            // Generates the 3 sets of sub keys used for 3DES
            binary generate_sub_key(binary& leftSide, binary& rightSide, int round);
            //Compress master key by running it through the pc1 table
            binary pc1_permutation(binary key); 
            //Shifts key 1 space to the left
            binary left_shift(binary input); 
            //Compress generated key into sub key
            binary pc2_permutation(binary key); 

            //*Encryption/Decryption
            void encrypt();
            void decrypt(); 
            void encrypt_fromFile();
            void encrypt_fromGeneration(const int& size);
            void decrypt_fromFile();

            //*3DES Algorithm functions
            binary initial_permutation();
            void expansion();
            void sub_box();
            void sub_permutation();
            binary inverse_permutation(binary combined);

            //*DES Calc functions
            int binary_to_decimal(binary binary);
            binary decimal_to_binary(int decimal);
            void swap_halves();
            void invert_sub_keys();

            //*Helper functions
            void check_plain_text();
            void write_Private_Key_toFile();
            void write_Plain_Text_toFile();
            void write_Cipher_Text_toFile();
    };

    //*Constants
    const int BLOCK_SIZE = 64;
    const binary MIN_KEY = "1000000000000000000000000000000000000000000000000000000000000000";
    const binary MAX_KEY = "1111111111111111111111111111111111111111111111111111111111111111";

    //PC1 Table
    const int pc1[56] = 
    {
        57,49,41,33,25,17,9, 
        1,58,50,42,34,26,18, 
        10,2,59,51,43,35,27, 
        19,11,3,60,52,44,36,		 
        63,55,47,39,31,23,15, 
        7,62,54,46,38,30,22, 
        14,6,61,53,45,37,29, 
        21,13,5,28,20,12,4 
    };

    //PC2 Table
    const int pc2[48] = 
    {
        14,17,11,24,1,5, 
        3,28,15,6,21,10, 
        23,19,12,4,26,8, 
        16,7,27,20,13,2, 
        41,52,31,37,47,55, 
        30,40,51,45,33,48, 
        44,49,39,56,34,53, 
        46,42,50,36,29,32 
    };

    // Initial permutation table
    const int initial_perm[64] =
    {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7};

    // Expansion table
    const int expansion_table[48] =
    {
        32, 1, 2, 3, 4, 5, 4, 5,
        6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27,
        28, 29, 28, 29, 30, 31, 32, 1};

    // Substitution boxes
    const int sub_boxes[8][4][16] =
    {
        {// Box1
         14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
         0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
         4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
         15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
        {// Box2
         15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
         3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
         0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
         13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
        {// Box3
         10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
         13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
         13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
         1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
        {// Box4
         7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
         13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
         10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
         3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
        {// Box5
         2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
         14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
         4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
         11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
        {// Box6
         12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
         10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
         9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
         4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
        {// Box7
         4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
         13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
         1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
         6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
        {// Box8
         13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
         1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
         7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
         2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    };

    // Post sub box permutation table
    const int sub_perm[32] =
    {   16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25};

    // Inverse permutation table
    const int inverse_perm[64] =
    {   40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};

}//end Triple_DES_HB

#endif