#include<bits/stdc++.h>
#include"structures.h"
using namespace std;

int main()
{
    /*
    puts("------------ aes --------------------");
    string file="input.txt";
    if(CTREN(file))
        cout<<"encryption completed\n";
    else
        cout<<"not completed\n";

    string file1="message.aes";
    if(CTRDE(file1))
        cout<<"decryption completed\n";
    else
        cout<<"not completed\n";

    // here
    puts("------------------------- aes functioanlity-----------------------");
    puts("subbyte: ");
    unsigned char stateA[16];
    string st="arafathussainzzz";
    puts("input in hex: ");
    for(int i=0; i<16; i++)
    {
        stateA[i]=st[i];
        cout << hex << (int) stateA[i];
        cout << " ";
    }
    puts("");
    SubBytes(stateA);
    puts("output after subbyte: ");
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");
    // dangerous part of my work!!
    // stage : shiftrows  4 4 kore dekhabo
    puts("Shiftrows: ");
    for(int i=0; i<16; i++)
    {
        if(i%4==0) puts("");
        cout << hex << (int) stateA[i];
        cout << " ";
    }
    puts("");
    ShiftRows(stateA);
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");

    // stage : MixColumn
    puts("MixColumn: ");
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");
    MixColumns(stateA);
    puts("after : ");
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");

    // stage : add round key lagbe na apatoto
    puts("add round key: before");
    for (int i = 0; i < 16; i++)
    {
        cout << hex << (int) stateA [i];
        cout << " ";
    }
    puts("");
    //AddRoundKey(stateA);
    // now look for inv
    puts("inverse mix column");
    InverseMixColumns(stateA);
    puts("after : ");
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");

    puts("inverse shift rows:");
    InvShiftRows(stateA);
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");

    puts("inverse sub byte: ");
    InvSubBytes(stateA);
    puts("output after subbyte: ");
    for (int i = 0; i < 16; i++)
    {
        cout<<hex<<(int)stateA[i]<<" ";
    }
    puts("");
    */

    

    puts("----------------------sha--------------------------");
    puts("sha : ");
    if(sha())
        cout<<"\nsha completed\n";
    else
        cout<<"not completed\n";

    puts("------------------------------sha functionality--------------------------");
    puts("sumA func");
    unsigned long long int a=0x5678ef4578dfae45;
    unsigned long long int b=0x3678ff4878bfae45;
    unsigned long long int c=0x2687ef4578cfae45;
    cout<<sumA(a)<<"\n";

    puts("sumE func");
    cout<<sumE(a)<<"\n";

    puts("sigma0");
    cout<<sigma0(a)<<"\n";

    puts("sigma1");
    cout<<sigma1(a)<<"\n";

    puts("maj");
    cout<<maj(a,b,c)<<"\n";

    puts("ch");
    cout<<ch(a,b,c)<<"\n";

    puts("rotr");
    cout<<ROTR(a,23)<<"\n";



    // extras
    /* string text="input.txt";
    string textk="message.aes";
    if(CBCEN(text))
        cout<<"encryption completed\n";
    else
        cout<<"not completed\n";
    if(CBCDE(textk))
        cout<<"decryption completed\n";
    else
        cout<<"not completed\n";
    
    //unsigned long long int a=64;
    //getchar();
    //---------------------rsa ---------------------------
    int p,q;
    while(1)
    {
        puts("enter two distinct prime numbers. p & q");
        cin>>p>>q;

        if(p==q) puts("they are same. they must be different.");
        else if(!isPrime(p)) puts("p is not prime");
        else if(!isPrime(q)) puts("q is not prime");
        else if(isPrime(p) and isPrime(q)) break;
    }

    int n=p*q;
    int phiN=(p-1)*(q-1);
    cout<<"n= "<<n<<"\nphi n= "<<phiN<<"\n";
    int e;
    while(1)
    {
        cout<<"choose an e (public key component) such that 1<e<phi n and e and phi n are coprime\n";
        cin>>e;
        if(__gcd(e,phiN)!=1) puts("e and phi n must be coprime");
        else if(e>=phiN) puts("choose e such that 1<e<phi n");
        else break;
    }

    if(rsa(e,phiN,n))
    cout<<"rsa completed\n";

    //-------------------- rsa functionality ------------------------------
    cout<<BigMod(3,103,7)<<"\n";
    cout<<mulInv(3,7);

    */
}