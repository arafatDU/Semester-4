#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{
  printf("my process ID is %d\n", getpid());
  printf("my parent's process ID is %d\n", getppid());
  exit(0);
}