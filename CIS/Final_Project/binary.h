//*Header file for binary class
#ifndef binary_H
#define binary_H
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace binary_HB
{
    // uses a string to represent a binary number
    class binary
    {

        private:
            string number;

        public:
            //*Constructors
            binary();
            binary(string num);
            binary(char num);
            binary(const char num[]);
            binary(int size);

            //* Getter/Setter Functions
            string get_Number();
            void set_Number(string newNum);

            //*Binary Overload Operations
            // Math
            // Does all the the normal operations, but adjusted for binary numbers
            friend binary operator+(const binary &num1, const binary &num2);
            // Precondition: minuend must be larger than subtrahend. No negatives allowed
            friend binary operator-(const binary &minuend, const binary &subtrahend);
            friend binary operator*(const binary &num1, const binary &num2);
            // Precondition: Cannot divide by 0
            friend binary operator/(const binary &divadend, const binary &divisor);
            // Precondition: Cannot divide by 0
            friend binary operator%(const binary &divadend, const binary &divisor);

            // Comparison
            // Does all the the normal operations, but adjusted for binary numbers
            friend bool operator>(const binary &large, const binary &small);
            friend bool operator<(const binary &small, const binary &large);
            friend bool operator>=(const binary &large, const binary &small);
            friend bool operator<=(const binary &small, const binary &large);
            friend bool operator==(const binary &num1, const binary &num2);
            friend bool operator!=(const binary &num1, const binary &num2);

            // Assignment
            // Does all the the normal operations, but adjusted for binary numbers
            binary &operator=(const binary &num2);
            binary &operator+=(const binary &num2);
            binary &operator-=(const binary &num2);
            binary &operator*=(const binary &num2);
            binary &operator/=(const binary &num2);
            binary &operator%=(const binary &num2);

            // Subscript
            // Treats the binary numbers like strings and gets the appriopriate value corresponding with index
            // Precondition: index must be inbounds
            char operator[](const int &index) const;
            char &operator[](const int &index);

            // Stream
            // Displays the binary number as if it was a string
            friend istream &operator>>(istream &ins, binary &num);
            friend ostream &operator<<(ostream &outs, const binary &num);

            //*Binary Calc Functions
            // Adds '0' to the end of a binary number padCount times
            binary PadRight(int padCount) const;
            // Adds '0' to the start of a binary number padCount times
            binary PadLeft(int padCount) const;
            // Removes leading 0s of a binary number
            void removeLeadingZeros();
            //Makes sure it is a binary number
            void check_binary();

            //*String overload functions
            // Allows string functions on Binary objects
            int size() const;
            void erase(const string::iterator &it);
            string::iterator begin();
            void push_back(const char &c);
            void append(const binary &b);
            void insert(const string::iterator it, const char &c);
            void pop_back();
            binary substr(const int &index1, const int &index2);
    };

    //*Binary Calc Functions
    // Calculates base^exponent % modulo quickly
    binary ModExpo(const binary &base, const binary &exponent, const binary &modulo);
    // Precondition: num1 and num2 must be the same length
    // Calculates Xor of num1 and num2
    binary Xor(const binary &num1, const binary &num2);
    // Calculates a random number between min and max inclusive
    binary getRandom(const binary &min, const binary &max);
    // Calculates greatest common denominator of 2 binary numbers
    binary gcd(const binary &num1, const binary &num2);
    int binary_to_decimal(const binary &num);
    binary decimal_to_binary(int decimal);

    //*Primes
    const binary first_primes[] = {"10", "11", "101", "111", "1011", "1101",
                                   "10001", "10011", "10111", "11101",
                                   "11111", "100101", "101001", "101011", "101111",
                                   "110101", "111011", "111101", "1000011",
                                   "1000111", "1001001", "1001111", "1010011",
                                   "1011001", "1100001", "1100101", "1100111",
                                   "1101011", "1101101", "1110001", "1111111",
                                   "10000011", "10001001", "10001011", "10010101",
                                   "10010111", "10011101", "10100011", "10100111",
                                   "10101101", "10110011", "10110101", "10111111",
                                   "11000001", "11000101", "11000111", "11010011",
                                   "11011111", "11100011", "11100101", "11101001",
                                   "11101111", "11110001", "11111011", "100000001",
                                   "100000111", "100001101", "100001111", "100010101",
                                   "100011001", "100011011", "100100101", "100110011",
                                   "100110111", "100111001", "100111101", "101001011",
                                   "101010001", "101011011", "101011101"};
    bool isPrime(const binary &num);
    bool simplePrimeCheck(const binary &num);
    bool millerTest(const binary &num, binary d);
    binary generatePrime(const int &Size);
    //Use when subtracting numbers that are or would result in a negative number
    //Modifies the second bool to represent - or +
    binary sub_neg(const binary &minuend, const binary &subtrahend, bool neg1, bool& neg_res);
} //end binary_HB

#endif