#!/bin/bash
rm mycc;
make
if ./mycc <<< "int main(void){return 7;}" | grep -q '7'; then
    echo "direct return test passed"
else
    echo "direct return test FAILED"
fi

if ./mycc <<< "int main(void){int x;x=5;return x;}" | grep -q '5'; then
    echo "seperate declare and assign test passed"
else
    echo "seperate declare and assign test FAILED"
fi

if ./mycc <<< "int main(void){int x=5;return x;}" | grep -q '5'; then
    echo "declare/assignment combo test passed"
else
    echo "declare/assignment combo test FAILED"
fi

if ./mycc <<< "int main(void){int x=5; int y=4; return y+x;}" | grep -q '9'; then
    echo "multi variable assignment passed"
else
    echo "multi variable assignment test FAILED"
fi

if ./mycc <<< "int main(void){int x=3; int y=4; y=y+7;x=x+y; return y*x;}" | grep -q '154'; then
    echo "multi variable complex test passed"
else
    echo "multi variable complex test FAILED"
fi

if ./mycc <<< "int main(void){int x=3; int y=4; y=y==4; y=y!=x;}" | grep -q '1'; then
    echo "boolean result test passed"
else
    echo "boolean result test FAILED"
fi

if ./mycc <<< "int main(void){int x=5;if (x==5){return x*x;}}}" | grep -q '25'; then
    echo "if only test passed"
else
    echo "if only test FAILED"
fi

if ./mycc <<< "int main(void){int x=5;if (x==6){return x*x;}else{return x+x;}}}" | grep -q '25'; then
    echo "if/else test passed"
else
    echo "if/else test FAILED"
fi

if ./mycc <<< "int main(void){int add(int x,int y){return x+y;}return add(2,2);}" | grep -q '4'; then
    echo "one function test passed"
else
    echo "one function test FAILED"
fi

if ./mycc <<< "int main(void){int double(int x){return x+x;}int add(int x,int y){return x+y;}return add(double(2),double(2));}" | grep -q '8'; then
    echo "two functions (both called by main) test passed"
else
    echo "two functions (both called by main) test FAILED"
fi

if ./mycc <<<"int main(void){
                int factorial(int x){
                    if(x==0){return 1;}
                else{return x*factorial(x-1);}
                }
                return factorial(10);
            }" | grep -q '3628800'; then
    echo "recursive factorial test passed"
else
    echo "recursive factorial test FAILED"
fi
