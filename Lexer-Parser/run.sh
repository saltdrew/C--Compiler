#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){int x=5;if (x==6){return x*x;}}}"
