#include<stdio.h>
#include<stdlib.h>



typedef struct treeNode
{
	int data;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

int main()
{
	treeNode *root = NULL;
	root = Insert(root, 5);
	root = Insert(root, -1);
	root = Insert(root, 3);
	root = Insert(root, -14);
	root = Insert(root, 8);
	root = Insert(root, 10);
	root = Insert(root, 9);
	root = Insert(root, 6);
	PrintInorder(root);
	printf("\n");
	root = Delete(root, 5);
	root = Delete(root, -1);
	PrintInorder(root);
	printf("\n");
	treeNode * temp;
	temp = FindMin(root);
	printf("Minimum element is %d\n", temp->data);
	temp = FindMax(root);
	printf("Maximum element is %d\n", temp->data);
	temp = Find(root, 8);
	if (temp == NULL)
	{
		printf("Element 8 not found\n");
	}
	else
	{
		printf("Element 8 Found\n");
	}
	temp = Find(root, 2);
	if (temp == NULL)
	{
		printf("Element 2 not found\n");
	}
	else
	{
		printf("Element 6 Found\n");
	}
}