//*Header file for ELGAMAL class
#ifndef ELGAMAL_H
#define ELGAMAL_H

class ELGAMAL
{

    private:
        int prime;
        int generator;
        int gen_powA;
        int private_key;

    public:
        //*Constructors
        ELGAMAL();

        //* Getter/Setter Functions
        void getPublicKey();
        void setPrime();
        void setGenerator();
        void setGen_PowA();

        //*Calc Functions
        int ModExpo(int a, int n, int k);


};

#endif