#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
  // Symbols
  PLUS_TOKEN,
  MINUS_TOKEN,
  EXPONENT_TOKEN,

  // Literals
  NUMBER_TOKEN,
  LETTER_TOKEN,

  // End of File
  EOF_TOKEN
} TokenKind;

typedef struct
{
  TokenKind kind;
  char *lexeme;
  int start;
  int end;
} Token;

void token_print(Token *);
char *token_kind_name(TokenKind);
char *token_kind_lexeme(TokenKind);

void token_print(Token *token)
{
  printf("(kind: %s, start: %d, end: %d, lexeme: %s)\n",
         token_kind_name(token->kind), token->start, token->end, token->lexeme);
}

char *token_kind_name(TokenKind kind)
{
  switch (kind)
  {
  case PLUS_TOKEN:
    return "Plus";
  case MINUS_TOKEN:
    return "Minus";
  case EXPONENT_TOKEN:
    return "Exponent";
  case NUMBER_TOKEN:
    return "Number";
  case LETTER_TOKEN:
    return "Letter";
  case EOF_TOKEN:
    return "End of File";
  default:
    return "Invalid Token";
  }
}

char *token_kind_lexeme(TokenKind kind)
{
  switch (kind)
  {
  case PLUS_TOKEN:
    return "+";
  case MINUS_TOKEN:
    return "-";
  case EXPONENT_TOKEN:
    return "^";
  case NUMBER_TOKEN:
    return "Numero";
  case LETTER_TOKEN:
    return "Letra";
  case EOF_TOKEN:
    return "Final da funcao";
  default:
    return "Simbolo Invalido";
  }
}

#endif