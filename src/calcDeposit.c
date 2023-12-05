#include "s21_smartcalc.h"

// Deposit calculator
void calcDeposit(double amount, int days, double deposit_rate,
                 double *profitability, double *convOutToD, int flag) {
  if (flag) {
    *profitability = (amount * deposit_rate * (double)days / 365) / 100;
    *convOutToD = amount + *profitability;
  } else {
    // Set default values when flag is not set
    *profitability = 0.0;
    *convOutToD = amount;
  }
}