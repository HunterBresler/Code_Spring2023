//*RSA Implementation file
#include "RSA.h"

using namespace std;

namespace RSA_HB
{
    //*Constructors
    RSA::RSA()
    {
        
    }

    RSA::RSA(int size)
    {
        encrypt_fromGeneration(size);
    }

    //* Getter/"Setter" Functions
    void RSA::get_Public_Key_fromFile()
    {
        ifstream fin;

        string line;
        fin.open("unsecure_channel/RSA_Public_Key.txt");

        // Get n from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        n = line;

        // Get e from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2);
        e = line;

        fin.close();
    }

    void RSA::get_Private_Key_fromFile()
    {
        ifstream fin;

        string line;
        fin.open("local_storage/RSA_Private_Key.txt");

        // Get private key from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        d = line;

        // Get p from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        p = line;

        // Get q from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        q = line;
        
        // Calculate phi
        phi = (p - '1') * (q - '1');

        fin.close();
    }

    void RSA::get_Plain_Text_fromFile()
    {
        ifstream fin;

        //binary block("");
        string line;
        fin.open("local_storage/RSA_Plain_Text.txt");

        // Get plain text from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        plain_text = line;

        /*
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
        */

        fin.close();
    }

    void RSA::get_Cipher_Text_fromFile()
    {
        ifstream fin;

        //binary block("");
        string line;
        fin.open("unsecure_channel/RSA_Cipher_Text.txt");

        // Get cipher text from file
        getline(fin, line);
        line = line.substr(line.find(": ") + 2); // increment to cut out the ": "
        cipher_text = line;

        /*
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
        */

        fin.close();
    }

    void RSA::generate_RSA_Primes(const int &size)
    {
        p = generatePrime(size);
        q = generatePrime(size);
    }

    void RSA::generate_Keys()
    {
        // Generate phi (needed for e and d)
        phi = (p - '1') * (q - '1');

        // Generate public key
        n = p * q;
        generate_e();

        // Generate private key
        generate_d();

        // Write keys to file
        write_Private_Key_toFile();
        write_Public_Key_toFile();
    }

    //*Encryption/Decription
    void RSA::encryption()
    {
        cipher_text = ModExpo(plain_text, e, n);
    }

    void RSA::decryption()
    {
        plain_text = ModExpo(cipher_text, d, n);
    }

    void RSA::encrypt_fromFile()
    {
        get_Public_Key_fromFile();
        get_Plain_Text_fromFile();
        encryption();
        write_Cipher_Text_toFile();
    }

    void RSA::encrypt_fromGeneration(const int& size)
    {
        generate_RSA_Primes(size);
        get_Plain_Text_fromFile();
        generate_Keys();
        encryption();
        write_Cipher_Text_toFile();
    }

    void RSA::decrypt_fromFile()
    {
        get_Private_Key_fromFile();
        get_Public_Key_fromFile();
        get_Cipher_Text_fromFile();
        decryption();
        write_Plain_Text_toFile();
    }


    //*Helper functions
    void RSA::generate_e()
    {
        do
        {
            e = getRandom('1', phi);
        } while (gcd(e, phi) != '1');
    }

    void RSA::generate_d()
    {
        binary s, t;
        bool sB, tB;
        EEA_for_d(e, phi, s, t, sB, tB);
        
        if (sB == true)
        {
            d = phi - s;
        }
        else
        {
            generate_e();
            generate_d();
        }
    }   

    binary RSA::EEA_for_d(const binary& a, const binary& b, binary& s, binary& t, bool& sB, bool& tB)
    {
        if (b == '0')
        {
            s = '1';
            t = '0';
            sB = false;
            tB = false;
            return a;
        }

        binary s1, t1, sub;
        binary c = EEA_for_d(b, a % b, s1, t1, sB, tB);
        s = t1;
        bool temp = sB;
        sB = tB;
        sub = t1 * (a / b);
        t = sub_neg(s1, (t1 * (a / b)), temp, tB);
        //cout << "\nS = " << s << " " << sB << " T = " << t << " " << tB << " sub = " << sub;
        return c;       
    }

    void RSA::write_Public_Key_toFile()
    {
        ofstream fout;

        // Write public key to a file
        fout.open("unsecure_channel/RSA_Public_Key.txt", ios::out);
        fout << "n: " << n << endl;
        fout << "e: " << e << endl;
        fout.close();
    }

    void RSA::write_Private_Key_toFile()
    {
        ofstream fout;

        // Write private key to a file
        fout.open("local_storage/RSA_Private_Key.txt", ios::out);
        fout << "d: " << d << endl;
        fout << "p: " << p << endl;
        fout << "q: " << q << endl;
        fout.close();
    }

    void RSA::write_Plain_Text_toFile()
    {
        ofstream fout;

        // Write plain text to a file
        fout.open("local_storage/RSA_Plain_Text.txt", ios::out);
        fout << "Plain Text: " << plain_text;

        /*
        // Loop through plain_text and print all of the blocks
        for (binary i : plain_text)
        {
            fout << i;
        }

        fout << endl;
        */

        fout.close();
    }

    void RSA::write_Plain_Text_to_3DES_Key()
    {
        ofstream fout;

        // Write plain text to a file
        fout.open("local_storage/3DES_Private_Key.txt", ios::out);
        fout << "key1: " << plain_text.substr(0, 64);
        fout << "key2: " << plain_text.substr(64, 128);
        fout << "key3: " << plain_text.substr(128, 192);
        fout.close();
    }

    void RSA::write_Cipher_Text_toFile()
    {
        ofstream fout;

        // Write cipher text to a file
        fout.open("unsecure_channel/RSA_Cipher_Text.txt", ios::out);
        fout << "Cipher Text: " << cipher_text;

        /*
        // Loop through cipher_text and print all of the blocks
        for (binary i : cipher_text)
        {
            fout << i;
        }

        fout << endl;
        */

        fout.close();
    }
} // end RSA_HB