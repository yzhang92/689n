#include <stdio.h>      /* for printf(), fprintf() */
#include <stdlib.h>     /* for exit() */
#include <Winsock2.h>

bool isValidIpAddress(char *ipAddr)
{
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ipAddr, &(sa.sin_addr));
	return result != 0;
}