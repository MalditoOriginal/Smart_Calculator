#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

extern "C" { // подключаем сишный файл извне
#include "../s21_smartcalc.h"
}

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

private slots:
    void on_calculate_clicked();
    void correction();

private:
    Ui::Deposit *ui;
    double amount, deposit_rate, tax_rate, profitability, total;
    int years, months, days, correct;
    QString total_sum, income;
};

#endif // DEPOSIT_H
