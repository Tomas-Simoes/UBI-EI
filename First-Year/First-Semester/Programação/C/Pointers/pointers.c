#include<stdio.h>

int main() {
  int x = 4;
  int * pX = &x; // set's a pointer pointing to an adress of the variable x 
  int y = *pX; // set's a variable with the value of what the pointer is pointing to 
}