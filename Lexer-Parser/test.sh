#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){int x=5; return x;}"
