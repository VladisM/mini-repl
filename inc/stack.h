#ifndef STACK_H_included
#define STACK_H_included

// DOUBLE STACK

struct DoubleStack {
  int top;
  double stack[256];
};
typedef struct DoubleStack DoubleStack;

void d_init(DoubleStack *stos);
int d_isEmpty(DoubleStack* stos);
double d_pop(DoubleStack* stos);
void d_push(DoubleStack* stos, double wartosc);
int d_size(DoubleStack* stos);

// CHAR STACK

struct CharStack {
  int top;
  char stack[1024];
};
typedef struct CharStack CharStack;

void c_init(CharStack *stos);
int c_isEmpty(CharStack* stos);
char c_pop(CharStack* stos);
char c_back(CharStack* stos);
void c_push(CharStack* stos, char wartosc);
int c_size(CharStack* stos);

// STRING STACK

struct StringStack {
  int top;
  char* stack[1024];
};
typedef struct StringStack StringStack;

void s_init(StringStack *stos);
void s_clear(StringStack *stos);
int s_isEmpty(StringStack* stos);
char* s_back(StringStack* stos);
char* s_pop(StringStack* stos);
void s_push(StringStack* stos, char* wartosc);
int s_size(StringStack* stos);

#endif
