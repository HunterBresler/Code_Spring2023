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

    }

    binary Triple_DES::generate_key()
    {
        return getRandom(MIN_KEY, MAX_KEY);
    }

    void Triple_DES::generate_sub_keys()
    {

    }

    binary Triple_DES::pc1_permutation(binary key)
    {

    }

    binary Triple_DES::left_shift(binary input)
    {

    }

    binary Triple_DES::pc2_permutation(binary generated_key)
    {

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

    }

    void Triple_DES::write_Plain_Text_toFile()
    {

    }

    void Triple_DES::write_Cipher_Text_toFile()
    {

    }
}//end Triple_DES_HB