#include <winsock.h>

void InputLoggerFile(char *);

void CloseClnSock(int clnsock) {
	closesocket(clnsock);
	InputLoggerFile("Client Socket Closed. Waiting for another clinet...");

}