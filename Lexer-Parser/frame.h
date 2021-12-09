
#include "nodes.h"

typedef union VALUE {
	int integer;
	int boolean;
	char* string;
}VALUE;

typedef struct BINDING {
	TOKEN *name ;
	union VALUE *val ;
	struct BINDING *next ;
} BINDING ;

typedef struct FRAME{
	struct BINDING *bindings;
	struct FRAME *next;
} FRAME;

VALUE *name_method(TOKEN *x, FRAME *frame);
VALUE *assign_method(TOKEN *x ,FRAME *frame);
