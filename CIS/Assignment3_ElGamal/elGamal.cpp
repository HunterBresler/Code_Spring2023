//*ELGAMAL Implementation
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "elGamal.h"


//*Constructors
ELGAMAL::ELGAMAL()
{
    char response;

    //Ask if the want to generate keys
    cout << "\nWould you like to generate keys (y/n): ";
    cin >> response;

    if (response == 'y' || response == 'Y')
    {
        generateKeys();
    }
}


ELGAMAL::ELGAMAL(string user)
{
    char response;

    //Ask if the want to generate keys
    cout << endl << user << " would you like to generate keys (y/n): ";
    cin >> response;

    if (response == 'y' || response == 'Y')
    {
        generateKeys();
    }
}


//* Getter/Setter Functions
void ELGAMAL::getPublicKey_fromFile()
{
    ifstream fin;

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

    fin.close();
}


void ELGAMAL::getPrivateKey_fromFile()
{
    ifstream fin;

    string line;
    fin.open("private_key.txt");
    

    // Get private key from file
    getline(fin, line);
    line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
    private_key = line;

    fin.close();
}


void ELGAMAL::getPlainText_fromFile()
{
    ifstream fin;
    string line;
    fin.open("Plain_text.txt");


    // Get plain textkey from file
    getline(fin, line);
    line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
    plain_text = line;


    //TODO later
    //read the whole plain text
    //while (fin)
    //{
        //Get plain text from file
    //    getline(fin, line);
    //    plain_text += line;
    //}

    fin.close();
}


void ELGAMAL::getCipherText_fromFile()
{
    ifstream fin;

    string line;
    fin.open("Cipher_text.txt");

    // Get gamma from file
    getline(fin, line);
    line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
    gamma = line;

    // Get delta text from file
    getline(fin, line);
    line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
    delta = line;

    //TODO later
    //read the whole cipher text
    //while (fin)
    //{
        //Get cipher text from file
    //    getline(fin, line);
    //    cipher_text += line;
    //}

    fin.close();
}

string ELGAMAL::getPrime()
{
    return prime;
}


string ELGAMAL::getGenerator()
{
    return generator;
}


string ELGAMAL::getGeneratorpPowPrivateKey()
{
    return generator_pow_private_key;
}


string ELGAMAL::getPrivateKey()
{
    return private_key;
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


    //Recurs until random num is <= max and random num > min
    if (IsGreaterThan(randomNum, max) || !IsGreaterThan(randomNum, min))
    {
        return getRandom(min, max);
    }


    return randomNum;
}


//Adds to a list of prime factors taken by reference
void ELGAMAL::findPrimeFactors(vector<string> &primes, string phi)
{

    //cout << "\nPrime factors in progress...";
    //cout << "\nPrime factors added: ";

    //Add all factors of 2
    while (Modulus(phi, "10") == "0")
    {
        primes.push_back("10");
        phi = Div(phi, "10");
        //cout << ", " << primes[primes.size()-1];
    }


    //Add all other factors > 2
    // (int i = 3; i^2 <= phi; i = i+2): add by 2 to skip over already covered evens
    for (string i = "11"; !IsGreaterThan(Multiply(i, i), phi); i = Add(i, "10"))
    {   
        //Add all factors of i
        while (Modulus(phi, i) == "0")
        {
            primes.push_back(i);
            phi = Div(phi, i);
            //cout << ", " << primes[primes.size()-1];
        }
    }

    //Add n if it is > 2
    //!Not sure why
    if (IsGreaterThan(phi, "10"))
    {
        primes.push_back(phi);
    }
}


string ELGAMAL::generateGenerator(string num)
{

    string phi = Sub(num, "1");
    vector<string> primeFactors = {};
    findPrimeFactors(primeFactors, phi);
    //cout << "\nPrime factors generated. Size = " << primeFactors.size();
    string testGenerator = "";

    //Runs until a generator is found
    //!May rerun generators
    while (true)
    {

        bool isGenerator = true;
        testGenerator = getRandom("10", phi);

        for (int index = 0; index != primeFactors.size() - 1; index++)
        {
            if (ModExpo(testGenerator, Div(phi, primeFactors[index]), num) == "1")
            {
                isGenerator = false;
                break;
            }
        }

        if (isGenerator)
        {
            return testGenerator;
        } 
   }
}

//*ELGAMAL Functions
//Generates private and public keys and writes them to file
void ELGAMAL::generateKeys() 
{

    int keySize = 0;
    ofstream fout;

    while (true)
    {
        cout << "\nEnter a bit size for your private key (16, 32, 64, or 128): ";
        cin >> keySize;

        if (keySize == 16 || keySize == 32 || keySize == 64 || keySize == 128)
        {
            break;
        }
        cout << "\nInvalid key size. Try again";
    }

    //Generate public key and private key
    //Gives progress updates through terminal
    prime = generatePrime(keySize);
    // << "\nPrime generated. Size = " << prime.size();
    private_key = getRandom("1", Sub(prime, "10"));
    //cout << "\nPrivate key generated. Size = " << private_key.size();
    generator = generateGenerator(prime);
    //cout << "\nGenerator generated. Size = " << generator.size();
    generator_pow_private_key = ModExpo(generator, private_key, prime);
    //cout << "\nGenerator^private key generated. Size = " << generator_pow_private_key.size();

    //Write private key to a file
    fout.open("Private_key.txt", ios::out);
    fout << "Private Key: " << private_key;
    fout.close();

    //Write public key to a file
    fout.open("Public_key.txt", ios::out);
    fout << "Prime: " << private_key << endl;
    fout << "Generator: " << generator << endl;
    fout << "Generator^Private Key: " << generator_pow_private_key << endl;
    fout.close();
    
}


bool ELGAMAL::isPrime(string num, int k)
{

    //Base cases
    if (num == "1" || num == "100")
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
    }


    //Run the miller test k times
    for (int i = 0; i < k; i++)
    {
        //If num is composite
        if (millerTest(num, d) == false)
        {
            return false;
        }
    }


    return true;
}


//!Might not work
//Returns true if prime
bool ELGAMAL::millerTest(string num, string d)
{

    //Declare variables
    string numMinus1 = Sub(num, "1");
    string a = getRandom("10", Sub(num, "10"));
    string x = ModExpo(a, d, num);

    //Prime checking
    if (x == "1" || x == numMinus1)
    {
        return true;
    }


    while (d != numMinus1)
    {
        x = ModExpo(x, "10", num);
        d = Multiply(d, "10");
 

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


string ELGAMAL::generatePrime(int Size)
{
    string genPrime = "1";
    string minValue = "";

    //Fill minValue
    for (int i = 0; i < Size-1; i++)
    {
        minValue += "1";
    }

    while (!isPrime(genPrime, genPrime.size() + 10))
    {
        genPrime = getRandom(minValue, minValue + "1"); //Generates a prime of Size bits
    }

    return genPrime;
}

//Gets public key through member variable and sends cipher text to file
void ELGAMAL::encrypt()
{

    ofstream fout;

    //Calculate ELGAMAL Variables gamma and delta
    string k = getRandom("1", Sub(prime, "10"));                             //Get random k, 1 <= k <= p-2
    gamma = ModExpo(generator, k, prime);                                       //gen^k mod p
    delta = ModExpo(Multiply(plain_text, generator_pow_private_key), k, prime); //(gen^a)^k mod p

    //Send Cipher text
    fout.open("Cipher_text.txt", ios::out);
    fout << "Gamma: " << gamma << endl;
    fout << "Delta: " << delta << endl;
    fout.close();
    
}


//Gets private key from member variable and sends plain text to file
void ELGAMAL::decrypt()
{

    ofstream fout;

    //Calculate exponent
    string exponent = Sub(prime, private_key); 
    exponent = Sub(exponent, "1");       

    //Calculate gamma^exponent mod prime and delta mod prime              
    string modGamma = ModExpo(gamma, exponent, prime);
    string modDelta = Modulus(delta, prime);

    //Calculate plain text
    plain_text = Modulus(Multiply(modGamma, modDelta), prime);

    //Send Plain text
    fout.open("Plain_text.txt", ios::out);
    fout << "Plain_text: " << plain_text << endl;
    fout.close();

}



//*Driver Function
void ELGAMAL::Drive()
{  

    char response;

    //Get public key from file
    getPublicKey_fromFile();

    //Ask for decryption or encription
    cout << "\nWould you like to decrypt or encrypt a message (d/e): ";
    cin >> response;

    if (response == 'd' || response == 'D')
    {
        //Make sure decrypt has access to cipher text and public key
        getCipherText_fromFile();
        getPublicKey_fromFile();
        decrypt();
    }
    else if (response == 'e' || response == 'E')
    {
        //Make sure encrypt has access to plain text and private key
        getPlainText_fromFile();
        getPrivateKey_fromFile();
        encrypt();
    }
    else
    {
        cout << "\nInvalid choice. Program terminated";
        exit(1);
    }
}