#define NUM_TILES_X 9
#define NUM_TILES_Y 9
#define NUM_MINES 10
#define RANDOM_NUMBER_SEED 42 // server

#include <stdio.h>
#include <stdlib.h>
#include <math.h>// not needed in final code?
#include <time.h>


typedef struct
{
	int adjacent_mines;// value from 0 to 8.
	int is_revealed;// value of 1 or 0
	int is_mine;// value of 1 or 0
	char display_symbol;
	// This struct builds the tiles; should i have a pointer to the next tile that i wish to update here?
} Tile;

typedef struct
{
	//... additional fields...
	int game_quit; // determine if game ends due to quitting
	int game_won; // determine if game has been successfully won
	int game_over;// state of game_over
	double time_taken;
	int current_mines_active;
	Tile tiles[NUM_TILES_X][NUM_TILES_Y]; // define game size
	// This stuct builds the whole game
} GameState;

Tile this_tile;
GameState this_game;
time_t start_t,end_t;
char A[9],B[9],C[9],D[9],E[9],F[9],G[9],H[9],I[9];
//srand(RANDOM_NUMBER_SEED);
//double difftime(time_t time1,time_t time2);
void initialise_game(){
	// initialise timer

	// initialise GameState params
	this_game.game_quit=0;
	this_game.game_over=0;
	this_game.current_mines_active=10;
	this_tile.display_symbol=' ';
	//time(&start_t);

}

/*
When passed in a x,y pair, check the grid to
see if the selected tile already has a mine
-> this_tile.is_mine=1
*/


int tile_contains_mine(int x, int y){
	// Check if this_tile.is_mine==1
	int result;
	if(this_game.tiles[y][x].is_mine==1){
		result=1;
	}
	else{
		result=0;
	}

	return result;
}

/*
  While the tile does not contain a mine, try to
  place a mine at the randomly selected x,y 
  position.
*/

void place_mines(){
	for(int i=0;i<NUM_MINES;i++){
		int x,y;
		do
		{
			x=rand() % NUM_TILES_X;
			y=rand() % NUM_TILES_Y;
		}while(tile_contains_mine(x,y));
		this_game.tiles[y][x].is_mine=1;
		this_game.tiles[y][x].display_symbol='*';
		// +1 to neighbour.adjacent_mines
		for(int xoff=-1;xoff<1+1;xoff++){
			for(int yoff=-1;yoff<1+1;yoff++){
				int i=x+xoff;
				int j=y+yoff;
				// If i,j are not outside of the map, +1 to their adjacent_mines
				if(i>-1&&i<9&&j>-1&&j<9){
					this_game.tiles[j][i].adjacent_mines+=1;
				
				}	
			}
		}
		printf("Mine %d placed at %d,%d\n",i,x,y);
	}

}

void place_flag(int x, int y){
	// Check if this tile has already been revealed AND is a mine
	// If yes, defuse it
		//-> Total mines -1
		//-> Place a Defused Bomb Symbol
	// If no, display text to inform player

	if(this_game.tiles[y][x].is_mine==0){
		printf("This is not a mine! Please Try another area!\n");
	}
	else if(this_game.tiles[y][x].is_mine==1){
		if(!this_game.tiles[y][x].is_revealed){
			printf("You found a mine! Mine has been defused.\n");
			this_game.current_mines_active-=1;
			this_game.tiles[y][x].is_revealed=1;
			this_game.tiles[y][x].display_symbol='+';
			printf("Number of active mines left: %d\n", this_game.current_mines_active);
		}else{
			printf("You have already defused this mine, find another mine!\n");
		}

	}

}
void place_lots_of_flags(){
	int x,y;
	x=rand()%NUM_TILES_X;
	y=rand()%NUM_TILES_Y;
	printf("Now Attempting to Place a flag at (%d,%d)\n",x,y);
	place_flag(x,y);

}

void reveal_this_tile(int x, int y){
	this_game.tiles[y][x].is_revealed=1;
	printf("Revealing Tile[%d][%d]\n",x,y);
	if(this_game.tiles[y][x].adjacent_mines!=0){
		// If this tile has a non-zero number of adjacent mines
		// Set its display symbol to the number of adjacent mines
		this_game.tiles[y][x].display_symbol=this_game.tiles[y][x].adjacent_mines+'0';
		//printf("Tile[%d][%d] has been revealed!It has %d neighbouring mines\n",x,y,this_game.tiles[y][x].adjacent_mines);
		return;
	}else{
		// This tile has no mines nearby; reveal all neighbours!
		this_game.tiles[y][x].display_symbol='0';
		for(int xoff=-1;xoff<1+1;xoff++){
			for(int yoff=-1;yoff<1+1;yoff++){
				int i=x+xoff;
				int j=y+yoff;

				// If i,j are not outside of the map, +1 to their adjacent_mines
				if(i>-1&&i<9&&j>-1&&j<9){
					//printf("i: %d\tj:%d\n",i,j);
					Tile t=this_game.tiles[j][i];
					// Check if this tile is reveal
					if(t.is_revealed==0){
						reveal_this_tile(i,j);
					}
				}
			}
		}
	}	

}
void reveal(int x,int y){
	// Check if this is a mine
	// If Yes, Game over
	if(this_game.tiles[y][x].is_mine==1){
		this_game.game_over=1;
		this_game.game_won=0;// This game has not been won, add 0 to number of games won in leaderboard.
		printf("You have steped on a mine and died. Better Luck Next Time!\n");
	}// If the tile if not a mine
	else{
		reveal_this_tile(x,y);
	}
}

void steppity_step(){

	int x,y;
	x=(int)(2/3*rand()%NUM_TILES_X);
	y=rand()%NUM_TILES_Y;
	reveal(x,y);
	
}
void update_char_array(){
	// For all the columns in Row A, store them in the char array

	for(int i=0;i<NUM_TILES_X;i++){
		if(this_game.tiles[0][i].is_revealed==1){
			A[i]=this_game.tiles[0][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			A[i]=' ';
		}
		if(this_game.tiles[1][i].is_revealed==1){
			B[i]=this_game.tiles[1][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			B[i]=' ';
		}
		if(this_game.tiles[2][i].is_revealed==1){
			C[i]=this_game.tiles[2][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			C[i]=' ';
		}
		if(this_game.tiles[3][i].is_revealed==1){
			D[i]=this_game.tiles[3][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			D[i]=' ';
		}
		if(this_game.tiles[4][i].is_revealed==1){
			E[i]=this_game.tiles[4][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			E[i]=' ';
		}
		if(this_game.tiles[5][i].is_revealed==1){
			F[i]=this_game.tiles[5][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			F[i]=' ';
		}
		if(this_game.tiles[6][i].is_revealed==1){
			G[i]=this_game.tiles[6][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			G[i]=' ';
		}
		if(this_game.tiles[7][i].is_revealed==1){
			H[i]=this_game.tiles[7][i].display_symbol;
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			H[i]=' ';
		}
		if(this_game.tiles[8][i].is_revealed==1){
			I[i]=this_game.tiles[8][i].display_symbol;
			//printf("I[%d] is %c\n",i,I[i]);
		}
		else if(this_game.tiles[0][i].is_revealed==0){
			I[i]=' ';
		}
		//printf("D[%d] is %c\n",i,D[i]);
	}


}

void display_game(){
	update_char_array();
	printf("\n\n\nRemaining Mines: %d\n", this_game.current_mines_active);
	printf("\n   \t0\t1\t2\t3\t4\t5\t6\t7\t8 \n");
	printf("-----------------------------------------------------------------------------------------\n");
	printf("0 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8]);
	printf("1 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",B[0],B[1],B[2],B[3],B[4],B[5],B[6],B[7],B[8]);
	printf("2 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",C[0],C[1],C[2],C[3],C[4],C[5],C[6],C[7],C[8]);
	printf("3 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",D[0],D[1],D[2],D[3],D[4],D[5],D[6],D[7],D[8]);
	printf("4 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",E[0],E[1],E[2],E[3],E[4],E[5],E[6],E[7],E[8]);
	printf("5 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",F[0],F[1],F[2],F[3],F[4],F[5],F[6],F[7],F[8]);
	printf("6 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",G[0],G[1],G[2],G[3],G[4],G[5],G[6],G[7],G[8]);
	printf("7 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7],H[8]);
	printf("8 |\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",I[0],I[1],I[2],I[3],I[4],I[5],I[6],I[7],I[8]);
}

void reveal_all(){
	for(int j=0;j<NUM_TILES_Y;j++){
		for(int i=0;i<NUM_TILES_X;i++){
			this_game.tiles[j][i].is_revealed=1;
			if(this_game.tiles[j][i].is_mine==0){
				this_game.tiles[j][i].display_symbol=' ';
			}

		}
	}

}
void cleanup(){
	//time(&end_t);
	// Pass out user, time taken, games won, total game played<- always + 1 when updating server


	// free all memory
	// return to main menu

	//this_game.time_taken=diff_time(end_t,start_t);
	

	
}


int main(int argc, char* argv[]){
	initialise_game();
	printf("Size of Tile is %d\n",sizeof(this_tile));
	printf("Size of GameState is %d\n",sizeof(this_game));

	// Manipulate some stuff
	//this_game.tiles[1][2].is_mine=1;
	place_mines();
//	reveal(3,6);
	//reveal_this_tile(7,4);
	//reveal_this_tile(8,2);

	int counter=0;
	while(!this_game.game_quit && !this_game.game_over && !this_game.game_won){
		
		if(this_game.current_mines_active==0){
			printf("Congratulations! You have defused all mines!\n");
			this_game.game_won=1;
			return this_game.game_won; // break out of the while loop here
		}
		// Wait for player input		
		//place_lots_of_flags();// Leave in for testing
		//reveal_this_tile(4,5);
		steppity_step();
		//counter+=1;
		//printf("Loops done: %d\n",counter);
		display_game();
	}

/*	
	reveal(3,7);
	display_game();
	reveal(8,3);
	display_game();
	reveal(1,8);
	display_game();
*/
	printf("\n\nDo Game Quit/ Game Over/ Game Won Logic Here\n");
	if(this_game.game_quit){
		printf("Quit Logic\n");
	}
	else if(this_game.game_over){
		printf("Gameover logic\n");
		reveal_all();
		
		display_game();
	}
	else{
		printf("Game Won Logic!\n");
	}	
	cleanup();
	printf("End of code\n");
	return 0;
}
