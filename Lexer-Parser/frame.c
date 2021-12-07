#include "frame.h"

typedef union VALUE {
	int integer;
	int boolean;
	char* string;
}value;

typedef struct BINDING {
	TOKEN *name ;
	union VALUE *val ;
	BINDING *next ;
} BINDING ;

typedef struct FRAME{
	BINDING *bindings;
	struct FRAME *next;
}


union VALUE* name_method (TOKEN *x, FRAME *frame ) {
    while ( frame != NULL ) {
        BINDING * bindings = frame - > bindings ;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
                return bindings -> val ;
            }
            bindings = bindings - > next ;
        }
        frame = frame -> next ;
    }
    error (" unbound variable " );
}

union VALUE* assign_method (TOKEN *x ,FRAME *frame ) {
    while ( frame != NULL ) {
        BINDING * bindings = frame - > bindings ;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
                bindings -> val = value ;
                return value ;
            }
            bindings = bindings - > next ;
        }
        frame = frame -> next ;
    }
    error (" unbound variable " );
}
