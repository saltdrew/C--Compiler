#include "frame.h"
#include <stddef.h>
#include <stdlib.h>

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

VALUE* assign_method (TOKEN *x , FRAME *frame, VALUE* value) {
    while ( frame != NULL ) {
        BINDING * bindings = frame -> bindings ;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
                bindings -> val = value;
                return value;
            }
            bindings = bindings -> next ;
        }
        frame = frame -> next ;
    }
    error (" unbound variable " );
}

VALUE * declaration_method ( TOKEN * x , FRAME * frame ) {
    BINDING * bindings = frame -> bindings ;
    BINDING * new = malloc ( sizeof ( BINDING ));
    if ( new !=0) { // check allocation worked
        new -> name = x;
        new -> val =( VALUE *)0; // temporary
        new -> next = bindings;
        frame -> bindings = new;
        return ( VALUE *)0; // temporary
    }
    error (" binding allocation failed " );
}
