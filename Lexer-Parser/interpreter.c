#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "C.tab.h"
#include "ctype.h"


VALUE *if_method (NODE *antecedent, NODE *consequent, NODE *alternative, FRAME *env) ;

VALUE* applyFunc(int function, VALUE* left, VALUE* right){
	VALUE* value=(VALUE*)malloc(sizeof(VALUE));
	printf("applying function %d on %d and %d\n",function,left->integer,right->integer);
	switch (function){
		case '+':
			value->integer = (left->integer) + (right->integer);
			break;
		case '-':
			value->integer = (left->integer) - (right->integer);
			break;
		case '*':
			value->integer = (left->integer) * (right->integer);
			break;
		case '/':
			value->integer = (left->integer) / (right->integer);
			break;
		case '%':
			value->integer = (left->integer) % (right->integer);
			break;
		case '<':
			value->boolean = (left->integer) < (right->integer);
			break;
		case '>':
			value->boolean = (left->integer) > (right->integer);
			break;
		case NE_OP:
			value->boolean = (left->integer) != (right->integer);
			break;
		case EQ_OP:
			value->boolean = (left->integer) == (right->integer);
			break;
		default:
			printf("other function detected\n");
			return NULL;
	}
	printf("result of function is %d\n",value->integer);
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
	VALUE* value=(VALUE*)malloc(sizeof(VALUE));
	VALUE* left;
	VALUE* right;
	printf("walking node with type %d\n",term->type);
	switch(term->type){
		case 'd':
			return walk(term->left,env);
			break;
		case 'D':
			return walk(term->right,env);
			break;
		case ';':
			left = walk(term->left,env);
			right = walk(term->right,env);
			return select_return(left,right);
			break;
		case '~':
			NODE *arg1=term->right;
			switch(arg1->type){
				case 'D':
					walk(term->right,env);
					break;
				case LEAF:
					return declaration_method((TOKEN*)(arg1->left),env);
					break;
				case '=':
					declaration_method((TOKEN*)(arg1->left->left),env);
					walk(arg1,env);
					return NULL;
					break;
				default:
					printf("defaulted in ~, returning null\n");
					return NULL;
			}
		case '=':{
			VALUE *toAssign= walk(term->right,env); //FIX THIS
			assign_method((TOKEN*)(term->left->left),env,toAssign);
			return NULL;
			break;
		}
    	case LEAF:
			TOKEN *token = (TOKEN*)(term->left);
			printf("encountered leaf, type is %d\n",token->type);
			if (token->type == IDENTIFIER){
				return name_method(token,env);
			}
			else if (token->type == CONSTANT){
				value->integer = token->value;
				return value;
			}
			else if (token->type ==STRING_LITERAL){
				//Something here...
			}
			break;
    	case RETURN:
			return walk(term->left,env);
			break;
		case IF:
			printf("here IF. right node is, %d\n",term->right->type);
			NODE* condition = term->left;
			NODE* consequent;
			NODE* alternative;

			if (term->right->type==ELSE){
				printf("heree\n");
				consequent = term->right->left;
				alternative = term->right->right;
			}else{
				consequent = term->right;
				alternative = NULL;
			}
			return if_method(condition,consequent,alternative,env);

		case WHILE:
			break;
		case CONTINUE:
			break;
		case BREAK:
			break;
		default:
			left = walk(term->left,env);
			right = walk(term->right,env);
			return applyFunc(term->type, left, right);
    }
}

VALUE *if_method(NODE *antecedent, NODE *consequent, NODE *alternative, FRAME *env) {
	if (walk(antecedent, env)->boolean == TRUE) {
		return walk(consequent ,env);
	}else{
		if (alternative!=NULL){
			return walk(alternative ,env);
		}
		return NULL;
	}
}

FRAME *extend_frame(FRAME *env, NODE *ids, NODE *args){
    FRAME *newenv = make_frame(NULL, NULL);
    BINDING *bindings = NULL;
	NODE* ip;
	NODE* ap;
    for (ip = ids, ap = args; (ip != NULL) && (ap != NULL); ip->right, ap->right){
        bindings = make_binding((TOKEN*)ip->left, walk(ap->left, env), bindings);
    }
    newenv -> bindings = bindings ;
    return newenv;
}

NODE* formals(CLOSURE* f){
	return (f->code->right->right);
}

VALUE * lexical_call_method ( TOKEN *name , NODE *args , FRAME *env) {
	CLOSURE *f = name_method (name, env)->closure;
	FRAME *newenv = extend_frame ( env , formals (f) , args );
	newenv -> next =f->env;
	return walk(f->code, newenv);
}


VALUE *interpret(NODE *term){
	FRAME *env = (FRAME*)malloc(sizeof(FRAME));
	VALUE* result = walk(term,env);
	free(env);
	return result;
}
