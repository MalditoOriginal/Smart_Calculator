#include "s21_smartcalc.h"

// General func to perform a smart calc
double smart_calc(char *str, double x) {
  double out = 0.0;
  char *expression = calloc(255, sizeof(char));
  if (expression == NULL) {
    // Handle allocation failure
    return NAN;
  }

  // Validate the input string and store the result in expr
  if (!validator(str, expression)) {
    // Handle validation failure
    free(expression);
    return NAN;
  }

  // Eval epxr with the value x
  out = evalRPN(expression, x);
  free(expression);
  return out;
}

/* Validate and convert a str into a valid epxr */
int validator(char *str, char *expression) {
  int isValid = TRUE, j = 0, brackets = 0;
  int len = (int)strlen(str);
  if (len > 255) return FALSE;
  for (int i = 0; i < len && isValid; i++) {
    if ((str[i] == l_bracket && str[i + 1] == r_bracket) ||
        (checkTrig(str, i) && str[i - 1] == r_bracket)) {
      isValid = FALSE;
    } else if (i == 0 && str[0] == Sub &&
               (strchr(NUM, str[1]) || str[1] == l_bracket ||
                checkTrig(str, 1))) {
      expression[j++] = '0';
      expression[j++] = Sub;
    } else if (checkTrig(str, i)) {
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

/* Check if the first char of a str is a spec char */
int isFirstElem(char *str) {
  return (str[0] == r_bracket || str[0] == point || str[0] == Div ||
          str[0] == Mul || str[0] == Pow);
}

/* Check if the last char of a str is a spec char */
int isLastElem(char *str, int len) {
  return (str[len - 1] == Div || str[len - 1] == Sum || str[len - 1] == Sub ||
          str[len - 1] == point || str[len - 1] == Mul || str[len - 1] == Pow ||
          str[len - 1] == l_bracket);
}

/* Check if a char in a str is a trig func */
int checkTrig(char *str, int i) {
  return (str[i] == 'l' || str[i] == 'c' || str[i] == 's' || str[i] == 'a' ||
          str[i] == 's' || str[i] == 't');
}

/* Check if a str contains a trig func and add it to the epxr */
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

/* Add a new element to the stack */
void push(stack **node, char op, int priority, double num) {
  stack *list = calloc(1, sizeof(stack));
  if (list != NULL) {
    list->operation = op;
    list->priority = priority;
    list->num = num;
    list->next = *node;
    *node = list;
  }
}

/* Remove and return the number from the top of a stack */
double popNum(stack **node) {
  stack *temp = *node;
  double num = temp->num;
  *node = temp->next;
  free(temp);
  return num;
}

/* Remove and return the operator from the top of the stack */
char popOp(stack **node) {
  stack *temp = *node;
  char op = temp->operation;
  *node = temp->next;
  free(temp);
  return op;
}

/* Determine the prior of an operator in a math expr */
int getPrior(char *expr, int *i) {
  int out = 0;
  if (expr[*i] == l_bracket || expr[*i] == r_bracket) out = 1;
  if (expr[*i] == Sum || expr[*i] == Sub) out = 2;
  if (expr[*i] == Div || expr[*i] == Mul || expr[*i] == Mod) out = 3;
  if (expr[*i] == Cos || expr[*i] == Sin || expr[*i] == Acos || expr[*i] == Asin ||
      expr[*i] == Tan || expr[*i] == Atan || expr[*i] == Sqrt || expr[*i] == Log ||
      expr[*i] == Ln || expr[*i] == Pow)
    out = 4;
  return out;
}

/* Execute a math operation on two vars and store the result */
void execOp(char op, double var_1, double var_2, double *out) {
  switch (op) {
    case Sum:
      *out = var_2 + var_1;
      break;
    case Sub:
      *out = var_2 - var_1;
      break;
    case Mul:
      *out = var_2 * var_1;
      break;
    case Div:
      *out = var_2 / var_1;
      break;
    case Mod:
      *out = fmodf(var_2, var_1);
      break;
    case Pow:
      *out = pow(var_2, var_1);
      break;
  }
}

/* Execute a trig or log func on a var and store a var */
void execTrig(char op, double var, double *out) {
  switch (op) {
    case Cos:
      *out = cos(var);
      break;
    case Sin:
      *out = sin(var);
      break;
    case Tan:
      *out = tan(var);
      break;
    case Asin:
      *out = asin(var);
      break;
    case Acos:
      *out = acos(var);
      break;
    case Atan:
      *out = atan(var);
      break;
    case Sqrt:
      *out = sqrt(var);
      break;
    case Log:
      *out = log(var);
      break;
    case Ln:
      *out = log10(var);
      break;
  }
}

/* Calculate the final result of a math expr */
void finalResult(stack **num, stack **op, double *out) {
  if ((*op)->operation >= 65 && (*op)->operation <= 84) {
    char oper = popOp(op);
    double var_1 = popNum(num);
    execTrig(oper, var_1, out);
    push(num, '\0', 0, *out);
  } else {
    while ((*num)->next != NULL) {
      char oper = popOp(op);
      double var_1 = popNum(num);
      double var_2 = popNum(num);
      execOp(oper, var_1, var_2, out);
      push(num, '\0', 0, *out);
    }
  }
}

/* Return final result as double */
double total(stack **num, stack **op) {
  double out = 0.0;
  if ((*op) != NULL && (*num) != NULL) {
    finalResult(num, op, &out);
  } else {
    out = (*num)->num;
  }
  return out;
}

/* Calc the result of a single operation in a math epxr */
void calcOp(stack **stack_of_num, stack **stack_of_op, double *out) {
  char op = popOp(stack_of_op);
  double var_1 = popNum(stack_of_num);
  if (op >= 65 && op <= 84) {
    execTrig(op, var_1, out);
    push(stack_of_num, '\0', 0, *out);
  } else {
    double var_2 = popNum(stack_of_num);
    execOp(op, var_1, var_2, out);
    push(stack_of_num, '\0', 0, *out);
  }
}

/* Convert a str of digits into a double and push it onto a stack of numbers */
void strToDouble(stack **stack_of_num, stack *stack_of_op, char *num_str, int *j,
             flags *flag) {
  /* Ptr to the first char after the converted number */
  char *ptrEnd;
  double var = strtod(num_str, &ptrEnd);

  /* Check if a unary minus sign is present and if it should be applied */
  if (flag->unary_minus && (stack_of_op == NULL || stack_of_op->priority == 3 ||
                          stack_of_op->priority == 4)) {
    var *= -1;
    flag->unary_minus--;
  }
  push(stack_of_num, '\0', 0, var);
  *j = 0;

  /* Clear the string of digits */
  memset(num_str, '\0', 50);
}

void checkNext(stack **stack_of_num, stack *stack_of_op, char *num_str,
                char *expression, int *i, int *j, flags *flag) {
  if (*i != (int)strlen(expression) - 1) {
    (*i)++;
    if (getPrior(expression, i)) {
      strToDouble(stack_of_num, stack_of_op, num_str, j, flag);
    }
    (*i)--;
  } else {
    strToDouble(stack_of_num, stack_of_op, num_str, j, flag);
  }
}

int isTrig(stack **op) {
  return ((*op)->operation == Cos || (*op)->operation == Sin ||
          (*op)->operation == Tan || (*op)->operation == Acos ||
          (*op)->operation == Asin || (*op)->operation == Atan ||
          (*op)->operation == Log || (*op)->operation == Ln ||
          (*op)->operation == Sqrt);
}

int canPush(int prior, stack *stack_of_op,
                             char *expression, int *i) {
  return (stack_of_op == NULL || prior > stack_of_op->priority ||
          (prior == 4 && stack_of_op->priority == 4) ||
          (prior == 1 && expression[*i] == l_bracket));
}

void dijkstraAlg(stack **stack_of_op, stack **stack_of_num, double *out,
              char *expression, int *i, double queue, int prior,
              flags *flag) {
  if ((*stack_of_op)->operation == Pow) {
    while ((*stack_of_op) != NULL && (*stack_of_op)->operation == Pow)
      calcOp(stack_of_num, stack_of_op, out);
    if ((*stack_of_op) != NULL && (*stack_of_op)->priority == prior) {
      calcOp(stack_of_num, stack_of_op, out);
      push(stack_of_op, expression[*i], prior, queue);
    } else if (expression[*i] != r_bracket ||
               (*stack_of_op)->priority < prior || (*stack_of_op) == NULL) {
      push(stack_of_op, expression[*i], prior, queue);
    } else {
      popOp(stack_of_op);
    }
  } else {
    if ((*stack_of_op)->operation == l_bracket && expression[*i] == r_bracket) {
      popOp(stack_of_op);
      if ((*stack_of_op) != NULL) calcOp(stack_of_num, stack_of_op, out);
    } else if ((*stack_of_op)->operation != l_bracket) {
      calcOp(stack_of_num, stack_of_op, out);
      if (expression[*i] == r_bracket && flag->open_bracket) {
        flag->stop = 1;
        if (flag->unary_minus) {
          (*stack_of_num)->num *= -1;
          flag->unary_minus--;
        }
        while ((*stack_of_op)->operation != l_bracket && flag->stop) {
          calcOp(stack_of_num, stack_of_op, out);
          if ((*stack_of_op)->operation == l_bracket) flag->stop = 0;
        }
        flag->open_bracket--;
        popOp(stack_of_op);
        if ((*stack_of_op) != NULL && isTrig(stack_of_op) &&
            (*stack_of_op)->next != NULL) {
          calcOp(stack_of_num, stack_of_op, out);
        }
      } else {
        if ((*stack_of_op) != NULL && (*stack_of_op)->priority == prior)
          calcOp(stack_of_num, stack_of_op, out);
        push(stack_of_op, expression[*i], prior, queue);
      }
    }
  }
}

double evalRPN(char *expression, double x) {
  double res = 0.0, queue = 0.0;
  stack *stack_of_op = NULL;
  stack *stack_of_num = NULL;
  flags flag = {0};
  char num_str[100];
  int j = 0, len = (int)strlen(expression);
  for (int i = 0; i < len; ++i) {
    int prior = getPrior(expression, &i);
    if (!prior) {
      if (expression[i] == 'x') {
        push(&stack_of_num, '\0', 0, x);
      } else {
        num_str[j++] = expression[i];
        checkNext(&stack_of_num, stack_of_op, num_str, expression, &i, &j,
                   &flag);
      }
    } else {
      if (canPush(prior, stack_of_op, expression, &i)) {
        push(&stack_of_op, expression[i], prior, ++queue);
        if (prior == 1) flag.open_bracket++;
      } else if ((expression[i - 1] == Mul || expression[i - 1] == Div ||
                  expression[i - 1] == Pow) &&
                 expression[i] == Sub) {
        flag.unary_minus++;
      } else {
        dijkstraAlg(&stack_of_op, &stack_of_num, &res, expression, &i, queue,
                 prior, &flag);
      }
    }
  }
  if (stack_of_op != NULL)
    res = total(&stack_of_num, &stack_of_op);
  else
    res = stack_of_num->num;
  popNum(&stack_of_num);
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