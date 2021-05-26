#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	int			sockfd;
	struct sockaddr_in	servaddr, cliaddr;
	char			buff[80];
	int			cli_len;
	cli_len = sizeof(cliaddr);
	
	//1. udp socket, connectionless
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
//	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_addr.s_addr = inet_addr("192.168.111.200");
	servaddr.sin_port        = htons(5000);
	
	
	//2. bind
	bind(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	
	//3. receive from 
	bzero(buff, sizeof(buff));
	recvfrom( sockfd, buff, sizeof(buff), 0, (struct sockaddr*) &cliaddr, (socklen_t*) &cli_len);
	printf("client IP: %s , client port: %u , recv message : %s \n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port, buff);
	//4. send to
	strcat(buff, "::UDPSERVER");
	sendto(sockfd, (char *) buff, strlen(buff), 0, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
	printf("UDP SERVER send to Done: %s \n", buff);

	
	
	return 0;
}
