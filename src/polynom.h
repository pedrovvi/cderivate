#ifndef POLYNOM_H
#define POLYNOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int base;
  int exponent;

  int have_exponent;
  int is_constant;

  char letter;
} Polynom;

void polynom_print(const Polynom *);
char *polynom_to_string(const Polynom *);

char *polynom_to_string(const Polynom *polynom)
{
  char *string = malloc(sizeof(char) * 300);
  char coeficient[20];

  if (polynom->is_constant)
  {
    if (polynom->base != 1 || (polynom->base == 1 && !polynom->have_exponent))
    {
      if (polynom->have_exponent && polynom->exponent != 1)
      {
        sprintf(coeficient, "%d^%d", polynom->base, polynom->exponent);
      }
      else
      {
        sprintf(coeficient, "%d", polynom->base);
      }
      sprintf(string, "%s", coeficient);
    }
    else
    {
      string[0] = '\0';
    }
  }
  else
  {
    if (polynom->base != 0)
    {
      if (polynom->base == 1 && polynom->have_exponent && polynom->exponent != 1)
      {
        sprintf(string, "%c^%d", polynom->letter, polynom->exponent);
      }
      else if (polynom->exponent == 1)
      {
        sprintf(string, "%d%c", polynom->base, polynom->letter);
      }
      else if (polynom->have_exponent && polynom->exponent != 1)
      {
        sprintf(string, "%d%c^%d", polynom->base, polynom->letter, polynom->exponent);
      }
      else if (!polynom->have_exponent)
      {
        sprintf(string, "%d", polynom->base);
      }
    }
    else
    {
      sprintf(string, "0");
    }
  }

  return string;
}

void polynom_print(const Polynom *polynom)
{
  printf("%s", polynom_to_string(polynom));
}

#endif