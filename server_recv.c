/*
*  Materials downloaded from the web. See relevant web sites listed on OLT
*  Collected and modified for teaching purpose only by Jinglan Zhang, Aug. 2006
*/
#define _GNU_SOURCE

#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <errno.h>
#include<signal.h>

	#define MAX_BUFFER_SIZE 100 /* Size of data sent*/

	#define USERNAME_SIZE 20  /* Size of username array */

	#define PASSWORD_SIZE 6  /* Size of password array */

	#define USERS 11 /* Number of registered users */	

	#define BACKLOG 10     /* how many pending connections queue will hold */

	#define RETURNED_ERROR -1

	char *usernameRecv;	
	char *passwordRecv;

    	char usernameReg[USERS][USERNAME_SIZE];
    	int passwordReg[USERS];

	char username[USERS][USERNAME_SIZE];
	int password[USERS];

	char buffer[MAX_BUFFER_SIZE];
	int i = 0;	
	int check;
	int sockfd, new_fd;  /* listen on sock_fd, new connection on new_fd */
	struct sockaddr_in my_addr;    /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	socklen_t sin_size;

/*Reads file and stores data from text file*/
void readFile(){

	FILE *ptr_file;

	int counter=0;

	// point to desired file
	//use pwd
	ptr_file=fopen("Authentication.txt","r");
	// if the file does not exists
	if (!ptr_file)
		exit(1);
	// scan the file
	while(fgets(buffer,sizeof(buffer),ptr_file)!=NULL){

		int counter1=0;
		//puts(buffer);
		sscanf(buffer,"%s %d",&username[counter][counter1], &password[counter]);
		counter++;
		counter1++;

	}	
	// close the file
	fclose(ptr_file);
}

/* Creates server socket */
void createServerSocket(int argc, char *argv[]){
	/* Get port number for server to listen on */
	if (argc != 2) {
		fprintf(stderr,"usage: client port_number (server)\n");

		exit(1);
	}

	/* generate the socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* generate the end point */
	my_addr.sin_family = AF_INET;         /* host byte order */
	my_addr.sin_port = htons(atoi(argv[1]));     /* short, network byte order */
	my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
		/* bzero(&(my_addr.sin_zero), 8);   ZJL*/     /* zero the rest of the struct */

	/* bind the socket to the end point */
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) \
	== -1) {
		perror("bind");
		exit(1);
	}

	/* start listnening */
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	printf("server starts listnening ...\n");
}

/* Receives data from client and store into char array*/
/* Return type = char pointer */
char *Recieve_Data(int socket_identifier, int size) {
    int number_of_bytes = 0;
	
	char *results = (char*)malloc(sizeof(char)*size);
	
	if ((number_of_bytes=recv(socket_identifier, results, sizeof(results), 0))== RETURNED_ERROR) {
		perror("recv");
		exit(EXIT_FAILURE);			
		    
	}
	return results;
}

/* Sends data to client */
void Send_Data(int socket_id, char *myArray) {
	send(socket_id, myArray, sizeof(myArray), 0);
}

/* Verify user input against registered users */
int verifyCred(char *usernameInput, char *passwordInput){
	int matching = 0;
	
	for(int i = 0; i<USERS; i++){
		if(strcmp(usernameInput, username[i]) == 0){
			for(int j = 0; j<USERS; j++){
				if(atoi(passwordInput) == password[j]){
					matching = 1;
				}
			}		
		}
	}
	return matching;
}

/* accept, send, receive data from clients*/
void connection_handler(){
	/* repeat: accept, send, close the connection */
	/* for every accepted connection, use a sepetate process or thread to serve it */
	while(1) {  /* main accept() loop */
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");

			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		
		if (!fork()) { /* this is the child process */

			/* Call method to recieve data */
			usernameRecv = Recieve_Data(new_fd,  USERNAME_SIZE);	
			passwordRecv = Recieve_Data(new_fd,  PASSWORD_SIZE);
			
			printf("Inputted: %s\n", usernameRecv);
			printf("Inputted: %s\n", passwordRecv);

			check = verifyCred(usernameRecv, passwordRecv);
			
			if(check == 1){
				printf("\nSuccessfully Logged On\n");
				Send_Data(new_fd, "match");
			}
			else{
				printf("\nLog In Failed\n");
				Send_Data(new_fd, "failed");
			}

			/* free memory allocation*/
			free(usernameRecv);
			free(passwordRecv);
		}
		close(new_fd);  /* parent doesn't need this */
		while(waitpid(-1,NULL,WNOHANG) > 0); /* clean up child processes */
	}
}

int main(int argc, char *argv[])
{
	readFile();
	createServerSocket(argc, argv);
	connection_handler();
	close(new_fd);
}
