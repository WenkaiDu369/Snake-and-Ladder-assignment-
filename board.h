// board.c [INTERFACE]
// A snakes and ladder ADT module

// board represents a game board for Snakes & Ladders
struct board;

// board_read() reads the board information from input, creates a game board,
//   and returns it.
// effects: allocates memory; client must call board_destroy()
// time:  O(n), where n is the number of fields on the board
struct board *board_read(void);

// board_destroy(snl) releases all resources used by snl.
// effects: invalidates snl
// time:  O(n), where n is the number of field on the board
void board_destroy(struct board *snl);

// board_next(snl, start, roll) retrieves the field on which a player will land
//   given a paricular game board (snl), a start field, and a dice roll.
// requires: start must be between 1 and the number of fields [both inclusive]
//   roll must be between the lowest and highest value of the die
int board_next(const struct board *snl, int start, int roll);

// board_print(snl) prints the content of the game board (snl).
// effects: creates output
void board_print(const struct board *snl);
