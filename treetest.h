#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct TREE
{
	int id;
	struct TREE* left;
	struct TREE* right;
	int ld;              //left child tree's depth
	int rd;
	int lwd;		//left child tree's width
	int rwd;
	int index;
}tree;


typedef struct NODE
{
	tree* pNode;
	struct NODE * next;
	struct NODE * prev;
}node;

typedef struct QUEUE
{
	node* head;
	node* tail;
}queue;

typedef struct TWODLK
{
	queue* pNode;
	struct TWODLK* next;
	struct TWODLK* prev;
}twodlk;

typedef struct TWODQUE
{
	twodlk* head;
	twodlk* tail;
}twodque;

#define max(a, b) ((a) > (b) ? (a) : (b))

///function define

bool init_node(tree* root);

bool insert_tree(tree* node, char child, int id);

void delete_tree(tree* node);

tree* search(tree* node, int id);

int depth(tree* root);

int l_width(tree * root);

int r_width(tree* root);

void* init_map(tree* root);

void update_map(int ** p_map, tree* root, int level, int index);

void free_map(int** p_map);

void trave_tree(tree* root, void (*visit)(void* node));

bool update_tree(tree* root);

void print_tree(tree* root, int ** p_map);

