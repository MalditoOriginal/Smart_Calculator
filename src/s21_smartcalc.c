#include "s21_smartcalc.h"

/* Add a new element to the stack */
void pushOps(stack **node, char op, int priority, double num) {
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
  if (expr[*i] == Cos || expr[*i] == Sin || expr[*i] == Acos ||
      expr[*i] == Asin || expr[*i] == Tan || expr[*i] == Atan ||
      expr[*i] == Sqrt || expr[*i] == Log || expr[*i] == Ln || expr[*i] == Pow)
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

/* Calculate the interim result of a math expr */
void interimResult(stack **num, stack **op, double *out) {
  if ((*op)->operation >= 65 && (*op)->operation <= 84) {
    char oper = popOp(op);
    double var_1 = popNum(num);
    execTrig(oper, var_1, out);
    pushOps(num, '\0', 0, *out);
  } else {
    while ((*num)->next != NULL) {
      char oper = popOp(op);
      double var_1 = popNum(num);
      double var_2 = popNum(num);
      execOp(oper, var_1, var_2, out);
      pushOps(num, '\0', 0, *out);
    }
  }
}

/* Return final result as double */
double convOutToD(stack **num, stack **op) {
  double out = 0.0;
  if ((*op) != NULL && (*num) != NULL) {
    interimResult(num, op, &out);
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
    // Case for trigonometric and other functions
    execTrig(op, var_1, out);
    pushOps(stack_of_num, '\0', 0, *out);
  } else {
    // Case for general arithmetic operations
    double var_2 = popNum(stack_of_num);
    execOp(op, var_1, var_2, out);
    pushOps(stack_of_num, '\0', 0, *out);
  }
}

/* Convert a str of digits into a double and push it onto a stack of numbers
 */
void strToDouble(stack **stack_of_num, stack *stack_of_op, char *num_str,
                 int *j, flags *flag) {
  /* Ptr to the first char after the converted number */
  char *endPtr;
  double var = strtod(num_str, &endPtr);

  /* Check if a unary minus sign is present and if it should be applied */
  if (flag->unary_minus && (stack_of_op == NULL || stack_of_op->priority == 3 ||
                            stack_of_op->priority == 4)) {
    var *= -1;
    flag->unary_minus--;
  }
  pushOps(stack_of_num, '\0', 0, var);
  *j = 0;

  /* Clear the string of digits */
  memset(num_str, '\0', 50);
}

/* Check the next char in the expr */
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

/* Check if the operation at the top of the stack of operations is a trig func
 */
int tOpIsTrig(stack **op) {
  return ((*op)->operation == Cos || (*op)->operation == Sin ||
          (*op)->operation == Tan || (*op)->operation == Acos ||
          (*op)->operation == Asin || (*op)->operation == Atan ||
          (*op)->operation == Log || (*op)->operation == Ln ||
          (*op)->operation == Sqrt);
}

/* Check if an operator can be pushed onto the stack of operations */
int canPushOps(int prior, stack *stack_of_op, char *expression, int *i) {
  return (stack_of_op == NULL || prior > stack_of_op->priority ||
          (prior == 4 && stack_of_op->priority == 4) ||
          (prior == 1 && expression[*i] == l_bracket));
}

/* Validate and convert a str into a valid expression */
int checkValidity(const char *str, char *expression) {
  int isValid = TRUE, j = 0, brackets = 0;  // Initialize variables
  int len = (int)strlen(str);

  // Check if the length of the input string exceeds the limit (255 characters)
  if (len > 255) return FALSE;  // Return FALSE if the length is exceeded

  // Iterate through each character in the input string
  for (int i = 0; i < len && isValid; i++) {
    // Check for specific cases that invalidate the expression
    if ((str[i] == l_bracket && str[i + 1] == r_bracket) ||
        (checkTrig(str, i) && str[i - 1] == r_bracket)) {
      isValid = FALSE;  // Invalid if brackets are empty or trigonometric
                        // function follows immediately
    } else if (i == 0 && str[0] == Sub &&
               (strchr(NUM, str[1]) || str[1] == l_bracket ||
                checkTrig(str, 1))) {
      // Handle the case where the expression starts with a unary minus
      expression[j++] = '0';
      expression[j++] = Sub;
    } else if (checkTrig(str, i)) {
      // Handle trigonometric functions
      is_Trig(str, expression, &j, &i);
    } else if (str[i] == l_bracket && str[i + 1] == Sub) {
      // Handle the case where a negative number is enclosed in brackets
      expression[j++] = l_bracket;
      expression[j++] = '0';
      brackets++;
    } else if (str[i] == l_bracket) {
      // Handle the case where an opening bracket is encountered
      expression[j++] = l_bracket;
      brackets++;
    } else if (str[i] == r_bracket) {
      // Handle the case where a closing bracket is encountered
      expression[j++] = r_bracket;
      brackets--;
    } else {
      // Copy normal characters to the expression
      expression[j++] = str[i];
    }
  }

  // Check if there are unmatched brackets
  if (brackets) isValid = FALSE;

  // Return the final validity status of the expression
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

/* Check if a char in a str is indicating a trig func */
int checkTrig(const char *str, int i) {
  return (str[i] == 'l' || str[i] == 'c' || str[i] == 's' || str[i] == 'a' ||
          str[i] == 's' || str[i] == 't');
}

/* Check if a str contains a trig func and add it to the epxr */
void is_Trig(const char *str, char *expression, int *j, int *i) {
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

// General func to perform a smart calc
double smart_calc(const char *str, double x) {
  double out = 0.0;
  char *expression = calloc(255, sizeof(char));

  // Check for memory allocation failure
  if (expression == NULL) {
    // Handle allocation failure
    return NAN;
  }

  // Validate the input string and store the result in expr
  if (!checkValidity(str, expression)) {
    // Handle validation failure
    free(expression);
    return NAN;
  }

  // Eval epxr with the value x
  out = evalRPN(expression, x);
  free(expression);
  return out;
}