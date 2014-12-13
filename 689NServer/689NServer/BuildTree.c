# include <stdio.h>
# include <string.h>
# include <winsock.h>

typedef struct treeNode
{
	int ascii;
	char *hostname;
	int *reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

char **StrToArray(char *);
int GetAscii(char *);

treeNode *BuildTree(char *fileName) {

	FILE *file = fopen(fileName, "r");
	long file_pos = 0;
	char *str;
	int count = 0;
	int i = 0;
	char ch;
	char **temp;
	treeNode *root = NULL;
	treeNode *new_node = NULL;
	int lenOfArr;
	char **str_arr;

	do{
		file_pos = ftell(file);
		do{
			ch = getc(file);
			if (ch == '\n' || ch == EOF) break;
			count++;
		} while (1);
		str = malloc(count + 1);
		str[count] = '\0';
		fseek(file, file_pos, SEEK_SET);
		while (i < count){
			str[i] = getc(file);
			i++;
		}
		count = 0;
		i = 0;
		file_pos = ftell(file);
		file_pos += 1;
		printf("%s\n", str);
		if (strlen(str) == 0){
			return root;
		}
		else {
			temp = StrToArray(str);
			lenOfArr = sizeof(temp) / sizeof(char *);
			new_node = malloc(sizeof(treeNode));
		    new_node->ascii = GetAscii(temp[0]);
			new_node->hostname = temp[0];
			new_node->reqTimes = 0;
			str_arr = malloc((lenOfArr - 2) * sizeof(char *));
			for (int i = 0; i < lenOfArr - 2; i++){
				str_arr[i] = temp[i + 2];
			}
			new_node->ipaddress = str_arr;
			new_node->left = NULL;
			new_node->right = NULL;
			root = Insert1(root, new_node);
		}
	} while (fgetc(file) != EOF);
	return root;



}
