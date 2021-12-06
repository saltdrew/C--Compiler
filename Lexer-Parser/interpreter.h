typedef union VALUE {
    int integer;
	int boolean;
	char* string;
}value;

union VALUE *walk(NODE *term);
