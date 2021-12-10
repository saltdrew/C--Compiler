#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"

VALUE* value;

VALUE *select_return(VALUE *l, VALUE *r){
	if (l==NULL){
		return r;
	}else{
		return l;
	}
}

void declare(int type, char *name, FRAME *env){

}

VALUE *walk(NODE *term, FRAME *env){
	printf("walking node with type %d\n",term->type);
	switch(term->type){
		case 'd':
			return walk(term->left,env);
		case 'D':
			return walk(term->right,env);
		case ';':
			return select_return(walk(term->left,env),walk(term->right,env));
		case '~':
			if (term->right->type == 'D'){
				walk(term->right,env);
			}else{
				printf("here1\n");
				return declaration_method((TOKEN*)(term->right),env);;
			}
		case '=':
			return assign_method((TOKEN*)(term->left),env,walk(term->right,env));

		case '+':
			value->integer= walk(term->left,env)->integer + walk(term->right,env)->integer;
			return value;
    	case LEAF:
			TOKEN *token = (TOKEN*)(term->left);
			printf("encountered leaf, type is %d\n",token->type);
			if (token->type == IDENTIFIER){
				printf("here\n");
				return name_method(token,env);
			}
			else if (token->type == CONSTANT){
				value->integer = token->value;
				return value;
			}
    	case RETURN:
			return walk(term->left,env);
		default:
			printf("defaulted in walk\n");
			value->integer=1;
			return value;
    }
}

VALUE *interpret(NODE *term){
	FRAME *env = (FRAME*)malloc(sizeof(FRAME));
	value=(VALUE*)malloc(sizeof(VALUE));

	return walk(term,env);
}
