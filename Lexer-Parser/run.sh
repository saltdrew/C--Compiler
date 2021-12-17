#!/bin/bash
rm mycc;
make
./mycc <<< "

int main(void){
    int x = 10;
    int f(void){return x;}
    int g(void){int x = 20; return f();}
    return g();
}
"
