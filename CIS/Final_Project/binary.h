//*Header file for binary class
#ifndef binary_H
#define binary_H

using namespace std;

//uses a string to represent a binary number
class binary
{

    private:

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
        friend string operator +(const binary& num1, const binary& num2);
        friend string operator -(const binary& minuend, const binary& subtrahend);
        friend string operator *(const binary& num1, const binary& num2);
        friend string operator /(const binary& divadend, const binary& divisor);
        friend string operator %(const binary& divadend, const binary& divisor);
        //Comparison
        friend bool operator >(const binary& num1, const binary& num2);
        friend bool operator <(const binary& num1, const binary& num2);
        friend bool operator >=(const binary& num1, const binary& num2);
        friend bool operator <=(const binary& num1, const binary& num2);
        friend bool operator ==(const binary& num1, const binary& num2);
        //Assignment
        binary& operator =(const binary& num2);
        binary& operator =(const string& num2);
        binary& operator +=(const binary& num2);
        binary& operator -=(const binary& num2);
        binary& operator *=(const binary& num2);
        binary& operator /=(const binary& num2);
        binary& operator %=(const binary& num2);
        //Subscript
        char operator [](const int& index) const;
        char& operator [](const int& index);
        //Stream
        friend istream& operator >>(istream &ins, binary &num);
        friend ostream& operator <<(ostream &outs, const binary &num);

        //*Binary Calc Functions
        string PadRight(int PadCount) const;
        string PadLeft(int PadCount) const;
        string ModExpo(const binary& base, const binary& exponent, const binary& modulo);
        string Xor(const binary& num1, const binary& num2);
        string getRandom(const binary& min, const binary& max);

        //*String overload functions
        int size() const;
        void erase(const string::iterator& it);
        string::iterator begin();

};

#endif