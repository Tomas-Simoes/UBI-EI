#include<stdio.h>

int f1(){
  printf("oi");
  return 1;
}

int f2(){
  printf("oi2");

  return 1;
}

int f3(){
    printf("oi3");

  return 1;
}

int f4(){
    printf("oi4");
  return 1;
}

void main(){
  int i, a;
  a = 0xffffffff;
  i = -a;
  if( i > 0 ){
    i = a & 0x7;
    if( i <= 6 )
      f1();
    else
      f2();
  }else{
    i = a & 0x7;
    if( i <= 6 )
      f3();
    else
      f4();
  }
}
