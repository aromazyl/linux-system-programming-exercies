/*
 * my_more.c
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE*);

int see_more(FILE*);

int
main(int argc, char* argv[]) {
  FILE* fp = NULL;
  if (argc == 1) do_more(stdin);
  else
    for (int i = 1; i < argc; ++i) {
      fp = fopen(argv[i], "r");
      if (!fp) exit(1);
      do_more(fp);
    }
  return 0;
}

void do_more(FILE* file) {
  char line[LINELEN];
  int num_of_lines = 0;
  int reply;
  FILE* tty_file = fopen("/dev/tty", "r");
  while (fgets(line, LINELEN, file)) {
    if (num_of_lines == PAGELEN) {
      reply = see_more(tty_file);
      if (!reply) break;
      num_of_lines -= reply;
    }
    if (fputs(line, stdout) == EOF) exit(0);
    num_of_lines ++;
  }
}

int see_more(FILE* cmd) {
  int c;
  printf("\033[7m more? \033[m");
  while ((c = getc(cmd)) != EOF) {
    if (c == 'q') return 0;
    if (c == ' ') return PAGELEN;
    if (c == '\n') return 1;
  }
  return 0;
}
