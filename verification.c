/*
This code serves as a scaffold on how the server.c can compare
incoming strings from client programs with these variables.

Ensure that the Authentication.txt file is located in the same directory/ folder as the file that runs this code.

*/

/*
Known Bugs:
The first element of the usernames list is overwritten with the same value as the password input

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
	// Dummy Input
	char input[2][20];
	// Dummy Authenication.txt data
	char usernames[6][20];
	int password[6]={(int)"Passwords",111111,222222,333333,123123,246246};
	
	int ret;// initialise int variable to store result of string comparison
	int username_same=0;// initialise an int variable to do boolean operations
	int password_same=0;


	// Dummy Authentication.txt data
	strcpy(usernames[0],"Usernames");
	strcpy(usernames[1],"Maolin");
	strcpy(usernames[2],"James");
	strcpy(usernames[3],"David");
	strcpy(usernames[4],"Maolin");
	strcpy(usernames[5],"Jason");


	// Dummy Client input
	printf("Input Username: \n");
	strcpy(input[1],"Maolin");
	printf("Input Password: \n");
	strcpy(input[2],"111111");
	printf("Username Input is %s \n",input[1]);
	printf("Password Input is %d \n",atoi(input[2]));


	/*
	printf("After user Input\n");	
	for(int i=0;i<5;i++){

		printf("Username[%d] is %s\n",i,usernames[i]);
		printf("Username Input is %s \n",input[1]);
		printf("Password Input is %d \n",atoi(input[2]));
	}*/

	// Actual Useful Code
	for(int i=1;i<6;i++){
		// String Comparison between user input [1] and the list of usernames
		ret=strcmp(input[1],usernames[i]);
		printf("Comparing: %s, %s\n",input[1],usernames[i]);
		// If the strings are the same (Valid Username)
		if(ret==0){
			// Set username boolean to TRUE
			username_same=1;
			printf("Names Match!\n");
			// Check Password
			printf("input[2] is %d\n",atoi(input[2]));
			printf("Current password is %d\n",password[i]);
			if(atoi(input[2])==password[i]){
				// Correct Associated Password (Set password boolean to TRUE)	

				password_same=1;
				printf("Successfully exit Program\n"); // Somehow connect to server
				//return 1;
				break;// -> exits for loop
			}else{
				// Correct User but wrong password (kick user off)
				password_same=0;
				printf("Wrong Password! \n");
				break;// ->exits for loop
			}
		}
		printf("Username comparison is not successful! \n");
		username_same=0; 
	}
	printf("Done Comparing Usernames! \n");
	if(password_same && username_same){
		printf("Valid Username and password!\n");
		return 1; // Pass this value to server.c to handle case
	}
	printf("No Matches Found!\n");// Kick User off
	return 0; // Pass this value to server.c to handle case
}