#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_calculate_clicked()
{
    if (!ui->sum->text().isEmpty() && (!ui->years->text().isEmpty() || !ui->months->text().isEmpty()) && !ui->percent->text().isEmpty()) {
        amount = ui->sum->text().toDouble();
        if (!ui->years->text().isEmpty()) years = ui->years->text().toDouble();
        else years = 0.0;
        if (!ui->months->text().isEmpty()) months = ui->months->text().toDouble();
        else months = 0.0;
        percent = ui->percent->text().toDouble();
        min_payment = 0, max_payment = 0;
        if (ui->an->isChecked()) {
            calcCredit(amount, years, months, percent, &pay, &overpay, &total, 0, &min_payment, &max_payment);
            monthly_payment = QString::number(pay, 'g', 7);
            total_sum = QString::number(total, 'g', 7);
            overpayment = QString::number(overpay, 'g', 7);
            ui->pay->setText(monthly_payment);
            ui->total->setText(total_sum);
            ui->overpay->setText(overpayment);

        } else if (ui->dif->isChecked()) {
            calcCredit(amount, years, months, percent, &pay, &overpay, &total, 1, &min_payment, &max_payment);
            monthly_payment = QString::number(max_payment, 'g', 7);
            min_pay_for_dif = QString::number(min_payment, 'g', 7);
            total_sum = QString::number(total, 'g', 7);
            overpayment = QString::number(overpay, 'g', 7);
            ui->pay->setText(monthly_payment + "..." + min_pay_for_dif);
            ui->total->setText(total_sum);
            ui->overpay->setText(overpayment);
        }
    }
}
