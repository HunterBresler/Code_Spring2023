//*Header file for binary class
#ifndef binary_H
#define binary_H

using namespace std;

//uses a string to represent a binary number
class binary
{

    protected:

        string number;

    public:

        //*Constructors
        binary();
        binary(string num);
        binary(char num);

        //* Getter/Setter Functions
        string get_Number();
        void set_Number(string newNum);

        //*Binary Overload Operations
        //Math
        //Does all the the normal operations, but adjusted for binary numbers
        friend binary operator +(const binary& num1, const binary& num2);
        //Precondition: minuend must be larger than subtrahend. No negatives allowed
        friend binary operator -(const binary& minuend, const binary& subtrahend);
        friend binary operator *(const binary& num1, const binary& num2);
        //Precondition: Cannot divide by 0
        friend binary operator /(const binary& divadend, const binary& divisor);
        //Precondition: Cannot divide by 0
        friend binary operator %(const binary& divadend, const binary& divisor);

        //Comparison
        //Does all the the normal operations, but adjusted for binary numbers
        friend bool operator >(const binary& large, const binary& small);
        friend bool operator <(const binary& small, const binary& large);
        friend bool operator >=(const binary& large, const binary& small);
        friend bool operator <=(const binary& small, const binary& large);
        friend bool operator ==(const binary& num1, const binary& num2);
        friend bool operator !=(const binary& num1, const binary& num2);

        //Assignment
        //Does all the the normal operations, but adjusted for binary numbers
        binary& operator =(const binary& num2);
        binary& operator +=(const binary& num2);
        binary& operator -=(const binary& num2);
        binary& operator *=(const binary& num2);
        binary& operator /=(const binary& num2);
        binary& operator %=(const binary& num2);

        //Subscript
        //Treats the binary numbers like strings and gets the appriopriate value corresponding with index
        //Precondition: index must be inbounds
        char operator [](const int& index) const;
        char& operator [](const int& index);

        //Stream
        //Displays the binary number as if it was a string
        friend istream& operator >>(istream &ins, binary &num);
        friend ostream& operator <<(ostream &outs, const binary &num);

        //*Binary Calc Functions
        //Adds '0' to the end of a binary number padCount times
        binary PadRight(int padCount) const;
        //Adds '0' to the start of a binary number padCount times
        binary PadLeft(int padCount) const;
        //Removes leading 0s of a binary number
        void removeLeadingZeros();
        //Calculates base^exponent % modulo quickly
        friend binary ModExpo(const binary& base, const binary& exponent, const binary& modulo);
        //Precondition: num1 and num2 must be the same length
        //Calculates Xor of num1 and num2
        friend binary Xor(const binary& num1, const binary& num2);
        //Calculates a random number between min and max inclusive
        friend binary getRandom(const binary& min, const binary& max); 

        //*String overload functions
        //Allows string functions on Binary objects
        int size() const;
        void erase(const string::iterator& it);
        string::iterator begin();
        void push_back(const char& c);
        void insert(const string::iterator it, const char&  c);
        void pop_back();
        binary substr(const int& index1, const int& index2);

};

#endif