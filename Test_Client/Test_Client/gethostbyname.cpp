#include <stdio.h>    /* for fprintf() */
#include <winsock.h>  /* for WSAGetLastError() */
#include <stdlib.h>   /* for exit() */
char * smtpIp(char * url)
{
	HOSTENT * iphost;
	char ipconfig[20];

	if ((iphost = gethostbyname(url)) != NULL)
	{
		int i = 0;

		while (iphost->h_addr_list[i])
		{
			char ip[20];
			memcpy(&ip, inet_ntoa(*((struct in_addr *)iphost->h_addr_list[i])), 20);
			printf("%s", ip);
			memset(ip, '\0', 20);
			i++;
		}
	}
	else return 0;
}