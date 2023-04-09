#include <iostream>
#include <string>
#include "binary.h"
#include "binary.cpp"

using namespace std;

int main()
{
    binary base("1101"), expo("11"), modulo("111");
    binary res = ModExpo(base, expo, modulo);
    cout << "\nResult: " << res;

    return 0;
}