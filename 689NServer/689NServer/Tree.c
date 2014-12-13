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


treeNode *FindMin1(treeNode *node)
{
	if (node == NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if (node->left) /* Go to the left sub tree to find the min element */
		return FindMin1(node->left);
	else
		return node;
}
treeNode * Insert1(treeNode *node, treeNode *new_node)
{
	if (node == NULL)
	{
		return new_node;
	}

	if ((new_node->ascii) >= (node->ascii))
	{
		node->right = Insert1(node->right, new_node);
	}
	else if ((new_node->ascii) < (node->ascii))
	{
		node->left = Insert1(node->left, new_node);
	}
	/* Else there is nothing to do as the ascii is already in the tree. */
	return node;

}

treeNode * Delete(treeNode *node, int ascii)
{
	treeNode *temp;
	if (node == NULL)
	{
		printf("Element Not Found");
	}
	else if (ascii < node->ascii)
	{
		node->left = Delete(node->left, ascii);
	}
	else if (ascii > node->ascii)
	{
		node->right = Delete(node->right, ascii);
	}
	else
	{
		/* Now We can delete this node and replace with either minimum element
		in the right sub tree or maximum element in the left subtree */
		if (node->right && node->left)
		{
			/* Here we will replace with minimum element in the right sub tree */
			temp = FindMin1(node->right);
			node->ascii = temp->ascii;
			/* As we replaced it with some other node, we have to delete that node */
			node->right = Delete(node->right, temp->ascii);
		}
		else
		{
			/* If there is only one or zero children then we can directly
			remove it from the tree and connect its parent to its child */
			temp = node;
			if (node->left == NULL)
				node = node->right;
			else if (node->right == NULL)
				node = node->left;
			free(temp); /* temp is longer required */
		}
	}
	return node;

}

treeNode *Find(treeNode *node, int ascii)
{
	if (node == NULL)
	{
		/* Element is not found */
		return NULL;
	}
	if (ascii > node->ascii)
	{
		/* Search in the right sub tree. */
		return Find(node->right, ascii);
	}
	else if (ascii < node->ascii)
	{
		/* Search in the left sub tree. */
		return Find(node->left, ascii);
	}
	else
	{
		/* Element Found */
		return node;
	}
}

void WriteTreeIntoDatabase(treeNode *node, char *filename)
{
	FILE *file = fopen(filename, "w");
	if (node == NULL)
	{
		return;
	}
	PrintInorder(node->left);

	PrintInorder(node->right);
}

