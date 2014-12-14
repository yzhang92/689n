#include <stdio.h>      /* for printf(), fprintf() */
#include <winsock.h>    /* for socket(),... */
#include <stdlib.h>     /* for exit() */
#include <string.h>

#define RCVBUFSIZE 256   /* Size of receive buffer */

char *CaseInsensitiveTest(char *);
int ValidIp(char **, int);
int StrToInt(char *);


void main(int argc, char *argv[])
{
	int sock;                       /* Socket descriptor */
	struct sockaddr_in servAddr;	/* Server address */
	char *servPort;		/* Server port */
	char *servIP;                   /* Server IP address (dotted quad) */
	char msgBuffer[RCVBUFSIZE];     /* Buffer for message string */
	int sendMsgLen;					/* Length of string to send */
	int bytesRcvd, totalBytesRcvd;  /* Bytes read in single recv() and total bytes read */
	WSADATA wsaData;                /* Structure for WinSock setup communication */
	char *requestNum;
	char *hostname;
	char **ip;
	int numberOfIp;
	int lengthOfIp = 0;
	char *command = NULL;
	int lengthOfCom = 0;


	/* Test for correct number of arguments */
	if (argc < 4)
	{
		fprintf(stderr, "Input Format Error: correct input format: %s <Server IP> <Server Port#> <request number> [<additional infor>]\n", argv[0]);
		exit(1);
	}

	servIP = argv[1];            
	servPort = argv[2];
	requestNum = argv[3];

	/* request number check*/
	if (argc > 3) {
		if (strlen(requestNum) != 1) {
			printf("Error: invalid request number. It should be from number 1 to 6.");
			exit(1);
		}
		if (requestNum[0] < 49 || requestNum[0] > 54) {
			printf("Error: invalid request number. It should be from number 1 to 6.");
			exit(1);
		}
	}

	/* caseinsensitive transfer*/
	if ((argc > 4) && atoi(requestNum) != 6) {
		hostname = CaseInsensitiveTest(argv[4]);
	}
	else if ((atoi(requestNum) == 6) && (argc > 4)){
		hostname = argv[4];
	}
	/* ip formate check*/
	if ((atoi(requestNum) == 2)&&(argc > 5)) {
		numberOfIp = argc - 5;
		ip = malloc(numberOfIp * sizeof(char *));
		for (int i = 0, j = 5; i < numberOfIp; i++, j ++) {
			ip[i] = argv[j];
			lengthOfIp += strlen(argv[j]);
		}
		if (!ValidIp(ip, numberOfIp)) {
			printf("Error: your ip format is invalid. Please restart the program.");
			exit(1);
		}
	}
	
	/* compose the sending message */
	if ((atoi(requestNum) == 4) || (atoi(requestNum) == 5)) {
		lengthOfCom = strlen(requestNum) + 3;
		command = malloc(lengthOfCom + 1);
		command[lengthOfCom] = '\0';
		strcpy(command, requestNum);
		strcat(command, "$$$");
	}
	else if (((atoi(requestNum) == 1) || (atoi(requestNum) == 3) || (atoi(requestNum) == 6)) && (argc > 4)) {
		lengthOfCom = strlen(requestNum) + 5 + strlen(hostname);
		command = malloc(lengthOfCom + 1);
		command[lengthOfCom] = '\0';
		strcpy(command, requestNum);
		strcat(command, "$$");
		strcat(command, hostname);
		strcat(command, "$$$");
	}
	else if ((atoi(requestNum) == 2) && (argc > 5)){
		lengthOfCom = strlen(requestNum) + strlen(hostname) + numberOfIp * 2 + 6;
		for (int i = 0; i < numberOfIp; i++) {
			lengthOfCom += strlen(ip[i]);
		}
		command = malloc(lengthOfCom);
		command[lengthOfCom] = '\0';
		strcpy(command, requestNum);
		strcat(command, "$$");
		strcat(command, hostname);
		strcat(command, "$$");
		for (int i = 0; i < numberOfIp; i++) {
			strcat(command, ip[i]);
			strcat(command, "$$");
		}
		strcat(command, "$");
	}
	else{
		printf("Error: Not enough input.");
		exit(1);
	}
	
//-----------------------------initialization-----------------------------------------------
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	{
		printf("Error: WSAStartup() failed");
		exit(1);
	}

	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("Error: socket() failed");
		exit(1);
	}

	/* Construct the server address structure */
	memset(&servAddr, 0, sizeof(servAddr));     /* Zero out structure */
	servAddr.sin_family = AF_INET;             /* Internet address family */
	if (inet_addr(servIP) == INADDR_NONE) {
		printf("Error: Input Ip address is invalied."); 
		exit(1);
	}
	if ((StrToInt(servPort) == 0) || (StrToInt(servPort) < 1) || (StrToInt(servPort) > 65536)) {
		printf("Error: Input port number is invalied.");
		exit(1);
	}
	servAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
	servAddr.sin_port = htons((StrToInt(servPort))); /* Server port */
	
	/* Establish the connection to the echo server */
	if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
		printf("Error: connet() failed.");
		exit(1);
	}

	/* Send the string, including the null terminator, to the server */
	if (send(sock, command, lengthOfCom, 0) != lengthOfCom) {
		printf("Error: send() sent a different number of bytes than expected");
		exit(1);
	}

	/* Receive string back from the server */
	totalBytesRcvd = 0;
	printf("Received: ");                /* Setup to print the echoed string */
	
	
	/* Receive up to the buffer size (minus 1 to leave space for
	a null terminator) bytes from the sender */
	if ((bytesRcvd = recv(sock, msgBuffer, RCVBUFSIZE - 1, 0)) <= 0) {
		printf("Error: recv() failed or connection closed prematurely");
		exit(1);
	}
	if (bytesRcvd > RCVBUFSIZE) {
		printf("Error: Size of Recieved message exeeced the size of buffer.");
	}
	msgBuffer[bytesRcvd] = '\0';  /* Add \0 so printf knows where to stop */
	printf("%s\n", msgBuffer);            /* Print the echo buffer */
	closesocket(sock);
	WSACleanup();  /* Cleanup Winsock */
	exit(1);
}