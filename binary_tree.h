#ifndef __BINARY_TREE_H
#define __BINARY_TREE_H

#define STK_QUE_LEN 150

typedef struct tree_s
{
    int id;
    struct tree_s * pleft;
    struct tree_s * pright;
}tree_t;

typedef struct queue_s
{
    void * pque[STK_QUE_LEN];
    int f;
    int len;
}que_t;

typedef struct stack_s
{
    void * pstack[STK_QUE_LEN];
    int top;
    int button;
}stk_t;

typedef struct
{
	tree_t * tnode;
	int flag;
}tpath_t;

typedef int (* handler_t)(tree_t * tnode, va_list * pargs);

#endif
