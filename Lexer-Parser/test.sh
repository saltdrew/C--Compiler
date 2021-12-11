#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){int x;x=8; return x;}"
