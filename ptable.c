#include "utils.h"

int main(int argc, char *argv[]) {
  if (argc >= 2 && strcmp(argv[1], "info") == 0) {
    printf("Works on thinkpad, so half of linux\n");
    return 0;
  }
  else if (argc >= 2 && strcmp(argv[1], "dep") == 0) {
    printf("requires stdio.h, stdlib.h, string.h, and ncurses.h\n");
    return 0;
  }

  initscr();
  atexit(endprog);
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  validpos();
  int cursor = 0;
  int ch;

  while (1) {

    for (int i = 0; i < cellcnt; i++) {
      int y = 2 + cells[i][0];
      int x = cells[i][1] * 3;

      if (i == cursor) attron(A_REVERSE);
      mvprintw(y, x, "%-2s", table[cells[i][0]][cells[i][1]]);
      if (i == cursor) attroff(A_REVERSE);
    }

    move(0, 0);
    clrtoeol();
    printw("ATN: %d | NAME: %s | AMU: %.3f ", get_atn(cursor), get_name(cursor), get_amu(cursor));

    refresh();
    ch = getch();

    switch (ch) {
      case 'q':
        return 0;
      case KEY_LEFT:
        cursor = (cursor - 1 + cellcnt) % cellcnt;
        break;
      case KEY_RIGHT:
        cursor = (cursor + 1) % cellcnt;
        break;
      case KEY_UP:
      case KEY_DOWN: {
        int dest = jmpcolumn(cursor, (ch == KEY_UP ? -1 : 1));
        if (dest != -1) cursor = dest;
        break;
      }
    }
  }
  return 0;
}