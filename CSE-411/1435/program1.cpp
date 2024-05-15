#include<bits/stdc++.h>
#include"structures.h"
using namespace std;

int CTREN(string input);
int CTRDE(string message);

int main()
{
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
    
    
    return 0;

    
}



int CTREN(string input)
{
    freopen(input.c_str(),"r",stdin);
    char message[1024];

    cout << "Enter the message to encrypt: ";
    cin.getline(message, sizeof(message));
    cout << message << endl;

    
    int originalLen = strlen((const char *)message);

    int paddedMessageLen = originalLen;

    if ((paddedMessageLen % 16) != 0)
    {
        paddedMessageLen = (paddedMessageLen / 16 + 1) * 16;
    }

    unsigned char * paddedMessage = new unsigned char[paddedMessageLen];


    for (int i = 0; i < paddedMessageLen; i++)
    {
        if (i >= originalLen)
        {
            paddedMessage[i]=0;
        }
        else
        {
            paddedMessage[i]= message[i];
        }

    }

    unsigned char * encryptedMessage = new unsigned char[paddedMessageLen];
    unsigned char * outputMessage = new unsigned char[paddedMessageLen];

    string str;
    ifstream infile;
    infile.open("keyfile.txt", ios::in | ios::binary);

    if (infile.is_open())
    {
        getline(infile, str); 
        infile.close();
    }

    else
        cout << "Unable to open file";

    istringstream hex_chars_stream(str);

    unsigned char key[16];
    int i = 0;
    unsigned int c;
    while (hex_chars_stream >> hex >> c)
    {
        key[i] = c;
        i++;
    }

    unsigned char expandedKey[176];

    KeyExpansion(key, expandedKey);
    string nonce="abcdzyxw";
    unsigned long long int ctr=1;

    for (int i = 0; i < paddedMessageLen; i += 16)
    {
        string in=nonce;
        string add=to_string(ctr);
        string ca;
        for(int j=0;j<8-add.size();j++)
        {
            ca+='0';
        }
        in+=ca;
        in+=add;
        cout<<in<<"\n";
        ctr++;
        unsigned char take[16];
        copy(in.begin(),in.end(),take);
        AESEncrypt(take, expandedKey,outputMessage+i);
        for(int j=0;j<16;j++)
        encryptedMessage[j+i]=outputMessage[i+j]^paddedMessage[i+j];

    }

    cout << "Encrypted message in hex:" << endl;
    for (int i = 0; i < paddedMessageLen; i++)
    {
        cout << hex << (int) encryptedMessage[i];
        cout << " ";
    }

    cout << endl;

    ofstream outfile;
    outfile.open("message.aes", ios::out | ios::binary);
    if (outfile.is_open())
    {
        outfile << encryptedMessage;
        outfile.close();
        cout << "Wrote encrypted message to file message.aes" << endl;
    }

    else
        cout << "Unable to open file";

    // Free memory
    delete[] paddedMessage;
    delete[] encryptedMessage;

    return 1;
}




int CTRDE(string message)
{
    string msgstr;
    ifstream infile;
    infile.open(message.c_str(), ios::in | ios::binary);

    if (infile.is_open())
    {
        getline(infile, msgstr); // The first line of file is the message
        cout << "Read in encrypted message from message.aes" << endl;
        infile.close();
    }

    else
        cout << "Unable to open file";

    char * msg = new char[msgstr.size()+1];

    strcpy(msg, msgstr.c_str());

    int n = strlen((const char*)msg);

    unsigned char * encryptedMessage = new unsigned char[n];

    for (int i = 0; i < n; i++)
    {
        encryptedMessage[i] = (unsigned char)msg[i];
    }

    // Free memory
    delete[] msg;


    string str;
    ifstream kinfile;
    kinfile.open("keyfile.txt", ios::in | ios::binary);

    if (kinfile.is_open())
    {
        getline(kinfile, str); // The first line of file should be the key
        kinfile.close();
    }

    else
        cout << "Unable to open file";

    istringstream hex_chars_stream(str);

    unsigned char key[16];
    int i = 0;
    unsigned int c;
    while (hex_chars_stream >> hex >> c)
    {
        key[i] = c;
        i++;
    }
    unsigned char * outputMessage = new unsigned char[n];
    int messageLen = strlen((const char *)encryptedMessage);
    unsigned char * decryptedMessage = new unsigned char[messageLen];

    unsigned char expandedKey[176];

    KeyExpansion(key, expandedKey);
    string nonce="abcdzyxw";
    unsigned long long int ctr=1;

    for (int i = 0; i < messageLen; i += 16)
    {
        string in=nonce;
        string add=to_string(ctr);
        string ca;
        for(int j=0;j<8-add.size();j++)
        {
            ca+='0';
        }
        in+=ca;
        in+=add;
        //cout<<in<<"\n";
        ctr++;
        unsigned char take[16];
        copy(in.begin(),in.end(),take);
        AESEncrypt(take, expandedKey,outputMessage+i);
        for(int j=0;j<16;j++)
        decryptedMessage[j+i]=outputMessage[i+j]^encryptedMessage[i+j];

    }

    cout << "Decrypted message in hex:" << endl;
    for (int i = 0; i < messageLen; i++)
    {
        cout << hex << (int)decryptedMessage[i];
        if((int)decryptedMessage[i]==0) {
                messageLen=i;
                break;
        }
        cout << " ";
    }
    cout << endl;

    cout << "Decrypted message: ";
    for (int i = 0; i <= messageLen; i++)
    {
        cout << decryptedMessage[i];
    }
    cout << endl;

   std::ofstream outfile;
outfile.open("output.txt");
if (outfile.is_open())
{
    outfile << decryptedMessage;
    outfile.close();
    std::cout << "Wrote decrypted message to file output.txt" << std::endl;
}
else
{
    std::cout << "Unable to open file";
}


    return 1;
}