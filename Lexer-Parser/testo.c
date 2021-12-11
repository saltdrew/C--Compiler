#include <stdlib.h>
#include <stdio.h>

typedef union VALUE {
	int integer;
	int boolean;
	char* string;
}VALUE;

VALUE *somefunc(void){
    VALUE *result = (VALUE*)malloc(sizeof(VALUE));
    result=0;
    return result;
}

int main(void){
    VALUE *result = somefunc();
    if (result==NULL){
        printf("here\n");
    }else{
        printf("number: %d\n", *(int*)somefunc());
    }



}
