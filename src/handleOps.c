#include "s21_smartcalc.h"

/* Processing operators within the context of evaluating math exprs */
void handleOps(stack **stack_of_op, stack **stack_of_num, double *out,
               char *expression, int *i, double queue, int prior, flags *flag) {
  stack *op = *stack_of_op;
  stack *num = *stack_of_num;

  // Check if the current operator is Pow
  if (op->operation == Pow) {
    // Process consecutive Pow operators
    while (op != NULL && op->operation == Pow) calcOp(&num, &op, out);

    // Check if the current operator has the same priority
    if (op != NULL && op->priority == prior) {
      calcOp(&num, &op, out);
      pushOps(&op, expression[*i], prior, queue);
    } else if (expression[*i] != r_bracket || op->priority < prior ||
               op == NULL) {
      // Push the current operator onto the stack
      pushOps(&op, expression[*i], prior, queue);
    } else {
      // Pop the top operator from the stack
      popOp(&op);
    }
  } else {
    // Check for special case of closing bracket after opening bracket
    if (op->operation == l_bracket && expression[*i] == r_bracket) {
      popOp(&op);
      if (op != NULL)
        // Process the next operation after closing the bracket
        calcOp(&num, &op, out);
    } else if (op->operation != l_bracket) {
      // Process the current operator
      calcOp(&num, &op, out);
      // Check for special case of closing bracket with open_bracket flag
      if (expression[*i] == r_bracket && flag->open_bracket) {
        flag->stop = 1;
        // Handle unary minus if needed
        if (flag->unary_minus) {
          num->num *= -1;
          flag->unary_minus--;
        }
        // Process operations until an opening bracket is encountered
        while (op->operation != l_bracket && flag->stop) {
          calcOp(&num, &op, out);
          if (op->operation == l_bracket) flag->stop = 0;
        }
        flag->open_bracket--;
        // Pop the opening bracket from the stack
        popOp(&op);
        // Process additional operation if it's a trigonometric function
        if (op != NULL && tOpIsTrig(&op) && op->next != NULL)
          calcOp(&num, &op, out);
      } else {
        // Check if the current operator has the same priority
        if (op != NULL && op->priority == prior) calcOp(&num, &op, out);
        // Push the current operator onto the stack
        pushOps(&op, expression[*i], prior, queue);
      }
    }
  }

  // Update the original pointers with the modified stacks
  *stack_of_op = op;
  *stack_of_num = num;
}