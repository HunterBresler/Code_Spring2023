/*
    Author: Hunter Bresler
    Date: 2/24/2023
    Assignment2: DES Implementation
*/

#include <iostream>
#include <vector>


using namespace std;


//*Function Definitions
void GetInput(string* plainText, string* key)
{
    //Get Plain Text
    cout << "\nEnter the message you want encoded:\n\t";
    cin >> *plainText;

    //Get Master Key
    cout << "\nEnter the master key:\n\t";
    cin >> *key;
}



//*Turn the plain text into binary
void PlainTextToBinary(string PlainText, string* ptBINARY)
{

}



//*MAIN
int main(){

    //Get Plain Text and Key
    string PlainText, ptBINARY, KeyMASTER;
    GetInput(&PlainText, &KeyMASTER);
    //Format Plain Text to Binary
    PlainTextToBinary(PlainText, &ptBINARY);


    return 0;
}