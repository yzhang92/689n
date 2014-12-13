#include <stdio.h>
#include <winsock.h>

char *GetIpByName(char *hostname) {
	struct sockaddr_in addr;
	struct hostent* h;

	h = gethostbyname(hostname);

	if (h == NULL) {
		return NULL;
	}
	char * ipbuf;
	addr.sin_addr = *(struct in_addr*) h->h_addr;
	ipbuf = inet_ntoa(addr.sin_addr);
	return ipbuf;
}