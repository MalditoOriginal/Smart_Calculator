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

void Credit::on_calculate_clicked() {
    // Extracting input values from UI elements
    const QString& sumText = ui->sum->text();
    const QString& yearsText = ui->years->text();
    const QString& monthsText = ui->months->text();
    const QString& percentText = ui->percent->text();

    // Checking if the necessary input fields are not empty
    if (!sumText.isEmpty() && (!yearsText.isEmpty() || !monthsText.isEmpty()) && !percentText.isEmpty()) {
        // Extracting input values and initializing variables
        amount = sumText.toDouble();
        years = yearsText.isEmpty() ? 0.0 : yearsText.toDouble();
        months = monthsText.isEmpty() ? 0.0 : monthsText.toDouble();
        percent = percentText.toDouble();
        min_payment = 0, max_payment = 0;

        // Calculating credit based on user choice
        int calculationType = ui->annuity->isChecked() ? 0 : 1;
        calcCredit(amount, years, months, percent, &pay, &overpay, &total, calculationType, &min_payment, &max_payment);

        // Displaying results based on user choice
        if (ui->annuity->isChecked()) {
            displayResults(pay, overpay, total);
        } else if (ui->dif->isChecked()) {
            displayResults(max_payment, min_payment, overpay, total);
        }
    }
}

void Credit::displayResults(double payment, double overpaymentValue, double total) {
    // Formatting results
    monthly_payment = QString::number(payment, 'g', 7);
    total_sum = QString::number(total, 'g', 7);
    overpayment = QString::number(overpaymentValue, 'g', 7);

    // Displaying results
    ui->pay->setText(monthly_payment);
    ui->total->setText(total_sum);
    ui->overpay->setText(overpayment);
}

void Credit::displayResults(double maxPayment, double minPayment, double overpaymentValue, double total) {
    // Formatting results
    monthly_payment = QString::number(maxPayment, 'g', 7);
    min_pay_for_dif = QString::number(minPayment, 'g', 7);
    total_sum = QString::number(total, 'g', 7);
    overpayment = QString::number(overpaymentValue, 'g', 7);  // Use a different variable name for clarity

    // Displaying results with a range for the payment
    ui->pay->setText(QString("%1...%2").arg(monthly_payment, min_pay_for_dif));
    ui->total->setText(total_sum);
    ui->overpay->setText(overpayment);
}
