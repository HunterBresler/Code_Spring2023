#include <iostream>
#include <string>
#include "binary.h"
#include "binary.cpp"

using namespace std;

int main()
{
    binary num1("100"), num2("11");
    binary sum = num1 - num2;
    cout << "\nSum: " << sum;

    return 0;
}