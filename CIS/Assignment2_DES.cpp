/*
    Author: Hunter Bresler
    Date: 2/24/2023
    Assignment2: DES Implementation
*/

#include <iostream>
#include <vector>


using namespace std;


class KEY 
{
    private:

        //*Declare member variables
        int var1;
        int var2;
        int var3;
        int var4;
        int var5;

    public:
        //*Constructor
        KEY();

        //*Getter Functions
        int get_var1();
        int get_var2();
        int get_var3();
        int get_var4();
        int get_var5();

        //*Setter Functions
        void set_var1(int var1);
        void set_var2(int var2);
        void set_var3(int var3);
        void set_var4(int var4);
        void set_var5(int var5);
};




//*MAIN
int main(){
    return 0;
}


/*
    !This is the list of functions in the KEY Class 
    !The functions will be folded below
*/ 
//*Constructor
KEY::KEY()
{

}

//*Getter Functions
int KEY::get_var1() {
    return var1;
}

int KEY::get_var2() {
    return var2;
}

int KEY::get_var3() {
    return var3;
}

int KEY::get_var4() {
    return var4;
}

int KEY::get_var5() {
    return var5;
}

//*Setter Functions
void KEY::set_var1(int new_var1) {
    var1 = new_var1;
}

void KEY::set_var2(int new_var2) {
    var2 = new_var2;
}

void KEY::set_var3(int new_var3) {
    var3 = new_var3;
}

void KEY::set_var4(int new_var4) {
    var4 = new_var4;
}

void KEY::set_var5(int new_var5) {
    var5 = new_var5;
}
