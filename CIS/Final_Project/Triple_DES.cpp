//*Implementation of Triple_DES 
#include "Triple_DES.h"

using namespace std;

namespace Triple_DES_HB
{
    //*Constructor
    Triple_DES::Triple_DES()
    {
        plain_text = {};
        cipher_text = {};
    }

    //*Getter/Setter functions
    binary Triple_DES::get_binary_key_1()
    {
        return key_1;
    }

    binary Triple_DES::get_binary_key_2()
    {
        return key_2;
    }

    binary Triple_DES::get_binary_key_3()
    {
        return key_3;
    }

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

        // Clear plain text
        plain_text = {};

        binary block("");
        char next;
        fin.open("local_storage/3DES_Plain_Text.txt");

        
        while (fin.eof() != true)
        {
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                next = fin.get();

                if (fin.eof())
                {
                    if (i == 0)
                    {
                        break;
                    }

                    block = block.PadLeft(BLOCK_SIZE - block.size());
                    break;
                }

                if (next == ' ')
                {
                    i--;
                }
                else
                {
                    // Add next read char
                    block.push_back(next);
                }
            }

            // Prevent empty blocks
            if (block == "")
            {
                break;
            }

            block.check_binary();
            plain_text.push_back(block);
            block = "";
        }

        fin.close();
    }

    void Triple_DES::get_Cipher_Text_fromFile()
    {
        ifstream fin;

        // Clear cipher text
        cipher_text = {};

        binary block("");
        char next;
        fin.open("unsecure_channel/3DES_Cipher_Text.txt");

        
        while (fin.eof() != true)
        {
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                next = fin.get();

                if (fin.eof())
                {
                    if (i == 0)
                    {
                        break;
                    }

                    block = block.PadLeft(BLOCK_SIZE - block.size());
                    break;
                }
                
                if (next == ' ')
                {
                    i--;
                }
                else
                {
                    // Add next read char
                    block.push_back(next);
                }
            }

            // Prevent empty blocks
            if (block == "")
            {
                break;
            }
            
            block.check_binary();
            cipher_text.push_back(block);
            block = "";
        }   

        fin.close();
    }

    //*Key generation
    void Triple_DES::generate_private_key()
    {
        key_1 = generate_key();
        key_2 = generate_key();
        key_3 = generate_key();

        write_Private_Key_toFile();
    }

    binary Triple_DES::generate_key()
    {
        binary result = getRandom(MIN_KEY, MAX_KEY);
        result.PadLeft(BLOCK_SIZE - result.size());
        return result;
    }

    void Triple_DES::generate_all_sub_keys()
    {

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
        //Reset cipher_text
        cipher_text = {};

        int index = 0; // keeps track of index for 2nd and 3rd keys
        binary left_half, right_half, modified_half;

        //First 
        for (binary block: plain_text)
        {
            // Step 1: initial permutation
            block = initial_permutation(block);

            // Step 2: split the result in half
            left_half = block.substr(0, 32);
            right_half = block.substr(32, 32);

            // Step 3: run 16 rounds of encryption
            for (int i = 0; i < 16; i++) // 16 is the amount of rounds of encryption to run
            {
                // Create modified half to encrypt with
                modified_half = right_half;

                // Step 3.1: run modified half through expansion table 32->48 bit
                modified_half = expansion(modified_half);
                // Step 3.2: modified_half = modified half Xor this round's corresponding sub key
                modified_half = Xor(modified_half, sub_keys_1[i]);
                // Step 3.3: run result through sub boxes 48->32 bit
                modified_half = sub_box(modified_half);
                // Step 3.4: sub box permutation
                modified_half = sub_permutation(modified_half);
                // Step 3.5: left_half = modified half Xor left half
                left_half = Xor(modified_half, left_half);
                // Step 3.6: swap right and left halves
                swap_halves(left_half, right_half);
            }

            // Step 4: inverse permutation of the combined halves
            // Swap halves once after encryption by combining backwards
            block = right_half;
            block.append(left_half);
            cipher_text.push_back(inverse_permutation(block));
            
        }

        //Second
        for (binary block: cipher_text)
        {
            // Step 1: initial permutation
            block = initial_permutation(block);

            // Step 2: split the result in half
            left_half = block.substr(0, 32);
            right_half = block.substr(32, 32);

            // Step 3: run 16 rounds of encryption
            for (int i = 0; i < 16; i++) // 16 is the amount of rounds of encryption to run
            {
                // Create modified half to encrypt with
                modified_half = right_half;

                // Step 3.1: run modified half through expansion table 32->48 bit
                modified_half = expansion(modified_half);
                // Step 3.2: modified_half = modified half Xor this round's corresponding sub key
                modified_half = Xor(modified_half, sub_keys_2[i]);
                // Step 3.3: run result through sub boxes 48->32 bit
                modified_half = sub_box(modified_half);
                // Step 3.4: sub box permutation
                modified_half = sub_permutation(modified_half);
                // Step 3.5: left_half = modified half Xor left half
                left_half = Xor(modified_half, left_half);
                // Step 3.6: swap right and left halves
                swap_halves(left_half, right_half);
            }

            // Step 4: inverse permutation of the combined halves
            // Swap halves once after encryption by combining backwards
            block = right_half;
            block.append(left_half);
            cipher_text[index] = inverse_permutation(block);

            // Increase index
            index++;
        }

        // reset index
        index = 0;

        //Third
        for (binary block: cipher_text)
        {
            // Step 1: initial permutation
            block = initial_permutation(block);

            // Step 2: split the result in half
            left_half = block.substr(0, 32);
            right_half = block.substr(32, 32);

            // Step 3: run 16 rounds of encryption
            for (int i = 0; i < 16; i++) // 16 is the amount of rounds of encryption to run
            {
                // Create modified half to encrypt with
                modified_half = right_half;

                // Step 3.1: run modified half through expansion table 32->48 bit
                modified_half = expansion(modified_half);
                // Step 3.2: modified_half = modified half Xor this round's corresponding sub key
                modified_half = Xor(modified_half, sub_keys_3[i]);
                // Step 3.3: run result through sub boxes 48->32 bit
                modified_half = sub_box(modified_half);
                // Step 3.4: sub box permutation
                modified_half = sub_permutation(modified_half);
                // Step 3.5: left_half = modified half Xor left half
                left_half = Xor(modified_half, left_half);
                // Step 3.6: swap right and left halves
                swap_halves(left_half, right_half);
            }

            // Step 4: inverse permutation of the combined halves
            // Swap halves once after encryption by combining backwards
            block = right_half;
            block.append(left_half);
            cipher_text[index] = inverse_permutation(block);

            // Increase index
            index++;
        }
    }

    void Triple_DES::decrypt()
    {
        // Invert keys and plaintext for DES to decrypt
        invert_sub_keys();
        vector<binary> temp = cipher_text;
        plain_text = cipher_text;

        // Encrypt() now decrypts, assigning the plaintext to ciphertext, so swap them
        // temp keeps the value of the original ciphertext from encryption
        encrypt();
        plain_text = cipher_text;
        cipher_text = temp;

        //binary block = plain_text[plain_text.size() - 1];
        //block.removeLeadingZeros();
        //plain_text[plain_text.size() - 1] = block;
        

        //invert sub keys again so they are back to normal
        invert_sub_keys();
    }

    void Triple_DES::encrypt_fromFile()
    {
        get_Plain_Text_fromFile();
        get_Private_Key_fromFile();
        generate_all_sub_keys();
        encrypt();
        write_Cipher_Text_toFile();
    }

    void Triple_DES::encrypt_fromGeneration()
    {
        get_Plain_Text_fromFile();
        generate_private_key();
        generate_all_sub_keys();
        encrypt();
        write_Cipher_Text_toFile();
    }

    void Triple_DES::decrypt_fromFile()
    {
        get_Cipher_Text_fromFile();
        get_Private_Key_fromFile();
        generate_all_sub_keys();
        decrypt();
        write_Plain_Text_toFile();
    }

    //*Helper functions
    void Triple_DES::invert_sub_keys()
    {
        //Invert the sub keys' order and sub_keys order
        binary temp, temp2;

        //Invert and swap sub_keys_1 and sub_keys_3
        for (int i = 0; i < 8; i++) // 8 is how many pairs of sub keys we have to swap
        {
            temp = sub_keys_1[i];
            temp2 = sub_keys_3[i];
            sub_keys_1[i] = sub_keys_3[15 - i]; // 15 is the last index of sub keys
            sub_keys_3[i] = sub_keys_1[15 - i]; // 15 is the last index of sub keys
            sub_keys_1[15 - i] = temp2;
            sub_keys_3[15 - i] = temp;
        }

        //Invert sub_keys2
        for (int i = 0; i < 8; i++) // 8 is how many pairs of sub keys we have to swap
        {
            temp = sub_keys_2[i];
            sub_keys_2[i] = sub_keys_2[15 - i]; // 15 is the last index of sub keys
            sub_keys_2[15 - i] = temp;
        }

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
        ofstream fout;

        // Write plain text to a file
        fout.open("local_storage/3DES_Plain_Text.txt", ios::out);

        // Loop through plain_text and print all of the blocks
        for (binary i : plain_text)
        {
            fout << i;
        }   

        fout.close();
    }

    void Triple_DES::write_Cipher_Text_toFile()
    {
        ofstream fout;

        // Write plain text to a file
        fout.open("unsecure_channel/3DES_Cipher_Text.txt", ios::out);

        // Loop through plain_text and print all of the blocks
        for (binary i : cipher_text)
        {
            fout << i;
        }   

        fout.close();
    }

    //*3DES Algorithm functions
    binary initial_permutation(binary text)
    {
        // Permutate plaintext with initial permutation table
        binary perm = "";
        for (int i = 0; i < 64; i++) // 64 is the size of plain text
        {
            perm.push_back(text[initial_perm[i] - 1]);
        }

        return perm;
    }

    binary expansion(binary modified_half)
    {
        // Expand modified half for Xor
        binary expanded = "";
        for (int i = 0; i < 48; i++) // 48 is the size of the expansion table
        {
            expanded.push_back(modified_half[expansion_table[i] - 1]);
        };

        return expanded;
    }

    binary sub_box(binary modified_half)
    {
        binary result = "";
        for (int i = 0; i < 8; i++) // 8 is how many sub boxes it runs through
        {
            // Each sub box takes every 6 bit piece of modified_half
            // And transforms it into a 4 bit piece, which it appends to result
            binary coordinate = modified_half.substr(i * 6, 6);

            // Combine the msb and lsb to get the row# in binary
            binary bRow = coordinate.substr(0, 1);
            bRow.append(coordinate.substr(5, 1));
            int row = binary_to_decimal(bRow);

            // The middle four digits are the column in binary
            int col = binary_to_decimal(coordinate.substr(1, 4));

            // Append the binary representation of the corresponding sub box int to result
            result.append(decimal_to_binary(sub_boxes[i][row][col]));
        }

        return result;
    }

    binary sub_permutation(binary modified_half)
    {
        // Permutate modified half after sub box
        binary perm = "";
        for (int i = 0; i < 32; i++) // 32 is the size of sub_perm
        {
            perm.push_back(modified_half[sub_perm[i] - 1]);
        }

        return perm;
    }

    binary inverse_permutation(binary combined)
    {
        // Permutate fully encrypted text into cipher text
        binary result = "";
        for (int i = 0; i < 64; i++) // 64 is the size of inverse perm
        {
            result.push_back(combined[inverse_perm[i] - 1]);
        }

        return result;
    }

    //*DES Calc functions
    int binary_to_decimal(const binary &num)
    {
        // read binary right to left and add 2^i to result if the read digit is '1'
        int result = 0;
        for (int i = 0; i < num.size(); i++)
        {
            // Math to read from right to left
            if (num[num.size() - (i + 1)] == '1')
            {
                result += pow(2, i);
            }
        }

        return result;
    }

    binary decimal_to_binary(int decimal)
    {
        // Get the remainder and add it as the right most digit of binary
        binary bNum = "";
        while (decimal != 0)
        {
            bNum.insert(bNum.begin(), (decimal % 2 == 0) ? '0' : '1'); 
            decimal /= 2;
        }

        // Make sure binary is 4 bits in length
        while (bNum.size() < 4)
        {
            bNum.insert(bNum.begin(), '0');
        }

        binary num(bNum);
        return num;
    }

    void swap_halves(binary& left, binary& right)
    {
        binary temp = left;
        left = right;
        right = temp;
    }

}//end Triple_DES_HB