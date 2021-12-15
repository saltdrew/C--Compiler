#!/bin/bash
rm mycc;
make
./mycc <<< "
            int main(void){
                function twice (function f) {
                    int g( int x) {return f(f(x));}
                    return g;
                }
                int double(int x){return x+x;}
                int quadruple = twice(double);
                return quadruple(2);
            }"
