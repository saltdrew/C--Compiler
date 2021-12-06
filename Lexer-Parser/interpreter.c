#include <stdio.h>
#include "C.tab.h"
#include "ctype.h"
#include "nodes.h"
#include <string.h>

union VALUE {
	int integer;
	int boolean;
	char* string;
}value;

union VALUE *walk(NODE *term){
	switch(term->type){
		case 'd':
			return walk(term->left);
		case 'D':
			return walk(term->right);
		case '+':
			value.integer= walk(term->left)->integer + walk(term->right)->integer;
			return &value;
    	case LEAF:
			TOKEN *token = (TOKEN*)(term->left);
    		value.integer = token->value;
        	return &value;
    	case RETURN:
			printf("return\n");
			printf("return node has type %d\n",term->type);
			printf("type of return's left node: %d\n",(term->left)->type);
			return walk(term->left);
		default:
			printf("defaulted in walk\n");
			value.integer=1;
			return &value;
    }
}
