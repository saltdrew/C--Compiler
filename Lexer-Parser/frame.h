
#include "nodes.h"

typedef struct binding {
	TOKEN *name ;
	VALUE *val ;
	BINDING *next ;
} BINDING ;

typedef struct frame{
	BINDING *bindings;
	FRAME *next;
}

VALUE * name_method (TOKEN *x, FRAME *frame );
VALUE * assign_method (TOKEN *x ,FRAME *frame );
