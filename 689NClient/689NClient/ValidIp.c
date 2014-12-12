#include <Winsock2.h>


int ValidIp(char ** ip, int numberOfIp){
	int flag = 1;
	for (int i = 0; i < numberOfIp; i++) {
		if (inet_addr(ip[i]) == INADDR_NONE) {
			flag = 0;
		}
	}
	return flag;
}