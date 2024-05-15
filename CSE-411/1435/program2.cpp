#include<bits/stdc++.h>
#include"structures.h"
using namespace std;


string padding(string s){
  stringstream givenString;
    for(int i=0;i<s.size();i++)
    {
        givenString<<bitset<8>(s[i]);
    }

    string originalMessage;
    originalMessage=givenString.str();
    int originalLength=originalMessage.size();
    int paddedLength;
    int modValue=originalLength%1024;

    if((1024-modValue)>128)
    {
        paddedLength=1024-modValue;
    }
    else
    {
        paddedLength=2048-modValue;
    }

    cout<<"Original message: "<<originalMessage<<"\n";
    originalMessage+='1';
    for(int i=0;i<paddedLength-129;i++)
    {
        originalMessage+='0';
    }

    cout<<"Padded message: "<<originalMessage<<"\n";

    string Size=bitset<128>(originalLength).to_string();
    originalMessage+=Size;
    cout<<"After add siz: "<<originalMessage<<endl;
  return originalMessage;
}

int sha(string input)
{
    freopen(input.c_str(),"r",stdin);
    string s, hash;
    getline(cin,s);
    cout<<s<<"\n";
    string originalmessage = padding(s);
    hash = sha512(originalmessage);
    cout<<"\nHash Value: "<<hash<<"\n";
    return 1;
}


int main()
{
    puts("----------------------SHA512--------------------------");
    puts("SHA : ");
    if(sha("message1.txt"))
        cout<<"\nsha completed\n";
    else
        cout<<"not completed\n";


    return 0;


}