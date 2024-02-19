#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
int main() 
{
  printf("my process ID is %d\n", getpid());
  exit(0);
}