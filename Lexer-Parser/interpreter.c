#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"
#define NONE 199967

VALUE* value;

VALUE* apply(int function, VALUE* left, VALUE* right){
	value=(VALUE*)malloc(sizeof(VALUE));
	int dataType;
	int integerType=0;
	int booleanType=1;
	int stringType=2;
	if (left->integer!=NULL && right->integer!=NULL){
		dataType=integerType;
	}else if (left->boolean!=NULL && right->boolean!=NULL){
		dataType=booleanType;
	}else if (left->string!=NULL && right->string!=NULL){
		dataType=stringType;
	}else{
		printf("Error in apply: No data type found!\n");
		return NULL;
	}

	switch (function){
		case '+':
			if (dataType!=integerType){
				printf("Error in apply, '+' called but types are not integer");
				return NULL;
			}
			value->integer = (left->integer) + (right->integer);
		case '-':
			if (dataType!=integerType){
				printf("Error in apply, '-' called but types are not integer");
				return NULL;
			}
			value->integer = (left->integer) - (right->integer);
		case '*':
			if (dataType!=integerType){
				printf("Error in apply, '*' called but types are not integer");
				return NULL;
			}
			value->integer = (left->integer) * (right->integer);
		case '/':
			if (dataType!=integerType){
				printf("Error in apply, '/' called but types are not integer");
				return NULL;
			}
			value->integer = (left->integer) / (right->integer);
		case '%':
			if (dataType!=integerType){
				printf("Error in apply, '/' called but types are not integer");
				return NULL;
			}
			value->integer = (left->integer) % (right->integer);
		case '<':
			if (dataType!=integerType){
				printf("Error in apply, '/' called but types are not integer");
				return NULL;
			}
			value->boolean = (left->integer) < (right->integer);
		case '>':
			if (dataType!=integerType){
				printf("Error in apply, '>' called but types are not integer");
				return NULL;
			}
			value->boolean = (left->integer) > (right->integer);
		case NE_OP:
			if (dataType==integerType){
				value->boolean = (left->integer) != (right->integer);
			}else if (dataType==booleanType){
				value->boolean = (left->boolean) != (right->boolean);
			}else {
				printf("Error in apply, '!=' called but types are not intger or boolean");
			}
		case EQ_OP:
			if (dataType==integerType){
				value->boolean = (left->integer) == (right->integer);
			}else if (dataType==booleanType){
				value->boolean = (left->boolean) == (right->boolean);
			}else {
				printf("Error in apply, '==' called but types are not intger or boolean");
			}

	}

	free(left);
	free(right);
	return value;
}

VALUE *select_return(VALUE *l, VALUE *r){

	if (l==NULL && r==NULL){
		return NULL;
	}
	else if (l==NULL){
		return r;
	}else if (r==NULL){
		return l;
	}else{
		printf("Error in select: Both branches have return values\n");
		return r;
	}
}

VALUE *walk(NODE *term, FRAME *env){
	value=(VALUE*)malloc(sizeof(VALUE));
	VALUE* left;
	VALUE* right;
	//printf("walking node with type %d\n",term->type);
	switch(term->type){
		case 'd':
			return walk(term->left,env);
		case 'D':
			return walk(term->right,env);
		case ';':
			left = walk(term->left,env);
			right = walk(term->right,env);
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
					walk(arg1,env);
					return NULL;
				default:
					//printf("defaulted in ~, returning null\n");
					return NULL;
			}break;
		case '=':
			VALUE *toAssign= walk(term->right,env); //FIX THIS
			assign_method((TOKEN*)(term->left->left),env,toAssign);
			return NULL;
		case '+':
			value->integer= walk(term->left,env)->integer + walk(term->right,env)->integer;
			return value;
		case '*':
			left = walk(term->left,env);
			right = walk(term->right,env);
			value->integer = left->integer * right->integer ;
			free(left);
			free(right);
			return value;

    	case LEAF:
			TOKEN *token = (TOKEN*)(term->left);
			//printf("encountered leaf, type is %d\n",token->type);
			if (token->type == IDENTIFIER){
				return name_method(token,env);
			}
			else if (token->type == CONSTANT){
				value->integer = token->value;
				return value;
			}
    	case RETURN:
			return walk(term->left,env);
		default:
			//printf("defaulted in walk, returning null\n");
			return NULL;
    }
}

VALUE *interpret(NODE *term){
	FRAME *env = (FRAME*)malloc(sizeof(FRAME));
	VALUE* result = walk(term,env);
	free(env);
	return result;
}
