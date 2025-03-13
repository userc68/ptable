#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "dat.h"

int cells[ROWS * COLS][2];
int cellcnt = 0;

void endprog(void) { endwin(); }

void validpos() {
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      if (table[r][c]) {
        cells[cellcnt][0] = r;
        cells[cellcnt][1] = c;
        cellcnt++;
      }
    }
  }
}

int jmpcolumn(int idx, int dir) {
  int cur_col = cells[idx][1];

  for (int i = idx + dir; i >= 0 && i < cellcnt; i += dir) {
    if (cells[i][1] == cur_col) return i;
  }

  for (int i = (dir < 0 ? cellcnt - 1 : 0); i >= 0 && i < cellcnt; i += (dir < 0 ? -1 : 1)) {
    if (cells[i][1] == cur_col) return i;
  }

  return idx;
}

double get_amu(int cursor) {
  const char *symbol = table[cells[cursor][0]][cells[cursor][1]];
  for (size_t i = 0; i < sizeof(elements) / sizeof(*elements); i++) {
    if (strcmp(elements[i].sym, symbol) == 0) {
      return elements[i].amu;
    }
  }
  return -1;
}

char *get_name(int cursor) {
  const char *symbol = table[cells[cursor][0]][cells[cursor][1]];
  for (size_t i = 0; i < sizeof(elements) / sizeof(*elements); i++) {
    if (strcmp(elements[i].sym, symbol) == 0) {
      return elements[i].name;
    }
  }
  return NULL;
}

int get_atn(int cursor) {
  const char *symbol = table[cells[cursor][0]][cells[cursor][1]];
  for (size_t i = 0; i < sizeof(elements) / sizeof(*elements); i++) {
    if (strcmp(elements[i].sym, symbol) == 0) {
      return elements[i].atn;
    }
  }
  return -1;
}

#endif