#include "treetest.h"

void print_node(tree node)
{
	printf("id=%d; ld=%d; rd=%d; lwd=%d; rwd=%d; left=%d; right=%d;\n",
		node.id,
		node.ld,
		node.rd,
		node.lwd,
		node.rwd,
		(node.left == NULL)?0:node.left->id,
		(node.right == NULL)?0:node.right->id)
};

bool ut_init_tree()
{
	tree tmpNode;
	init_node(&tmpNode);
	print_node(tmpNode);
};

bool ut_insert_tree()
{
	bool insert_tree(tree* node, char child, int id);
};

bool ut_delete_tree()
{
	void delete_tree(tree* node);
};

bool ut_search()
{
	tree* search(tree* node, int id);
};

bool ut_depth()
{
	int depth(tree* root);
};

bool ut_l_width()
{
	int l_width(tree * root);
};

bool ut_r_width()
{
	int r_width(tree* root);
};

bool ut_init_map()
{
	void* init_map(tree* root);
};

bool ut_update_map()
{
	void update_map(int ** p_map, tree* root, int level, int index);
};

bool ut_free_map()
{
	void free_map(int** p_map);
};

bool ut_trave_tree()
{
	void trave_tree(tree* root, void (*visit)(void* node));
};

bool ut_update_tree()
{
	void update_tree(tree* root);
};

bool ut_print_tree()
{
	void print_tree(tree* root, int ** p_map);
}



void main()
{
	
};
