#ifndef SRC_S21_SMARTCALC_H
#define SRC_S21_SMARTCALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX 256
#define NUM "0123456789"

typedef enum {
  Cos = 67,
  Sin = 83,
  Tan = 84,
  Acos = 65,
  Asin = 73,
  Atan = 78,
  Sqrt = 81,
  Ln = 76,
  Log = 71,
  Mod = 37,
  l_bracket = 40,
  r_bracket = 41,
  Div = 47,
  Sum = 43,
  Sub = 45,
  point = 46,
  Mul = 42,
  Pow = 94
} lexems;

typedef struct flags {
  int open_bracket;
  int stop;
  int unary_minus;
} flags;

typedef struct stack {
  double num;
  char operation;
  int priority;
  struct stack *next;
} stack;

double smart_calc(char *str, double x);
int isFirstElem(char *str);
int isLastElem(char *str, int len);
int checkValidity(char *str, char *expression);
int checkTrig(char *str, int i);

void is_Trig(char *str, char *expression, int *j, int *i);
void pushOps(stack **node, char op, int priority, double num);
double popNum(stack **node);
char popOp(stack **node);
int getPrior(char *expr, int *i);

void strToDouble(stack **stack_of_num, stack *stack_of_op, char *num_str, int *j,
             flags *flag);

void checkNext(stack **stack_of_num, stack *stack_of_op, char *num_str,
                char *expression, int *i, int *j, flags *flag);

int canPushOps(int prior, stack *stack_of_op,
                             char *expression, int *i);

int canPush(int prioritet, stack *stack_of_op,
                             char *expression, int *i);

void execOp(char op, double var_1, double var_2, double *out);
void execTrig(char op, double var, double *res);
int isTrig(stack **op);

void dijkstraAlg(stack **stack_of_op, stack **stack_of_num, double *res,
              char *expression, int *i, double queue, int prioritet,
              flags *flag);

double convOutToD(stack **num, stack **op);
void finalResult(stack **num, stack **op, double *res);
void calcOp(stack **stack_of_num, stack **stack_of_op, double *out);
double evalRPN(char *expression, double x);

// Credit caluclator
void calcCredit(double sum, double years, double months, double percent,
                 double *pay, double *overpay, double *total, int flag,
                 double *min_payment, double *max_payment);

// Deposit calculator
void calcDeposit(double amount, int days, double deposit_rate,
                  double *profitability, double *total, int flag);

#endif  // SRC_S21_SMARTCALC_H