#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){int bigger(int x, int y){if(x>y){return x;}else{return y;}} return bigger(19,44);}"
