/* include fig01 */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
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
	int			udpsockfd1, udpsockfd2, udpsockfd3;
	struct sockaddr_in	udpservaddr1,udpservaddr2, udpservaddr3, udpcliaddr1, udpcliaddr2, udpcliaddr3;
	char			udpbuff1[80], udpbuff2[80], udpbuff3[80];
	int			udpcli_len1, udpcli_len2, udpcli_len3;
	int			uclient1[FD_SETSIZE], uclient2[FD_SETSIZE], uclient3[FD_SETSIZE];
	int 			unready;
	udpcli_len1 = sizeof(udpcliaddr1);
	udpcli_len2 = sizeof(udpcliaddr2);
	udpcli_len3 = sizeof(udpcliaddr3);
	//1. udp socket, connectionless
	udpsockfd1 = socket(AF_INET, SOCK_DGRAM, 0);
	udpsockfd2 = socket(AF_INET, SOCK_DGRAM, 0);
	udpsockfd3 = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&udpservaddr1, sizeof(udpservaddr1));
	bzero(&udpservaddr2, sizeof(udpservaddr2));
	bzero(&udpservaddr3, sizeof(udpservaddr3));
	udpservaddr1.sin_family      = AF_INET;
	udpservaddr2.sin_family      = AF_INET;
	udpservaddr3.sin_family      = AF_INET;
//	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	udpservaddr1.sin_addr.s_addr = inet_addr("192.168.111.200");
	udpservaddr1.sin_port        = htons(5001);
	udpservaddr2.sin_addr.s_addr = inet_addr("192.168.111.200");
	udpservaddr2.sin_port        = htons(5002);
	udpservaddr3.sin_addr.s_addr = inet_addr("192.168.111.200");
	udpservaddr3.sin_port        = htons(5003);
	
	
	//2. bind
	bind(udpsockfd1, (const struct sockaddr *) &udpservaddr1, sizeof(udpservaddr1));
	bind(udpsockfd2, (const struct sockaddr *) &udpservaddr2, sizeof(udpservaddr2));
      	bind(udpsockfd3, (const struct sockaddr *) &udpservaddr3, sizeof(udpservaddr3));	
	
	fd_set urset;
	FD_ZERO(&urset);

	
	
	printf("si\n");	
	
	
	
	
	
/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
			
		//udp child code
		if(fork() == 0){
			
			printf("here0");
			
				

					FD_SET(udpsockfd1, &urset);
					FD_SET(udpsockfd2, &urset);
					FD_SET(udpsockfd3, &urset);					
					if( (unready = select(4, &rset, NULL,NULL,NULL))<0){
				            if(errno == EINTR)
               					 continue;
            				    else
				                perror("select error");
        				}

				
					//3. receive from 
					if(FD_ISSET(udpsockfd1, &urset)){
						bzero(udpbuff1, sizeof(udpbuff1));
						printf("here2");
						recvfrom(udpsockfd1, udpbuff1, sizeof(udpbuff1), 0, (struct sockaddr*) &udpcliaddr1, (socklen_t*) &udpcli_len1);
						printf("client IP: %s , client port: %u , UDPrecv message : %s \n", inet_ntoa(udpcliaddr1.sin_addr), udpcliaddr1.sin_port, udpbuff1);
				
						if(udpbuff1[strlen(udpbuff1)-1] == '\n') udpbuff1[strlen(udpbuff1)-1] = '\0';
						strcat(udpbuff1, "_YES");
						sendto(udpsockfd1, (char *) udpbuff1, strlen(udpbuff1), 0, (const struct sockaddr *) &udpcliaddr1, sizeof(udpcliaddr1));
						printf("FTP SERVER send : %s \n", udpbuff1);
	
					
						}
					//3. receive from 
					if(FD_ISSET(udpsockfd2, &urset)){
						bzero(udpbuff2, sizeof(udpbuff2));
						recvfrom(udpsockfd2, udpbuff1, sizeof(udpbuff2), 0, (struct sockaddr*) &udpcliaddr2, (socklen_t*) &udpcli_len2);
						printf("client IP: %s , client port: %u , UDPrecv message : %s \n", inet_ntoa(udpcliaddr2.sin_addr), udpcliaddr2.sin_port, udpbuff2);
						if(udpbuff1[strlen(udpbuff2)-1] == '\n') udpbuff2[strlen(udpbuff2)-1] = '\0';
						strcat(udpbuff2, "_YES");
						sendto(udpsockfd2, (char *) udpbuff2, strlen(udpbuff2), 0, (const struct sockaddr *) &udpcliaddr2, sizeof(udpcliaddr2));
						printf("FTP SERVER send : %s \n", udpbuff2);



					}
					//3. receive from 
					if(FD_ISSET(udpsockfd3, &urset)){
						bzero(udpbuff3, sizeof(udpbuff3));
						recvfrom(udpsockfd3, udpbuff3, sizeof(udpbuff3), 0, (struct sockaddr*) &udpcliaddr3, (socklen_t*) &udpcli_len3);
						printf("client IP: %s , client port: %u , UDPrecv message : %s \n", inet_ntoa(udpcliaddr1.sin_addr), udpcliaddr1.sin_port, udpbuff3);
						if(udpbuff3[strlen(udpbuff2)-1] == '\n') udpbuff3[strlen(udpbuff3)-1] = '\0';
						strcat(udpbuff3, "_YES");
						sendto(udpsockfd3, (char *) udpbuff3, strlen(udpbuff3), 0, (const struct sockaddr *) &udpcliaddr3, sizeof(udpcliaddr3));
						printf("FTP SERVER send : %s \n", udpbuff3);


					}

				
				}
				return 0;
		
			}
	
		//tcp parent code	
	
	
		rset = allset;		/* structure assignment */
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
                       printf("client ip: %s, client port : %u \n",      inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

			for (i = 0; i < FD_SETSIZE; i++){
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
						if (buf[i] == ','){
							point = i;
							break;
						}
									
					}
					
					for(int i = 0; i < point; i++){
						ID[i] = buf[i];
					}
					int pd = 0;
					for(int i = point+1; i <strlen(buf); i++){
						passwd[pd] = buf[i];
						pd ++;
					} 
					printf("pwd:%s", passwd);
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
