typedef union VALUE {
    int integer;
	int boolean;
	char* string;
}value;

union VALUE *interpret(NODE *term);
