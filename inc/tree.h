#ifndef TREE_H_included
#define TREE_H_included

struct Leaf {
  char* name;
  double value;
  struct Leaf* left;
  struct Leaf* right;
};
typedef struct Leaf Leaf;

struct Tree {
  Leaf* root;
};
typedef struct Tree Tree;

void init_tree(Tree* tree);
void add_leaf(Leaf** leaf, char* name, double value);
void set(Tree* tree, char* name, double value);
double get_leaf(Leaf* leaf, char* name);
double get(Tree* tree, char* name);
void clear_leaf(Leaf* leaf);
void clear_tree(Tree* tree);
void print_leaf(Leaf* leaf, char* parent);
void print_tree(Tree* tree);

#endif
