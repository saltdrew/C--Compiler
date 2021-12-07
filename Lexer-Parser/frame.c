VALUE * name_method (TOKEN *x, FRAME *frame ) {
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

VALUE * assign_method (TOKEN *x ,FRAME *frame ) {
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
