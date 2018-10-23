#define NUM_TILES_X 9
#define NUM_TILES_Y 9
#define NUM_MINES 10
#define RANDOM_NUMBER_SEED 42 // server

typedef struct
{
	int adjacent_mines;
	bool revealed;
	bool is_mine;
	// This struct builds the tiles; should i have a pointer to the next tile that i wish to update here?
} Tile;

typedef struct
{
	//... additional fields...
	bool game_quit; // determine if game ends due to quitting
	bool game_won; // determine if game has been successfully won

	Tile tiles[NUM_TILES_X][NUM_TILES_Y]; // define game size
	// This stuct builds the whole game
} GameState;


void place_mines(){

	for(int i=0;i<NUM_MINES;i++){
		int x,y;
		do{
			x=rand() % NUM_TILES_X;
			y=rand() % NUM_TILES_Y;

		}while(tile_contains_mine(x,y));
		// Places mine at (x,y)
	}
	// Function to place a mine at the beginning of the game
}

int tile_contains_mine(int x, int y){
	if(tiles[x][y].is_mine){
		return 1;
	}
	else{
		return 0;
	}
	// this function acts as a bool, c has no library for booleans
}

void cleanup(){
	// Update leaderboards if applicable
	// free all memory
	// return to main menu

}

int main(int argc, char* argv[]){
	// [...]
	// Server side
	// start up with a single input of PORT_NUMBER<- if none-> default_PORT_NUMBER=12345
	// While (!terminate)-> do everything
	// initialise authentication table
	// Seed the server
	srand(RANDOM_NUMBER_SEED); // seed the random number generator
	// Allocate Storage for the state of the clients game.
	// Randomly place mines
	// Wait for client to send game option
	// Wait for client to send co-ords
	// run tile_contains_mine
	// if true-> game_over/ place flag
	// else-> reveal(recursive)/ error message
	// Go through linked list?-> check if tile[x][y].revealed is true
		// if yes-> put [x][y][value],[x][y][value] into buffer to be sent to client
		// if no-> go to next tile
	// send buffer to client
	// clear buffer
	// [...]

	// Client side
	// startup with 2 input of hostname and PORT_NUMBER<- receives a thread here
	// store username in buffer
	// store password in buffer
	// send buffer to server
	// clear buffer
	// receive buffer from server<- successful login/ login failed
	// if not successful, will terminate
	// else-> draw_main_menu
	// scan input-> store into buffer (play,show,quit)
	// send to server
	// clear buffer
	// receive buffer from server (game,leaderboard,terminate)
	// if game-> draw_game
		// enter infinite while loop
			// wait for further input
		// return to main_menu		
	// else if leaderboard-> draw_leaderboard
		// wait for input
		
	// else terminate

}