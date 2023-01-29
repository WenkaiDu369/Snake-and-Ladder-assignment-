#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int main(void) {
  struct board *snl = board_read();
  board_print(snl);
  
  char c = '\0';
  scanf("%c", &c);
  
  int field = INT_MIN, roll = INT_MIN;
  while (scanf("%d%d", &field, &roll) == 2) {
    printf("From field %03d, a roll of %d would take you to field %03d.\n",
          field, roll,board_next(snl, field, roll));
  }
  board_destroy(snl);
  return EXIT_SUCCESS;
}
