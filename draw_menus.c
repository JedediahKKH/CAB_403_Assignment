/*
This code should serve as a scaffold on how the various menus should be drawn by the server
and displayed by the client programs to elicit responses from or inform the player in order
to faciitate the game of Minesweeper.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char username, password;
int active_mines;
// Placeholder Arrays to display information
char A[9],B[9],C[9],D[9],E[9],F[9],G[9],H[9],I[9];


void draw_req_username(){
	printf("Username: ");
	scanf(&username);
}

void draw_req_password(){
	printf("\nPassword: ");
	scanf(&password);

}
void draw_welcome(){
	printf("======================================================== \n");
	printf("Welcome to the online Minesweeper gaming system \n");
	printf("======================================================== \n");
	printf("\nYou are required to log on with your registered user name and password. \n");
	draw_req_username();
	draw_req_password();
}

void draw_login_failure(){
	printf("You entered either an incorrect username or password. Disconnecting.\n");

}


void draw_Minesweeper_menu(){
	printf("Welcome to the Minesweeper gaming system.\n\n");
	printf("Please enter a selection: \n");
	printf("<1> Play minesweeper \n");
	printf("<2> Show Leaderboard \n");
	printf("<3> Quit \n");
	printf("\nSelection option (1-3):");

}

/*
void draw_empty_game(){
	printf("\n\n\nRemaining Mines: %d\n", active_mines);
	printf("\n    1 2 3 4 5 6 7 8 9 \n");
	printf("----------------------\n");
	printf("A |\n");
	printf("B |\n");
	printf("C |\n");
	printf("D |\n");
	printf("E |\n");
	printf("F |\n");
	printf("G |\n");
	printf("H |\n");
	printf("I |\n");


}
*/
void draw_game_options(){
	printf("\n\n\nChoose an option: \n");
	printf("<R> Reveal Tile\n");
	printf("<P> Place Flag\n");
	printf("<Q> Quit Game\n");
	printf("\nOption (R,P,Q): ");

}

void draw_game(){
	printf("\n\n\nRemaining Mines: %d\n", active_mines);
	printf("\n    1 2 3 4 5 6 7 8 9 \n");
	printf("----------------------\n");
	printf("A | %s %s %s %s %s %s %s %s %s\n",&A[1],&A[2],&A[3],&A[4],&A[5],&A[6],&A[7],&A[8],&A[9]);
	printf("B | %s %s %s %s %s %s %s %s %s\n",&B[1],&B[2],&B[3],&B[4],&B[5],&B[6],&B[7],&B[8],&B[9]);
	printf("C | %s %s %s %s %s %s %s %s %s\n",&C[1],&C[2],&C[3],&C[4],&C[5],&C[6],&C[7],&C[8],&C[9]);
	printf("D | %s %s %s %s %s %s %s %s %s\n",&D[1],&D[2],&D[3],&D[4],&D[5],&D[6],&D[7],&D[8],&D[9]);
	printf("E | %s %s %s %s %s %s %s %s %s\n",&E[1],&E[2],&E[3],&E[4],&E[5],&E[6],&E[7],&E[8],&E[9]);
	printf("F | %s %s %s %s %s %s %s %s %s\n",&F[1],&F[2],&F[3],&F[4],&F[5],&F[6],&F[7],&F[8],&F[9]);
	printf("G | %s %s %s %s %s %s %s %s %s\n",&G[1],&G[2],&G[3],&G[4],&G[5],&G[6],&G[7],&G[8],&G[9]);
	printf("H | %s %s %s %s %s %s %s %s %s\n",&H[1],&H[2],&H[3],&H[4],&H[5],&H[6],&H[7],&H[8],&H[9]);
	printf("I | %s %s %s %s %s %s %s %s %s\n",&I[1],&I[2],&I[3],&I[4],&I[5],&I[6],&I[7],&I[8],&I[9]);
}

void draw_game_over(){
	printf("\n\n Game Over! You have hit a mine.");

}


void draw_leaderboards(){
	// Empty Leaderboard scenario
	printf("==============================================================================\n\n");
	printf("There is no information currently stored in the leaderboard. Try again later. \n");
	printf("==============================================================================\n\n");

	// Leaderboard with info
	
	
}


int main(int argc, char **argv){

	//draw_welcome();
	//draw_login_failure();
	//draw_Minesweeper_menu();
	//draw_empty_game();
	//send username and password?
	draw_game();
	draw_leaderboards();


}