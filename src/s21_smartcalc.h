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
int s21_check_first_elem(char *str);
int s21_check_last_elem(char *str, int len);
int validator(char *str, char *expression);
int trigonometry_check(char *str, int i);
void is_trigonometry(char *str, char *expression, int *j, int *i);
void push(stack **node, char oper, int priority, double num);
double pop_numbers(stack **node);
char pop_oper(stack **node);
int priority_is(char *exp, int *i);
void my_atof(stack **stack_of_num, stack *stack_of_op, char *num_str, int *j,
             flags *flag);
void check_next(stack **stack_of_num, stack *stack_of_op, char *num_str,
                char *expression, int *i, int *j, flags *flag);
int check_condition_for_push(int prioritet, stack *stack_of_op,
                             char *expression, int *i);
void math_operation(char op, double var_1, double var_2, double *res);
void trigonometry_operation(char op, double var, double *res);
int check_func_trig(stack **op);
void dijkstra(stack **stack_of_op, stack **stack_of_num, double *res,
              char *expression, int *i, double queue, int prioritet,
              flags *flag);
double total(stack **num, stack **op);
void total_res(stack **num, stack **op, double *res);
void schet(stack **stack_of_num, stack **stack_of_op, double *res);
double polish_notation(char *expression, double x);

// Credit caluclator
void credit_calc(double sum, double years, double months, double percent,
                 double *pay, double *overpay, double *total, int flag,
                 double *min_payment, double *max_payment);

// Deposit calculator
void deposit_calc(double amount, int days, double deposit_rate,
                  double *profitability, double *total, int flag);

#endif  // SRC_S21_SMARTCALC_H