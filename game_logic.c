#define NUM_TILES_X 9
#define NUM_TILES_Y 9
#define NUM_MINES 10
#define RANDOM_NUMBER_SEED 42 // server

#include <stdio.h>
#include <stdlib.h>
#include <math.h>// not needed in final code?


typedef struct
{
	int adjacent_mines;// value from 0 to 8.
	int is_revealed;// value of 1 or 0
	int is_mine;// value of 1 or 0
	// This struct builds the tiles; should i have a pointer to the next tile that i wish to update here?
} Tile;

typedef struct
{
	//... additional fields...
	int game_quit; // determine if game ends due to quitting
	int game_won; // determine if game has been successfully won
	int game_over;// state of game_over
	int current_mines_active;
	Tile tiles[NUM_TILES_X][NUM_TILES_Y]; // define game size
	// This stuct builds the whole game
} GameState;

Tile this_tile;
GameState this_game;
//srand(RANDOM_NUMBER_SEED);


void initialise_game(){
	// initialise timer

	// initialise GameState params
	this_game.game_quit=0;
	this_game.game_over=0;
	this_game.current_mines_active=10;

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

void reveal_this_tile(int x, int y){\
	
	printf("Now Jumping really hard at %d,%d \n",x,y);	
	// Check if this is a mine
		// If Yes, Game over
	if(this_game.tiles[y][x].is_mine==1){
		this_game.game_over=1;
		this_game.game_won=0;// This game has not been won, add 0 to number of games won in leaderboard.
		printf("You have steped on a mine and died. Better Luck Next Time!\n");
	}// If the tile if not a mine
		
	else{
		printf("Phew! This tile is not a mine. What a lucky day!\n");
		//-> check if ANY of the neighbours are mines
		printf("Checking all 8 neighours for mines!\n");
		for(int xoff=-1;xoff<1+1;xoff++){
			for(int yoff=-1;yoff<1+1;yoff++){
				int i=x+xoff;
				int j=y+yoff;
				// If i,j are not outside of the map, do the checking
				if(i>-1&&i<9&&j>-1&&j<9){
				
					// This will check self, however, since self is not a mine, +0 will not affect total.
					if(this_game.tiles[j][i].is_mine==1){
						this_game.tiles[y][x].adjacent_mines+=1;// Add a mine for each neighbouring mine
						printf("This neighbour (%d,%d) is a mine!\n",i,j);
					}// else, this neighbour tile is not a mine
					else{
						printf("This neighbour (%d,%d) is not a mine!\n",i,j);
					}	
				}
				else{
					printf("We did not check the tiles(%d,%d) located outside the map!\n",i,j);				
				}
			}//inner nested for
		}// After checking all 8 neighbours, is this_tile.adjacent_mines==0?
	// If yes-> perform a recursive reveal on all non-revealed neighbours
		
	}// If this_tile.adjacent_mines!=0, pass this value out to be handled
	printf("This tile (%d, %d) has %d neighbouring mines!\n",x,y,this_game.tiles[y][x].adjacent_mines);
}

void steppity_step(){

	int x,y;
	x=rand()%NUM_TILES_X;
	y=rand()%NUM_TILES_Y;
	reveal_this_tile(x,y);
	
}

void cleanup(){
	// Update leaderboards if applicable
	// free all memory
	// return to main menu

}
int main(int argc, char* argv[]){
	initialise_game();
	printf("Size of Tile is %d\n",sizeof(this_tile));
	printf("Size of GameState is %d\n",sizeof(this_game));

	// Manipulate some stuff
	//this_game.tiles[1][2].is_mine=1;
	place_mines();
	//reveal_this_tile(5,6);
	int counter=0;
	while(!this_game.game_quit && !this_game.game_over && !this_game.game_won){
		
		if(this_game.current_mines_active==0){
			printf("Congratulations! You have defused all mines!\n");
			this_game.game_won=1;
		}
		place_lots_of_flags();// Leave in for testing
		//reveal_this_tile(1,6);
		//steppity_step();
		counter+=1;
		printf("Loops done: %d\n",counter);
	}

	
	printf("\n\nDo Game Quit/ Game Over/ Game Won Logic Here\n");
	
	
	printf("End of code\n");
}
