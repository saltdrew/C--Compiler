
#include "nodes.h"

struct CLOSURE;

typedef union VALUE {
	int integer;
	int boolean;
	char* string;
	struct CLOSURE* closure;
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

typedef struct CLOSURE {
	FRAME *env ;
	NODE *code ;
} CLOSURE ;




VALUE *name_method(TOKEN *x, FRAME *frame);
VALUE *assign_method(TOKEN *x ,FRAME *frame, VALUE *value);
VALUE *declaration_method ( TOKEN *x , FRAME *frame );

FRAME* make_frame(BINDING *bindings, FRAME* next);
BINDING* make_binding(TOKEN *name, VALUE* val, BINDING* next);
