#include "treetest.h"

#define STK_QUE_LEN 100

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
    stk_t stack[2] = {0};
    stack_init(&stack[0]);
    stack_init(&stack[1]);
    tree_t * tmp = NULL;
    int f = 0;
    int s = 1;
    s_push(&stack[f], proot);
    printf("%d\n", proot->id);
    while(stack[f].top >= 0){
        tmp = s_pop(&stack[f]);
        if(tmp->pleft != NULL){
            s_push(&stack[s], tmp->pleft);
            printf("%d-", tmp->pleft->id);
        }
        if(tmp->pright != NULL){
            printf("%d ", tmp->pright->id);
            s_push(&stack[s], tmp->pright);
        }
        if(stack[f].top < 0){
            printf("\n");
            int idx = f;
            f = s;
            s = idx;
        }
    }
}

void tree_init(tree_t * proot){
    que_t queue = {0};
    que_init(&queue);
    int depth = 0;
    int level = 0;
    tree_t * tmp = proot;
    int id = 0;
    while(tmp != NULL){
        if(level > 5)
            break;
        if(NULL == tmp->pleft){
            tmp->pleft = (tree_t *)malloc(sizeof(tree_t));
            tmp->pleft->id = ++id;
            q_push(&queue, tmp->pleft);
            level ++;
        }
        if(NULL == tmp->pright){
            tmp->pright = (tree_t*)malloc(sizeof(tree_t));
            tmp->pright->id = ++id;
            q_push(&queue, tmp->pright);
            level ++;
        }
        level --;
        tmp = q_pop(&queue);
    }
}

void main(){

    tree_t arr[15] = {0};
    int i = 0;
    arr[0].id = 0;
    tree_t * pnode = &arr[0];
    while(i<15)
    {
        arr[i].id = i;
        pnode->pleft = &arr[i];
        pnode = pnode->pleft;
        i++;
    }
    printf("test tree depth:%d\n", tree_dep(&(arr[0])));
    for(i=1; i<15; i++){
        printf("node %d depth is %d\n", i, tree_node_dep(&arr[0], i));
    }
//    return;
    tree_t tree = {0};
    tree_init(&tree);
    tree_print(&tree);
}
