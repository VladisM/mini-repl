#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"

// DOUBLE STACK

void d_init(DoubleStack *stos) {
  stos->top = 0;
}

int d_isEmpty(DoubleStack* stos) {
  return stos->top;
}

double d_pop(DoubleStack* stos) {
  stos->top -= 1;
  return stos->stack[stos->top];
}

void d_push(DoubleStack* stos, double wartosc) {
  stos->stack[stos->top] = wartosc;
  stos->top += 1;
}

int d_size(DoubleStack* stos) {
  return stos->top;
}


// CHAR STACK

void c_init(CharStack *stos) {
  stos->top = 0;
  for(unsigned short i = 0; i < 1024; i++) {
    stos->stack[i] = ' ';
  }
}

int c_isEmpty(CharStack* stos) {
  return stos->top;
}

char c_pop(CharStack* stos) {
  stos->top -= 1;
  return stos->stack[stos->top];
}

char c_back(CharStack* stos) {
  return stos->stack[stos->top];
}


void c_push(CharStack* stos, char wartosc) {
  stos->stack[stos->top] = wartosc;
  stos->top += 1;
}

int c_size(CharStack* stos) {
  return stos->top;
}


// STRING STACK

void s_init(StringStack *stos) {
  stos->top = 0;
  for(unsigned short i = 0; i < 1024; i++) {
    stos->stack[i] = malloc(256);
  }
}

void s_clear(StringStack *stos) {
  for(unsigned short i = 0; i < 1024; i++) {
    free(stos->stack[i]);
  }
}

int s_isEmpty(StringStack* stos) {
  return stos->top;
}

char* s_back(StringStack* stos) {
  return stos->stack[stos->top];
}

char* s_pop(StringStack* stos) {
  stos->top -= 1;
  return stos->stack[stos->top];
}

void s_push(StringStack* stos, char* wartosc) {
  strcpy(stos->stack[stos->top], wartosc);
  stos->top += 1;
}

int s_size(StringStack* stos) {
  return stos->top;
}
