/*
    Author: Hunter Bresler
    Date: 2/24/2023
    Assignment2: DES Implementation
*/

#include <iostream>
#include <vector>
#include <string>


using namespace std;



//*Keeps track of and generates keys associated with a master key
class KEY 
{
    private:

        //*Declare member variables
        string master_key;
        string sub_keys[16];

        //*Constant member Variables
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

    public:
        //*Constructor
        KEY();

        //*Getter Functions
        string* get_sub_keys();
        string get_master_key();

        //*Setter Functions
        //void set_sub_keys(string new_sub_keys);
        void set_master_key(string master_key);

        //*Key generation functions
        void key_generator();
        //Generates all sub keys and assigns them to sub_keys
        //Uses the functions below

        string pc1_permutation(); //Compress master key by running it through the pc1 table
        string left_shift(string input_string); //Shifts key 1 space to the left
        string pc2_permutation(string generated_key); //Compress generated key into sub key
};



//*Implements DES
//*Accesses and utilizes KEY class
class DES 
{
    private:

        //*Declare member variables
        int var3;
        int var4;
        int var5;

    public:
        //*Constructor
        DES();

        //*Getter Functions
        int get_var3();
        int get_var4();
        int get_var5();

        //*Setter Functions
        void set_var3(int var3);
        void set_var4(int var4);
        void set_var5(int var5);
};



//*MAIN
int main(){

    //Test key generation
    KEY secret_key;
    secret_key.set_master_key("1010101010111011000010010001100000100111001101101100110011011101");
    secret_key.key_generator();
    string* subKeys = secret_key.get_sub_keys();
    for (int i = 0; i < 16; i++)
    {
        cout << "Sub Key "<< i+1 << ": " << subKeys[i] << endl;
    }

    return 0;
}


/*
    !This is the list of functions in the KEY Class 
    !The functions will be folded below
*/ 
//*Constructor
KEY::KEY()
{
    cout << endl << "secret key made" << endl << endl;
}


//*Getter Functions
string* KEY::get_sub_keys() {
    return sub_keys;
}

string KEY::get_master_key() {
    return master_key;
}


//*Setter Functions
/*
void KEY::set_generated_keys(int new_generated_keys) {
    generated_keys = new_generated_keys;
}
*/

void KEY::set_master_key(string new_master_key) {
    master_key = new_master_key;
}


//*Key generation functions
void KEY::key_generator()
{
    //Permutate the master key using pc1
    //Then split it in half
    string perm_key = pc1_permutation();
    string leftSide = perm_key.substr(0, 28);
    string rightSide = perm_key.substr(28, 28);


    //Generate all 16 sub keys
    for (int i = 0; i < sizeof(sub_keys)/sizeof(sub_keys[0]); i++)
    {
        //Shift each half to the the left once for sub keys 1, 2, 9, and 16
        //Shift twice for all other rounds
        if (i == 0 || i == 1 || i== 8 || i == 15)
        {
            //Shift once
            leftSide = left_shift(leftSide);
            rightSide = left_shift(rightSide);
        }
        else
        {
            //Shift twice
            leftSide = left_shift(leftSide);
            leftSide = left_shift(leftSide);
            rightSide = left_shift(rightSide);
            rightSide = left_shift(rightSide);
        }

        //Combine leftSide and rightSide to get the generated key
        string generated_key = leftSide + rightSide;
        //Use pc2 to generate sub key and assign it to sub_keys in order
        sub_keys[i] = pc2_permutation(generated_key);
    }   
}

string KEY::pc1_permutation()
{
    string perm_key = "";
    for (int i = 0; i < sizeof(pc1)/sizeof(pc1[0]); i++)
    {
        //Running master key through pc1 table
        perm_key += master_key[pc1[i]-1];
    }

    return perm_key;
}

string KEY::pc2_permutation(string generated_key)
{
    string sub_key = "";
    //Generates subkey
    for (int i = 0; i < sizeof(pc2)/sizeof(pc2[0]); i++)
    {
        //Running generated key through pc2 table
        sub_key += generated_key[pc2[i]-1];
    }

    return sub_key;
}

string KEY::left_shift(string input_string)
{
    string shifted = "";
    for (int i = 1; i < input_string.size(); i++)
    {
        //shifts each character to the left
        shifted += input_string[i];
    }
    //shifts the first character to the back
    shifted += input_string[0];

    return shifted;
}



/*
    !This is the list of functions in the DES Class 
    !The functions will be folded below
*/ 
//*Constructor
DES::DES()
{

}


//*Getter Functions
int DES::get_var3()
{

}

int DES::get_var4()
{

}

int DES::get_var5()
{

}


//*Setter Functions
void DES::set_var3(int var3)
{

}

void DES::set_var4(int var4)
{

}

void DES::set_var5(int var5)
{

}
