#!/bin/bash
rm mycc;
make
./mycc <<< "int fact(int x){if (x<1){return 1;}else{return x*fact(x-1);}}int f(void){fact(11);} int main(void){return f();}"
