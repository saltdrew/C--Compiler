#!/bin/bash
make
./mycc <<< "int main(void){return (5+1);}"
