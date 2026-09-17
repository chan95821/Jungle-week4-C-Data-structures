//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode
{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode; // You should not change the definition of BSTNode

typedef struct _stackNode
{
	BSTNode *data;
	struct _stackNode *next;
} StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
} Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root) // ㅗ
{

	if (root == NULL)
	{
		return;
	}
	/* add your code here */
	Stack *s = malloc(sizeof(Stack));
	BSTNode *cur = root;
	BSTNode *prev_processed = root;
	push(s, root);
	while (!isEmpty(s))
	{ // push시 항상 자식만 넣는다. // prev processed는 상위노드이거나 / 자식인 경우  
		cur = peek(s);
		// prev_processed 부터 먼저 케이스 분리하기
		if (prev_processed != cur->left && prev_processed != cur->right) //prev_processed는 항상 NULL아니다.
		{
			if (cur->left != NULL) // left 있는데 prev 아니므로, left가 처리 안됨
				push(s, cur->left);
			else if (cur->right != NULL) // left 없고 right 있는데 prev 아니므로, right 처리 안됨
				push(s, cur->right);
			else // 둘다 없으니 바로 pop
			{
				printf("%d ", cur->item);
				pop(s);
			}
		}
		else if (prev_processed == cur->left)
		{
			if (cur->right != NULL) //right 탐색
				push(s, cur->right);
			else
			{
				printf("%d ", cur->item);
				pop(s);
			}
		}
		else // cur->right인 경우만 남음
		{
			printf("%d ", cur->item);
			pop(s);
		}

		prev_processed = cur;
	}

	free(s);
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value > (*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode *pop(Stack *s)
{
	StackNode *temp, *t;
	BSTNode *ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode *peek(Stack *s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
