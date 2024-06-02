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

void print_function(Polynom *polynoms, int polynom_count, int is_derivate)
{
  char source[300] = "";
  strcat(source, !is_derivate ? "f(x) =" : "f'(x) =");

  for (int i = 0; i < polynom_count; i++)
  {
    Polynom polynom = polynoms[i];

    if (polynom.base == 0)
      continue;

    char current[100];
    sprintf(current, "%s%s", polynom.base >= 0 && i > 0 ? " + " : " ", polynom_to_string(&polynom));
    strcat(source, current);
  }

  printf(source);
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

#endif