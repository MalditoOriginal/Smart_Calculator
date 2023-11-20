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
    if(!ui->sum->text().isEmpty() && (!ui->years->text().isEmpty() || !ui->months->text().isEmpty()) && !ui->rate->text().isEmpty()) {
        amount = ui->sum->text().toDouble();
        years = months = 0;
        if(!ui->years->text().isEmpty()) years = ui->years->text().toInt();
        if(years > 3) {
            int residue = years % 4;
            years -= residue;
            int lean = years / 4;
            years = 3 * lean + residue;
            days = years * 365 + lean * 366;

        } else {
            days = years * 365;
        }
        if(!ui->months->text().isEmpty()) {
            months = ui->months->text().toInt();
            correction();
            days += 31;
            months--;
            while(months) {
                days += 30;
                months--;
            }
            days += correct;
        }
        deposit_rate = ui->rate->text().toDouble();
        profitability = 0, total = 0;
        if (ui->no->isChecked()) {
        deposit_calc(amount, days, deposit_rate, &profitability, &total, 1);
        income = QString::number(profitability, 'g', 7);
        total_sum = QString::number(total, 'g', 7);
        ui->income->setText(income);
        ui->total->setText(total_sum);
        }
    }
}

void Deposit::correction()
{
    correct = 0;
    if(months == 2) correct = -2;
    if(months == 3 || months == 4) correct = -1;
    if(months == 7) correct = 1;
    if(months == 8 || months == 9) correct = 2;
    if(months == 10 || months == 11) correct = 3;

}
