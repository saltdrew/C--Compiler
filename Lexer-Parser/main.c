#include <stdio.h>
#include <ctype.h>
#include "C.tab.h"
#include <string.h>
#include "interpreter.h"
#include <stdlib.h>
#include "print_tree.h"

extern int yydebug;
extern NODE* yyparse(void);
extern NODE* ans;
extern void init_symbtable(void);

int main(int argc, char** argv)
{
    NODE* tree;
    if (argc>1 && strcmp(argv[1],"-d")==0) yydebug = 1;
    init_symbtable();
    printf("--C COMPILER\n");
    yyparse();
    tree = ans;
    printf("parse finished with %p\n", tree);
    print_tree(tree);
    VALUE *result = interpret(tree);
    if (result==NULL){
        printf("result is null\n");
    }else{
        printf("Answer is %d\n",result->integer);
    }
    free(result);
    return 0;
}
