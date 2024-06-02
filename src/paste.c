#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int base;
    int expo;
    int constant_flag;
    int sign;
} Polynom;

int is_eof(char *source, int cursor) {
    return cursor < strlen(source) ? 0 : 1;
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

char next(char *source, int *cursor) {
    char current = source[*cursor];
    *cursor += 1;
    return current;
}

void print_polynom(Polynom *polynom) {
    if (polynom->constant_flag == 1) {
        printf("%d\n", polynom->base);
    } else {
        if (polynom->base == 1 && polynom->expo != 0) {
            printf("x^%d\n", polynom->expo);
        } else {
            printf("%dx^%d\n", polynom->base, polynom->expo);
        }
    }
}

int parse_number(char *source, int *cursor) {
    int start = *cursor;
    while (!is_eof(source, *cursor) && is_digit(source[*cursor])) {
        (*cursor)++;
    }

    char *result;
    strncpy(result, &source[start], *cursor - start);
    result[*cursor-start] = '\0';

    return atoi(result);
}

int main(void) {
    char source[300];

    printf("Digite a funcao polinomial: ");
    fgets(source, 300, stdin);

    Polynom *polynoms = malloc(sizeof(Polynom));
    Polynom *p;

    char curr;

    int cursor = 0;
    int count = 0;

    while (!is_eof(source, cursor)) {
        p = malloc(sizeof(Polynom));

        curr = next(source, &cursor);

        if (curr == '-' || curr == '+') {
            p->sign = curr == '-' ? -1 : 1;
            curr = next(source, &cursor);
        } else {
            p->sign = 1;
        }

        if (is_digit(curr)) {
            cursor--;
            p->base = parse_number(source, &cursor);
            curr = next(source, &cursor);
        } else {
            p->base = 1;
        }

        if (curr == 'x') {
            p->constant_flag = 0;
            curr = next(source, &cursor);
        } else {
            p->constant_flag = 1;
        }

        if (curr == '^') {
            curr = next(source, &cursor);
            if (is_digit(curr)) {
                cursor--;
                p->expo = parse_number(source, &cursor);
            } else {
                printf("Erro durante a interpretacao da funcao.");
                return 1;
            }
        } else {
            p->expo = p->constant_flag ? 0 : 1;
        }

        p->base = p->base * p->sign;

        polynoms = realloc(polynoms, sizeof(Polynom) * (count + 1));
        polynoms[count] = *p;
        count++;

        free(p);
    }

    for (int i = 0; i < count; i++) {
        print_polynom(&polynoms[i]);
    }

    free(polynoms);

    return 0;
}
