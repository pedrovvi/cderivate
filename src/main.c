#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"

#define STR_LEN 300

int main() {
  char source[STR_LEN];
  printf("Digite a funcao polinomial: ");
  fgets(source, STR_LEN, stdin);

  Lexer lexer = construct_lexer(source);
  Token* tokens = lexer_lex(&lexer);

  if (lexer.had_error) {
    printf(lexer.error_source);
    return 1;
  }

  for (int i = 0; i < lexer.token_count; i++)
    token_print(&tokens[i]);

  return 0;
}