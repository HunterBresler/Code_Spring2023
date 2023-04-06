//*Header file for BinaryNumber class
#include <string>
#ifndef BinaryNumber_H
#define BinaryNumber_H

using namespace std;

//uses a string to represent a binary number
class BinaryNumber
{

    private:

        string number;

    public:

        //*Constructors
        BinaryNumber();
        BinaryNumber(string num);
        BinaryNumber(char num);

        //* Getter/Setter Functions
        string get_Number();
        int size() const;
        void set_Number(string newNum);

        //*Binary Overload Operations
        friend string operator +(const BinaryNumber &num1, const BinaryNumber &num2);
        friend string operator -(const BinaryNumber &minuend, const BinaryNumber &subtrahend);
        friend bool operator >(const BinaryNumber &num1, const BinaryNumber &num2);
        friend bool operator <(const BinaryNumber &num1, const BinaryNumber &num2);
        friend bool operator >=(const BinaryNumber &num1, const BinaryNumber &num2);
        friend bool operator <=(const BinaryNumber &num1, const BinaryNumber &num2);
        friend bool operator ==(const BinaryNumber &num1, const BinaryNumber &num2);
        friend string operator *(const BinaryNumber &num1, const BinaryNumber &num2);
        friend string operator /(const BinaryNumber &divadend, const BinaryNumber &divisor);
        friend string operator %(const BinaryNumber &divadend, const BinaryNumber &divisor);
        
        void operator =(const BinaryNumber &num2);
        friend void operator +=(BinaryNumber &num1, const BinaryNumber &num2);
        friend void operator -=(BinaryNumber &num1, const BinaryNumber &num2);
        friend void operator *=(BinaryNumber &num1, const BinaryNumber &num2);
        friend void operator /=(BinaryNumber &num1, const BinaryNumber &num2);
        friend void operator %=(BinaryNumber &num1, const BinaryNumber &num2);
        
        char operator [](const int &index) const;
        char& operator [](const int &index);

        //*Binary Calc Functions
        string PadRight(int PadCount) const;
        string PadLeft(int PadCount) const;
        string ModExpo(const BinaryNumber &base, const BinaryNumber &exponent, const BinaryNumber &modulo);
        string Xor(const BinaryNumber &num1, const BinaryNumber &num2);
        string getRandom(const BinaryNumber &min, const BinaryNumber &max);

};

#endif