#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "binary_tree.h"

#define log_info(msg,...)  printf(msg, ##__VA_ARGS__)

void * q_pop(que_t * queue){
    int idx = queue->f;
    if(queue->len == 0)
        return NULL;
    queue->f = (queue->f+1)>(STK_QUE_LEN-1)?0:(queue->f+1);
    queue->len --;
    return queue->pque[idx];
}

void q_push(que_t * queue, void * ptr){
    int idx = queue->f + queue->len;
    if(queue->len < STK_QUE_LEN)
        queue->len ++;
    else
        queue->f = (queue->f-1)>0?(queue->f-1):(STK_QUE_LEN-1);
    queue->pque[idx] = ptr;
}

void que_init(que_t * queue){
    memset(queue, 0, sizeof(que_t));
    queue->f = 0;
    queue->len = 0;
}

void * s_pop(stk_t * stack){
    int idx = stack->top;
    if(0 > idx)
        return NULL;
    --stack->top;
    return stack->pstack[idx];
}

void s_push(stk_t * stack, void * ptr){
    if(STK_QUE_LEN-1 <= stack->top)
        return;
    ++stack->top;
    stack->pstack[stack->top] = ptr;
}

void stack_init(stk_t * stack){
    memset(stack, 0, sizeof(stk_t));
    stack->button = 0;
    stack->top = -1;
}

int tree_node_dep(tree_t * proot, int id){
    que_t queue = {0};
    que_init(&queue);
    tree_t * node = proot;
    int level = 0;
    while(NULL != node){
        level ++;
        if(NULL != node->pleft){
            if(node->pleft->id == id)
                return level;
            q_push(&queue, node->pleft);
        }
        else if(NULL != node->pright){
            if(node->pright->id == id){
                return level;
            }
            q_push(&queue, node->pright);
        }
        else{
            level--;
        }
        node = q_pop(&queue);
    }
}

int tree_dep(tree_t * proot){
    stk_t stack = {0};
    stack_init(&stack);
    tree_t * node = proot;
    int depth = 0;
    int level = 0;
    while(NULL != node){
        if(level > depth)
            depth = level;
        if((NULL != node->pleft)||
                (NULL != node->pright)){
            if(NULL != node->pleft){
                s_push(&stack, node->pleft);
            }
            if(NULL != node->pright){
                s_push(&stack, node->pright);
            }
            level++;
        }
        else{
            level--;
        }
        node = s_pop(&stack);
    }
    return depth;
}

void tree_print(tree_t * proot){
    que_t queue = {0};
    que_init(&queue);
    tree_t line_end = {.id = 0xFFFFFFFF, .pleft = NULL, .pright=NULL};
	tree_t * tmp = NULL;
    q_push(&queue, proot);
	q_push(&queue, &line_end);
    while(queue.len > 0){
        tmp = q_pop(&queue);
		if(tmp->id == 0xFFFFFFFF){
			log_info("\n");
			if(queue.len == 0)
				break;
			else
				q_push(&queue, &line_end);
		}
		else{
			log_info("%d ", tmp->id);
		}
        if(tmp->pleft != NULL){
            q_push(&queue, tmp->pleft);
        }
        if(tmp->pright != NULL){
            q_push(&queue, tmp->pright);
        }
    }
}

/*前序遍历*/
tree_t * ftravel(tree_t * proot, handler_t func){
    stk_t stack = {0};
    stack_init(&stack);
	tree_t * tmp = proot;
    while(NULL != tmp){
		if(func(tmp->id) == 1)
			return tmp;
		if(tmp->pright != NULL){
            s_push(&stack, tmp->pright);
        }
        if(tmp->pleft != NULL){
        	tmp = tmp->pleft;
        }
		else{
			tmp = s_pop(&stack);
		}
    }
}

/*中序遍历*/
tree_t * ctravel(tree_t * proot, handler_t func){
    stk_t stack = {0};
    stack_init(&stack);
	tree_t * tmp = proot;
    while(NULL != tmp){
        if(tmp->pright != NULL){
            s_push(&stack, tmp->pright);
        }

		s_push(&stack, tmp);
		
        if(tmp->pleft != NULL){
			if(func(tmp->pleft->id) == 1)
				return tmp->pleft;
            tmp = tmp->pleft;
        }
		else{
			tmp = s_pop(&stack);
		}
    }
}

/*后序遍历*/
tree_t * btravel(){
    que_t queue = {0};
    que_init(&queue);
	tree_t * tmp = proot;
    while(NULL != tmp){
		
		if(tmp->pright != NULL){
			q_push(&queue, tmp->pright);
		}

		if(1 == func(tmp->id))
			return tmp;

        if(tmp->pleft != NULL){
            q_push(&queue, tmp->pleft);
        }

		
		q_push(&queue, tmp);
    }
}

tree_t * search(tree_t * proot, int id){
}

void insert(tree_t * proot, int id){
}

void del(tree_t * proot, int id){
}

void tree_init(tree_t * proot){
    que_t queue = {0};
    que_init(&queue);
    tree_t line_end = {.id = 0xFFFFFFFF, .pleft = NULL, .pright=NULL};
	tree_t * tmp = NULL;
    q_push(&queue, proot);
	q_push(&queue, &line_end);
    int level = 0;
    int id = 0;
    while(queue.len > 0){
        if(level > 4)
            break;
		tmp = q_pop(&queue);
		if(tmp->id == 0xFFFFFFFF){
			level ++;
			if(queue.len == 0)
				break;
			else
				q_push(&queue, &line_end);
		}
		else{
	        if(NULL == tmp->pleft){
	            tmp->pleft = (tree_t *)malloc(sizeof(tree_t));
	            tmp->pleft->id = ++id;
	            q_push(&queue, tmp->pleft);
	        }
	        if(NULL == tmp->pright){
	            tmp->pright = (tree_t*)malloc(sizeof(tree_t));
	            tmp->pright->id = ++id;
	            q_push(&queue, tmp->pright);
	        }
		}
    }
}

void main(){
    tree_t tree = {0};
    tree_init(&tree);
    tree_print(&tree);
}
