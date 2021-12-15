#!/bin/bash
rm mycc;
make
./mycc <<< "int main(void){
                int factorial(int x){
                    if(x==0){return 1;}
                else{return x*factorial(x-1);}
                }
                return factorial(10);
            }"
