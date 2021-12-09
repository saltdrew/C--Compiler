#include <stdio.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"

VALUE value;

VALUE *walk(NODE *term, FRAME *env){
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
			if (token->type = IDENTIFIER){
				return name_method(token,env);
			}
			else if (token->type = CONSTANT){
				value.integer = token ->value;
				return &value;
			}
    	case RETURN:
			return walk(term->left,env);
		default:
			printf("defaulted in walk\n");
			value.integer=1;
			return &value;
    }
}

VALUE *interpret(NODE *term){
	FRAME *env;
	walk(term,env);
}
