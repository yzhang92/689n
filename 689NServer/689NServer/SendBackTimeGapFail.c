#include <winsock.h>
#include <string.h>
#include <stdlib.h>
/*
	this is where error may happened.
*/
void SendBackTimeGapFail(int clntSocket,  char const *str) {
	
	

	send(clntSocket, str, strlen(str) + 1, 0);
	InputLoggerFile("Alert sent. Close Client Socket.");
	closesocket(clntSocket);

}