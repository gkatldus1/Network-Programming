#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAXLINE 80


int
main(int argc, char **argv)
{
	int					sockfd, n;
	char				buff[MAXLINE];
	struct sockaddr_in	servaddr;

	
	//1. socket

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.111.200");
	servaddr.sin_port   = htons(5001);	
	

	//2. connect
	if (connect(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		perror("connect error");

	// write --> send
//	strcpy(buff, "hello Server~~~~");
	printf("Message: ");
	fgets(buff, sizeof(buff), stdin);
	send(sockfd, buff, strlen(buff), 0);
	printf("Client send : %s \n", buff);

	//read --> receive
	bzero(buff, sizeof(buff));
	recv(sockfd, buff, sizeof(buff), 0);
	printf("Client recv: %s \n", buff);

	exit(0);
}
