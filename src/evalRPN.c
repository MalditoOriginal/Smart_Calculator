#include "s21_smartcalc.h"

/* Final calculation of RPN */
double evalRPN(char *expression, double x) {
  double out = 0.0;
  stack *stack_of_op = NULL;
  stack *stack_of_num = NULL;
  flags flag = {0};
  char num_str[100];
  num_str[0] = '\0';  // Null-terminate the string
  int j = 0, len = (int)strlen(expression);

  // Loop through the characters in the expression
  for (int i = 0; i < len; ++i) {
    int prior = getPrior(expression, &i);

    // Check if the current character is a number or variable
    if (!prior) {
      if (expression[i] == 'x') {
        // Push the variable 'x' onto the number stack
        pushOps(&stack_of_num, '\0', 0, x);
      } else {
        // Build a number string and check for the next character
        if (j < (int)sizeof(num_str) - 1) {
          num_str[j++] = expression[i];
          num_str[j] = '\0';  // Null-terminate the string
        }
        checkNext(&stack_of_num, stack_of_op, num_str, expression, &i, &j,
                  &flag);
      }
    } else {
      // Check if the operator can be pushed onto the operator stack
      if (canPushOps(prior, stack_of_op, expression, &i)) {
        pushOps(&stack_of_op, expression[i], prior, ++flag.open_bracket);
      } else if ((expression[i - 1] == Mul || expression[i - 1] == Div ||
                  expression[i - 1] == Pow) &&
                 expression[i] == Sub) {
        // Handle unary minus
        flag.unary_minus++;
      } else {
        // Process the operator using handleOps function
        handleOps(&stack_of_op, &stack_of_num, &out, expression, &i,
                  flag.open_bracket, prior, &flag);
      }
    }
  }

  // Perform the final calculation using the stacks
  out = (stack_of_op != NULL) ? convOutToD(&stack_of_num, &stack_of_op)
                              : stack_of_num->num;

  // Pop the remaining number from the stack
  popNum(&stack_of_num);
  return out;
}
