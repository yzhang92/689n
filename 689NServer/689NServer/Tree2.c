#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode
{
	int ascii;
	char *hostname;
	int *reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

treeNode *FindMin2(treeNode *node)
{
	if (node == NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if (node->left) /* Go to the left sub tree to find the min element */
		return FindMin2(node->left);
	else
		return node;
}

treeNode* FindMax2(treeNode *node)
{
	if (node == NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if (node->right) /* Go to the left sub tree to find the min element */
		FindMax2(node->right);
	else
		return node;
}

treeNode * Insert2(treeNode *node, treeNode *new_node)
{
	if (node == NULL)
	{
		return new_node;
	}

	if ((node->reqTimes) >(node->reqTimes))
	{
		node->right = Insert2(node->right, new_node);
	}
	else if ((node->reqTimes) < (node->reqTimes))
	{
		node->left = Insert2(node->left, new_node);
	}
	/* Else there is nothing to do as the reqTimes is already in the tree. */
	return node;

}