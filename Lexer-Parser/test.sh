#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){return (5+1);}"
