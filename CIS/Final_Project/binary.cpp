//*binary Implementation
#include <iostream>
#include <string>
#include <cmath>
#include "binary.h"

//*Constructors
binary::binary()
{
    number = "0";
}

binary::binary(string num)
{
    number = num;
}

binary::binary(char num)
{
    number = num;
}

binary::binary(const char num[])
{
    number = num;
}

binary::binary(int size)
{
    number = "1";
    number.append(size-1, '0');
}

//* Getter/Setter Functions
string binary::get_Number()
{
    return number;
}

void binary::set_Number(string newNum)
{
    number = newNum;
}


//*Binary Overload Operations
binary operator+(const binary& num1, const binary& num2)
{
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    binary sum("");
    int carry = 0; //Carry for bit addition

    while (i >= 0 || j >= 0 || carry == 1)
    {
        carry += ((i >= 0) ? num1.number[i] - '0': 0);
        carry += ((j >= 0) ? num2.number[j] - '0': 0);
        
        sum.insert(sum.begin(), char(carry%2 + '0'));

        carry /= 2;

        //Decrement i and j
        i--;
        j--;
    }

    return sum;
}

binary operator-(const binary& minuend, const binary& subtrahend)
{
    binary result;

    //Short circuit if minuend and subtrahend are equal
    if (minuend == subtrahend)
    {
        return result;
    }

    //Make sure minuend is greater than subtrahend
    if (minuend < subtrahend)
    {
        cout << "\nError: ELGAMAL::minuend must be >= than subtrahend";
        exit(1);
    }

    //Make them equal in size
    result = subtrahend;
    result.removeLeadingZeros();
    result = result.PadLeft(minuend.size() - result.size()); 


    //Replace result with it's 1s complement
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = ((result[i] == '1') ? '0': '1');
    }

    //Add minuend and the 1s complement for subtraction
    result += minuend;

    //Check for carry and add it back into sum
    if (result.size() > minuend.size())
    {
        result.erase(result.begin()); //Remove the first element
        result += '1';
    }

    //Remove excess 0s
    result.removeLeadingZeros();

    return result;
}

binary operator*(const binary& num1, const binary& num2)
{
    binary result, shifted;
    int len = num2.size();

    //Add 
    for (int i = len-1; i >= 0; i--)
    {
        if (num2[i] == '1')
        {
            //Uses repeated addition to multiply
            shifted = num1.PadRight(len - (i+1));
            result += shifted;
        }
        else
        {
            continue;
        }
    }

    return result;
}

binary operator/(const binary& divadend, const binary& divisor)
{
    binary result, beingSubbed("");

    //Check for error/base cases
    if (divisor == '0')
    {
        cout << "\nDivide by 0: ERROR";
        exit(4);
    }
    else if (divadend < divisor)
    {
        return result;
    }

    //Long division
    for (int i = 0; i < divadend.size(); i++)
    {
        
        beingSubbed.removeLeadingZeros();

        //Make sure divisor is greater than being subbed before running
        if (divisor > beingSubbed)
        {
            beingSubbed.push_back(divadend[i]);
        }

        //If beingSubbed - divisor is possible, run
        if (beingSubbed >= divisor)
        {
            beingSubbed -= divisor;
            result.push_back('1');
        }
        else
        {
            result.push_back('0');
        }

    }

    result.removeLeadingZeros();
    return result;
}

binary operator%(const binary& divadend, const binary& divisor)
{
    //Error Check
    if (divisor == '0')
    {
        cout << "\nDivide by 0: ERROR";
        exit(4);
    }

    binary result = divadend, shifted;
    result.removeLeadingZeros();

    //repeated subtraction
    while (divisor.size() <= result.size())
    {

        // Uses Sub to divide
        shifted = divisor.PadRight(result.size() - divisor.size());

        // Make sure result is greater than or equal to shifted before sub
        if (result >= shifted)
        {
            result -= shifted;
        }
        else if (result > divisor) // In case the shift makes result larger than divisor
        {
            shifted.pop_back();
            result -= shifted;
        }
        else
        {
            break;
        }
    }

    return result;
}

bool operator>(const binary& large, const binary& small)
{
    binary l = large, s = small;
    l.removeLeadingZeros();
    s.removeLeadingZeros();
    int lLen = l.size();
    int sLen = s.size();
    
    if (lLen > sLen)
    {
        return true;
    }
    else if (lLen < sLen)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < lLen; i++)
        {
            if (l[i] == s[i])
            {
                continue;
            }
            else if (l[i] == '1')
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    //large == small
    return false; 
}

bool operator<(const binary& small, const binary& large)
{
    return large > small;
}

bool operator>=(const binary& large, const binary& small)
{
    return large > small || large == small;
}

bool operator<=(const binary& small, const binary& large)
{
    return small < large || small == large;
}

bool operator==(const binary& num1, const binary& num2)
{
    return num1.number == num2.number;
}

bool operator !=(const binary& num1, const binary& num2)
{
    return num1.number != num2.number;
}

binary& binary::operator=(const binary& num2)
{
    number = num2.number;
    return *this;
}

binary& binary::operator+=(const binary& num2)
{
    *this = number + num2;
    return *this;
}

binary& binary::operator-=(const binary& num2)
{
   *this = number - num2;
    return *this;
}

binary& binary::operator*=(const binary& num2)
{
    *this = number * num2;
    return *this;
}

binary& binary::operator/=(const binary& num2)
{
    *this = number / num2;
    return *this;
}

binary& binary::operator%=(const binary& num2)
{
    *this = number % num2;
    return *this;
}


char binary::operator[](const int& index) const
{
    if (index > number.size() || index < 0)
    {
        cout << "\nError:Index Out of Bounds";
        exit(0);
    }
    return number[index];
}

char& binary::operator[](const int& index)
{
    if (index > number.size() || index < 0)
    {
        cout << "\nError:Index Out of Bounds";
        exit(0);
    }
    return number[index];
}


istream& operator>>(istream &ins, binary &num)
{
    ins >> num.number;
    return ins;
}

ostream& operator<<(ostream &outs, const binary &num)
{
    outs << num.number;
    return outs;
}


//*Binary Calc Functions
binary binary::PadRight(int padCount) const
{
    string shifted = number;
    shifted.append(padCount, '0');
    return shifted;
}

binary binary::PadLeft(int padCount) const
{
    string shifted = number;
    shifted.insert(shifted.begin(), padCount, '0');
    return shifted;
}

void binary::removeLeadingZeros()
{
    while(number[0] == '0')
    {
        number.erase(number.begin());
    }

    if (number == "")
    {
        number = '0';
    }
}


//*String overload functions
int binary::size() const
{
    return number.size();
}

void binary::erase(const string::iterator& it)
{
    number.erase(it);
}

string::iterator binary::begin()
{
    return number.begin();
}

void binary::push_back(const char& c)
{
    number.push_back(c);
}

void binary::insert(const string::iterator it, const char&  c)
{
    number.insert(it, c);
}

void binary::pop_back()
{
    number.pop_back();
}

binary binary::substr(const int& index1, const int& index2)
{
    return number.substr(index1, index2);
}


//*Binary Calc Functions
binary ModExpo(const binary& base, const binary& exponent, const binary& modulo)
{

    //Declare variable for return  value
    binary result('1');

    //Short circuit if modulo is 1
    if (modulo == '1')
    {
        result = '0';
        return result;
    }

    //Short circuit to prevent error with the next if statement
    if (exponent.size() == 0)
    {   
        cout << "\nError:Exponent cannot be an empty value";
        exit(1);
    }

    
    if (exponent[0] == '1')
    {
        result = base;
    }

    //Checks for the exponent being 1 or 0
    if (exponent.size() == 1)
    {
        return result % modulo;
    }
    
    for (int i = 1; i < exponent.size(); i++)
    {

        result = (result * result) % modulo;

        if (exponent[i] == '1')
        {
            result = (base * result) % modulo;
        }

    }

    return result;
    
}

binary Xor(const binary& num1, const binary& num2)
{

    //Error check
    if (num1.size() != num2.size())
    {
        cout << "\nError:Can only Xor numbers of equal size";
        exit(2);
    }

    binary result("");
	for(int i = 0; i < num1.size(); i++)
    { 
		if(num1[i] != num2[i])
        { 
			result.push_back('1'); 
		}
		else
        { 
			result.push_back('0'); 
		} 
	} 

	return result; 

}

binary getRandom(const binary& min, const binary& max)
{

    binary randomNum("");

    //Fill in random sized string with random binary values
    for (int i = 0; i < max.size(); i++)
    {
        randomNum.push_back((rand() % 2 == 1) ? '1': '0');
    }


    //Remove excess 0s
    randomNum.removeLeadingZeros();


    //Recurs until random num is <= max and random num > min
    if (randomNum > max || randomNum < min)
    {
        return getRandom(min, max);
    }


    return randomNum;
}


//*Primes
//Returns true if prime
bool isPrime(const binary& num)
{

    if (simplePrimeCheck(num) == false) //aka if num is composite
    {
        return false;
    }

    //Run Miller if num passes the simple prime check
    //find an odd d where d*2^r = n-1
    binary d = num - "1";
    while (d % "10" == "0")
    {
        d /= "10";
    }
    

    int k = 4; //Amount of times to run miller test
    //auto begin = chrono::high_resolution_clock::now();
    //Run the miller test k times
    for (int i = 0; i < k; i++)
    {
        //If num is composite
        if (millerTest(num, d) == false)
        {
            //auto end = chrono::high_resolution_clock::now();
            //auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

            //printf("\n\nRabin time measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);
            return false;
        }
    }

    //auto end = chrono::high_resolution_clock::now();
    //auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    //printf("\n\nRabin time measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);

    return true;

}

//Returns true if prime
bool simplePrimeCheck(const binary& num)
{
    //Base cases
    if (num == "1" || num == "0")
    {
        return false;
    }
    else if (num == "10" || num == "11")
    {
        return true;
    }
    
    //Check first 70 primes
    for (binary i : first_primes)
    {
        if (num % i == "0")
        {
            return false;
        }
    }

    //Passes simple prime check
    passed++;
    return true;
    
}

//Returns true if prime
bool millerTest(const binary& num, binary d)
{

    //Declare variables
    binary numMinus1 = num - "1";
    binary a = getRandom("10", num - "10");
    binary x = ModExpo(a, d, num);

    //Prime checking
    if (x == "1" || x == numMinus1)
    {
        return true;
    }


    while (d != numMinus1)
    {
        x = ModExpo(x, "10", num);
        d *= "10";
 
        if (x == "1")
        {
            return false;
        }
        else if (x == numMinus1)
        {
            return true;
        }
    }

    return false;
}


binary generatePrime(const int& Size)
{
    binary genPrime, minValue(Size), maxValue(Size+1);
    int checkCount = 0;

    while (!isPrime(genPrime))
    {

        genPrime = getRandom(minValue, maxValue); // Generates a prime of Size bits
        checkCount++;
    }

    cout << "\nCheck count: " << checkCount;
    cout << "\nPassed count: " << passed;

    return genPrime;
}

//!Move to 3DES
int binary_to_decimal(const binary& num)
{
    //read binary right to left and add 2^i to result if the read digit is '1'
    int result = 0;
    for (int i = 0; i < num.size(); i++)
    {
        //Math to read from right to left
        if (num[num.size() - (i+1)] == '1')
        {
            result += pow(2, i);
        }
    }
    
    return result;
}

binary decimal_to_binary(int decimal)
{
    //Get the remainder and add it as the right most digit of binary
    string bNum = "";
    while (decimal != 0)
    {
        bNum = (decimal % 2 == 0 ? "0":"1") + bNum; //Sick new operator. Ternary operator epic
        decimal /= 2;
    }

    //Make sure binary is 4 bits in length
    while (bNum.size() < 4)
    {
        bNum = "0" + bNum;
    }

    binary num(bNum);
    return num;
}