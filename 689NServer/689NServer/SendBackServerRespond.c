#include <winsock.h>
#include <string.h>
#include <stdlib.h>
/*
	this is where error may happened.
*/
void SendBackServerRespond(int clntSocket,  char const *str) {
	
	send(clntSocket, str, strlen(str) + 1, 0);
	InputLoggerFile(str);

	closesocket(clntSocket);

}