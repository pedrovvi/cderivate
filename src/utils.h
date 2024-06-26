#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polynom.h"

double get_y(Polynom *, int, int);
void derivate_polynom(Polynom *);
void derivate_polynoms(Polynom *, int);
void print_function(Polynom *, int, int);
char* repeatc(char, int);

void print_function(Polynom *polynoms, int polynom_count, int is_derivate)
{
    char source[300] = "";
    strcat(source, !is_derivate ? "f(x) = 0" : "f'(x) = 0");

    int initialized = 0;

    for (int i = 0; i < polynom_count; i++)
    {
        Polynom polynom = polynoms[i];

        if (polynom.base == 0)
            continue;

        if (!initialized) {
            if (!is_derivate) {
                strcpy(source, "f(x) =");
            } else {
                strcpy(source, "f'(x) =");
            }
            initialized = 1;
        }

        char current[100];
        sprintf(current, "%s%s", polynom.base >= 0 && i > 0 ? " + " : " ", polynom_to_string(&polynom));
        strcat(source, current);
    }

    printf("%s", source);
}

void derivate_polynom(Polynom *polynom)
{
  if (polynom->is_constant)
  {
    polynom->base = 0;
    polynom->have_exponent = 0;
    polynom->exponent = 1;
  }
  else
  {
    polynom->base *= polynom->exponent;
    polynom->exponent--;
    polynom->have_exponent = 1;

    if (polynom->exponent == 0)
    {
      polynom->have_exponent = 0;
      polynom->exponent = 1;
      polynom->is_constant = 1;
    }
  }
}

void derivate_polynoms(Polynom *polynoms, int polynom_count)
{
  for (int i = 0; i < polynom_count; i++)
    derivate_polynom(&polynoms[i]);
}

double get_y(Polynom *polynoms, int polynom_count, int x)
{
  double result = 0;

  for (int i = 0; i < polynom_count; i++)
  {
    Polynom p = polynoms[i];

    if (p.is_constant)
    {
      if (p.have_exponent)
      {
        result += pow(p.base, p.exponent);
      }
      else
      {
        result += p.base;
      }
    }
    else
    {
      result += pow(x, p.exponent) * p.base;
    }
  }

  return result;
}

char* repeatc(char c, int n) {
  char* result = (char*) malloc(sizeof(char) * n);
  
  for (int i = 0; i < n; i++)
    result[i] = c;
  result[n] = '\0';
  
  return result;
}

#endif