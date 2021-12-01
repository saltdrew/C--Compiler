#include <stdio.h>
#include "main.c"


extern NODE* yyparse(void);
extern NODE* ans;

int interpret(char* argv){	
	NODE* tree;
	yyparse();
	tree=ans;
	return 0;
}	



