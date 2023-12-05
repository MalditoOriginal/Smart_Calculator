#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a list of buttons and their corresponding slots
    QList<QPair<QPushButton*, const char*>> buttonConnections = {
        { ui->pushButton_1, SLOT(digits_numbers()) },
        { ui->pushButton_2, SLOT(digits_numbers()) },
        { ui->pushButton_3, SLOT(digits_numbers()) },
        { ui->pushButton_4, SLOT(digits_numbers()) },
        { ui->pushButton_5, SLOT(digits_numbers()) },
        { ui->pushButton_6, SLOT(digits_numbers()) },
        { ui->pushButton_7, SLOT(digits_numbers()) },
        { ui->pushButton_8, SLOT(digits_numbers()) },
        { ui->pushButton_9, SLOT(digits_numbers()) },
        { ui->pushButton_0, SLOT(zero()) },
        { ui->pushButton_openbracket, SLOT(brackets()) },
        { ui->pushButton_closebracket, SLOT(brackets()) },
        { ui->pushButton_sum, SLOT(math_operations()) },
        { ui->pushButton_sub, SLOT(minus()) },
        { ui->pushButton_div, SLOT(math_operations()) },
        { ui->pushButton_mul, SLOT(math_operations()) },
        { ui->pushButton_pow, SLOT(math_operations()) },
        { ui->pushButton_mod, SLOT(math_operations()) },
        { ui->pushButton_cos, SLOT(trigonometry()) },
        { ui->pushButton_sin, SLOT(trigonometry()) },
        { ui->pushButton_tan, SLOT(trigonometry()) },
        { ui->pushButton_acos, SLOT(trigonometry()) },
        { ui->pushButton_asin, SLOT(trigonometry()) },
        { ui->pushButton_atan, SLOT(trigonometry()) },
        { ui->pushButton_log, SLOT(trigonometry()) },
        { ui->pushButton_ln, SLOT(trigonometry()) },
        { ui->pushButton_sqrt, SLOT(trigonometry()) }
    };

    // Connect the buttons to their respective slots using a loop
    for (const auto& buttonConnection : buttonConnections) {
        connect(buttonConnection.first, SIGNAL(clicked()), this, buttonConnection.second);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_flags()
{
    number = 0;
    open_bracket = 0;
    close_bracket = 0;
    point = 0;
    trig_func = 0;
    math_func = 0;
    zero_first = 0;
    error = 0;
    x_symbol = 0;
    x_line = 0;
}

void MainWindow::flags_for_x()
{
    x_number = 0;
    x_dot = 0;
    x_minus = 0;
    x_zero = 0;
}

void MainWindow::check_emptiness()
{
    if (ui->Result_show->text().isEmpty())
        init_flags();

}

void MainWindow::check_error()
{
    if(error) {
        ui->Result_show->setText("");
        init_flags();
    }
}

void MainWindow::mul_before_num()
{
    if(ui->Result_show->text().endsWith(")") || ui->Result_show->text().endsWith("x"))
        ui->Result_show->setText(ui->Result_show->text() + "*");

}

void MainWindow::digits_numbers()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (!button) {
        // Handle the case where sender() is not a QPushButton
        return;
    }

    if (!x_line) {
        check_emptiness();
        check_error();
        mul_before_num();

        QString buttonText = button->text();

        if (ui->Result_show->text().endsWith("0") && !zero_first) {
            ui->Result_show->setText("");
        }

        if (!zero_first) {
            ui->Result_show->setText(ui->Result_show->text().append(buttonText));
            math_func = 0;
            trig_func = 0;
            number = 1;
        } else {
            QString tmp = ui->Result_show->text();
            tmp.chop(1);
            ui->Result_show->setText(tmp);
            ui->Result_show->setText(ui->Result_show->text().append(buttonText));
            math_func = 0;
            trig_func = 0;
            number = 1;
            zero_first = false;
        }
    } else {
        ui->x_num->setText(ui->x_num->text().append(button->text()));
        x_number = 1;
    }
}


void MainWindow::zero()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    check_emptiness();

    if (error) {
        ui->Result_show->setText("");
        init_flags();
    }

    if (!x_line) {
        mul_before_num();

        if (!zero_first) {
            ui->Result_show->setText(ui->Result_show->text().append(button->text()));
        }

        if (!point && !number) {
            zero_first = true;
        }
    } else {
        if (!x_zero) {
            ui->x_num->setText(ui->x_num->text().append(button->text()));
        }

        if (!x_number && !x_dot) {
            x_zero = true;
        }
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (!x_line) {
        if ((number && !point) || zero_first) {
            ui->Result_show->setText(ui->Result_show->text().append(button->text()));
            point = true;
            zero_first = false;
        }
    } else {
        if ((x_number && !x_dot) || x_zero) {
            ui->x_num->setText(ui->x_num->text().append(button->text()));
            x_dot = true;
            x_zero = false;
        }
    }
}

void MainWindow::on_pushButton_x_clicked() // Var X
{

    QPushButton *button = (QPushButton *)sender();

    if(!x_line) {
        check_emptiness();


        if (number || (zero_first && !ui->Result_show->text().endsWith(".")) || ui->Result_show->text().endsWith(")") || ui->Result_show->text().endsWith("x")) {
            ui->Result_show->setText(ui->Result_show->text() + "*");
            if(number) number = 0;
            if(zero_first) zero_first = 0;
        }

        if (!ui->Result_show->text().endsWith("x")) {
            ui->Result_show->setText(ui->Result_show->text().append(button->text()));
            x_symbol = 1;
        }
    }
}

void MainWindow::math_operations()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (!x_line) {
        check_emptiness();

        if (number || ui->Result_show->text().endsWith(")") || ui->Result_show->text().endsWith("x")) {
            ui->Result_show->setText(ui->Result_show->text().append(button->text()));
            number = false;
            math_func = true;
            point = false;
            zero_first = false;
        }
    }
}

void MainWindow::minus()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (!x_line) {
        check_emptiness();
        check_error();

        if (ui->Result_show->text().endsWith("(") || (math_func && !ui->Result_show->text().endsWith("+")) || number || ui->Result_show->text().isEmpty() || ui->Result_show->text().endsWith("x")) {
            ui->Result_show->setText(ui->Result_show->text().append(button->text()));
            number = false;
            point = false;
            math_func = false;
        }
    } else {
        if (!x_minus && ui->x_num->text().isEmpty()) {
            ui->x_num->setText(ui->x_num->text().append(button->text()));
            x_minus = true;
        }
    }
}

void MainWindow::trigonometry()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (!x_line) {
        check_error();
        check_emptiness();

        if (number || ui->Result_show->text().endsWith("0") || ui->Result_show->text().endsWith("x")) {
            ui->Result_show->setText(ui->Result_show->text().append("*"));
            if (number) number = false;
        }

        if (zero_first) zero_first = false;

        ui->Result_show->setText(ui->Result_show->text() + button->text() + "(");
        open_bracket++;
    }
}


void MainWindow::brackets() // brackets
{
    QPushButton *button = (QPushButton *)sender();
    if(!x_line) {
        if(button->text() == "(") {
            if(number || ui->Result_show->text().endsWith(")") || ui->Result_show->text().endsWith("x")) {
                ui->Result_show->setText(ui->Result_show->text() + "*");
                number = 0;
            }
            ui->Result_show->setText(ui->Result_show->text() + button->text());
            open_bracket++;
        }
        if(button->text() == ")") {
            if((open_bracket && !ui->Result_show->text().endsWith("(") && !math_func) && (number|| x_symbol || ui->Result_show->text().endsWith(")"))) {
                ui->Result_show->setText(ui->Result_show->text() + button->text());
                open_bracket--;
                if (open_bracket) close_bracket = 1;
                else close_bracket = 0;
                number = 0;
            }
        }
    }

}

void MainWindow::on_pushButton_AC_clicked() // clear
{

        ui->Result_show->setText("");
        init_flags();
        ui->x_num->setText("0");
        flags_for_x();
}

void MainWindow::on_pushButton_x_num_clicked() // Transfer to the input field 'x'
{
    if(x_symbol) x_line = 1;
    flags_for_x();
    ui->x_num->setText("");

}

void MainWindow::on_pushButton_ok_clicked() // Complete input 'x'
{
    if (!ui->x_num->text().endsWith("."))
    x_line = 0;
}

void MainWindow::on_pushButton_eq_clicked() // Equality
{
    if((number || ui->Result_show->text().endsWith("x") || ui->Result_show->text().endsWith(")") ) && !ui->Result_show->text().endsWith(".") && !open_bracket) {
    QString str = ui->Result_show->text();
    QByteArray ba_1 = str.toLocal8Bit();
    char *c_str = ba_1.data();
    double x = ui->x_num->text().toDouble();
    double result = smart_calc(c_str, x);
    QString answer = QString::number(result, 'g', 7);
    if(answer == "nan" || answer == "inf") {
        ui->Result_show->setText("Error");
        error = 1;
    } else {
        ui->Result_show->setText(answer);
        init_flags();
        number = 1;
    }
    }
}

void MainWindow::on_pushButton_graph_clicked()
{
    if (!open_bracket && !math_func && !trig_func && !ui->Result_show->text().endsWith("-") && !ui->Result_show->text().endsWith("."))
    {
        graph = new Graph;
        graph->show();
        connect(this, &MainWindow::signal, graph, &Graph::slot);
        emit signal(ui->Result_show->text());
    }
}

void MainWindow::on_credit_clicked()
{
    credit = new Credit;
    credit->show();

}

void MainWindow::on_deposit_clicked()
{
    deposit = new Deposit;
    deposit->show();
}

