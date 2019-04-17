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

void * s_top(stk_t * stack){
    return stack->pstack[stack->top];
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

static tpath_t * new_path_node(tree_t * tnode){
	tpath_t * path = (tpath_t *)malloc(sizeof(tpath_t));
	if(NULL == path)
		return NULL;
	path->tnode = tnode;
	path->flag = 0;
	return path;
}

static inline void free_path_node(tpath_t * path){
	if(NULL != path)
		free(path);
}

static inline tree_t * new_tree_node(int id){
	tree_t * tmpNode = (tree_t *)malloc(sizeof(tree_t));
	if(NULL != tmpNode){
		tmpNode->pleft = NULL;
		tmpNode->pright = NULL;
		tmpNode->id = id;
	}
	return tmpNode;
}

void tree_print(tree_t * proot){
	char prefix[1024] = {0};
	int pfx_idx = 0;
	int times = 0;
    stk_t stack = {0};
    stack_init(&stack);
	tpath_t * tmp = new_path_node(proot);
	tpath_t * current = NULL;
	tree_t * ptnode = NULL;
	s_push(&stack, tmp);
	log_info("%d\n", proot->id);
    while(stack.top >= 0){
		current = s_top(&stack);
		ptnode = current->tnode;
		if(((ptnode->pright != NULL)||(ptnode->pleft != NULL))&&
			(current->flag < 2)){
			if((ptnode->pleft != NULL)&&(current->flag < 1)){
				tmp = new_path_node(ptnode->pleft);
				s_push(&stack, tmp);
				if(ptnode->pright != NULL){
					log_info("%s├──%d\n",prefix,ptnode->pleft->id);
					sprintf(prefix, "%s│     ", prefix);
				}
				else{
					log_info("%s└──%d\n",prefix,ptnode->pleft->id);
					sprintf(prefix, "%s      ", prefix);
				}
				pfx_idx += 5;
				prefix[pfx_idx] = 0;
				current->flag = 1;
			}
			else{
				 if((ptnode->pright != NULL)&&(current->flag < 2)){
					log_info("%s└──%d\n",prefix,ptnode->pright->id);
					tmp = new_path_node(ptnode->pright);
					s_push(&stack, tmp);
					sprintf(prefix, "%s     ", prefix);
					pfx_idx += 5;
					prefix[pfx_idx] = 0;
				}
				current->flag = 2;
	        }
		}
		else{
			s_pop(&stack);
			pfx_idx -= 5;
			prefix[pfx_idx] = 0;
		}
    }
}

/*前序遍历*/
tree_t * ftravel(tree_t * proot, handler_t func, ...){

    stk_t stack = {0};
    stack_init(&stack);
	tree_t * tmp = proot;
    while(NULL != tmp){
	    va_list ap;
	    va_start( ap, func);
		if(func(tmp, &ap) == 1)
			return tmp;
		va_end(ap);
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
	return NULL;
}

/*中序遍历*/
tree_t * ctravel(tree_t * proot, handler_t func, ...){
    va_list ap;
    va_start( ap, func);
    stk_t stack = {0};
    stack_init(&stack);
	tree_t * tmp = proot;
    while((NULL != tmp)||(stack.top >= 0)){
		if(tmp != NULL){
			s_push(&stack, tmp);
			tmp = tmp->pleft;
		}
		else{
			tree_t * node = s_pop(&stack);
			if(1 == func(node, &ap))
				return node;
			tmp = node->pright;
		}
    }
	va_end(ap);
	return NULL;
}

/*后序遍历*/
tree_t * btravel(tree_t * proot, handler_t func, ...){
    va_list ap;
    va_start( ap, func);
    stk_t stack = {0};
    stack_init(&stack);
	tree_t * tmp = proot;
	tree_t * pre = NULL;
	s_push(&stack, tmp);
    while((NULL != tmp)&&
		(stack.top >= 0)){
		tmp = s_top(&stack);
		if((tmp->pright == NULL&&tmp->pleft == NULL)||
		   ((pre != NULL)&&
		   (tmp->pleft == pre||tmp->pright == pre))){
		   if(func(tmp, &ap) == 1)
				return tmp;
		   s_pop(&stack);
		   pre = tmp;
		}
		else{
			if(tmp->pright != NULL){
				s_push(&stack, tmp->pright);
			}
			
	        if(tmp->pleft != NULL){
	            s_push(&stack, tmp->pleft);
	        }
		}
    }
	va_end(ap);
	return NULL;
}

/*层次遍历*/
tree_t * ltravel(tree_t * proot, handler_t func,  ...){
    va_list ap;
    va_start( ap, func);
    que_t queue = {0};
    que_init(&queue);
    tree_t line_end = {.id = 0xFFFFFFFF, .pleft = NULL, .pright=NULL};
	tree_t * tmp = NULL;
    q_push(&queue, proot);
	q_push(&queue, &line_end);
    while(queue.len > 0){
        tmp = q_pop(&queue);
		if(func(tmp, &ap) == 1)
			return tmp;

		if(tmp->id == 0xFFFFFFFF){
			if(queue.len == 0)
				break;
			else
				q_push(&queue, &line_end);
		}
        if(tmp->pleft != NULL){
            q_push(&queue, tmp->pleft);
        }
        if(tmp->pright != NULL){
            q_push(&queue, tmp->pright);
        }
    }
	va_end(ap);
	return NULL;
}

int node_search(tree_t * tnode, ...){
	va_list ap;
	va_start( ap, tnode);
	int id2 = va_arg(ap, int);
	va_end(ap);
	if(id2 == tnode->id)
		return 1;
}

tree_t * search_fnode(tree_t * proot, int id){
	tree_t * tmp = proot;
	if(tmp->id == id)
		return tmp;
	while(NULL != tmp){
		if(tmp->id < id){
			if(NULL == tmp->pright){
				return tmp;
			}else{
				if(id <= tmp->pright->id)
					return tmp;
				else
					tmp = tmp->pright;
			}
		}
		else{
			if(NULL == tmp->pleft){
				return tmp;
			}
			else{
				if(id >= tmp->pleft->id)
					return tmp;
				else
					tmp = tmp->pleft;
			}
		}
	}
	return NULL;
}

tree_t * search(tree_t * proot, int id){
	tree_t * tmp = proot;
	while(NULL != tmp){
		if(tmp->id < id){
			if(id < tmp->pright->id)
				return tmp;
			else
				tmp = tmp->pright;
		}
		else if(tmp->id == id)
			return tmp;
		else{
			if(id > tmp->pleft->id)
				return tmp;
			else
				tmp = tmp->pleft;
		}
	}
	return NULL;
}

void insert(tree_t * proot, int id){
	tree_t * newNode = NULL;
	tree_t * fnode = search_fnode(proot, id);
	if(fnode->id == id){
		log_info("The node %d is existed!\n", id);
		return;
	}
	newNode = new_tree_node(id);
	if(NULL == newNode){
		log_info("The New node malloc failed!\n");
		return;
	}
	if(fnode->id > id){
		newNode->pleft = fnode->pleft;
		fnode->pleft = newNode;
	}
	else{
		newNode->pright = fnode->pright;
		fnode->pright = newNode;
	}
}

int destroy(tree_t * pNode, va_list * args){
	//log_info("del %d\n", pNode->id);
	free(pNode);
	return 0;
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
        if(level > 2)
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

void delete(tree_t * root, int id){
	tree_t * fnode = search_fnode(root, id);
	if(fnode->pleft != NULL){
		if(fnode->pleft->id == id){
			btravel(fnode->pleft, destroy);
			fnode->pleft = NULL;
		}
	}
	else if(fnode->pright != NULL){ 
		if(fnode->pright->id == id){
			btravel(fnode->pright, destroy);
			fnode->pright = NULL;
		}
	}
	else if(fnode->id = id){
		destroy(fnode,NULL);
	}
	else{
		log_info("There is no this node,please check!\n");
	}
}

int tree_count(tree_t * pNode, va_list * pargs){
	int * num = va_arg(*pargs, int *);
	(*num) += 1;
	return 0;
}

void print_tree_info(tree_t * root){
	int depth = tree_dep(root);
	int node_num = 0;
	ftravel(root, tree_count, &node_num);
	log_info("Tree Max depth:%d\n", depth);
	log_info("Tree node count:%d\n", node_num);
}

int print_node(tree_t * tnode, va_list * args){
	if(tnode->id != 0xFFFFFFFF)
		log_info("%d ", tnode->id);
	return 0;
}

void print_prompt(){
	log_info("Forward travel please press 'f'!\n");
	log_info("Central travel please press 'c'!\n");
	log_info("Backword travel please press 'b'!\n");
	log_info("Level travel please press 'l'!\n");
	log_info("Insert node please press 'i'!\n");
	log_info("Delete node please press 'd'!\n");
	log_info("Print tree please press 'p'!\n");
	log_info("Get prompt please press '?'!\n");
	log_info("Quit this program please press 'q'!\n");
}

void print_eof(){
	log_info("#input order[insert/del/print/?/quit]:");
}

void main(){
	tree_t * root = new_tree_node(0);
	tree_init(root);
	tree_print(root);
	btravel(root, destroy, 0);
    root = new_tree_node(500);
	if(NULL == root){
		log_info("Tree root init failed!\n");
		return;
	}
	print_prompt();
	print_eof();
	char order;
	int id;
	while(1)
	{
		setbuf(stdin, NULL);
		scanf("%c", &order);
		setbuf(stdin, NULL);
		switch(order)
		{
			case 'i':
				//insert
				log_info("\n please input node id which you want insert:");
				setbuf(stdin, NULL);
				scanf("%d", &id);
				setbuf(stdin, NULL);
				insert(root,id);
				print_eof();
				break;
			case 'd':
				//delete
				log_info("\n please input node id which you want delete:");
				setbuf(stdin, NULL);
				scanf("%d", &id);
				setbuf(stdin, NULL);
				delete(root,id);
				print_eof();
				break;
			case 'q':
				//quit
				btravel(root, destroy);
				log_info("it's time to quit!\n");
				return;
			case '?':
				//help
				print_prompt();
				print_eof();
				break;
			case 'p':
				//print
				log_info("***print tree list as follow*****\n");
				tree_print(root);
				print_eof();
				break;

			case 's':
				//show
				log_info("***show tree base info as follow*****\n");
				print_tree_info(root);
				print_eof();
				break;

			case 'f':
				log_info("front travel:\n");
				ftravel(root, print_node);
				log_info("\n");
				print_eof();
				break;

			case 'c':
				log_info("central travel:\n");
				ctravel(root, print_node);
				log_info("\n");
				print_eof();
				break;
			
			case 'b':
				log_info("back travel:\n");
				btravel(root, print_node);
				log_info("\n");
				print_eof();
				break;
				
			case 'l':
				log_info("level travel:\n");
				ltravel(root, print_node);
				log_info("\n");
				print_eof();
				break;

			case 'g':
				log_info("\n please input node id which you want get fnode:");
				setbuf(stdin, NULL);
				scanf("%d", &id);
				setbuf(stdin, NULL);
				tree_t * fnode = search_fnode(root, id);;
				log_info("Father node: %d\n", fnode->id);
				print_eof();
				break;
				
			default:
				break;
		};
	}
	return;
}
