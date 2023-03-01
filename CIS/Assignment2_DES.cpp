/*
    Author: Hunter Bresler
    Date: 2/24/2023
    Assignment2: DES Implementation
*/

#include <iostream>
#include <string>



using namespace std;



//*Keeps track of and generates keys associated with a master key
class KEY 
{
    private:

        //*Declare member variables
        string master_key;
        string sub_keys[16];

        //*Constant member Variables: No get/set functions
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
        void set_master_key(string master_key);

        //*Key generation functions
        void key_generator(); //*Class driver function
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
        string* sub_keys;
        string current_key;
        string plain_text;
        string cipher_text;
        KEY master_key;
        string left_half;
        string right_half;
        string modified_half;


        //*Constant member variables: No get/set functions
        //Initial permutation table
        const int initial_perm[64] =
        {
            58,50,42,34,26,18,10,2, 
            60,52,44,36,28,20,12,4, 
            62,54,46,38,30,22,14,6, 
            64,56,48,40,32,24,16,8, 
            57,49,41,33,25,17,9,1, 
            59,51,43,35,27,19,11,3, 
            61,53,45,37,29,21,13,5, 
            63,55,47,39,31,23,15,7
        };
        //Expansion table
        const int expansion_table[48] =
        {
            32,1,2,3,4,5,4,5, 
            6,7,8,9,8,9,10,11, 
            12,13,12,13,14,15,16,17, 
            16,17,18,19,20,21,20,21, 
            22,23,24,25,24,25,26,27, 
            28,29,28,29,30,31,32,1
        };
        //Substitution boxes
        const int sub_boxes[8][4][16] =
        {
        {   //Box1
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
        }, 
        {   //Box2
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
        }, 
        {   //Box3
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
        }, 
        {   //Box4
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
        }, 
        {   //Box5
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
        }, 
        {   //Box6
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
        }, 
        {   //Box7
            4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
        }, 
        {   //Box8
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
        }};
        //Post sub box permutation table
        const int sub_perm[32] =
        {
            16,7,20,21,29,12,28,17, 
            1,15,23,26,5,18,31,10, 
            2,8,24,14,32,27,3,9,
            19,13,30,6,22,11,4,25
        };
        //Inverse permutation table
        const int inverse_perm[64] =
        {
            40,8,48,16,56,24,64,32, 
            39,7,47,15,55,23,63,31, 
            38,6,46,14,54,22,62,30, 
            37,5,45,13,53,21,61,29, 
            36,4,44,12,52,20,60,28, 
            35,3,43,11,51,19,59,27, 
            34,2,42,10,50,18,58,26, 
            33,1,41,9,49,17,57,25
        };

    public:
        //*Constructor
        DES();

        //*Getter Functions
        string* get_sub_keys();
        string get_plain_text();
        string get_cipher_text();

        //*Setter Functions
        void set_plain_text(string plain_text);

        //*DES implementation
        void DES_driver(); //*Driver function
        //Runs DES
        //Uses the functions below

        void KEY_call();
        string initial_permutation();
        void expansion();
        string Xor(string a, string b);
        string sub_box();
        void sub_permutation();
        void inverse_permutation(string combined);
        string binary_to_decimal();
        string decimal_to_binary();
        void swap_halves();
        void encrypt();
        void decrypt();

};



//*MAIN
int main(){

    //Test key generation
    /*
    KEY secret_key;
    secret_key.set_master_key("1010101010111011000010010001100000100111001101101100110011011101");
    secret_key.key_generator();
    string* subKeys = secret_key.get_sub_keys();
    for (int i = 0; i < 16; i++)
    {
        cout << "Sub Key "<< i+1 << ": " << subKeys[i] << endl;
    }
    */

    DES run_DES;
    run_DES.DES_driver();
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
string* KEY::get_sub_keys() 
{
    return sub_keys;
}

string KEY::get_master_key() 
{
    return master_key;
}


//*Setter Functions
void KEY::set_master_key(string new_master_key) 
{
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
    cout << "DES initiated";
}


//*Getter Functions
string* DES::get_sub_keys() 
{
    return sub_keys;
}

string DES::get_plain_text()
{
    return plain_text;
}

string DES::get_cipher_text()
{
    return cipher_text;
}

//*Setter Functions
void DES::set_plain_text(string plain_text)
{

}

//*DES implementation
//*Driver function
void DES::DES_driver()
{
    KEY_call();
}

void DES::KEY_call() //Gets key from KEY class
{
    master_key.set_master_key("1010101010111011000010010001100000100111001101101100110011011101");
    master_key.key_generator();
    sub_keys = master_key.get_sub_keys();
    current_key = sub_keys[0];
    for (int i = 0; i < 16; i++)
    {
        cout << "Sub Key "<< i+1 << ": " << sub_keys[i] << endl;
    }
}

string DES::initial_permutation()
{
    //Permutate plaintext with initial permutation table
    string perm = ""; 
	for(int i = 0; i < sizeof(initial_perm)/sizeof(initial_perm[0]); i++)
    { 
		perm += plain_text[initial_perm[i]-1]; 
	}

    return perm;
}

void DES::expansion()
{
    //Expand modified half for Xor
    string expanded = "";
    for(int i = 0; i < sizeof(expansion_table)/sizeof(expansion_table[0]); i++) 
    { 
      		expanded += modified_half[expansion_table[i]-1]; 
    };

    modified_half = expanded;
}

string DES::Xor(string a, string b)
{
    //Xor the input strings a and b
    //Assume a and b are equal in size
    string result = ""; 
	for(int i = 0; i < a.size(); i++){ 
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

string DES::sub_box()
{

}

void DES::sub_permutation()
{
    //Permutate modified half after sub box
    string perm =""; 
	for(int i = 0; i < sizeof(sub_perm)/sizeof(sub_perm[0]); i++){ 
		perm += modified_half[sub_perm[i]-1]; 
	}

    modified_half = perm;
}

void DES::inverse_permutation(string combined)
{
    //Permutate fully encrypted text into cipher text
    string result = "";
    for(int i = 0; i < sizeof(inverse_perm)/sizeof(inverse_perm[0]); i++)
    { 
		result += combined[inverse_perm[i]-1]; 
	}

    cipher_text = result;
}

string DES::binary_to_decimal()
{

}

string DES::decimal_to_binary()
{

}

void DES::swap_halves()
{
    //Swap halves after each round of encryption
    string temp = right_half;
	right_half = left_half;
	left_half = temp;
}

void DES::encrypt()
{

}

void decrypt()
{

}
