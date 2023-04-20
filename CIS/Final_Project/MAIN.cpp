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

    //Receiver has RSA private key
    //Sender send 3DES keys after encrypting them
    RSA ReceiverRSA(64), SenderRSA;
    Triple_DES RevceiverDES, SenderDES;

    //Sender generates 3DES private key and sends it to RSA
    //SenderDES.generate_private_key();
    SenderDES.get_Private_Key_fromFile();
    binary pt = "";
    pt.append(SenderDES.get_binary_key_1());
    //pt.append(SenderDES.get_binary_key_2());
    //pt.append(SenderDES.get_binary_key_3());

    ofstream fout;

    // Write private key to RSA pt file
    fout.open("local_storage/RSA_Plain_Text.txt", ios::out);
    fout << pt;
    fout.close();

    //Sender encrypts 3DES key with RSA and sends the cipher text
    SenderRSA.encrypt_fromFile();

    //Public decrypts sent 3DES key and puts it to pt
    ReceiverRSA.decrypt_fromFile();

    binary a("11110"), b("110010");
    binary s, t;
    bool s1 = false, t1 = false;
    binary gcdd = ReceiverRSA.EEA_for_d(a, b, s, t, s1, t1);
    cout << "\nGCD = " << gcdd << " S = " << s << " " << s1 << " T = " << t << " " << t1;

    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    printf("\n\nTime measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);
    
    return 0;
}