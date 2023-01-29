#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "board.h"

// === Snakes & Ladders Board Field ==========================================

struct board_block {
  int pos;
  int snake;
  int ladder;
  struct board_block *next;
};
// -1 is non-exist
// other int is snake to or ladder to

// === Snakes & Ladders Board ================================================

struct board {
  struct board_block *front;
};

struct board *clean_board(void) {
  struct board *snl = malloc(sizeof(struct board));
  snl->front = NULL;
  int board_len = 100;
  while(board_len > 0) {
    struct board_block *new_block = malloc(sizeof(struct board_block));
    new_block->pos = board_len;
    new_block->snake = -1;
    new_block->ladder = -1;
    new_block->next = snl->front;
    snl->front = new_block;
    board_len--;
  }
  return snl;
}

// See board.h for documentation
struct board *board_read() {
  struct board *snl = clean_board();
  int i = 0; // first int
  int j = 0; // second int
  int k = 0; // third int
  int start = 1; // the starting position of traversing
  struct board_block *change_block = snl->front;
  while(scanf("%d", &i) == 1 && scanf("%d", &j) == 1 && scanf("%d", &k) == 1) {
    while (start < i) {
      change_block = change_block->next;
      start++;
    }
    // at this moment, block->pos is equal to i, where we need to modify the list
    change_block->snake = j;
    change_block->ladder = k;
    start = 1;
    change_block = snl->front;
  }
  return snl;
}

// See board.h for documentation
void board_destroy(struct board *snl) {
  struct board_block *current_block = snl->front;
  struct board_block *next_block = NULL;
  while(current_block) {
    next_block = current_block->next;
    free(current_block);
    current_block = next_block;
  }
  free(snl);
}

// See board.h for documentation
int board_next(const struct board *snl, int start, int roll) {
  assert(snl);
  assert(start >= 1 && start < 100);
  assert(roll >= 1 && roll <= 6);
  int n = 1;
  int pos = start + roll;
  if (pos >= 100) {
    return 100;
  }
  const struct board_block *test_block = snl->front;
  while(n < pos) {
    test_block = test_block->next;
    n++;
  }
  if (test_block->snake != -1) {
    return test_block->snake;
  } if (test_block->ladder != -1) {
    return test_block->ladder;
  } else {
    return test_block->pos;
  }
}

// See board.h for documentation
void board_print(const struct board *snl) {
  assert(snl);
  const struct board_block *next_block = snl->front;
  int column = 10;
  int row = 10;
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < column; j++) {
      if (!(i == 9 && j == 9)) {
        if (next_block->snake == -1 && next_block->ladder == -1) {
          printf("[   %03d   ] => ", next_block->pos);
        } else if (next_block->ladder == -1) {
          printf("[%03d (%02d>)] => ", next_block->pos, next_block->snake);
        } else {
          printf("[%03d (<%02d)] => ", next_block->pos, next_block->ladder);
        }
        next_block = next_block->next;
      }
    }
    if (i != 9) {
      printf("\n");
    }
  }
  if (next_block->snake == -1 && next_block->ladder == -1) {
    printf("[   %03d   ]\n", next_block->pos);
  } else if (next_block->ladder == -1) {
    printf("[%03d (%02d>)]\n => ", next_block->pos, next_block->snake);
  } else {
    printf("[%03d (<%02d)]\n => ", next_block->pos, next_block->ladder);
  }
}
