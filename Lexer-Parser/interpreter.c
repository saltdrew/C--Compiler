#include <stdio.h>
#include "C.tab.h"
#include "ctype.h"
#include "frame.h"
#include <string.h>

union VALUE {
	int integer;
	int boolean;
	char* string;
}value;


union VALUE *walk(NODE *term, TOKEN** env){
	printf("%d\n",lookup_token("size")->value);
	switch(term->type){
		case 'd':
			return walk(term->left,env);
		case 'D':
			return walk(term->right,env);
		case '+':
			value.integer= walk(term->left,env)->integer + walk(term->right,env)->integer;
			return &value;
    	case LEAF:
			TOKEN *token = (TOKEN*)(term->left);
			lookup_token()
    		value.integer = token->value;
        	return &value;
    	case RETURN:
			return walk(term->left,env);
		default:
			printf("defaulted in walk\n");
			value.integer=1;
			return &value;
    }
}

union VALUE *interpret(NODE *term){
	init_symbtable();
	walk(term,symbtable);
}
