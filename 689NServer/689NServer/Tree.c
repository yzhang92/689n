#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct treeNode
{
	char *hostname;
	int *reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

int GetAscii(char *);

treeNode *Findmax1(treeNode *node)
{
	if (node == NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if (node->left) /* Go to the left sub tree to find the max element */
		return Findmax1(node->left);
	else
		return node;
}
treeNode * Insert1(treeNode *node, treeNode *new_node)
{
	if (node == NULL)
	{
		return new_node;
	}
	int ascii = GetAscii(new_node->hostname);

	if (ascii >= GetAscii(node->hostname))
	{
		node->right = Insert1(node->right, new_node);
	}
	else if ((ascii) < GetAscii(node->hostname))
	{
		node->left = Insert1(node->left, new_node);
	}
	/* Else there is nothing to do as the ascii is already in the tree. */
	return node;

}

treeNode * Delete(treeNode *node, char *hostname)
{
	treeNode *temp;
	if (node == NULL) {
		printf("not found\n");
	}
	else if (GetAscii(hostname) < GetAscii(node->hostname))
	{
		node->left = Delete(node->left, hostname);
	}
	else if (GetAscii(hostname) > GetAscii(node->hostname))
	{
		node->right = Delete(node->right, hostname);
	}
	else
	{
		if (strcmp(hostname, node->hostname) != 0) {
			node->right= Delete(node->right, hostname);
		}
		else {
			/* Now We can delete this node and replace with either maximum element
			in the right sub tree or maximum element in the left subtree */
			if (node->right && node->left)
			{
				/* Here we will replace with maximum element in the right sub tree */
				temp = Findmax1(node->right);
				node->hostname = temp->hostname;
				node->reqTimes = temp->reqTimes;
				node->ipaddress = temp->ipaddress;
				/* As we replaced it with some other node, we have to delete that node */
				node->right = Delete(node->right, temp->hostname);
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
	}
	return node;

}

treeNode *Find(treeNode *node, char *hostname)
{
	if (node == NULL)
	{
		/* Element is not found */
		return NULL;
	}
	if (GetAscii(hostname) > GetAscii(node->hostname))
	{
		/* Search in the right sub tree. */
		return Find(node->right, hostname);
	}
	else if (GetAscii(hostname) < GetAscii(node->hostname))
	{
		/* Search in the left sub tree. */
		return Find(node->left, hostname);
	}
	else
	{
		if (strcmp(hostname, node->hostname) != 0) 	return Find(node->right, hostname);

		return node;
	}
}

void WriteTreeIntoDatabase(treeNode *node, char *filename)
{	
	if (node == NULL)
	{
		return;
	}
	char *stringInfo = NodeToString(node);
	FILE *file = fopen(filename, "a");
	WriteTreeIntoDatabase(node->left, filename);
	fprintf(file, "%s", stringInfo);
	WriteTreeIntoDatabase(node->right, filename);
}


void PrintInOrder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
	PrintInOrder(node->left);
	printf("%s ", node->hostname);
	printf("%d " ,GetAscii(node->hostname));
	printf("%d\n", node->reqTimes);
	PrintInOrder(node->right);
}

int FindMax(treeNode *node)
{
	int max;
	if (node == NULL)
	{
		return -1;
	}
	int me = node->reqTimes;
	int right = FindMax(node->right);
	int left = FindMax(node->left);
	max = me;
	if (max < right) max = right;
	if (max < left) max = left;
	
	return max;
}

char *FindReq(treeNode *root, int index) {
	char *str;
	char *right;
	char *left;
	char *me;
	if (root == NULL) return NULL;
	if (root->reqTimes == index) me = NodeToString(root);
	else me = NULL;
	right = FindReq(root->right, index);
	left = FindReq(root->left, index);
	str = StringAppend(me, right);
	str = StringAppend(str, left);
	return str;
}

int FindMin(treeNode *node)
{
	int min;
	if (node == NULL)
	{
		return 999;
	}
	int me = node->reqTimes;
	int right = FindMin(node->right);
	int left = FindMin(node->left);
	min = me;
	if (min >= right) min = right;
	if (min >= left) min = left;

	return min;
}


