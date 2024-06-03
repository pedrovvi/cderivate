#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "utils.h"
#include "polynom.h"

#define STR_LEN 300

void interpret(Polynom **polynoms, int *polynom_count, char *source, int print_err)
{
  *polynoms = NULL;
  
  Lexer lexer = construct_lexer(source);
  Token *tokens = lexer_lex(&lexer);

  if (lexer.had_error)
  {
    if (print_err)
    {
      printf("==================================\n");
      printf(lexer.error_source);
      printf("\n==================================\n");
      return;
    }

    return;
  }

  Parser parser = construct_parser(tokens, lexer.token_count, source);
  *polynoms = parser_parse(&parser);
  *polynom_count = parser.polynom_count;

  if (parser.had_error)
  {
    if (print_err)
    {
      printf("==================================\n");
      printf(parser.error_source);
      printf("\n==================================\n");
      return;
    }

    return;
  }
}
void input_function(char *source, Polynom **polynoms, 
  Polynom **derivated_polynoms, int *polynom_count)
{
  printf("============ Como Usar ===========\n");
  printf("-> A funcao deve ser escrita da seguinte maneira: \n");
  printf("-> 2x^3 + 3x^4 - 4x^5\n");
  printf("-> Utilize ^ para indicar o expoente.\n");
  printf("==================================\n");

  int is_valid = 0;
  
  do
  {
    printf("-> Digite sua funcao: \nf(x) = ");
    fgets(source, STR_LEN, stdin);

    source[strcspn(source, "\n")] = 0;

    interpret(polynoms, polynom_count, source, 1);
    interpret(derivated_polynoms, polynom_count, source, 0);

    if (*polynoms == NULL || *derivated_polynoms == NULL || *polynom_count <= 0)
    {
      free(*polynoms);
      free(*derivated_polynoms);
      printf("-> Funcao invalida. Tente novamente.\n");
    }
    else
    {
      is_valid = 1;
    }
  } while (!is_valid);
}


void print_functions(Polynom *polynoms, Polynom *derivated_polynoms, int polynom_count)
{
  printf("-> Funcao: ");
  print_function(polynoms, polynom_count, 0);
  printf("\n-> Derivada: ");
  print_function(derivated_polynoms, polynom_count, 1);
  printf("\n=============================\n");
}

void setup_menu()
{
  printf("============ Menu ===========\n");
  printf("-> (0) Sair\n");
  printf("-> (1) Trocar funcao\n");
  printf("-> (2) Calcular valor funcional no ponto a\n");
  printf("-> (3) Calcular equacao da reta tangente no ponto P(a, f'(a))\n");
  printf("=============================\n");
}

void calculate_functional_value(Polynom* polynoms, Polynom* derivated_polynoms, int polynom_count) {
  double a, y, derivated_y;
  printf("-> Digite o valor de a: ");
  scanf("%lf", &a);
  getchar();

  y = get_y(polynoms, polynom_count, a);
  derivated_y = get_y(derivated_polynoms, polynom_count, a);

  printf("=============================\n");
  printf("-> a: %.2lf\n", a);
  printf("-> Funcao: ");
  printf("f(%.2lf) = %.2lf", a, y);
  printf("\n-> Derivada: ");
  printf("f'(%.2lf) = %.2lf", a, derivated_y);
  printf("\n-> Ponto: ");
  printf("P(%.2lf, %.2lf)\n", a, y);
  printf("=============================\n");
}

void calculate_tangent_line(Polynom* polynoms, Polynom* derivated_polynoms, int polynom_count) {
  getchar();
  double a, y, m, n;
  printf("-> Digite o valor de a: ");
  scanf("%lf", &a);
  getchar();

  y = get_y(polynoms, polynom_count, a);
  m = get_y(derivated_polynoms, polynom_count, a);
  n = -(m * a) + y;

  printf("=============================\n");
  
  if (m == 1) {
    printf("-> y = x %c %.2lf\n", n < 0 ? '-' : '+' , n < 0 ? n * -1 : n);
  } else if (m == -1) {
    printf("-> y = -x %c %.2lf\n", n < 0 ? '-' : '+' , n < 0 ? n * -1 : n);
  } else {
    printf("-> y = %.2lfx %c %.2lf\n", m, n < 0 ? '-' : '+' , n < 0 ? n * -1 : n);
  }

  printf("=============================\n");
}

int main()
{
  Polynom *polynoms = NULL;
  Polynom *derivated_polynoms = NULL;
  int polynom_count;
  char source[STR_LEN];

  input_function(source, &polynoms, &derivated_polynoms, &polynom_count);
  derivate_polynoms(derivated_polynoms, polynom_count);

  system("cls");
  setup_menu();
  print_functions(polynoms, derivated_polynoms, polynom_count);

  int is_valid;
  int option = -1;
  
  while (option != 0) {
    do
    {
      printf("-> Selecione uma opcao de 0 a 3: ");
      scanf("%d", &option);

      if (option >= 0 && option <= 3)
        is_valid = 1;
      else
      {
        is_valid = 0;
        printf("(*) Opcao invalida, tente novamente.\n");
      }
    } while (!is_valid);

    switch (option)
    {
    case 0:
      system("cls");
      free(polynoms);
      free(derivated_polynoms);
      return 0;
    case 1:
      system("cls");
      getchar();
      input_function(source, &polynoms, &derivated_polynoms, &polynom_count);
      derivate_polynoms(derivated_polynoms, polynom_count);
      printf("=============================\n");
      print_functions(polynoms, derivated_polynoms, polynom_count);
      break;
    case 2:
      system("cls");
      printf("=============================\n");
      print_functions(polynoms, derivated_polynoms, polynom_count);
      calculate_functional_value(polynoms, derivated_polynoms, polynom_count);
      break;
    case 3:
      system("cls");
      printf("=============================\n");
      print_functions(polynoms, derivated_polynoms, polynom_count);
      calculate_tangent_line(polynoms, derivated_polynoms, polynom_count);
      break;
    }
    
    printf("\n-> Pressione enter para continuar: ");
    getchar();
    system("cls");
    setup_menu();
    print_functions(polynoms, derivated_polynoms, polynom_count);
  }
  
  return 0;
}