#include <ctime>
#include <chrono>
#include "binary.h"
#include "binary.cpp"
#include "RSA.h"
#include "RSA.cpp"
#include "Triple_DES.h"
#include "Triple_DES.cpp"

using namespace std;
using namespace binary_HB;
using namespace RSA_HB;
using namespace Triple_DES_HB;

int main()
{
    
    //Test time
    auto begin = chrono::high_resolution_clock::now();

    //Set seed for random numbers
    srand(time(NULL));

    //Public has public key
    //Sender send 3DES keys after encrypting them
    RSA PublicRSA(32), SenderRSA;
    /*
    Triple_DES PublicDES, SenderDES;

    //Sender generates 3DES private key and sends it to RSA
    SenderDES.generate_private_key();
    binary pt = "";
    pt.append(SenderDES.get_binary_key_1());
    pt.append(SenderDES.get_binary_key_2());
    pt.append(SenderDES.get_binary_key_3());

    ofstream fout;

    // Write private key to RSA pt file
    fout.open("local_storage/RSA_Plain_Text.txt", ios::out);
    fout << pt;
    fout.close();

    //Sender encrypts 3DES key with RSA and sends the cipher text
    SenderRSA.encrypt_fromFile();
    */
    //Public decrypts sent 3DES key and puts it to pt
    PublicRSA.decrypt_fromFile();

    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    printf("\n\nTime measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);
    
    return 0;
}