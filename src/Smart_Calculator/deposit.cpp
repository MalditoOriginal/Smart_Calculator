#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit)
{
    ui->setupUi(this);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::on_calculate_clicked()
{
    // Validate input; if validation fails, return early
    if (!validateInput())
        return;

    // Extract input values from UI elements
    amount = ui->sum->text().toDouble();
    years = ui->years->text().isEmpty() ? 0 : calculateAdjustedYears(ui->years->text().toInt());
    months = ui->months->text().isEmpty() ? 0 : ui->months->text().toInt();

    // Perform a correction step
    correction();

    // Calculate the total number of days
    days = years * 365 + months * 30 + correct;

    // Extract deposit rate from UI element
    deposit_rate = ui->rate->text().toDouble();
    profitability = 0, total = 0;

    // Check if a specific option is selected (e.g., "no")
    if (ui->no->isChecked()) {
        // Perform deposit calculation
        calcDeposit(amount, days, deposit_rate, &profitability, &total, 1);

        // Update the user interface with the calculated values
        updateUI();
    }
}

bool Deposit::validateInput() const
{
    return !ui->sum->text().isEmpty() && (!ui->years->text().isEmpty() || !ui->months->text().isEmpty()) && !ui->rate->text().isEmpty();
}

int Deposit::calculateAdjustedYears(int inputYears) const
{
    /* Formula for years greater than three */
    if (inputYears > 3) {
        int residue = inputYears % 4;
        return 3 * (inputYears / 4) + residue;
    } else {
        return inputYears;  /* if years less than three the residue remains the same */
    }
}

void Deposit::updateUI()
{
    // Format profitability and total as strings
    income = QString::number(profitability, 'g', 7);
    total_sum = QString::number(total, 'g', 7);

    // Update UI elements with the formatted values
    ui->income->setText(income);
    ui->total->setText(total_sum);
}

void Deposit::correction()
{
    correct = 0;

    // Adjust correct based on the value of the months variable
    if(months == 2) correct = -2;
    if(months == 3 || months == 4) correct = -1;
    if(months == 7) correct = 1;
    if(months == 8 || months == 9) correct = 2;
    if(months == 10 || months == 11) correct = 3;

}
