#include "token.h"

typedef struct node {
  int          type;
  struct node *left;
  struct node *right;
} NODE;

NODE* make_leaf(TOKEN* l);
NODE* make_node(int t, NODE* left, NODE* right);
