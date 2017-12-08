#include "treetest.h"

bool init_node(tree* root)
{
	if (NULL != root)
	{
		root->id = 0;
		root->left = NULL;
		root->right = NULL;
		root->ld = 1;
		root->rd = 1;
		root->lwd = 1;
		root->rwd = 1;
		return true;
	};
	return false;
};

bool insert_tree(tree* node, char child, int id)
{
	if (NULL != node)
	{
		tree* tmp = malloc(sizeof(tree));
		memset(tmp, 0, sizeof(tree));
		if (init_node(tmp))
		{
			tmp->id = id;
			if ((child == 'l') && (NULL == node->left))
			{
				node->left = tmp;
				return true;
			}
			else if ((child == 'r') && (NULL == node->right))
			{
				node->right = tmp;
				return true;
			}
			else
			{
				printf("this node is exists or input error!\n");
			};
		};
	};
	return false;
};

void delete_tree(tree* node)
{
	if (NULL != node)
	{
		delete_tree(node->left);
		delete_tree(node->right);
		free(node);
	}
	else
	{
		return;
	};
};

tree* search(tree* node, int id)
{
	int tmp = 0;
	tree* tmpnode1 = NULL;
	tree* tmpnode2 = NULL;
	if (NULL != node)
	{
		if (node->id == id)
		{
			return node;
		};
		tmpnode1 = search(node->left, id);
		tmpnode2 = search(node->right, id);
		return (tmpnode1 != NULL) ? tmpnode1 : tmpnode2;
	}
	else
	{
		return NULL;
	};
};

tree* search_f_node(tree* node, int id)
{
	int tmp = 0;
	tree* tmpnode1 = NULL;
	tree* tmpnode2 = NULL;
	if (NULL != node)
	{
		if (NULL != (node->left))
		{
			if ((node->left->id) == id)
			{
				return node;
			};
		};
		if (NULL != (node->right))
		{
			if ((node->right->id) == id)
			{
				return node;
			};
		};
		tmpnode1 = search_f_node(node->left, id);
		tmpnode2 = search_f_node(node->right, id);
		return (tmpnode1 != NULL) ? tmpnode1 : tmpnode2;
	}
	else
	{
		return NULL;
	};
};

int depth(tree* root)
{
	int cd = 0;
	if (root)
	{
		root->ld = depth(root->left) + 1;
		root->rd = depth(root->right) + 1;
		cd = (root->ld > root->rd) ? (root->ld) : (root->rd);
		return cd;
	}
	else
	{
		return 0;
	};
};

int l_width(tree * root)
{
	int lwd1 = 0;
	int lwd2 = 0;
	if (root)
	{
		lwd1 = l_width(root->left);
		lwd2 = l_width(root->right);
		if (2 < lwd2)
		{
			lwd1 = (lwd1>(lwd2 - 2)) ? lwd1 : (lwd2 - 2);
		};
		root->lwd = lwd1 + 1;
		return lwd1 + 1;
	}
	else
	{
		return 0;
	};
};

int r_width(tree* root)
{
	int rwd1 = 0;
	int rwd2 = 0;
	if (root)
	{
		rwd2 = r_width(root->left);
		rwd1 = r_width(root->right);
		if (2 < rwd2)
		{
			rwd1 = (rwd1>(rwd2 - 2)) ? rwd1 : (rwd2 - 2);
		};
		root->rwd = rwd1 + 1;
		return rwd1 + 1;
	}
	else
	{
		return 0;
	};
};

void q_insert(queue* que, node* pNode)
{
	if (NULL == que)
	{
		return;
	};
	if (NULL == que->head)
	{
		pNode->next = NULL;
		pNode->prev = NULL;
		que->head = pNode;
		que->tail = pNode;
	}
	else
	{
		pNode->next = NULL;
		pNode->prev = que->tail;
		que->tail->next = pNode;
		que->tail = pNode;
	};
};

void q_pop(queue* que)
{
	node* tmpNode = que->head;
	que->head = que->head->next;
	if (NULL != que->head)
	{
		que->head->prev = NULL;
	};
	free(tmpNode);
};

void q_destroy(queue* pQue)
{
	if (NULL == pQue)
	{
		return;
	};
	while (NULL != pQue->head)
	{
		q_pop(pQue);
	};
};

bool create_treelist(tree* root, queue* pQue)
{
	node* cursor = NULL;
	node* head = malloc(sizeof(node));
	if ((NULL == head) || (NULL == root))
	{
		return false;
	};

	head->pNode = root;
	q_insert(pQue, head);
	cursor = head;
	while (NULL != cursor)
	{
		if (NULL != cursor->pNode->left)
		{
			node* tmpNode = malloc(sizeof(node));
			if (NULL == tmpNode)
			{
				return false;
			};

			tmpNode->pNode = cursor->pNode->left;
			q_insert(pQue, tmpNode);
		};
		if (NULL != cursor->pNode->right)
		{
			node* tmpNode = malloc(sizeof(node));
			if (NULL == tmpNode)
			{
				return false;
			};

			tmpNode->pNode = cursor->pNode->right;
			q_insert(pQue, tmpNode);
		};
		cursor = cursor->next;
	};
	return true;
};

void print_treelist(queue* pQue)
{
	if (NULL == pQue)
	{
		return;
	};

	while (NULL != pQue->head)
	{
		printf("*%d*", pQue->head->pNode->id);
		q_pop(pQue);
	};
	printf("\n");
};

void print_tree_q(queue* pQue)
{
	tree* line = NULL;
	if (NULL != pQue->head->pNode->left)
	{
		line = pQue->head->pNode->left;
	}
	else if (NULL != pQue->head->pNode->right)
	{
		line = pQue->head->pNode->right;
	};

	while (NULL != pQue->head)
	{
		if (line == pQue->head->pNode)
		{
			printf("\n");
			line = NULL;
		};
		if (NULL == line)
		{
			if (NULL != pQue->head->pNode->left)
			{
				line = pQue->head->pNode->left;
			}
			else if (NULL != pQue->head->pNode->right)
			{
				line = pQue->head->pNode->right;
			};
		};
		printf("*%d*", pQue->head->pNode->id);
		q_pop(pQue);
	};
	printf("\n");
};

void q_2d_insert(twodque* que, twodlk* pNode)
{
	if (NULL == que)
	{
		return;
	};
	if (NULL == que->head)
	{
		pNode->next = NULL;
		pNode->prev = NULL;
		que->head = pNode;
		que->tail = pNode;
	}
	else
	{
		pNode->next = NULL;
		pNode->prev = que->tail;
		que->tail->next = pNode;
		que->tail = pNode;
	};
};

void q_2d_pop(twodque* que)
{
	twodlk* tmpNode = que->head;
	que->head = que->head->next;
	if (NULL != que->head)
	{
		que->head->prev = NULL;
	};
	free(tmpNode->pNode);
	free(tmpNode);
};

void q_2d_destroy(twodque* pQue)
{
	if (NULL == pQue)
	{
		return;
	};
	while (NULL != pQue->head)
	{
		q_2d_pop(pQue);
	};
};

void create_tree_que(queue* pQue, twodque* p2dque)
{
	tree* line = pQue->head->pNode;
	node* cursor = NULL;
	cursor = pQue->head;
	twodlk* tmpQue = NULL;
	queue* tmpList = NULL;
	while (NULL != cursor)
	{
		if (line == cursor->pNode)
		{
			tmpQue = malloc(sizeof(twodlk));
			memset(tmpQue, 0, sizeof(twodlk));
			tmpList = malloc(sizeof(queue));
			memset(tmpList, 0, sizeof(queue));
			if (NULL != tmpQue)
			{
				if (NULL != tmpList)
				{
					tmpList->head = cursor;
					tmpList->tail = tmpList->head;
				};
				tmpQue->pNode = tmpList;
				tmpQue->next = NULL;
				tmpQue->prev = NULL;
			};
			q_2d_insert(p2dque, tmpQue);
			line = NULL;
		};
		if (NULL == line)
		{
			if (NULL != cursor->pNode->left)
			{
				line = cursor->pNode->left;
			}
			else if (NULL != cursor->pNode->right)
			{
				line = cursor->pNode->right;
			};
		};
		tmpList->tail = cursor;
		cursor = cursor->next;
	};
};

void print_tree_que(twodque* pQue)
{
	twodlk* line = pQue->head;
	while (line != NULL)
	{
		node* tmpNode = line->pNode->head;
		while (NULL != tmpNode)
		{
			printf("**%3d**", tmpNode->pNode->id);
			if (line->pNode->tail == tmpNode)
			{
				break;
			};
			tmpNode = tmpNode->next;
		};
		printf("\n");
		line = line->next;
	};
};

int max_index(twodlk* p2dlk, node* pNode)
{
	node* tmpNode = p2dlk->pNode->head;
	int index = 1;
	while (tmpNode != pNode)
	{
		if (tmpNode->pNode->index > index)
		{
			index = tmpNode->pNode->index;
		};
		if (tmpNode == p2dlk->pNode->tail)
		{
			break;
		};
		tmpNode = tmpNode->next;
	};
	return index;
};

void update_f_index(twodlk* p2dlk)
{
	node* tmpNode = NULL;
	int index = 0;
	bool ischange = false;

	if (NULL != p2dlk)
	{
		tmpNode = p2dlk->pNode->head;
		while (NULL != tmpNode)
		{
			index = 0;
			if (NULL != tmpNode->pNode->left)
			{
				index = tmpNode->pNode->left->index + 1;
			}
			else if (NULL != tmpNode->pNode->right)
			{
				index = tmpNode->pNode->right->index - 1;
			};
			if (index > tmpNode->pNode->index)
			{
				tmpNode->pNode->index = index;
				ischange = true;
			};
			if (p2dlk->pNode->tail == tmpNode)
			{
				break;
			};
			tmpNode = tmpNode->next;
		};
		if (!ischange)
		{
			return;
		};
		update_f_index(p2dlk->prev);
	};
};

void update_tree_index(twodque* p2dque)
{
	twodlk* cursor = p2dque->head;
	node* pNode = NULL;
	int index = 1;
	while (NULL != cursor)
	{
		pNode = cursor->pNode->head;
		index = 1;
		while (NULL != pNode)
		{
			if(index != 1)
			{
				if(pNode->prev->pNode->index >= pNode->pNode->index)
				{
					pNode->pNode->index = pNode->prev->pNode->index+1;
				};
			};
			if(NULL != pNode->pNode->left)
			{
				if(1 == pNode->pNode->index)
				{
					pNode->pNode->index ++;
				};
				pNode->pNode->left->index = pNode->pNode->index - 1;
			};
			if(NULL != pNode->pNode->right)
			{
				pNode->pNode->right->index = pNode->pNode->index + 1;
			};
			index++;
			if (cursor->pNode->tail == pNode)
			{
				break;
			};
			pNode = pNode->next;
		};
		update_f_index(cursor->prev);
		cursor = cursor->next;
	};
};

void print_blank(int num)
{
	for (int i = 0; i< num; i++)
	{
		printf(" ");
	};
};

void print_golden(twodque* p2dque)
{
	twodlk* cursor = p2dque->head;
	node* pNode = NULL;
	while (NULL != cursor)
	{
		printf("\n");
		pNode = cursor->pNode->head;
		while (NULL != pNode)
		{
			if (pNode->pNode->index > 1)
			{
				print_blank(pNode->pNode->index - pNode->prev->pNode->index);
			};
			printf("%d", pNode->pNode->id);
			if (cursor->pNode->tail == pNode)
			{
				break;
			};
			pNode = pNode->next;
		};
		cursor = cursor->next;
	};
};

void* init_map(tree* root)
{
	int** p_map = NULL;
	int dep = 0;
	int wid = 1;
	if (NULL == root)
	{
		return NULL;
	};
	dep = (root->ld>root->rd) ? (root->ld) : (root->rd);
	wid = root->lwd + root->rwd;
	p_map = (int**)malloc((dep + 1) * sizeof(int*));
	if (NULL == p_map)
	{
		return NULL;
	};
	memset(p_map, 0, (dep + 1) * sizeof(int**));
	for (int i = 0; i<dep; i++)
	{
		p_map[i] = (int*)malloc((wid) * sizeof(int));
		if (NULL != p_map[i])
		{
			memset(p_map[i], 0, (wid) * sizeof(int));
			p_map[i][wid-1] = 0xFFFFFFFF;
		};
	};
	p_map[dep] = NULL;
	return p_map;
};

void update_map(int ** p_map, tree* root, int level, int index)
{
	if ((0 > level) || (0 > index) || (NULL == root) || (NULL == p_map))
	{
		return;
	};
	p_map[level][index] = root->id;
	update_map(p_map, root->left, level + 1, index - 1);
	update_map(p_map, root->right, level + 1, index + 1);
};

void free_map(int** p_map)
{
	int index = 0;
	while (NULL != p_map[index])
	{
		free(p_map[index]);
		index++;
	};
	free(p_map);
};

bool update_tree(tree* root)
{
	int dep = depth(root);
	int lwd = l_width(root);
	int rwd = r_width(root);
	if ((0 != dep) || (0 != lwd + rwd))
	{
		return true;
	};
	return false;
};

void print_tree(tree* root, int ** p_map)
{
	int dep = (((root->ld)>(root->rd)) ? (root->ld) : (root->rd));
	printf("\ndep:%d left width:%d  right width:%d\n", dep, root->lwd, root->rwd);
	if ((NULL == root) || (NULL == p_map))
	{
		return;
	};
	if (1 == root->id)   //tree's root
	{
		for (int i = 0; i<dep; i++)
		{
			for (int j = 0; j<(root->lwd + root->rwd)-1; j++)
			{
				if (0 == p_map[i][j])
				{
					printf("%3s", " ");
				}
				else
				{
					printf("%3d", p_map[i][j]);
				};
			};
			printf("\n");
		};
	};
};

void print_prompt()
{
	printf("\n******************************\n");
	printf("*show this tree please input 's'*******\n");
	printf("*insert node please input 'i'**********\n");
	printf("*delete node please input 'd'*********\n");
	printf("*print tree que please input 't'********\n");
	printf("*print detail tree queue please input 'f'*\n");
	printf("*print tree list please input 'p'********\n");
	printf("*quit please input 'q'***************\n");
	printf("printf golden tree input 'g'***********\n");
	printf("*print prompt please input '?'********\n");
	printf("********************************\n");
};
void main()
{
	int ** pp_map = NULL;
	int new_id = 0;
	int id = 0;
	char flag = 0;
	char contor = ' ';
	tree* root = malloc(sizeof(tree));
	memset(root, 0, sizeof(tree));
	queue que = { 0 };
	twodque d2que = { 0 };

	if (!init_node(root))
	{
		printf("\nsystem happened unknown fault!\n");
		return;
	};
	root->id = 1;
	print_prompt();

	while (true)
	{
		setbuf(stdin, NULL);
		scanf("%c", &contor);
		setbuf(stdin, NULL);
		switch (contor)
		{
		case 's':
			pp_map = init_map(root);
			update_map(pp_map, root, 0, root->lwd - 1);
			print_tree(root, pp_map);
			free_map(pp_map);
			pp_map = NULL;
			break;
		case 'i':
			printf("\n please input node id which you want insert:");
			setbuf(stdin, NULL);
			scanf("%d", &new_id);
			setbuf(stdin, NULL);
			if (NULL != search(root, new_id))
			{
				printf("\nthis node is exists");
			}
			else
			{
				printf("\n please input father node id whose you want insert:");
				setbuf(stdin, NULL);
				scanf("%d", &id);
				setbuf(stdin, NULL);
				if (NULL != search(root, id))
				{
					printf("\n please input node flag which you want insert:(l/r)  ");
					setbuf(stdin, NULL);
					scanf("%c", &flag);
					setbuf(stdin, NULL);
					tree* tmpNode = search(root, id);
					if (false == insert_tree(tmpNode, flag, new_id))
					{
						printf("\ninsert node is failed!\n");
					}
					else
					{
						if (!update_tree(root))
						{
							printf("\nhapped some unknown fault!\n");
						};
					};
				}
				else
				{
					printf("\n the father node is not exists  \n");
				};
			};
			break;
		case 'd':
			printf("\n please input node id which you want delete:");
			setbuf(stdin, NULL);
			scanf("%d", &new_id);
			setbuf(stdin, NULL);
			tree* tmpNode1 = NULL;
			tree* tmpNode2 = NULL;
			tmpNode1 = search_f_node(root, new_id);
			tmpNode2 = search(root, new_id);
			if ((NULL != tmpNode1) && (tmpNode1->left != NULL))
			{
				if (tmpNode1->left->id == new_id)
				{
					tmpNode1->left = NULL;
				};
			}
			else if ((NULL != tmpNode1) && (tmpNode1->right != NULL))
			{
				if (tmpNode1->right->id == new_id)
				{
					tmpNode1->right = NULL;
				};
			};
			if (NULL == tmpNode2)
			{
				printf("\nthis node is not exists");
				break;
			}
			else
			{
				delete_tree(tmpNode2);
				update_tree(root);
			};
			break;
		case 'q':
			printf("it's time to quit!\n");
			delete_tree(root);
			return;
		case '?':
			print_prompt();
			break;
		case 'p':
			printf("***print tree list as follow*****");
			memset(&que, 0, sizeof(queue));
			create_treelist(root, &que);
			print_treelist(&que);
			break;
		case 't':
			printf("***print tree queue as follow*****\n");
			memset(&que, 0, sizeof(queue));
			create_treelist(root, &que);
			print_tree_q(&que);
			break;
		case 'f':
			printf("***print tree queue by line as follow*****\n");
			memset(&que, 0, sizeof(queue));
			create_treelist(root, &que);
			create_tree_que(&que, &d2que);
			print_tree_que(&d2que);
			q_2d_destroy(&d2que);
			q_destroy(&que);
			break;
		case 'g':
			printf("***print golden tree  as follow*****\n");
			memset(&que, 0, sizeof(queue));
			create_treelist(root, &que);
			create_tree_que(&que, &d2que);
			update_tree_index(&d2que);
			print_golden(&d2que);
			q_2d_destroy(&d2que);
			break;
		default:
			break;
		};
	};
};
