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
  Cos = 67,        // 'C'
  Sin = 83,        // 'S'
  Tan = 84,        // 'T'
  Acos = 65,       // 'A'
  Asin = 73,       // 'I'
  Atan = 78,       // 'N'
  Sqrt = 81,       // 'Q'
  Ln = 76,         // 'L'
  Log = 71,        // 'G'
  Mod = 37,        // '%'
  l_bracket = 40,  // '('
  r_bracket = 41,  // ')'
  Div = 47,        // '/'
  Sum = 43,        // '+'
  Sub = 45,        // '-'
  point = 46,      // '.'
  Mul = 42,        // '*'
  Pow = 94         // '^'
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

void pushOps(stack **node, char op, int priority, double num);
double popNum(stack **node);
char popOp(stack **node);
int getPrior(char *expr, int *i);
void execOp(char op, double var_1, double var_2, double *out);
void execTrig(char op, double var, double *res);
void interimResult(stack **num, stack **op, double *res);
double convOutToD(stack **num, stack **op);
void calcOp(stack **stack_of_num, stack **stack_of_op, double *out);
void strToDouble(stack **stack_of_num, stack *stack_of_op, char *num_str,
                 int *j, flags *flag);
void checkNext(stack **stack_of_num, stack *stack_of_op, char *num_str,
               char *expression, int *i, int *j, flags *flag);
int tOpIsTrig(stack **op);
int canPushOps(int prior, stack *stack_of_op, char *expression, int *i);
void handleOps(stack **stack_of_op, stack **stack_of_num, double *res,
               char *expression, int *i, double queue, int prioritet,
               flags *flag);
double evalRPN(char *expression, double x);
int checkValidity(const char *str, char *expression);

int isFirstElem(char *str);
int isLastElem(char *str, int len);

int checkTrig(const char *str, int i);
void is_Trig(const char *str, char *expression, int *j, int *i);

// Credit caluclator
void calcCredit(double sum, double years, double months, double percent,
                double *pay, double *overpay, double *total, int flag,
                double *min_payment, double *max_payment);

// Deposit calculator
void calcDeposit(double amount, int days, double deposit_rate,
                 double *profitability, double *total, int flag);

// General function to perform a smart calc
double smart_calc(const char *str, double x);
#endif  // SRC_S21_SMARTCALC_H