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
	int					sockfd;
	struct sockaddr_in	servaddr;
	int 			serv_len;
	char			buff[80];
	char			sendbuf[80];
	serv_len = sizeof(servaddr);
	bzero(sendbuf, sizeof(sendbuf));
	

	
	
	//1. udp socket

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5001);
	servaddr.sin_addr.s_addr = inet_addr("192.168.111.200");
	
	//server sendto
	printf("choose: 1.FTP, 2.Movie, 3.Chatting ");
	fgets(buff, sizeof(buff), stdin);
	
	if(strcmp(buff, "1.FTP\n")==0){
		servaddr.sin_port = htons(5001);
		
		strcpy(sendbuf, "NetworkProgramming.pdf");
		sendto(sockfd, (char *) sendbuf, strlen(sendbuf), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("UDP client sendto Done: %s \n", sendbuf);
		//receive from server
		bzero(buff, sizeof(buff));
		recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*) &servaddr, (socklen_t*) &serv_len);
		printf("Server IP : %s, Server port : %u, recv message: %s \n", inet_ntoa(servaddr.sin_addr), servaddr.sin_port, buff);
		exit(0);	
		
	}
	
	else if(strcmp(buff, "2.Movie\n")==0){
		servaddr.sin_port = htons(5002);
		strcpy(sendbuf, "Apple");
		sendto(sockfd, (char *) sendbuf, strlen(sendbuf), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("UDP client sendto Done: %s \n", sendbuf);
		//receive from server
		bzero(buff, sizeof(buff));
		recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*) &servaddr, (socklen_t*) &serv_len);
		printf("Server IP : %s, Server port : %u, recv message: %s \n", inet_ntoa(servaddr.sin_addr), servaddr.sin_port, buff);
		exit(0);		
	
	}
	
	else {
		while(1){
			servaddr.sin_port = htons(5003);
			fgets(sendbuf, sizeof(sendbuf), stdin);
			sendto(sockfd, (char *) sendbuf, strlen(sendbuf), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
			printf("UDP client sendto Done: %s \n", sendbuf);
			//receive from server
			bzero(buff, sizeof(buff));
			recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*) &servaddr, (socklen_t*) &serv_len);
			printf("Server IP : %s, Server port : %u, recv message: %s \n", inet_ntoa(servaddr.sin_addr), servaddr.sin_port, buff);
			if(strcmp(buff, "quit")==0)	exit(0);
		}			
	
	}

	

	exit(0);
}
