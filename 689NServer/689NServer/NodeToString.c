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

char *ArrToStr(char **);

char *NodeToString(treeNode *node) {
	if (node == NULL) return "";
	char *hostname = node->hostname;
	char requestNum[5];
	sprintf(requestNum, "%d", node->reqTimes);
	char *ips = ArrToStr(node->ipaddress);
	int len = strlen(hostname) + strlen(requestNum) + strlen(ips) + 4;
	char *text = malloc(len);
	text[len] = '\0';
	strcpy(text, hostname);
	strcat(text, " ");
	strcat(text, requestNum);
	strcat(text, " ");
	strcat(text, ips);
	strcat(text, "\n");
	return text;

}