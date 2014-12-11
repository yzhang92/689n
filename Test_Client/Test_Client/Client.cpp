/* CHANGES FROM UNIX VERSION                                                   */
/*                                                                             */
/* 1.  Changed header files.                                                   */
/* 2.  Added WSAStartUP() and WSACleanUp().                                    */
/* 3.  Used closesocket() instead of close().                                  */

#include <stdio.h>      /* for printf(), fprintf() */
#include <winsock.h>    /* for socket(),... */
#include <stdlib.h>     /* for exit() */
#include <string.h>

#define RCVBUFSIZE 256   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

void main(int argc, char *argv[])
{
	int sock;                        /* Socket descriptor */
	struct sockaddr_in echoServAddr; /* Echo server address */
	unsigned short echoServPort;     /* Echo server port */
	char *servIP;                    /* Server IP address (dotted quad) */
	//char *echoString;                /* String to send to echo server */
	char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
	//int echoStringLen;               /* Length of string to echo */
	int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() and total bytes read */
	WSADATA wsaData;                 /* Structure for WinSock setup communication */
	char *requestNum;
	char *hostname;
	char *ip;


	if (argc < 3)    /* Test for correct number of arguments */
	{
		fprintf(stderr, "Usage: %s <Server IP> <Request #> <Echo Word> [<Echo Port>]\n", argv[0]);
		exit(1);
	}

	servIP = argv[1];             /* First arg: server IP address (dotted quad) */
	//echoString = argv[2];         /* Second arg: string to echo */
	requestNum = argv[3];
	hostname = argv[4];


	struct hostent *hp = gethostbyname(argv[4]);
	char ipAddr[50];
	
	if (hp == NULL) 
	{
		printf("gethostbyname() failed\n");
	}
	else {
		printf("%s = ", hp->h_name);
		unsigned int i = 0;
		while (hp->h_addr_list[i] != NULL)
		{
			ip[i] = inet_ntoa(*(struct in_addr*)(hp->h_addr_list[i]));
		}

//		for (i = 0; hp->h_addr_list[i] != NULL;i++)
//		{
//			ip[i] = inet_ntoa(*(struct in_addr*)(hp->h_addr_list[i]));
			//printf("ip address is %s ", inet_ntoa(*(struct in_addr*)(hp->h_addr_list[i])));
//			i++;
//		}
		printf("\n");
	}


	//struct hostent *he;
	//struct in_addr **addr_list;
	//int i;
	//he = gethostbyname(argv[4]);
	//	printf("Official name is: %s\n", he->h_name);
	//	printf("    IP addresses: ");
	//addr_list = (struct in_addr **)he->h_addr_list;
	//for (i = 0; addr_list[i] != NULL; i++) {
	//printf("%s ", inet_ntoa(*addr_list[i]));
	//}
	//printf("\n");

	if (argc == 6)
		echoServPort = atoi(argv[2]); /* Use given port, if any */
	else
		echoServPort = 0;  /* otherwise, 7 is the well-known port for the echo service */

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}

	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithError("socket() failed");

	/* Construct the server address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
	echoServAddr.sin_family = AF_INET;             /* Internet address family */
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
	echoServAddr.sin_port = htons(echoServPort); /* Server port */
	/* Establish the connection to the echo server */
	if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		DieWithError("connect() failed");

	char echoString[50];
	strcpy_s(echoString, 50,requestNum);
	strcat_s(echoString, 50, "$$");
	strcat_s(echoString, 50,hostname);
	strcat_s(echoString, 50, "$$");
	strcat_s(echoString, 50,ip);
	strcat_s(echoString, 50, "$$$");
	//printf("%s", echoString);



	//echoStringLen = strlen(echoString);          /* Determine input length */

	/* Send the string, including the null terminator, to the server */
	
	//if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
		//DieWithError("send() sent a different number of bytes than expected");

//	int requestNumLen = strlen(requestNum);
//	if (send(sock, requestNum, requestNumLen, 0) != requestNumLen)
//		DieWithError("send() sent a different number of bytes than expected");

//	int hostnamelen = strlen(hostname);
//	if (send(sock, hostname, hostnamelen, 0) != hostnamelen)
//		DieWithError("send() sent a different number of bytes than expected");

//	int iplen = strlen(ip);
//	if (send(sock, ip, iplen, 0) != iplen)
//		DieWithError("send() sent a different number of bytes than expected");
	

	/* Receive the same string back from the server */
		totalBytesRcvd = 0;
		printf("Received: ");                /* Setup to print the echoed string */
//	while (totalBytesRcvd < echoStringLen)
//	{
		/* Receive up to the buffer size (minus 1 to leave space for
		a null terminator) bytes from the sender */
//		if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
//			DieWithError("recv() failed or connection closed prematurely");
//		totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
//		echoBuffer[bytesRcvd] = '\0';  /* Add \0 so printf knows where to stop */
//		printf("%s", echoBuffer);            /* Print the echo buffer */
//	}

	printf("\n");    /* Print a final linefeed */

	closesocket(sock);
	WSACleanup();  /* Cleanup Winsock */
	getchar();
	exit(0);
}