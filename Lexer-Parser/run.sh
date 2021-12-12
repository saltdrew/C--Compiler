#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){int x=3; int y=4; y=y+7;x=x+y; return y*x;}"
