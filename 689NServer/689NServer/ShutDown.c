#include <stdlib.h>
#include <stdio.h>

typedef struct treeNode
{
	char *hostname;
	int reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

void ShutDown(treeNode *root, char *filename){
	FILE *file = fopen(filename, "w");
	WriteTreeIntoDatabase(root, filename);
	fclose(file);
	FreeTree(root);
	InputLoggerFile("Entrys were written back to the database. Server shutted down. ");
}