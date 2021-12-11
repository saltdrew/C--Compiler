#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"
#define NONE 199967

VALUE* value;


VALUE *select_return(VALUE *l, VALUE *r){
	if (l->integer==NONE){
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
			NODE *arg1=term->right;
			switch(arg1->type){
				case 'D':
					walk(term->right,env);
				case IDENTIFIER:
					return declaration_method((TOKEN*)(arg1),env);
				case '=':
					declaration_method((TOKEN*)(arg1->left),env);
					printf("new var is %d\n",0000); //DO THIS
					walk(arg1,env);
					value->integer=NONE;
					return value;
				default:
					printf("defaulted in ~\n");
					value->integer=NONE;
					return value;
			}break;
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
			value->integer=NONE;
			return value;
    }
}

VALUE *interpret(NODE *term){
	FRAME *env = (FRAME*)malloc(sizeof(FRAME));
	value=(VALUE*)malloc(sizeof(VALUE));

	return walk(term,env);
}
