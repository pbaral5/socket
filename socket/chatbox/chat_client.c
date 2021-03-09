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


#define BUFSIZE 1024
#define SERVER_PORT 60000	//The port of the server

int main(int argc, char const **argv)
{
	int sd;							//socket descriptor
	struct sockaddr_in server;		//server information
	struct hostent *server_host;
	char buf[BUFSIZE];
	int nbytes;
	int count;
	char sendmsg[1024],msg[1024];
//Create a socket

	if ((sd=socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		fprintf(stderr, "%s: cannot create socket: ", argv[0] );
		perror(0);
		exit(1);
	}

printf("socket created\n");
//Find server by IP
	if ((server_host=gethostbyname(argv[1]))==NULL)	
	{
		fprintf(stderr, "%s: unknwon host %s\n",argv[0], argv[1] );
		exit(1);
	}

//Save necessary information about to the strcut sockaddr_in 

	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	bcopy((char*)server_host->h_addr, (char*)&server.sin_addr, server_host->h_length);

//Connect to the server
	if (connect(sd, (struct sockaddr *) &server, sizeof(server))<0)
	{
		fprintf(stderr, "%s: cannot connect to server: ", argv[0]);
		perror(0);
		exit(1);
	}

printf("Connection Established\n");
// Receive data form server
	if ((nbytes=read(sd, buf, BUFSIZE-1))<=0)
	{
		fprintf(stderr, "%s read failed",argv[0] );
		perror(0);
		exit(1);
	}
	buf[nbytes] = 0;
	printf("Server name is %s\n", buf );
printf("Enter Message one by one and press enter\n");
while(1){
	printf("client: ");
	fgets(sendmsg,sizeof(sendmsg),stdin);
	if((count = send(sd, sendmsg,1024,0))<0){ printf("Cannot Send");	//send message to server
		exit(errno);}
	if((count=recv(sd, msg,1024,0))<0){ printf("Cannot receive");		//receive message from server
		exit(errno);}	
	printf("%s",msg);
}
	close(sd);
	exit(0);




	return 0;
}
