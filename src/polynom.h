#ifndef POLYNOM_H
#define POLYNOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int base;
  int exponent;

  int have_exponent;
  int is_constant;

  char letter;
} Polynom;

void polynom_print(const Polynom*);
char* polynom_to_string(const Polynom*);

char* polynom_to_string(const Polynom* polynom) {
  char *string = malloc(sizeof(char) * 300);

  if (polynom->is_constant) {
    if (polynom->have_exponent && polynom->exponent != 1) {
      sprintf(string, "%d^%d", polynom->base, polynom->exponent);
    } else {
      sprintf(string, "%d", polynom->base);
    }
  } else {
    if (polynom->have_exponent && polynom->exponent != 1 && polynom->base != 1) {
      sprintf(string, "%d%c^%d", polynom->base, polynom->letter, polynom->exponent);
    } else if (polynom->have_exponent && polynom->exponent != 1 && polynom->base == 1) {
      sprintf(string, "%c^%d", polynom->letter, polynom->exponent);
    } else if (polynom->base == 1 && !polynom->have_exponent) {
      sprintf(string, "%c", polynom->letter);
    } else {
      sprintf(string, "%d%c", polynom->base, polynom->letter);
    }
  }

  return string;
}

void polynom_print(const Polynom* polynom) {
  printf("%s", polynom_to_string(polynom));
}


#endif