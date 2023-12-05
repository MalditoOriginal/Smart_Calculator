#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

// Include a C header file
extern "C" {
#include "../s21_smartcalc.h"
}

// Declare the Ui namespace
namespace Ui {
class Credit;
}

// Declare the Credit class, subclassing QWidget
class Credit : public QWidget {
  Q_OBJECT  // Macro indicating that this class uses Qt's meta-object system

      public :
      // Constructor
      explicit Credit(QWidget *parent = nullptr);

  // Destructor
  ~Credit();

 private:
  Ui::Credit *ui;  // Pointer to the user interface components
  double amount, years, months, percent, pay, overpay, total, max_payment,
      min_payment;
  QString monthly_payment, min_pay_for_dif, total_sum, overpayment;

  // Function to display results for a single payment type
  void displayResults(double payment, double overpayment, double total);

  // Function to display results for both minimum and maximum payments
  void displayResults(double maxPayment, double minPayment, double overpayment,
                      double total);

 private slots:
  // Slot for handling the click event of a button named "calculate"
  void on_calculate_clicked();
};

#endif  // CREDIT_H
