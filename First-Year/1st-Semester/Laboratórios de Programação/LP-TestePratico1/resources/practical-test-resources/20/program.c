#include<stdio.h>

void warming(){
  int i, a;
  int j = 0x82ff22ff;
  for(i = 0; i < 10000000; i++){
    a = a + j;
    j--;
  }
}

void function1(){
  int i, a;
  int j = 0x82ff22ff;
  for(i = 0; i < 10000000; i++){
    a = a ^ j;
    j--;
  }
}

void function2(){
  int i, a;
  int j = 0x82ff22ff;
  for(i = 0; i < 10000000; i++){
    a = a * j;
    j--;
  }
}

void function3(){
  int i, a;
  int j = 0x82ff22ff;
  for(i = 0; i < 10000000; i++){
    a = a / j;
    j--;
  }
}

void main(){
  warming();
  function1();
  function2();
  function3();
}
