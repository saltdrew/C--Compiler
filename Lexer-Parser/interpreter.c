#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"
#define NONE 199967

VALUE* value;


VALUE *select_return(VALUE *l, VALUE *r){

	if (l==NULL && r==NULL){
		printf("Both Null! \n");
		return l;
	}
	else if (l==NULL){
		return r;
	}else if (r==NULL){
		return l;
	}else{
		printf("both have values\n");
		return r;
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
			printf("left is %d\n",term->left->type);
			printf("right is %d\n",term->right->type);
			VALUE *left = walk(term->left,env);
			VALUE *right = walk(term->right,env);
			printf("right result %d\n",right->integer);
			return select_return(left,right);
		case '~':
			NODE *arg1=term->right;
			switch(arg1->type){
				case 'D':
					walk(term->right,env);
				case LEAF:
					return declaration_method((TOKEN*)(arg1->left),env);
				case '=':
					declaration_method((TOKEN*)(arg1->left->left),env);
					printf("new var is %d\n",0000); //DO THIS
					walk(arg1,env);
					return NULL;
				default:
					printf("defaulted in ~, returning null\n");
					return NULL;
			}break;
		case '=':
			VALUE *toAssign= walk(term->right,env); //FIX THIS
			printf("value to assign is %d\n",toAssign);
			assign_method((TOKEN*)(term->left->left),env,toAssign);
			return NULL;
		case '+':
			printf("here11\n");
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
				printf("here5\n");
				value->integer = token->value;
				return value;
			}
    	case RETURN:
			return walk(term->left,env);
		default:
			printf("defaulted in walk, returning null\n");
			return NULL;
    }
}

VALUE *interpret(NODE *term){
	FRAME *env = (FRAME*)malloc(sizeof(FRAME));
	value=(VALUE*)malloc(sizeof(VALUE));
	VALUE* result = walk(term,env);
	free(env);
	return result;
}
