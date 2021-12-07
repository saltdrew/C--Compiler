
#include "nodes.h"

typedef union VALUE {
	int integer;
	int boolean;
	char* string;
}VALUE;

typedef struct BINDING {
	TOKEN *name;
	union VALUE *val;
	struct BINDING *next;
} BINDING;

typedef struct FRAME{
	struct BINDING *bindings;
	struct FRAME *next;
} FRAME;
union VALUE *name_method(TOKEN *x, struct FRAME *frame);
union VALUE *assign_method(TOKEN *x ,struct FRAME *frame);
