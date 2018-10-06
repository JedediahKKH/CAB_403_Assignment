// Tester code for Assignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int NUM_USERS=15;
const int USERNAME_LENGTH=20;
const int PASSWORD_LENGTH=20;
int main(){

	FILE *ptr_file;
	char buffer[150],username[NUM_USERS][USERNAME_LENGTH];
	int password[NUM_USERS];
	//char* value;
	int counter=0;
	//char array[20];

	// point to desired file
	ptr_file=fopen("/home/koh_kim_hai/Downloads/CAB403_Assignment/Authentication.txt","r");
	// if the file does not exists
	if (!ptr_file)
		return 1;
	// scan the file
	while(fgets(buffer,sizeof(buffer),ptr_file)!=NULL){

		int counter1=0;
		//puts(buffer);
		sscanf(buffer,"%s %d",&username[counter][counter1], &password[counter]);
		counter++;
		counter1++;

	}
	// Printing it
	for(int i=0; i<11;i++){

		printf("Printing Usernames: \n");
		printf("%s\n",username[i]);

		printf("Printing Passwords: \n");
		printf("Password[%d] is %d\n",i,password[i]);

		
	}

	// close the file
	fclose(ptr_file);
	return 0;

/*
	char input[12];
	//input=itoa(77);
	snprintf(input,"%s \n",77);
*/
}
