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


#define LOGFILE stderr






int main(int argc, char *argv[])
{
	// IRC tcp port 6667
	
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






	return 0;
}
