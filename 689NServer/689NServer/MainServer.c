#include <stdio.h>     
#include <winsock.h>   
#include <stdlib.h> 
#include <string.h>
#include <time.h>

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFFERSIZE 256

typedef struct treeNode
{
	char *hostname;
	int reqTimes;
	char **ipaddress;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

void InputLoggerFile(char *message);
int StrToInt(char *str);
int ErrorCheckForInput(int port, char *filename, int timeGap);
void SendBackServerRespond(int clntSocket, char const *str);
int ReqErrorCheck(int clntSocket);
char *GetInforfromClnt(int clntSocket);
void HandleTCPClient(int clntSocket);
char **SplitRecvMessage(char *recvMessage);
int Switching(char **, char *, int, treeNode *);
void CloseClnSock(int);



void main(int argc, char *argv[]) {

//------------------Declaration-------------------------------

	unsigned short servPort;     /* Server port */
	char *dataFileName;              /*Data File Name*/
	int timeGap;                       /*Time Gap*/

	int servSock;                        /* Socket descriptor */
	int clntSock;
	WSADATA wsaData;                 /* Structure for WinSock setup communication */
	struct sockaddr_in ServAddr;
	struct sockaddr_in ClntAddr;
	int clntLen;
	char *message;
	char *recInfor;
	char **recvParameter; 
	char *originIp = "";
	char *curIp;
	time_t lastTime = 0;
	time_t curTime;

	char Buffer[RCVBUFFERSIZE];        /* Buffer for echo string */
	int recvMsgSize;                    /* Size of received message */
	treeNode *root = NULL;

	InputLoggerFile("The Server Started. Begin input check...");

//---------------server input error check-----------------------------
	if (argc != 4) {
		fprintf(stderr, "Usage:  %s <Server Port> <Data File Name> <Time Gap>\n", argv[0]);
		InputLoggerFile("Wrong Input Number. Server shuts down.\n\n\n");
		exit(1);
	}

	if ((servPort = StrToInt(argv[1])) == 0) {
		InputLoggerFile("InputCheck failed. Server shuts down.\n\n\n");
		exit(1);
	}
	dataFileName = argv[2];
	if ((timeGap = StrToInt(argv[3])) == 0) {
		InputLoggerFile("InputCheck failed. Server shuts down.\n\n\n");
		exit(1);
	}

	if (ErrorCheckForInput(servPort, dataFileName, timeGap)) {
		InputLoggerFile("InputCheck failed. Server shuts down.\n\n\n");
		exit(1);
	}

	InputLoggerFile("InputCheck successed.Start building socket.");
//--------------------------Building the tree--------------------------------------
	InputLoggerFile("Tree is built.");
	root = BuildTree(dataFileName);
	PrintInOrder(root);
//--------------------------set up socket-------------------------------------------
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	{
		InputLoggerFile("Socket Setting Up Failed.(WSAStartup() failed)\n\n\n");
		ShutDown(root, dataFileName);
		exit(1);
	}

	/* Create socket for incoming connections */
	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		InputLoggerFile("Socket Setting Up Failed.(WSAStartup() failed)\n\n\n");
		ShutDown(root, dataFileName);
		exit(1);
	}

	/* Construct local address structure */
	memset(&ServAddr, 0, sizeof(ServAddr));   /* Zero out structure */
	ServAddr.sin_family = AF_INET;                /* Internet address family */
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	ServAddr.sin_port = htons(servPort);      /* Local port */

	/* Bind to the local address */
	if (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) {
		InputLoggerFile("Socket Setting Up Failed.(bind() failed)\n\n\n");
		ShutDown(root, dataFileName);
		exit(1);
	}

	/* Mark the socket so it will listen for incoming connections */
	if (listen(servSock, MAXPENDING) < 0) {
		InputLoggerFile("Socket Setting-up failed. (listen() failed)\n\n\n");
		ShutDown(root, dataFileName);
		exit(1);
	}
	InputLoggerFile("Socket Setting-up successed. Waiting for Client...");

	for (;;) /* Run forever */
	{


		/* Set the size of the in-out parameter */
		clntLen = sizeof(ClntAddr);

		/* Wait for a client to connect */
		if ((clntSock = accept(servSock, (struct sockaddr *) &ClntAddr, &clntLen)) < 0) {
			InputLoggerFile("Building connection failed. (accpet()) failed");
			CloseClnSock(clntSock);
			continue;
		} 

//----------------------A request Builded-------------------------------------------------
		/* form a log infor*/

		message = StringAppend("Cline: ", inet_ntoa(ClntAddr.sin_addr));

		message = StringAppend(message," attampts to connect server.");

		InputLoggerFile("------------------------------------------------");

		InputLoggerFile(message);

//--------------------Time Gap Check--------------------------------------------------------
		curTime = time(NULL);
		curIp = inet_ntoa(ClntAddr.sin_addr);
		if (((lastTime == 0 || (curTime - lastTime) >= timeGap)) || ((strcmp(curIp, originIp) != 0) || (originIp == 0))) {
			InputLoggerFile("Time Gap check passed.");

//----------------------Decompose Infor-----------------------------------------------------
			if ((recvMsgSize = recv(clntSock, Buffer, RCVBUFFERSIZE, 0)) < 0) {
				InputLoggerFile("Recieving message failed. ");
				CloseClnSock(clntSock);
				continue;
			}

			Buffer[recvMsgSize] = '\0';
			recInfor = malloc(recvMsgSize + 1);
			recInfor[recvMsgSize] = '\0';
			strcpy(recInfor, Buffer);
			recvParameter = SplitRecvMessage(recInfor);
//-------------------------Switching-----------------------------------------------
			root = Switching(recvParameter, dataFileName, clntSock, root);
			CloseClnSock(clntSock);
			lastTime = curTime;
			originIp = curIp;
		}
		else {
			int diff = timeGap - (curTime - lastTime);
			InputLoggerFile("Time Gap check failed. Send fail response to the client side.");
			char *message;
			char str2[3];
			sprintf(str2, "%d", diff);
			message = StringAppend("Please wait another ", str2);
			message = StringAppend(message, " seconds before another submission.");
			SendBackServerRespond(clntSock, message);
			CloseClnSock(clntSock);
		}
	}
	
}