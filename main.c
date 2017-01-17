#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "hash-map.h"
#include "math.h"
#include "tree.h"

double infix(char* wejscie, Tree* tree);
int conversion = 0;
void convert(int liczba, int system) {
  if(liczba >= system) {
    convert(liczba/system, system);
    if(liczba % system == 10) printf("A");
    else if(liczba % system == 11) printf("B");
    else if(liczba % system == 12) printf("C");
    else if(liczba % system == 13) printf("D");
    else if(liczba % system == 14) printf("E");
    else if(liczba % system == 15) printf("F");
    else printf("%d", liczba % system);
  }
  else {
    if(system > 10) {
      if(liczba == 10) printf("A");
      else if(liczba == 11) printf("B");
      else if(liczba == 12) printf("C");
      else if(liczba == 13) printf("D");
      else if(liczba == 14) printf("E");
      else if(liczba == 15) printf("F");
    }
    else {
      printf("%d", liczba);
    }
  }
}

int handle_variables(char* wejscie, Tree* tree) {
  const int len = strlen(wejscie);
  if(len > 4 && strstr(wejscie, "let") != 0) {
    char var_text[256] = {' '};
    int iter = 0;
    char variable[64] = {' '};
    int iterator = 0;
    double var = 0;

    // starting from 1 because 0 is @
    for(unsigned int i = 4; i < len; i++) {
      char c = wejscie[i];
      if (c >= 'a' && c <= 'z') {
        variable[iterator++] = '@';
        while(i < len && c >= 'a' && c <= 'z') {
          variable[iterator++] = wejscie[i++];
          c = wejscie[i];
        }
        --i; // going backward to convert cursor position

        while(i < len && c != '=') {
          c = wejscie[++i];
        }
        c = wejscie[++i]; // eat = char;

        while(i < len - 1) {
          char cc = wejscie[i++];
          if(cc != '\n') {
            var_text[iter++] = cc;
          }
        }

        var = infix(var_text, tree);
      }
    }

    set(tree, variable, var);

    return 1;
  }

  return 0;
}

double onp(char* wejscie, Tree* tree) {
  DoubleStack stos;
  d_init(&stos);
  const int len = strlen(wejscie);

  for(unsigned int i = 0; i < len; i++) {
    char c = wejscie[i];

    if((c == '+' || c == '/' || c == '-' || c == '*' || c == '^') && d_size(&stos) > 1) {
      double wynik;
      double snd = d_pop(&stos);
      double fst = d_pop(&stos);

      switch(c) {
      case '+':
        wynik = fst + snd;
        break;
      case '-':
        wynik = fst - snd;
        break;
      case '/':
        if(snd == 0) {
          printf("Cannot divide by 0!!!");
          break;
        }
        wynik = fst / snd;
        break;
      case '*':
        wynik = fst * snd;
        break;
      case '^':
        wynik = power(fst, snd);
        break;
      }

      d_push(&stos, wynik);
    }

    else if (c >= 'a' && c <= 'z') {
      char function[64] = {' '};
      int iterator = 0;

      while(i < len && c >= 'a' && c <= 'z') {
        function[iterator++] = wejscie[i++];
        c = wejscie[i];
      }
      --i;

      double wynik;
      if(strstr(function, "add") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = fst + snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "subtract") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = fst - snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "multiply") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = fst * snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "divide") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        if(snd == 0) {
          printf("Cannot divide by 0!!!\n");
          return 0;
        }
        wynik = fst / snd;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "pow") != 0) {
        double snd = d_pop(&stos);
        double fst = d_pop(&stos);
        wynik = power(fst, snd);
        d_push(&stos, wynik);
      }

      else if(strstr(function, "neg") != 0) {
        double fst = d_pop(&stos);
        wynik = -fst;
        d_push(&stos, wynik);
      }

      else if(strstr(function, "root") != 0) {
        double fst = d_pop(&stos);
        double snd = d_pop(&stos);
        wynik = root(fst, snd);
        d_push(&stos, wynik);
      }

      else if(strstr(function, "sqrt") != 0) {
        d_push(&stos, root(d_pop(&stos), 2));
      }

      else if(strstr(function, "factorial") != 0) { // factorial
        d_push(&stos, factorial(d_pop(&stos)));
      }

      else if(strstr(function, "sin") != 0) { // sine
        d_push(&stos, sine(d_pop(&stos)));
      }

      else if(strstr(function, "cos") != 0) { // cosine
        d_push(&stos, cosine(d_pop(&stos)));
      }

      else if(strstr(function, "tangent") != 0) { // tangent
        d_push(&stos, tangent(d_pop(&stos)));
      }

      else if(strstr(function, "cotangent") != 0) { // cotangent
        d_push(&stos, cotangent(d_pop(&stos)));
      }

      else if(strstr(function, "rad") != 0) { // convert to radians
        d_push(&stos, to_radians(d_pop(&stos)));
      }

      else if(strstr(function, "deg") != 0) { // convert to degrees
        d_push(&stos, to_degrees(d_pop(&stos)));
      }

      else if(strstr(function, "pi") != 0) { // pi
        d_push(&stos, PI);
      }

      else if(strstr(function, "abs") != 0) { // pi
        d_push(&stos, absolute(d_pop(&stos)));
      }

      else if(strstr(function, "convert") != 0) {
        int system = d_pop(&stos);
        int liczba = d_pop(&stos);
        convert(liczba, system);
        conversion = 1;
      }
    }

    else if ((c >= '0' && c <= '9') || c == '.') {
      char number[256] = {' '};
      int iterator = 0;
      while(i < len && ((c >= '0' && c <= '9') || c == '.')) {
        number[iterator++] = wejscie[i++];
        c = wejscie[i];
      }
      double val = 0;
      sscanf(number, "%lf", &val);
      d_push(&stos, val);
    }

  }

  double result = d_pop(&stos);
  return result;
}

double infix(char* wejscie, Tree* tree) {
  CharStack stos;
  StringStack function_stack;
  s_init(&function_stack);
  c_init(&stos);

  const unsigned int len = strlen(wejscie);
  char wyjscie[1024] = {' '};
  unsigned int iterator = 0;
  for(int i = 0; i < len; i++) {
    char c = wejscie[i];

    if(c == '(') {
      c_push(&stos, c);
    }

    else if (c == ')') {
      while(c_size(&stos) > 0) {
        char top = c_pop(&stos);
        if(top != '(') {
          if(top == '#') {
            char* function = s_pop(&function_stack);
            unsigned int len = strlen(function);
            for(unsigned int ii = 0; ii < len; ii++) {
              wyjscie[iterator++] = function[ii];
            }
          } else {
            wyjscie[iterator++] = top;
          }
          wyjscie[iterator++] = ' ';
        } else break;
      }
    }

    else if (c == '+' || c == '-') {
      while(c_size(&stos) > 0) {
        char o2 = c_back(&stos);
        if(o2 == '+' || o2 == '-' || o2 == '*' || o2 == '/') {
          wyjscie[iterator++] = o2;
          wyjscie[iterator++] = ' ';
          c_pop(&stos);
        }

        else if(o2 == '#') {
          c_pop(&stos);
          char* function = s_pop(&function_stack);
          unsigned int len = strlen(function);
          for(unsigned int i = 0; i < len; i++) {
            wyjscie[iterator++] = function[i];
          }
          wyjscie[iterator++] = ' ';
        } else break;

      }
      c_push(&stos, c);
    }

    else if (c == '*' || c == '/') {
      while(c_size(&stos) > 0) {
        char o2 = c_back(&stos);

        if(o2 == '*' || o2 == '/') {
          wyjscie[iterator++] = o2;
          wyjscie[iterator++] = ' ';
          c_pop(&stos);
        }

        else if(o2 == '#') {
          c_pop(&stos);
          char* function = s_pop(&function_stack);
          unsigned int len = strlen(function);
          for(unsigned int i = 0; i < len; i++) {
            wyjscie[iterator++] = function[i];
          }
          wyjscie[iterator++] = ' ';
        } else break;
      }
      c_push(&stos, c);
    }

    else if ((c >= '0' && c <= '9') || c == '.') {
      char number[256] = {' '};
      unsigned int ii = 0;
      do {
        number[ii++] = c;
        c = wejscie[++i];
      } while(i < len && ((c >= '0' && c <= '9') || c == '.'));
      c = wejscie[--i];

      const unsigned int ln = strlen(number);
      for(unsigned int j = 0; j < ln; j++) {
        wyjscie[iterator++] = number[j];
      }
      wyjscie[iterator++] = ' ';
    }

    else if(c == '@') {
      char variable[64] = {' '};
      int iter = 0;
      // eat @
      variable[iter++] = '@';
      c = wejscie[++i];
      while(i < len && c >= 'a' && c <= 'z') {
        variable[iter++] = wejscie[i++];
        c = wejscie[i];
      }
      --i;

      double var = get(tree, variable);
      char result_string[50] = {' '};
      snprintf(result_string, 50, "%f", var);
      unsigned int len = strlen(result_string);
      int ii = 0;
      while(ii < len) {
        wyjscie[iterator++] = result_string[ii++];
      }

      wyjscie[iterator++] = ' ';
    }

    else if (c >= 'a' && c <= 'z') { // funkcje
      char function[64] = {' '};
      int iterator = 0;

      while(i < len && c >= 'a' && c <= 'z') {
        function[iterator++] = wejscie[i++];
        c = wejscie[i];
      }
      --i;

      c_push(&stos, '#');
      s_push(&function_stack, function);
    }

    else if (c == ',') {
      while(c_size(&stos) > 0) {
        char top = c_pop(&stos);
        if(top != '(') {
          if(top == '#') {
            char* function = s_pop(&function_stack);
            unsigned int len = strlen(function);
            for(unsigned int i = 0; i < len; i++) {
              wyjscie[iterator++] = function[i];
            }
          } else {
            wyjscie[iterator++] = top;
          }
          wyjscie[iterator++] = ' ';
        } else break;
      }
    }

  }

  while(c_size(&stos) > 0) {
    char last = c_pop(&stos);
    if(last == '#') {
      char* function = s_pop(&function_stack);
      unsigned int len = strlen(function);
      for(unsigned int i = 0; i < len; i++) {
        wyjscie[iterator++] = function[i];
      }
    } else {
      wyjscie[iterator++] = last;
    }
  }

  //printf("wyjscie: %s\n", wyjscie);
  double result = onp(wyjscie, tree);
  return result;
}

int main (int argc, char** argv) {

  Tree tree;
  init_tree(&tree);

  int mode = 0; // set infix mode to default
  for(unsigned int i = 0; i < argc; i++) {
    char* arg = argv[i];
    if(strstr(arg, "--infix") != 0) {
      mode = 0;
      printf("Running in INFIX mode\n");
      break;
    }
    else if(strstr(arg, "--onp") != 0) {
      mode = 0;
      printf("ONP mode not supported\n");
      break;
    }
  }

  char rownanie[256] = {' '};
  printf("> ");

  while(fgets(rownanie, sizeof(rownanie), stdin) != NULL && strstr(rownanie, "exit") == 0 && strlen(rownanie) > 1) {
    if(strstr(rownanie, "print") != 0) {
      print_tree(&tree);
    };
    switch(mode) {
    case 0: //infix
      if(!handle_variables(rownanie, &tree)) {
        double result = infix(rownanie, &tree);
        if(!conversion) {
          printf("%0.2f\n", result);
        } else {
          conversion = 0;
          printf("\n");
        }
      }
      break;
    case 1: // onp
      onp(rownanie, &tree);
      break;
    }
    printf("> ");
  }

  // dealocate tree
  clear_tree(&tree);
  return 0;
}
