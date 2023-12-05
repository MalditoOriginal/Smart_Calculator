#include "s21_smartcalc.h"

// Credit calculator
void calcCredit(double amount, double years, double months, double rate,
                double *payment, double *interest, double *convOutToD, int flag,
                double *min_payment, double *max_payment) {
  double term = years * 12 + months;  // Total number of payments
  double P = rate / 12 / 100;         // Monthly interest rate

  if (!flag) {
    // User specifies the monthly payment
    double N = P / (pow((1 + P), term) - 1);  // Monthly payment factor
    *payment = amount * (P + N);              // Monthly payment
    *convOutToD = *payment * term;            // Total repayment
    *interest = *convOutToD - amount;         // Total interest paid
  } else {
    // User specifies the loan term
    double initLoanAmount = amount;
    double princPay =
        amount / term;         // Calculation of the monthly principal payment.
    double Imax = amount * P;  // Share of interest in the monthly payment.
    *max_payment = princPay + Imax;  // Monthly installment amount
    *convOutToD = *max_payment;
    for (int i = 1; i < term; i++) {
      amount -= princPay;
      double Imin = amount * P;
      *min_payment = princPay + Imin;
      *convOutToD += *min_payment;
    }
    *interest = *convOutToD - initLoanAmount;  // Total interest paid
  }
}