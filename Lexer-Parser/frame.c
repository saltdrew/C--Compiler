#include "frame.h"
#include "stddef.h"

VALUE* name_method (TOKEN *x, FRAME *frame ) {
    while ( frame != NULL ) {
        BINDING * bindings = frame -> bindings ;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
                return bindings -> val ;
            }
            bindings = bindings -> next ;
        }
        frame = frame -> next ;
    }
    return 0;
}

VALUE* assign_method (TOKEN *x , FRAME *frame ) {
    while ( frame != NULL ) {
        BINDING * bindings = frame -> bindings ;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
				VALUE* tempval;
				tempval->integer=x->value;
                bindings -> val = tempval;
                return tempval;
            }
            bindings = bindings -> next ;
        }
        frame = frame -> next ;
    }
    error (" unbound variable " );
}
