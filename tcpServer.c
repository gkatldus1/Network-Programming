#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SERVERIP	"192.168.111.200"
#define MAXLINE 80
#define PORT 5000

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr, cliaddr;
	char				buff[MAXLINE];
	int cli_len;
	cli_len = sizeof(cliaddr);
	//1. socket
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	

	//servaddr for bind
	bzero(&servaddr, sizeof(servaddr));//0 clear
	servaddr.sin_family      = AF_INET;
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_addr.s_addr = inet_addr(SERVERIP);
	servaddr.sin_port        = htons(5000);	/* daytime server */
	//2. bind
	bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	//3. listen
	listen(listenfd, 10);

	for ( ; ; ) {
		//4. accept
		connfd = accept(listenfd, (struct sockaddr*)&cliaddr, (socklen_t*) &cli_len);
		printf("client ip: %s, client port : %u \n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);


		if( fork() == 0) {	//child process

			close(listenfd);
        		//server read
			bzero(buff, sizeof(buff));	//buf clear
			read(connfd, buff, sizeof(buff));
			
			if( buff[strlen(buff)-1] == '\n') buff[strlen(buff)-1] = '\0';

			printf("Server read : %s \n", buff);

			//server write
			//strcat(buff, "~~"); //usage of strcat
			strcpy(buff, "SEVER_OK");
	        	write(connfd, buff, strlen(buff));
			printf("Sever write %s \n", buff);
			
			exit(0);
		}	//end child process
		//parent process
		close(connfd);
	}
}
