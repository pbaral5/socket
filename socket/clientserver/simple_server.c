//Prashant Baral
//siu856384505
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void serve (int);

#define PORT 60000	//Specific port
#define MAXHOSTNAME 100
int a,b;
int main(int argc, char const **argv)
{
	int my_socket;
	struct sockaddr_in sin;	//Socket that will remain open for the connection
	int sin_size = sizeof(sin);
	int sd;


//Create socket
	if ((my_socket=socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		fprintf(stderr, "%s: cannot creare listening socket: ",argv[0] );
		perror(0);
		exit(1);
	}

//Naming of socket and binding

	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(my_socket, (struct sockaddr *) &sin, sin_size)<0)
	{
		fprintf(stderr, "%s: cannot bind listening socket: ",argv[0] );
		perror(0);
		exit(1);
	}


//Initialization of queue for 5 connections

	if (listen(my_socket,5)<0)
	{
		fprintf(stderr, "%s: cannot listen on socket: ",argv[0] );
		perror(0);
		exit(1);
	}


// Ignore SIGPIPE
	signal(SIGPIPE, SIG_IGN);



//The server is ready for incmoning clients

	while(1){
		if ((sd=accept(my_socket, (struct sockaddr *) &sin, &sin_size))<0)
			exit(errno);
		if(fork()==0){								//creating child process
		serve(sd);
		shutdown(sd,2);
		close(sd);

	}

}
}

void serve(int sd){
	char host[MAXHOSTNAME+1];
	gethostname(host, MAXHOSTNAME);
	write(sd, host, strlen(host));
	return;
}
