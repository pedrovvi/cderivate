#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "utils.h"

#define STR_LEN 300

int main()
{
  char source[STR_LEN];
  printf("Digite a funcao polinomial: ");
  fgets(source, STR_LEN, stdin);

  Lexer lexer = construct_lexer(source);
  Token *tokens = lexer_lex(&lexer);

  if (lexer.had_error)
  {
    printf(lexer.error_source);
    return 1;
  }

  /*
    for (int i = 0; i < lexer.token_count; i++)
      token_print(&tokens[i]);
  */

  Parser parser = construct_parser(tokens, lexer.token_count, source);
  Polynom *polynoms = parser_parse(&parser);

  if (parser.had_error)
  {
    printf(parser.error_source);
    return 1;
  }

  /*
  for (int i = 0; i < parser.polynom_count; i++)
    polynom_print(&polynoms[i]);
  */

  double x;
  printf("Digite o ponto x: ");
  scanf("%lf", &x);

  printf("\n");
  print_function(polynoms, parser.polynom_count, 0);
  printf("\nf(%.2lf) = %.2lf\n", x, get_y(polynoms, parser.polynom_count, x));

  derivate_polynoms(polynoms, parser.polynom_count);
  print_function(polynoms, parser.polynom_count, 1);
  printf("\nf'(%.2lf) = %.2lf\n", x, get_y(polynoms, parser.polynom_count, x));

  free(polynoms);
  free(tokens);

  free(lexer.source);
  free(lexer.tokens);

  free(parser.polynoms);
  free(parser.tokens);

  return 0;
}