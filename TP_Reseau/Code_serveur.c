#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SUCCESS 0
#define ERROR 1

#define END_LINE 0x0
#define SERVER_PORT 1500
#define MAX_MSG 100


int main(int argc, char *argv[])
{
	int sd, newSd, cliLen;
	struct sockaddr_in cliAddr, servAddr;
	
	char line[MAX_MSG];
	char * rcv_msg = malloc(sizeof(char));;
	int n = 0;
	int m = 0;
	
	/*Create socket*/
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd<0)
	{
		perror("cannot open socket");
		return ERROR;
	}
	
	/*Blind server port*/
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servAddr.sin_port = htons(SERVER_PORT);
	
	if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) <0)
	{
		perror("Cannot bind port");
		return ERROR;
	}
	
	listen(sd,5);
	while(/*m == 0 && n == 0*/1)
	{
		printf("%s: waiting for data on port TCP %u\n", argv[0], SERVER_PORT);
		cliLen = sizeof(cliAddr);
		printf("%i", cliLen);
		
		newSd = accept(sd, (struct sockaddr *) &cliAddr, (socklen_t *) &cliLen);
		if(newSd <0)
		{
			perror("Cannot open connexion");
			return ERROR;
		}
		
		/*init line*/
		memset(line, 0x0, MAX_MSG);
	
		/*receive segments*/
		
		memset(rcv_msg, 0x0, MAX_MSG);/*init buffer*/
		m = recv(newSd, rcv_msg, sizeof(rcv_msg)-1, 0)-1;
		rcv_msg[m] = '\0';
		//n = recv(newSd, line, sizeof(line)-1 , 0);/*wait for data*/
		printf("%s: received from %s:TCP%d : %s\n", argv[0], inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line);
		printf("Message reçu : %s\n", rcv_msg);
		/*init line*/
		memset(line, 0x0, MAX_MSG);
		
	}
	/*while(1)*/
}
