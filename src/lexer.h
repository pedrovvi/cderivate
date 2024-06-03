#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "utils.h"

typedef struct
{
  // Errors
  int had_error;
  char error_source[300];

  // Source
  char *source;
  int start;
  int cursor;

  // Tokens
  Token *tokens;
  int token_count;
} Lexer;

Lexer construct_lexer(char *);
Token *lexer_lex(Lexer *);
int lexer_is_eof(Lexer *);
char lexer_next(Lexer *);
void lexer_read_token(Lexer *);
void lexer_push_token(Lexer *, TokenKind);
void lexer_read_number(Lexer *);
int lexer_is_digit(Lexer *);
char *lexer_get_lexeme(Lexer *);

Lexer construct_lexer(char *source)
{
  Lexer lexer;

  lexer.had_error = 0;

  lexer.source = source;
  lexer.cursor = 0;
  lexer.tokens = (Token *)malloc(sizeof(Token));
  lexer.token_count = 0;

  return lexer;
}

Token *lexer_lex(Lexer *lexer)
{
  while (!lexer_is_eof(lexer) && !lexer->had_error)
  {
    lexer->start = lexer->cursor;
    lexer_read_token(lexer);
  }

  return lexer->tokens;
}

int lexer_is_eof(Lexer *lexer)
{
  return lexer->cursor >= strlen(lexer->source);
}

void lexer_read_token(Lexer *lexer)
{
  const char current = lexer_next(lexer);

  switch (current)
  {
  case '+':
    return lexer_push_token(lexer, PLUS_TOKEN);
  case '-':
    return lexer_push_token(lexer, MINUS_TOKEN);
  case '^':
    return lexer_push_token(lexer, EXPONENT_TOKEN);
  case 'x':
    return lexer_push_token(lexer, LETTER_TOKEN);

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return lexer_read_number(lexer);

  case ' ':
    return;

  case '\0':
  case '\n':
    return lexer_push_token(lexer, EOF_TOKEN);

  default:
    lexer->had_error = 1;
    char invalid[2];
    invalid[0] = current;
    invalid[1] = '\n';
    invalid[2] = '\0';

    char error_line[100];
    sprintf(error_line, "%s^", repeatc(' ', lexer->start));

    strcat(lexer->error_source, "~lexer: Erro, foi encontrado um caractere invalido: ");
    strcat(lexer->error_source, invalid);
    strcat(lexer->error_source, lexer->source);
    strcat(lexer->error_source, "\n");
    strcat(lexer->error_source, error_line);

    break;
  }
}

char lexer_next(Lexer *lexer)
{
  char current = lexer->source[lexer->cursor++];
  return current;
}

void lexer_push_token(Lexer *lexer, TokenKind kind)
{
  char *lexeme = kind == EOF_TOKEN ? '\0' : lexer_get_lexeme(lexer);

  Token token = {kind, lexeme, lexer->start, lexer->cursor};
  lexer->tokens = (Token *)realloc(lexer->tokens, sizeof(Token) * (lexer->token_count + 1));
  lexer->tokens[lexer->token_count++] = token;
};

void lexer_read_number(Lexer *lexer)
{
  while (!lexer_is_eof(lexer) && lexer_is_digit(lexer))
  {
    lexer_next(lexer);
  }

  lexer_push_token(lexer, NUMBER_TOKEN);
}

int lexer_is_digit(Lexer *lexer)
{
  const char c = lexer->source[lexer->cursor];
  return (c >= '0' && c <= '9');
}

char *lexer_get_lexeme(Lexer *lexer)
{
  int len = lexer->cursor - lexer->start;
  char *lexeme = (char *)malloc(sizeof(char) * len);
  strncpy(lexeme, &lexer->source[lexer->start], len);
  lexeme[len] = '\0';

  return lexeme;
}

#endif