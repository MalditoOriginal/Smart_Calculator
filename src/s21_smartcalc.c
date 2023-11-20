#include "s21_smartcalc.h"

double smart_calc(char *str, double x) {
  double out = 0.0;
  char *expression = calloc(255, sizeof(char));
  if (expression == NULL) {
    // Handle allocation failure
    return NAN;
  }

  if (!validator(str, expression)) {
    // Handle validation failure
    free(expression);
    return NAN;
  }

  out = polish_notation(expression, x);
  free(expression);
  return out;
}

int validator(char *str, char *expression) {
  int isValid = TRUE, j = 0, brackets = 0;
  int len = (int)strlen(str);
  if (len > 255) return FALSE;
  for (int i = 0; i < len && isValid; i++) {
    if ((str[i] == l_bracket && str[i + 1] == r_bracket) ||
        (trigonometry_check(str, i) && str[i - 1] == r_bracket)) {
      isValid = FALSE;
    } else if (i == 0 && str[0] == Sub &&
               (strchr(NUM, str[1]) || str[1] == l_bracket ||
                trigonometry_check(str, 1))) {
      expression[j++] = '0';
      expression[j++] = Sub;
    } else if (trigonometry_check(str, i)) {
      is_trigonometry(str, expression, &j, &i);
    } else if (str[i] == l_bracket && str[i + 1] == Sub) {
      expression[j++] = l_bracket;
      expression[j++] = '0';
      brackets++;
    } else if (str[i] == l_bracket) {
      expression[j++] = l_bracket;
      brackets++;
    } else if (str[i] == r_bracket) {
      expression[j++] = r_bracket;
      brackets--;
    } else {
      expression[j++] = str[i];
    }
  }
  if (brackets) isValid = FALSE;
  return isValid;
}

int s21_check_first_elem(char *str) {
  return (str[0] == r_bracket || str[0] == point || str[0] == Div ||
          str[0] == Mul || str[0] == Pow);
}

int s21_check_last_elem(char *str, int len) {
  return (str[len - 1] == Div || str[len - 1] == Sum || str[len - 1] == Sub ||
          str[len - 1] == point || str[len - 1] == Mul || str[len - 1] == Pow ||
          str[len - 1] == l_bracket);
}

int trigonometry_check(char *str, int i) {
  return (str[i] == 'l' || str[i] == 'c' || str[i] == 's' || str[i] == 'a' ||
          str[i] == 's' || str[i] == 't');
}

void is_trigonometry(char *str, char *expression, int *j, int *i) {
  if (str[*i] == 'c' && str[(*i) + 1] == 'o' && str[(*i) + 2] == 's') {
    expression[(*j)++] = Cos;
    (*i) += 2;
  } else if (str[*i] == 's' && str[(*i) + 1] == 'i' && str[(*i) + 2] == 'n') {
    expression[(*j)++] = Sin;
    (*i) += 2;
  } else if (str[*i] == 't' && str[(*i) + 1] == 'a' && str[(*i) + 2] == 'n') {
    expression[(*j)++] = Tan;
    (*i) += 2;
  } else if (str[*i] == 'a' && str[(*i) + 1] == 'c' && str[(*i) + 2] == 'o' &&
             str[(*i) + 3] == 's') {
    expression[(*j)++] = Acos;
    (*i) += 3;
  } else if (str[*i] == 'a' && str[(*i) + 1] == 's' && str[(*i) + 2] == 'i' &&
             str[(*i) + 3] == 'n') {
    expression[(*j)++] = Asin;
    (*i) += 3;
  } else if (str[*i] == 'a' && str[(*i) + 1] == 't' && str[(*i) + 2] == 'a' &&
             str[(*i) + 3] == 'n') {
    expression[(*j)++] = Atan;
    (*i) += 3;
  } else if (str[*i] == 's' && str[(*i) + 1] == 'q' && str[(*i) + 2] == 'r' &&
             str[(*i) + 3] == 't') {
    expression[(*j)++] = Sqrt;
    (*i) += 3;
  } else if (str[*i] == 'l' && str[(*i) + 1] == 'n') {
    expression[(*j)++] = Ln;
    (*i)++;
  } else if (str[*i] == 'l' && str[(*i) + 1] == 'o' && str[(*i) + 2] == 'g') {
    expression[(*j)++] = Log;
    (*i) += 2;
  }
}

void push(stack **node, char oper, int priority, double num) {
  stack *list = calloc(1, sizeof(stack));
  if (list != NULL) {
    list->operation = oper;
    list->priority = priority;
    list->num = num;
    list->next = *node;
    *node = list;
  }
}

double pop_numbers(stack **node) {
  stack *temp = *node;
  double num = temp->num;
  *node = temp->next;
  free(temp);
  return num;
}

char pop_oper(stack **node) {
  stack *temp = *node;
  char op = temp->operation;
  *node = temp->next;
  free(temp);
  return op;
}

int priority_is(char *exp, int *i) {
  int res = 0;
  if (exp[*i] == l_bracket || exp[*i] == r_bracket) res = 1;
  if (exp[*i] == Sum || exp[*i] == Sub) res = 2;
  if (exp[*i] == Div || exp[*i] == Mul || exp[*i] == Mod) res = 3;
  if (exp[*i] == Cos || exp[*i] == Sin || exp[*i] == Acos || exp[*i] == Asin ||
      exp[*i] == Tan || exp[*i] == Atan || exp[*i] == Sqrt || exp[*i] == Log ||
      exp[*i] == Ln || exp[*i] == Pow)
    res = 4;
  return res;
}

void math_operation(char op, double var_1, double var_2, double *res) {
  switch (op) {
    case Sum:
      *res = var_2 + var_1;
      break;
    case Sub:
      *res = var_2 - var_1;
      break;
    case Mul:
      *res = var_2 * var_1;
      break;
    case Div:
      *res = var_2 / var_1;
      break;
    case Mod:
      *res = fmodf(var_2, var_1);
      break;
    case Pow:
      *res = pow(var_2, var_1);
      break;
  }
}

void trigonometry_operation(char op, double var, double *res) {
  switch (op) {
    case Cos:
      *res = cos(var);
      break;
    case Sin:
      *res = sin(var);
      break;
    case Tan:
      *res = tan(var);
      break;
    case Asin:
      *res = asin(var);
      break;
    case Acos:
      *res = acos(var);
      break;
    case Atan:
      *res = atan(var);
      break;
    case Sqrt:
      *res = sqrt(var);
      break;
    case Log:
      *res = log(var);
      break;
    case Ln:
      *res = log10(var);
      break;
  }
}

void total_res(stack **num, stack **op, double *res) {
  if ((*op)->operation >= 65 && (*op)->operation <= 84) {
    char oper = pop_oper(op);
    double var_1 = pop_numbers(num);
    trigonometry_operation(oper, var_1, res);
    push(num, '\0', 0, *res);
  } else {
    while ((*num)->next != NULL) {
      char oper = pop_oper(op);
      double var_1 = pop_numbers(num);
      double var_2 = pop_numbers(num);
      math_operation(oper, var_1, var_2, res);
      push(num, '\0', 0, *res);
    }
  }
}

double total(stack **num, stack **op) {
  double res = 0.0;
  if ((*op) != NULL && (*num) != NULL) {
    total_res(num, op, &res);
  } else {
    res = (*num)->num;
  }
  return res;
}

void schet(stack **stack_of_num, stack **stack_of_op, double *res) {
  char op = pop_oper(stack_of_op);
  double var_1 = pop_numbers(stack_of_num);
  if (op >= 65 && op <= 84) {
    trigonometry_operation(op, var_1, res);
    push(stack_of_num, '\0', 0, *res);
  } else {
    double var_2 = pop_numbers(stack_of_num);
    math_operation(op, var_1, var_2, res);
    push(stack_of_num, '\0', 0, *res);
  }
}

void my_atof(stack **stack_of_num, stack *stack_of_op, char *num_str, int *j,
             flags *flag) {
  char *ptrEnd;
  double var = strtod(num_str, &ptrEnd);
  if (flag->unary_minus && (stack_of_op == NULL || stack_of_op->priority == 3 ||
                          stack_of_op->priority == 4)) {
    var *= -1;
    flag->unary_minus--;
  }
  push(stack_of_num, '\0', 0, var);
  *j = 0;
  memset(num_str, '\0', 50);
}

void check_next(stack **stack_of_num, stack *stack_of_op, char *num_str,
                char *expression, int *i, int *j, flags *flag) {
  if (*i != (int)strlen(expression) - 1) {
    (*i)++;
    if (priority_is(expression, i)) {
      my_atof(stack_of_num, stack_of_op, num_str, j, flag);
    }
    (*i)--;
  } else {
    my_atof(stack_of_num, stack_of_op, num_str, j, flag);
  }
}

int check_func_trig(stack **op) {
  return ((*op)->operation == Cos || (*op)->operation == Sin ||
          (*op)->operation == Tan || (*op)->operation == Acos ||
          (*op)->operation == Asin || (*op)->operation == Atan ||
          (*op)->operation == Log || (*op)->operation == Ln ||
          (*op)->operation == Sqrt);
}

int check_condition_for_push(int prioritet, stack *stack_of_op,
                             char *expression, int *i) {
  return (stack_of_op == NULL || prioritet > stack_of_op->priority ||
          (prioritet == 4 && stack_of_op->priority == 4) ||
          (prioritet == 1 && expression[*i] == l_bracket));
}

void dijkstra(stack **stack_of_op, stack **stack_of_num, double *res,
              char *expression, int *i, double queue, int prioritet,
              flags *flag) {
  if ((*stack_of_op)->operation == Pow) {
    while ((*stack_of_op) != NULL && (*stack_of_op)->operation == Pow)
      schet(stack_of_num, stack_of_op, res);
    if ((*stack_of_op) != NULL && (*stack_of_op)->priority == prioritet) {
      schet(stack_of_num, stack_of_op, res);
      push(stack_of_op, expression[*i], prioritet, queue);
    } else if (expression[*i] != r_bracket ||
               (*stack_of_op)->priority < prioritet || (*stack_of_op) == NULL) {
      push(stack_of_op, expression[*i], prioritet, queue);
    } else {
      pop_oper(stack_of_op);
    }
  } else {
    if ((*stack_of_op)->operation == l_bracket && expression[*i] == r_bracket) {
      pop_oper(stack_of_op);
      if ((*stack_of_op) != NULL) schet(stack_of_num, stack_of_op, res);
    } else if ((*stack_of_op)->operation != l_bracket) {
      schet(stack_of_num, stack_of_op, res);
      if (expression[*i] == r_bracket && flag->open_bracket) {
        flag->stop = 1;

        if (flag->unary_minus) {
          (*stack_of_num)->num *= -1;
          flag->unary_minus--;
        }

        while ((*stack_of_op)->operation != l_bracket && flag->stop) {
          schet(stack_of_num, stack_of_op, res);
          if ((*stack_of_op)->operation == l_bracket) flag->stop = 0;
        }
        flag->open_bracket--;
        pop_oper(stack_of_op);
        if ((*stack_of_op) != NULL && check_func_trig(stack_of_op) &&
            (*stack_of_op)->next != NULL) {
          schet(stack_of_num, stack_of_op, res);
        }
      } else {
        if ((*stack_of_op) != NULL && (*stack_of_op)->priority == prioritet)
          schet(stack_of_num, stack_of_op, res);
        push(stack_of_op, expression[*i], prioritet, queue);
      }
    }
  }
}

double polish_notation(char *expression, double x) {
  double res = 0.0, queue = 0.0;
  stack *stack_of_op = NULL;
  stack *stack_of_num = NULL;
  flags flag = {0};
  char num_str[100];
  int j = 0, len = (int)strlen(expression);
  for (int i = 0; i < len; ++i) {
    int prioritet = priority_is(expression, &i);
    if (!prioritet) {
      if (expression[i] == 'x') {
        push(&stack_of_num, '\0', 0, x);
      } else {
        num_str[j++] = expression[i];
        check_next(&stack_of_num, stack_of_op, num_str, expression, &i, &j,
                   &flag);
      }
    } else {
      if (check_condition_for_push(prioritet, stack_of_op, expression, &i)) {
        push(&stack_of_op, expression[i], prioritet, ++queue);
        if (prioritet == 1) flag.open_bracket++;
      } else if ((expression[i - 1] == Mul || expression[i - 1] == Div ||
                  expression[i - 1] == Pow) &&
                 expression[i] == Sub) {
        flag.unary_minus++;
      } else {
        dijkstra(&stack_of_op, &stack_of_num, &res, expression, &i, queue,
                 prioritet, &flag);
      }
    }
  }
  if (stack_of_op != NULL)
    res = total(&stack_of_num, &stack_of_op);
  else
    res = stack_of_num->num;
  pop_numbers(&stack_of_num);
  return res;
}

// Credit calculator
void credit_calc(double sum, double years, double months, double percent,
                 double *pay, double *overpay, double *total, int flag,
                 double *min_payment, double *max_payment) {
  double term = years * 12 + months;
  double P = percent / 12 / 100;
  if (!flag) {
    double N = P / (pow((1 + P), (int)term) - 1);
    *pay = sum * (P + N);
    *total = *pay * term;
    *overpay = *total - sum;
  } else {
    double first_sum = sum;
    double b =
        sum / term;  //  Calculation of the monthly principal payment.
    double Imax = sum * P;  // Share of interest in the monthly payment.
    *max_payment = b + Imax;  // Monthly installment amount
    *total = *max_payment;
    term--;
    double Imin = 0;
    while (term) {
      sum -= b;
      Imin = sum * P;
      *min_payment = b + Imin;
      *total += *min_payment;
      term--;
    }
    *overpay = *total - first_sum;
  }
}

// Deposit calculator
void deposit_calc(double amount, int days, double deposit_rate,
                  double *profitability, double *total, int flag) {
  if (flag) {
    *profitability = (amount * deposit_rate * (double)days / 365) / 100;
    *total = amount + *profitability;
  }
}
