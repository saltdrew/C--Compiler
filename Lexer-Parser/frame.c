#include "frame.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

VALUE *name_method (TOKEN *x, FRAME *frame ) {
    while(frame!=NULL){
        BINDING * bindings = frame -> bindings ;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
                return bindings -> val ;
            }
            bindings = bindings -> next ;
        }
        frame = frame -> next ;
    }
    perror("Attempting to access unbound variable");
    return NULL;
}

VALUE *assign_method (TOKEN *x ,FRAME *frame, VALUE* value) {
    while ( frame != NULL ) {
        BINDING *bindings = frame->bindings;
        while ( bindings != NULL ) {
            if ( bindings -> name == x){
                printf("assigning %d to %s\n",value->integer,bindings->name->lexeme);
                bindings -> val = value;
                return value;
            }
            bindings = bindings -> next ;
        }
        frame = frame -> next ;
    }
    perror("Attempting to assign unbound variable");
}



VALUE * declaration_method (TOKEN *x, FRAME* frame ) {
    BINDING * bindings = frame -> bindings ;
    BINDING * new = malloc ( sizeof ( BINDING ));
    if ( new !=0) { // check allocation worked
        new -> name = x;
        new -> val =( VALUE *)0; // temporary
        new -> next = bindings;
        frame -> bindings = new;
        return ( VALUE *)0; // temporary
    }
    perror("Binding allocation failed");
}

FRAME* make_frame(BINDING *bindings, FRAME* next){
    FRAME *a = (FRAME*)malloc(sizeof(FRAME));
    if (a==NULL) {
      perror("Cannot make frame");
      exit(1);
    }
    a->bindings = bindings;
    a->next = next;
    return a;

}
BINDING* make_binding(TOKEN *name, VALUE* val, BINDING* next){
    BINDING *a = (BINDING*)malloc(sizeof(BINDING));
    if (a==NULL) {
      perror("Cannot make frame");
      exit(1);
    }
    a->name=name;
    a->val=val;
    a->next=next;
    return a;
}

CLOSURE* make_closure(FRAME *env, NODE* code){
    CLOSURE* a = (CLOSURE*)malloc(sizeof(CLOSURE));
    if (a==NULL) {
      perror("Cannot make frame");
      exit(1);
    }
    a->env = env;
    a->code = code;

}
