#include <stdio.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"

union VALUE value;

union VALUE *walk(NODE *term, struct FRAME *env){
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
	struct FRAME *env;
	walk(term,env);
}
