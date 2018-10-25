#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

	#define MAXDATASIZE 100 /* max number of bytes we can get at once */

	#define USERNAME_SIZE 20 /* username array size */

	#define PASSWORD_SIZE 6 /* password array size */

char welcomeMessage[200] = 
/**/ "=========================================================\n"
/**/ "Welcome to the online Minesweeper gaming system\n"
/**/ "=========================================================\n";

char gameWelcome[100] = "\nWelcome to the online Minesweeper gaming system\n";
char success[100] = "match";

char *fromServer;
char username[USERNAME_SIZE] = {};
char password[PASSWORD_SIZE] = {};

int sockfd, selectOption;  
struct hostent *he;
struct sockaddr_in their_addr; /* connector's address information */

/* Send data to server function*/
void Send_Data(int socket_id, char *myArray) {
	send(socket_id, myArray, sizeof(myArray), 0);
}

/* Recieve data from server function*/
char *Recieve_Data(int socket_identifier, int size) {
    int number_of_bytes = 0;
	
	char *results = (char*)malloc(sizeof(char)*size);
	
	if ((number_of_bytes=recv(socket_identifier, results, sizeof(results), 0)) == -1) {
		perror("recv");
		exit(EXIT_FAILURE);			
		    
	}
	return results;
}

/* creates client socket*/
void createSocket(int argc, char *argv[]){

	if (argc != 3) {
		fprintf(stderr,"usage: client_hostname port_number (client)\n");
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL) {  /* get the host info */
		herror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}


	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(atoi(argv[2]));    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, \
	sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
}

/* Displays game menu screen */
void gameScreen(){

printf("%s", gameWelcome);
printf("\nPlease enter a selection:\n");
printf("<1> Play Minesweeper\n");
printf("<2> Play Show Leaderboard\n");
printf("<3> Quit\n");

printf("\nSelection option (1-3): ");
scanf("%d", &selectOption);

printf("Selection Option is: %d\n", selectOption);
}

/* Displays Welcome and log in screen  */
void welcomeScreen(){
        printf("%s", welcomeMessage);
        printf("\nYou are required to log on with your registered user name and password.\n\n"); 

	/* Ask for username */
	printf("Username: ");
	scanf("%s", username);
	Send_Data(sockfd, username);

	/* Ask for password */
	printf("Password: ");
	scanf("%s", password);
	Send_Data(sockfd, password);

	/* Receive message back from server */
	fromServer = Recieve_Data(sockfd, MAXDATASIZE);

	/* Compare received message with stored message*/
	if(strcmp(fromServer, success) == 0){
		gameScreen();
	}else{
		printf("\nYou entered either an incorrect username or password. Disconnecting...\n\n");
		close(sockfd);
		exit(1);	
	}
}

int main(int argc, char *argv[]) {
	createSocket(argc, argv);
	welcomeScreen();
	return 0;
}
