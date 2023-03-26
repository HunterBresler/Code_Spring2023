//*ELGAMAL Implementation
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "elGamal.h"


//*Constructors
ELGAMAL::ELGAMAL()
{

}


//* Getter/Setter Functions
void ELGAMAL::getPublicKey_fromFile()
{
    string line;
    fin.open("Public_key.txt");

    //Get prime from file
    getline(fin, line);
    line = line.substr(line.find(": ")+2); // increment to cut out the ": "
    prime = line;

    //Get generator from file
    getline(fin, line);
    line = line.substr(line.find(": ")+2);
    generator = line;

    //Get generator_pow_private_key from file
    getline(fin, line);
    line = line.substr(line.find(": ")+2);
    generator_pow_private_key = line;

}


void ELGAMAL::getPlainText_fromFile()
{

    string line;
    plain_text = "";
    fin.open("Plain_text.txt");

    //read the whole plain text
    while (fin)
    {
        //Get plain text from file
        getline(fin, line);
        plain_text += line;
    }

}


void ELGAMAL::getCipherText_fromFile()
{

    string line;
    cipher_text = "";
    fin.open("Cipher_text.txt");

    //read the whole cipher text
    while (fin)
    {
        //Get cipher text from file
        getline(fin, line);
        cipher_text += line;
    }

}


//*Binary Calc Functions
void ELGAMAL::MakeEqualSize(string &first, string &second)
{
    int lenFirst = first.size();
    int lenSecond = second.size();
    string addToFront = "";

    if (lenFirst > lenSecond) //When first is longer
    {

        //Add extra 0s
        for (int i = 0; i < lenFirst-lenSecond; i++)
        {
            addToFront += '0';
        }
        //Add original value
        second = addToFront + second;
    
    }
    else if (lenSecond > lenFirst) //When second is longer
    {

        //Add extra 0s
        for (int i = 0; i < lenFirst-lenSecond; i++)
        {
            addToFront += '0';
        }
        //Add original value
        first = addToFront + first;
    
    }
}


//Shift string by certain amonut for binary multiplication
string ELGAMAL::MakeShiftedString(string shiftStr, int shiftCount)
{
    for (int i = 0; i < shiftCount; i++)
    {
        shiftStr += "0";
    }
    return shiftStr;
}


//Binary Modular Exponentiation
string ELGAMAL::ModExpo(string base, string exponent, string modulo)
{
    
    //Declare variable for return  value
    string result = "1";

    //Short circuit if modulo is 1
    if (modulo == "1")
    {
        return "0";
    }

    //Short circuit to prevent error with the next if statement
    if (exponent.size() == 0)
    {   
        cout << "\nError:Exponent cannot be an empty value";
        return result;
    }

    
    if (exponent[0] == '1')
    {
        result = base;
    }

    //Checks for the exponent being 1 or 0
    if (exponent.size() == 1)
    {
        return Modulus(result, modulo);
    }
    
    for (int i = 1; i < exponent.size(); i++)
    {

        result = Modulus(Multiply(result, result), modulo);

        if (exponent[i] == '1')
        {
            result = Modulus(Multiply(base, result), modulo);
        }

    }


    return result;
    
}


//Binary Addition
string ELGAMAL::Add(string add1, string add2)
{

    int i = add1.size() - 1;
    int j = add2.size() - 1;
    string sum = "";
    int carry = 0; //Carry for bit addition

    while (i >= 0 || j >= 0 || carry == 1)
    {
        carry += ((i >= 0) ? add1[i] - '0': 0);
        carry += ((j >= 0) ? add2[j] - '0': 0);
        
        sum = char(carry%2 + '0') + sum;

        carry /= 2;

        //Decrement i and j
        i--;
        j--;
    }

    return sum;
}


bool ELGAMAL::IsGreaterThan(string large, string small)
{
    int lSize = large.size();
    int sSize = small.size();
    bool equal = true;

    //check for negatives
    if (lSize < sSize)
    {
        return false;
    }
    else if (lSize == sSize) //make sure large is larger than small
    {
        for (int i = 0; i < lSize; i++)
        {
            if (large[i] != small[i] && small[i] == '1')
            {
                return false;
            }
            else if (large[i] == '1' && small[i] == '0')
            {
                equal = false;
                break;
            }
        }

        //Check if they're equal
        if (equal)
        {
            return false;
        }
    }

    return true;

}

//Binary subtraction
//WILL NOT COMPUTE NEGATIVES
string ELGAMAL::Sub(string minuend, string subtrahend)
{
    string sum = "";

    //Short circuit if minuend  and subtrahend are equal
    if (minuend == subtrahend)
    {
        return "0";
    }

    //Make sure minuend is greater than subtrahend
    if (!IsGreaterThan(minuend, subtrahend))
    {
        cout << "\nError: ELGAMAL::minuend must be larger than subtrahend";
        return "0";
    }

    //Make sure they are equal in size
    MakeEqualSize(minuend, subtrahend);


    //Replace subtrahend with it's 1s complement
    for (int i = 0; i < subtrahend.size(); i++)
    {
        subtrahend[i] = ((subtrahend[i] == '1') ? '0': '1');
    }

    //Add minuend and the 1s complement for subtraction
    sum = Add(minuend, subtrahend);

    //Check for carry and add it back into sum
    if (sum.size() > minuend.size())
    {
        sum.erase(sum.begin());
        sum = Add(sum, "1");
    }

    //Remove excess 0s
    while (sum[0] == '0')
    {
        sum.erase(sum.begin());
    }

    return sum;
}


string ELGAMAL::Xor(string a, string b)
{
    //Xor the input strings a and b
    //Assume a and b are equal in size
    string result = ""; 
	for(int i = 0; i < a.size(); i++)
    { 
		if(a[i] != b[i])
        { 
			result += "1"; 
		}
		else
        { 
			result += "0"; 
		} 
	} 

	return result; 
}


//Binary Multiplication
string ELGAMAL::Multiply(string X, string Y)
{

    string result = "0";
    string shifted;
    int len = Y.size();

    //Add 
    for (int i = len-1; i >= 0; i--)
    {
        if (Y[i] == '1')
        {
            //Uses repeated addition to multiply
            shifted = MakeShiftedString(X, len - (i+1));
            result = Add(shifted, result);
        }
        else
        {
            continue;
        }
    }

    return result;
}

string ELGAMAL::Modulus(string divadend, string divisor)
{

    string result = divadend;
    string shifted;


    //Sub
    while (divisor.size() <= result.size())
    {
        if (result[0] == '1')
        {
            //Uses Sub to divide
            shifted = MakeShiftedString(divisor, result.size()-divisor.size());

            //Make sure shifted is greater than or equal to result before sub
            if (IsGreaterThan(result, shifted) || result == shifted)
            {
                result = Sub(result, shifted);
            }
            else if (result.size() > divisor.size()) //In case the shift makes result larger than divisor
            {
                shifted.pop_back();
                result = Sub(result, shifted);
            }
            else
            {
                break;
            }
        }
        else //!Might never run
        {
            result.erase(result.begin());
        }
    }

    return result;
}


string ELGAMAL::Div(string divadend, string divisor)
{
    string result = "";
    string shifted;
    int zeros;

    //Check for error cases
    if (divadend == divisor)
    {
        return "1";
    }
    else if (!IsGreaterThan(divadend, divisor))
    {
        cout << "\nError:divadend must be >= divisor";
        return "0";
    }

    //Sub
    while (divisor.size() <= divadend.size())
    {
        zeros = divadend.size(); //Keeps track of how many "0"s to add in between subtractions

        if (divadend[0] == '1')
        {
            //Uses Sub to divide
            shifted = MakeShiftedString(divisor, divadend.size()-divisor.size());

            //Make sure shifted is greater than or equal to divadend before sub
            if (IsGreaterThan(divadend, shifted) || divadend == shifted)
            {
                result += "1";
                divadend = Sub(divadend, shifted);
            }
            else if (divadend.size() > divisor.size()) //In case the shift makes divadend larger than divisor
            {
                result += "01";
                shifted.pop_back();
                divadend = Sub(divadend, shifted);
            }
            else
            {
                break;
            }

            zeros -= divadend.size();

            //Adds in "0"s 
            for (int i = 0; i < zeros-1; i++)
            {
                result += "0";
            }
        }
        else //!Might never run
        {
            result += "0";
            divadend.erase(divadend.begin());
        }
    }

    return result;
    
}



string ELGAMAL::getRandom(string min, string max)
{
    
    int randSize = rand() % (max.size()+1);
    string randomNum = "";


    //Recurs until randSize is larger than minSize
    if (randSize <= min.size())
    {
        return getRandom(min, max);
    }


    //Fill in random sized string with random binary values
    for (int i = 0; i < randSize; i++)
    {
        randomNum += ((rand() % 2 == 1) ? '1': '0');
    }


    //Remove excess 0s
    while (randomNum[0] == '0')
    {
        randomNum.erase(randomNum.begin());
    }


    //Recurs until random num is < max and random num > min
    if (IsGreaterThan(randomNum, max) || randomNum == max || !IsGreaterThan(randomNum, min))
    {
        return getRandom(min, max);
    }

    return randomNum;
}



//*ELGAMAL Functions
void ELGAMAL::generatePrivateKey()
{

}


bool ELGAMAL::isPrime(string num, int k)
{

    //Base cases
    if (num == "1")
    {
        return false;
    }
    else if (num == "10" || num == "11")
    {
        return true;
    }

    //Check if num is even
    if (Modulus(num, "10") == "0")
    {
        return false;
    }


    //find an odd d where d*2^r = n-1
    string d = Sub(num, "1");
    while (Modulus(d, "10") == "0")
    {
        d = Div(d, "10");
        cout << "\nCount: " << d;
        cout << "\nNUM: " << num;
    }

    //Run the miller test k times
    for (int i = 0; i < k; i++)
    {
        if (millerTest(num, d) == false)
        {
            return false;
        }
    }


    return true;
}


//Returns true if prime
bool ELGAMAL::millerTest(string num, string d)
{

    //Declare variables
    string a = getRandom("10", Sub(num, "10"));
    string x = ModExpo(a, d, num);;


    //Prime checking
    if (x == "1" || x == Sub(num, "1"))
    {
        return true;
    }


    while (d != Sub(num, "1"))
    {
        x = ModExpo(x, x, num);
        d = Multiply(d, "10");

        

        if (x == "1")
        {
            return false;
        }
        else if (x == Sub(num, "1"))
        {
            return true;
        }
    }

    return false;
}