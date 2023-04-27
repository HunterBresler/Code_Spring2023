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
    RSA ReceiverRSA, SenderRSA;
    Triple_DES RevceiverDES, SenderDES;

    //ReceiverRSA.generate_RSA_Primes(256);
    //ReceiverRSA.generate_Keys();
    //SenderDES.generate_private_key();
    //SenderDES.write_Private_Key_toRSA();

    SenderRSA.encrypt_fromFile();

    ReceiverRSA.decrypt_fromFile();
    ReceiverRSA.write_Plain_Text_to_3DES_Key();

    RevceiverDES.encrypt_fromFile();
    SenderDES.decrypt_fromFile();

    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    printf("\n\nTime measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);
    
    return 0;
}