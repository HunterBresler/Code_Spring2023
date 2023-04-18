//*Implementation of Triple_DES 
#include "Triple_DES.h"

using namespace std;

namespace Triple_DES_HB
{
    //*Constructor
    Triple_DES::Triple_DES()
    {

    }

    //*Getter/Setter functions
    void Triple_DES::get_Private_Key_fromFile()
    {
        ifstream fin;

        string line;
        fin.open("local_storage/3DES_Private_Key.txt");

        // Get key_1 from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        key_1 = line;

        // Get key_2 from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        key_2 = line;

        // Get key_3 from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        key_3 = line;

        fin.close();
    }

    void Triple_DES::get_Plain_Text_fromFile()
    {
        ifstream fin;

        binary block("");
        fin.open("local_storage/3DES_Plain_Text.txt");

        
        while (fin)
        {
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                if (fin.good())
                {
                    // Add next read char
                    block.push_back(fin.get());
                }
                else
                {
                    // Pad 0s until block has a length of block size
                    block.push_back('0');
                }
            }

            plain_text.push_back(block);
            block = "";
        }
        

        fin.close();
    }

    void Triple_DES::get_Cipher_Text_fromFile()
    {
        ifstream fin;

        binary block("");
        fin.open("unsecure_channel/3DES_Plain_Text.txt");

        
        while (fin)
        {
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                if (fin.good())
                {
                    // Add next read char
                    block.push_back(fin.get());
                }
                else
                {
                    // Pad 0s until block has a length of block size
                    block.push_back('0');
                }
            }

            cipher_text.push_back(block);
            block = "";
        }
        

        fin.close();
    }

    //*Key generation
    void Triple_DES::generate_all_keys()
    {
        key_1 = generate_key();
        key_2 = generate_key();
        key_3 = generate_key();

        //Permutate the keys using pc1
        //Then split them in half
        binary perm_key_1 = pc1_permutation(key_1);
        binary leftSide_1 = perm_key_1.substr(0, 28);
        binary rightSide_1 = perm_key_1.substr(28, 28);
        binary perm_key_2 = pc1_permutation(key_2);
        binary leftSide_2 = perm_key_2.substr(0, 28);
        binary rightSide_2 = perm_key_2.substr(28, 28);
        binary perm_key_3 = pc1_permutation(key_3);
        binary leftSide_3 = perm_key_3.substr(0, 28);
        binary rightSide_3 = perm_key_3.substr(28, 28);

        // Generate all 16 sub keys for ech key
        for (int i = 0; i < 16; i++) // 16 is the size of sub_keys
        {
            sub_keys_1[i] = generate_sub_key(leftSide_1, rightSide_1, i);
            sub_keys_2[i] = generate_sub_key(leftSide_2, rightSide_2, i);
            sub_keys_3[i] = generate_sub_key(leftSide_3, rightSide_3, i);
        }

        cout << endl << sub_keys_1[14];
    }

    binary Triple_DES::generate_key()
    {
        binary result = getRandom(MIN_KEY, MAX_KEY);
        result.PadLeft(BLOCK_SIZE - result.size());
        return result;
    }

    binary Triple_DES::generate_sub_key(binary& leftSide, binary& rightSide, int round)
    {
        //Shift each half to the the left once for sub keys 1, 2, 9, and 16
        //Shift twice for all other rounds
        if (round == 0 || round == 1 || round == 8 || round == 15)
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
        binary generated_key = leftSide;
        generated_key.append(rightSide);

        //Use pc2 to generate sub key and return it
        generated_key = pc2_permutation(generated_key);

        return generated_key;
    }

    binary Triple_DES::pc1_permutation(binary key)
    {
        binary perm_key = "";
        for (int i = 0; i < 56; i++) // 56 is the size of pc1
        {
            // Running key through pc1 table
            perm_key.push_back(key[pc1[i] - 1]);
        }

        return perm_key;
    }

    binary Triple_DES::left_shift(binary input)
    {
        binary shifted = "";
        for (int i = 1; i < input.size(); i++)
        {
            // shifts each character to the left
            shifted.push_back(input[i]);
        }
        // shifts the first character to the back
        shifted.push_back(input[0]);

        return shifted;
    }

    binary Triple_DES::pc2_permutation(binary key)
    {
        binary sub_key = "";
        // Generates subkey
        for (int i = 0; i < 48; i++) // 48 is the size of pc2
        {
            // Running generated key through pc2 table
            sub_key.push_back(key[pc2[i] - 1]);
        }

        return sub_key;
    }


    //*Encryption/Decryption
    void Triple_DES::encrypt()
    {

    }

    void Triple_DES::decrypt()
    {

    }

    void Triple_DES::encrypt_fromFile()
    {

    }

    void Triple_DES::encrypt_fromGeneration(const int &size)
    {

    }

    void Triple_DES::decrypt_fromFile()
    {

    }

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
    void Triple_DES::check_plain_text()
    {

    }

    void Triple_DES::write_Private_Key_toFile()
    {
        ofstream fout;

        // Write private key to a file
        fout.open("local_storage/3DES_Private_Key.txt", ios::out);
        fout << "key 1: " << key_1 << endl;
        fout << "key 2: " << key_2 << endl;
        fout << "key 3: " << key_3 << endl;
        fout.close();
    }

    void Triple_DES::write_Plain_Text_toFile()
    {

    }

    void Triple_DES::write_Cipher_Text_toFile()
    {

    }
}//end Triple_DES_HB