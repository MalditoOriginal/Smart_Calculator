#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

extern "C" { // Connect C file externally
#include "../s21_smartcalc.h"
}

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

private:
    Ui::Credit *ui;
    double amount, years, months, percent, pay, overpay, total, max_payment, min_payment;
    QString monthly_payment, min_pay_for_dif, total_sum, overpayment;

private slots:
    void on_calculate_clicked();
};

#endif // CREDIT_H
