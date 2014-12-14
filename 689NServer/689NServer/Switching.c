# include <stdio.h>
# include <string.h>
# include <winsock.h>

#define SECURITYCODE "689_IS_AWESOME"

typedef struct treeNode
{
	char *hostname;
	int reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;


int StrToInt(char *);
int InputLoggerFile(char *);
void SendBackServerRespond(int, char const *);
void CloseClnSock(int clnsock);
int GetAscii(char *);
char *ArrToStr(char **);
char *GetIpByName(char *);


treeNode *Switching(char ** para_arr, char *dataFileName, int clnclock, treeNode *root) {
	int req_num = StrToInt(para_arr[0]);
	int ascii;
	treeNode *node = NULL;
	char *sendBackInfo;
	char **ip_arr;
	char *ipp;
	char *ip;
	int len;
	FILE *file;
	int numbOfArr;

	switch (req_num) {

	case 1:
		node = Find(root, para_arr[1]);

		if (node == NULL) {
			InputLoggerFile("Ip address not found.Try to find it.");
			if ((ip = GetIpByName(para_arr[1])) == NULL){
				InputLoggerFile("Ip address not found by using gethostbyname().");
				SendBackServerRespond(clnclock, "Ip address not found.");
			}
			else {
				len = strlen(ip);
				printf("%d\n", len);
				ipp = malloc((len + 1) * sizeof(char));
				ipp[len] = '\0';
				strcpy(ipp, ip);
				printf("%s\n", ipp);
				InputLoggerFile("Ip address is found.");
				node = malloc(sizeof(treeNode));
				node->hostname = para_arr[1];
				node->reqTimes = 1;
				ip_arr = malloc(2 *sizeof(char *));
				ip_arr[0] = ipp;
				printf("%s\n", ip_arr[0]);
				ip_arr[1] = NULL;
				node->ipaddress = ip_arr;
				node->left = NULL;
				node->right = NULL;
				SendBackServerRespond(clnclock, ip);
				InputLoggerFile("Adding new record into database...");
				root = Insert1(root, node);
				InputLoggerFile("Display the new try");
			}
		}
		else {
			InputLoggerFile("Ip address found.");
			node->reqTimes += 1;
			sendBackInfo = ArrToStr(node->ipaddress);
			SendBackServerRespond(clnclock, sendBackInfo);
		}
		PrintInOrder(root);

		break;

	case 2:
		if (node = Find(root, para_arr[1]) != NULL) {
			InputLoggerFile("Record with the same hostname exists. Please try another one.");
			SendBackServerRespond(clnclock, "Record with the same hostname exists. Please try another one.");
		}
		else {
			InputLoggerFile("Record with the same hostname does not exist. Adding to the database.");
			node = malloc(sizeof(treeNode));
			node->hostname = para_arr[1];
			node->reqTimes = 1;
			numbOfArr = -1;
			while (para_arr[++numbOfArr] != NULL);
			int count = numbOfArr + 1 - 2;
			ip_arr = malloc(count * sizeof(char *));
			ip_arr[count - 1] = NULL;
			for (int i = 0; i < count - 1; i++) {
				ip_arr[i] = para_arr[i + 2];
			}
			node->ipaddress = ip_arr;
			node->left = NULL;
			node->right = NULL;
			root = Insert1(root, node);
			PrintInOrder(root);
			SendBackServerRespond(clnclock , "Adding record to database successed.");
			InputLoggerFile("Adding record to database successed.");
		}
		PrintInOrder(root);

		break;

	case 3:
		if ((node = Find(root, para_arr[1])) == NULL) {
			InputLoggerFile("Record with the same hostname does not exist. Please try another one.");
			SendBackServerRespond(clnclock, "Record with the same hostname does not exist. Please try another one.");
		}
		else {
			root = Delete(root, para_arr[1]);
			InputLoggerFile("Record with the same hostname is found and deleted.");
			SendBackServerRespond(clnclock, "Record with the same hostname is found and deleted.");
		}
		PrintInOrder(root);

		break;

	case 4: 
		PrintInOrder(root);
		int max = FindMax(root);
		if (max == -1) {
			InputLoggerFile("Database is empty. No record found.");
			SendBackServerRespond(clnclock, "Error: Database is empty. No record returned.");
		}
		else{
			sendBackInfo = FindReq(root, max);
			InputLoggerFile("Most requested record is found. Send back to the client.");
			SendBackServerRespond(clnclock, sendBackInfo);
		}
		
		break;

	case 5:
		PrintInOrder(root);
		int min = FindMin(root);
		if (min == 999) {
			InputLoggerFile("Database is empty. No record found.");
			SendBackServerRespond(clnclock, "Error: Database is empty. No record returned.");
		}
		else{
			sendBackInfo = FindReq(root, min);
			InputLoggerFile("Most requested record is found. Send back to the client.");
			SendBackServerRespond(clnclock, sendBackInfo);
		}
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
			ShutDown(root, dataFileName);
			exit(1);
		}
		break;	
	default:
		break;
	}
	return root;
}