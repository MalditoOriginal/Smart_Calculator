#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

extern "C" {  // Connect C file externally
#include "../s21_smartcalc.h"
}

// Declare the UI namespace
namespace Ui {
class Deposit;
}

// Declare the Deposit class, subclassing QWidget
class Deposit : public QWidget {
  Q_OBJECT /* Macro indicating that this class uses Qt's meta-object system */

      public :
      // Constructor
      explicit Deposit(QWidget *parent = nullptr);

  // Destructor
  ~Deposit();

 private slots:
  // Slot for handling the click event of a button named "calculate"
  void on_calculate_clicked();
  void correction();
  bool validateInput() const;
  int calculateAdjustedYears(int inputYears) const;

  // updateUI: updating the user interface
  void updateUI();

 private:
  Ui::Deposit *ui;  // ui: pointer to the UI components
  double amount, deposit_rate, tax_rate, profitability, total;
  int years, months, days, correct;
  QString total_sum, income;
};

#endif  // DEPOSIT_H
