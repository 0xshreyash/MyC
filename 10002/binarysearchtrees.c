typedef struct node node_t;

struct node
{
	void* data;  /* Enables polymorphic nature */
	node_t *left;
	mode_t *right;
}
typedfef struct
{
	node_t *root;
	int* cmp(void*,void*);
}tree_t;
tree_t* make_empty_tree(int func(void*,void*)
{
	tree_t* tree;
	tree=malloc(sizeof(*tree));
	assert(tree!=NULL);
	/* Initialize the tree as being empty */
	tree->root=NULL;
	tree->cmp=func;
}

		
	
	