/*
	RFC: 2813
	Internet Relay Chat: Server Protocol
	
	https://tools.ietf.org/html/rfc2813



*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // unsigned int sleep(unsigned int seconds);
#include <string.h> // size_t strlen(const char *s);
#include <ctype.h> // int isprint(int c);
#include "message_parser.h"



#define LOGFILE stderr
#define MESSAGE_BUF 513	// one more than limit to add '\0'
#define MESSAGE_BUF_LIMIT 512 





int main(int argc, char *argv[])
{
	// IRC tcp port 6667
	// "Command-line Arguments" 5.10 K & R p.114	

	
	int serv_sock_fd, client_sock_fd, client_length, child_pid;
	struct sockaddr_in client_addr, serv_addr;

	/*
	 *	create socket
	 *	 int socket(int domain, int type, int protocol);
	 *	On success, a file descriptor for the new socket is returned.  
	 *	On error, -1 is returned, and errno is set appropriately.
	 */
	if ((serv_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		fprintf(LOGFILE, "%s\n", "Error: Unable to create socket\n");
	
	
	
	/*
	 *	Bind - assign address to socket
 	 *	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	 *	On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
	 */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6667);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);


	if (bind(serv_sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		fprintf(LOGFILE, "%s\n", "Error: Unable to bind socket\n");
	




	/*
	 *	listen
	 *	int listen(int sockfd, int backlog);
	 *	On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
	 *
	 */
	if (listen(serv_sock_fd, 5) == -1)
		fprintf(LOGFILE, "%s\n", "Error: Unable to listen\n");


	/* 
	 *	accept
	 *	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	 *	On success, these system calls return a nonnegative integer that is a file descriptor for the accepted socket.  
	 *	On error, -1 is returned, and errno is set appropriately.
	 */
	client_length = sizeof(client_addr);
	if ((client_sock_fd = accept(serv_sock_fd, (struct sockaddr *)&client_addr, (socklen_t *) &client_length)) == -1)
		fprintf(LOGFILE, "%s\n", "Error: Unable to accept\n");

	// welcome
	// ssize_t send(int sockfd, const void *buf, size_t len, int flags);
	// On success, these calls return the number of bytes sent.  On error, -1 is returned, and errno is set appropriately.
	char *welcome_message = "Welcome\n";
	ssize_t bytes_sent = send(client_sock_fd, welcome_message, strlen(welcome_message), 0);
	printf("%zd Bytes sent\n", bytes_sent);


	//specification states that messages are no longer than 512 bytes
	// buffer will be 513 to append '\0' if message is well formated and exactly 512 bytes
	char recv_buf[MESSAGE_BUF];
	
	while (1)
	{
		// Using telnet to connect to irc_server 6667 to test.  Telnet automagically sends \r\n
		// receive message
		// ssize_t recv(int sockfd, void *buf, size_t len, int flags);	
		ssize_t bytes_recv = recv(client_sock_fd, recv_buf, MESSAGE_BUF_LIMIT, 0);
		
		if (bytes_recv == MESSAGE_BUF_LIMIT)
		{
		// can buffer be checked to see if it was exceeded
			if (recv_buf[MESSAGE_BUF_LIMIT] == '\n' && recv_buf[MESSAGE_BUF_LIMIT - 1] == '\r')
			{	
				recv_buf[(int)bytes_recv] = '\0';  //Now message is a string
				//handle message
			}
			else
			{
			// disgard	
			//send message "too big!"
			}	
		}
		else
		{
			recv_buf[(int)bytes_recv] = '\0';  //Now message is a string
			printf("%zd %s", bytes_recv,  "Bytes received\n");
			//printf("%s", recv_buf);
			for (int i = 0; recv_buf[i] != '\0'; i++)
			{
				if (isprint(recv_buf[i]))
					printf("%c", recv_buf[i]);
				else if (recv_buf[i] == '\n')
					printf("\\%x\n", recv_buf[i]);
				else
					printf("\\%x", recv_buf[i]);
			}
		
		}
		// check message
		print_hello();
		
		// execute message


		// respond to message


	}
		


	return 0;
}
