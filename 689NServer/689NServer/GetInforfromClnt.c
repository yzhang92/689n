#include <winsock.h>
#include <time.h>

#define	BUFFERSIZE 50    /* Maximum size of receive buffer */

char *GetInforfromClnt(int clntSock) {

	time_t begTime;
	time_t curTime;

	char *str = "";
	char *temp;
	int last;
	int recvMsgSize;
	int totalRevMsgSize = 0;
	char ServBuffer[BUFFERSIZE];       /* SERVER BUFFER */

	while (1)    
	{
		if ((recvMsgSize = recv(clntSock, ServBuffer, BUFFERSIZE, 0)) < 0) {
			InputLoggerFile("recv() failed");
			exit(1);
		}
		if (totalRevMsgSize == 0) {
			begTime = time(NULL);
		}

		totalRevMsgSize += recvMsgSize;
		temp = malloc(recvMsgSize + 1);
		strcpy(temp, ServBuffer);
		temp[recvMsgSize] = '\0';

		str = StringAppend(str, temp);
		last = strlen(str) - 1;
		if (str[last] == '\n' && str[last - 1] == '\n') break;		

		curTime = time(NULL);
		if ((curTime - begTime) > 60) {
			InputLoggerFile("Long time no response from clinet. Cut connection.");
			/* send error back*/
			closesocket(clntSock);
			return NULL;
		}
	}
	return str;

}