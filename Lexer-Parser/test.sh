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

if ./mycc <<< "int main(void){int x=3; int y=4; y=y+7;x=x+y return y*x;}" | grep -q '154'; then
    echo "multi variable complex test passed"
else
    echo "multi variable complex test FAILED"
fi
