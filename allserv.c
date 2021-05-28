/* include fig01 */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 80
#define SERVERIP "192.168.111.200"
#define SERV_PORT 5000
#define LISTENQ 5


int
main(int argc, char **argv)
{
	int					i, maxi, maxfd, listenfd, connfd, sockfd;
	int					nready, client[FD_SETSIZE];
	ssize_t				n;
	fd_set				rset, allset;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVERIP);
	servaddr.sin_port        = htons(SERV_PORT);

	bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	maxfd = listenfd;			/* initialize */
	maxi = -1;					/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;			/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	
	// udp bind code
	int			sockfd1;
	struct sockaddr_in	servaddr1, cliaddr1;
	char			buff[80];
	int			cli_len1;
	cli_len1 = sizeof(cliaddr);
	
	//1. udp socket, connectionless
	sockfd1 = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr1, sizeof(servaddr1));
	servaddr1.sin_family      = AF_INET;
//	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr1.sin_addr.s_addr = inet_addr("192.168.111.200");
	servaddr1.sin_port        = htons(5000);
	
	
	//2. bind
	bind(sockfd1, (const struct sockaddr *) &servaddr1, sizeof(servaddr1));
	
	
	
	
	
	
	
/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
	
		//udp child code
		if(fork() == 0){
			
			
			//3. receive from 
			bzero(buff, sizeof(buff));
			recvfrom( sockfd1, buff, sizeof(buff), 0, (struct sockaddr*) &cliaddr1, (socklen_t*) &cli_len1);
			printf("client IP: %s , client port: %u , UDPrecv message : %s \n", inet_ntoa(cliaddr1.sin_addr), cliaddr1.sin_port, buff);
			//4. send to
			if(buff[strlen(buff)-1] == '\n') buff[strlen(buff)-1] = '\0';
			strcat(buff, "_UdpServer");
			sendto(sockfd1, (char *) buff, strlen(buff), 0, (const struct sockaddr *) &cliaddr1, sizeof(cliaddr1));
			printf("UDP SERVER send : %s \n", buff);

			
			
			return 0;
		
		}
	
		//tcp parent code	
	
	
		rset = allset;		/* structure assignment */
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
                       printf("client ip: %s, client port : %u \n",      inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE)
				perror("too many clients");

			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				bzero(buf, sizeof(buf));
				if ( (n = recv(sockfd, buf, MAXLINE, 0)) == 0) {
						/*4connection closed by client */
					
					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else
				{
					char ID[20], passwd[20];
					bzero(ID, sizeof(ID));
					bzero(passwd, sizeof(passwd));
					
					if(buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = '\0';
					int point = 0;
					for(int i = 0; i < strlen(buf); i++){
						if (buf[i] == ',')
							point = i;
									
					}
					
					for(int i = 0; i < point; i++){
						ID[i] = buf[i];
					}
					for(int i = point+1; i <strlen(buf); i++){
						int pd = 0;
						passwd[pd] = buf[i];
						printf("%c", buf[i]);
						pd ++;
					} 
					
					if(strcmp(ID, "AhnYoungah")==0){
						if(strcmp(passwd, "1234567")==0){
							bzero(buf, sizeof(buf));
							strcpy(buf, "AhnYoungah_loginOK");
							send(sockfd, buf, strlen(buf), 0);
						}
					
					}
					
					

				}
				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}
/* end fig02 */
