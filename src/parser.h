#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "polynom.h"

typedef struct {
    int had_error;
    char error_source[300];

    int cursor;
    Token* tokens;
    int token_count;

    Polynom* polynoms;
    int polynom_count;
} Parser;

Parser construct_parser(Token*, int);
Polynom* parser_parse(Parser*);
int parser_is_eof(Parser*);
Token parser_eat(Parser*, TokenKind);
Token parser_peek(Parser*);
int parser_is_curr(Parser*, TokenKind);
void parser_parse_polynom(Parser*);
void parser_push_polynom(Parser*, Polynom*);

Parser construct_parser(Token* tokens, int token_count) {
    Parser parser;
    parser.had_error = 0;
    parser.cursor = 0;
    parser.tokens = tokens;
    parser.token_count = token_count;
    parser.polynom_count = 0;
    parser.polynoms = NULL;

    return parser;
}

Polynom* parser_parse(Parser* parser) {
    while (!parser_is_eof(parser) && !parser->had_error && parser_peek(parser).kind != EOF_TOKEN) {
        parser_parse_polynom(parser);
    }

    return parser->polynoms;
}

int parser_is_eof(Parser* parser) {
    return parser->cursor >= parser->token_count;
}

Token parser_eat(Parser* parser, TokenKind kind) {
    Token token = parser_peek(parser);
    
    if (token.kind != kind) {
        parser->had_error = 1;
        sprintf(parser->error_source, "~parser: Erro, foi encontrado um token invalido: %s, esperado: %s", 
                token_kind_name(token.kind), token_kind_name(kind));
        return token;
    }
    
    parser->cursor++;
    return token;
}

Token parser_peek(Parser* parser) {
    return parser->tokens[parser->cursor];
}

int parser_is_curr(Parser* parser, TokenKind kind) {
    Token token = parser_peek(parser);
    return token.kind == kind;
}

void parser_parse_polynom(Parser* parser) {
    Polynom* polynom = malloc(sizeof(Polynom));
    polynom->base = 1; 
    polynom->exponent = 1;
    polynom->have_exponent = 0; 
    polynom->is_constant = 0; 

    Token current = parser_peek(parser);

    if (parser_is_curr(parser, EOF_TOKEN)) 
      return;

    if (parser_is_curr(parser, MINUS_TOKEN) || parser_is_curr(parser, PLUS_TOKEN)) {
        current = parser_eat(parser, current.kind);
        polynom->base = current.kind == MINUS_TOKEN ? -1 : 1;
    }

    if (parser_is_curr(parser, NUMBER_TOKEN) || parser_is_curr(parser, LETTER_TOKEN)) {
        current = parser_peek(parser);

        if (current.kind == NUMBER_TOKEN) {
            current = parser_eat(parser, NUMBER_TOKEN);
            polynom->base *= atoi(current.lexeme);
            polynom->is_constant = 1;
            current = parser_peek(parser);
        }

        if (current.kind == LETTER_TOKEN) {
            current = parser_eat(parser, LETTER_TOKEN);
            polynom->letter = current.lexeme[0];
            polynom->is_constant = 0;
            current = parser_peek(parser);
        }

        if (current.kind == EXPONENT_TOKEN) {
            parser_eat(parser, EXPONENT_TOKEN);
            current = parser_eat(parser, NUMBER_TOKEN);

            if (parser->had_error) {
                free(polynom);
                return;
            }

            polynom->exponent = atoi(current.lexeme);
            polynom->have_exponent = 1;
        }

        parser_push_polynom(parser, polynom);
    } else {
        free(polynom);
        parser_eat(parser, NUMBER_TOKEN);
        return;
    }
}

void parser_push_polynom(Parser* parser, Polynom* polynom) {
    parser->polynoms = (Polynom*) realloc(parser->polynoms, sizeof(Polynom) * (parser->polynom_count + 1));
    if (parser->polynoms == NULL) {
        parser->had_error = 1;
        sprintf(parser->error_source, "Erro na alocacao de memoria ao adicionar polinomio.");
        free(polynom);
        return;
    }
    parser->polynoms[parser->polynom_count++] = *polynom;
    free(polynom); 
}

#endif
