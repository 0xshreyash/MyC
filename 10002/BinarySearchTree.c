node_t
*search_tree(tree_t tree, char *key)
{
	assert(tree->root);
	return recursive_search_tree(tree->root, key);
}

node
*recursive_search_tree(node_t *, char *key)
{
	if(node == 	NULL)
	{
		return NULL;
	}
	if(strcmp(node->data, key)>0)
	{
		return recursive_search_tree(node->left, key);
	}
	else if(strcmp(node->data, key)<0)
	{
		return recursive_search_tree(node->right, key);
	}
	else
	{
		return node;
	}

}

tree_t
*make_empty_tree(void *func(void *, void *))
{
	tree_t *tree;
	assert(tree!=NULL);

	tree->root = NULL;
	tree->cmp = func;
	return tree;
}
/* You used strcmp twice in the if and else if statmnts, it makes the 
   program slow and should not be done.. */
tree_t
*insert_in_order(tree_t *tree, char *key)
{
	assert(tree->root);
	node_t *new = malloc(sizeof(new));
	new->data = key;
	new->left = NULL;
	new->right = NULL
	return recursive_inseert(tree->root, node);
}
node_t
*recursive_insert(node_t *root, node *new)
{
	if(root == NULL)
	{
		return new;
	}
	else if((outcome=strcmp(root->data, key)>0)
	{
		root->right = recursive_insert(root->right, new);
	}
	else
	{
		root->left = recursive_insert(root->left, new);
	}
	return root;
}
void
traverse_tree(tree_t *tree)
{
	assert(tree->root!=NULL);
	recursive_traverse(tree);
}
void
recursive_traverse(node *root)
{
	if (root)
	{
		reursive_traverse(root->left);
		printf("%s", root->data);
		recursive_traverse(root->right);/* code */
	}
}
   

