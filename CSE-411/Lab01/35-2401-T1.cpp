#include <bits/stdc++.h>
using namespace std;

void encrypt(string filepath, int key)
{
   ifstream inputFile(filepath);

   if (!inputFile.is_open())
   {
      cerr << "Error opening file: "<< filepath << endl;
      return;
   }

   char ch;
   ofstream outputFile("encrypt.txt");

   if (!outputFile.is_open())
   {
      cerr << "Error creating file: " << endl;
      return;
   }
   while (inputFile.get(ch))
   {

      if (ch == ' ')
         outputFile << " ";
      else
      {
         if (ch + key <= 'z' or ch + key <= 'Z')
         {
            outputFile << char(ch + key);
         }
         else
         {
            outputFile << char(ch - 26 + key);
         }
      }
   }
}

void decrypt(string filepath, int key)
{
   ifstream inputFile(filepath);

   if (!inputFile.is_open())
   {
      cerr << "Error opening file: input.txt" << endl;
      return;
   }

   char ch;
   ofstream outputFile("Original.txt");

   if (!outputFile.is_open())
   {
      cerr << "Error creating file: " << endl;
      return;
   }
   while (inputFile.get(ch))
   {

      if (ch == ' ')
         outputFile << " ";
      else
      {
         if (ch - key >= 'a' or ch - key >= 'A')
         {
            outputFile << char(ch - key);
         }
         else
         {
            outputFile << char(ch + 26 - key);
         }
      }
   }
}

int main()
{
   int key;
   string filepath;

   cout << "Enter your choice: \n1.Encrypt\n2.Decrypt\n3.Exit\n";
   int choice;
   cin >> choice;
   while (choice)
   {
      if (choice == 1)
      {
         cout << "Enter Key value ";
         cin >> key;

         cout << "Enter file name:";
         cin >> filepath;

         encrypt(filepath, key);
      }
      else if (choice == 2)
      {
         cout << "Enter Key value ";
         cin >> key;

         cout << "Enter file name:";
         cin >> filepath;

         decrypt(filepath, key);
      }
      else
         break;
      cout << "Enter your choice: \n1.Encrypt\n2.Decrypt\n3.Exit\n";
      cin >> choice;
   }

   return 0;
}