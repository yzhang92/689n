# include <stdio.h>
# include <string.h>
# include <winsock.h>

#define SECURITYCODE "689_IS_AWESOME"

typedef struct treeNode
{
	int ascii;
	char *hostname;
	int *reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;


int StrToInt(char *);
int InputLoggerFile(char *);
void SendBackServerRespond(int, char const *);
void CloseClnSock(int clnsock);
treeNode *BuildTree(char *);
int GetAscii(char *);
treeNode *Find(treeNode *, int);
char *ArrToStr(char **);
char *GetIpByName(char *);


int Switching(char ** para_arr, char *dataFileName, int clnclock) {

	int req_num = StrToInt(para_arr[0]);
	int ascii;
	treeNode *root =  NULL;
	treeNode *node = NULL;
	char *sendBackInfo;
	root = BuildTree(dataFileName);
	char **ip_arr;
	char *ip;
	FILE *file;
	

	switch (req_num) {

	case 1:
		SendBackServerRespond(clnclock,"Test: get case 1");
		ascii = GetAscii(para_arr[0]);
		node = Find(root, ascii);
		if (node == NULL) {
			InputLoggerFile("Ip address not found.Try to find it.");
			node = malloc(sizeof(treeNode));
			node->ascii = GetAscii(para_arr[0]);
			node->hostname = para_arr[0];
			node->reqTimes = 0;
			ip_arr = malloc(sizeof(char *));
			if (ip = GetIpByName(para_arr[0]) == NULL){
				InputLoggerFile("Ip address not found by using gethostbyname().");
				SendBackServerRespond("Ip address not found.", clnclock);
				CloseClnSock(clnclock);
				free(node);
			}
			else {
				InputLoggerFile("Ip address is found.");
				SendBackServerRespond(ip, clnclock);
				CloseClnSock(clnclock);
				InputLoggerFile("Adding new record into database...");
				ip_arr[0] = ip;
				node->ipaddress = ip_arr;
				node->left = NULL;
				node->right = NULL;
				root = insert1(root, node);
				fopen(dataFileName, "w");

			}
			


		}
		else {
			InputLoggerFile("Ip address found.");
			sendBackInfo = ArrToStr(node->ipaddress);
			SendBackServerRespond(sendBackInfo, clnclock);
			CloseClnSock(clnclock);
		}
		/* send back result */
		break;
	case 2:
		SendBackServerRespond(clnclock,"Test: get case 2");

		/* if (AlreadyExist(para_arr, tree) == 1) return 0; */
		/* insert entry*/
		break;

	case 3:
		SendBackServerRespond(clnclock,"Test: get case 3");

		/* if (AlreadyExist(para_arr, tree) == 0) return 0 */
		/* deleting entry */
		break;

	case 4: 
		SendBackServerRespond(clnclock, "Test: get case 4");

		/* return most requested record */
		break;

	case 5:
		SendBackServerRespond(clnclock, "Test: get case 5");

		/* return least requested record */
		break;

	case 6:
		InputLoggerFile("Clinet is attempting shutting down the server. (Request = 6)");
		InputLoggerFile("Checking the security code...");
		if (strcmp(para_arr[1], SECURITYCODE) != 0) {
			InputLoggerFile("Security code check failed. Closing the client side.");
			SendBackServerRespond(clnclock, "Security code check failed");
			CloseClnSock(clnclock);
		}
		else{
			InputLoggerFile("Security code check passed. Closing the server.");
			SendBackServerRespond(clnclock, "Security code check passed. Server is closed");
			closesocket(clnclock);
			InputLoggerFile("Server is shutted Down.");
			exit(1);
		}

		/* if (CodeSame() == 0) return 0;*/
		/* terminate server ;*/
		break;

	
	default:
		return 0;
	}

	/* update the tree and put data into database */
	return 1;
}