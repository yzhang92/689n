#include <winsock.h>
#include <string.h>
#include <stdlib.h>
/*
	this is where error may happened.
*/
void SendBackServerRespond(int clntSocket,  char const *str) {
	char *message;
	send(clntSocket, str, strlen(str) + 1, 0);
	message = StringAppend("Sending system message to the client. The content is: ", str);
	InputLoggerFile(message);
	closesocket(clntSocket);

}