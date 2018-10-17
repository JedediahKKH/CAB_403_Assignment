#define NUM_TILES_X 9
#define NUM_TILES_Y 9
#define NUM_MINES 10
#define RANDOM_NUMBER_SEED 42 // server

typedef struct
{
	int adjacent_mines;
	bool revealed;
	bool is_mine;

} Tile;

typedef struct
{
	//... additional fields...
	bool game_quit; // determine if game ends due to quitting
	bool game_won; // determine if game has been successfully won

	Tile tiles[NUM_TILES_X][NUM_TILES_Y]; // define game size
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

}

bool tile_contains_mine(int x, int y){
	if(tiles[x][y].is_mine){
		return true;
	}
	else{
		return false;
	}
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
}