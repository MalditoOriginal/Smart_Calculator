#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <deposit.h>
#include <graph.h>

#include <QLineEdit>
#include <QMainWindow>
#include <QVector>

extern "C" {  // connect C file externally
#include "../s21_smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graph *graph;
  Credit *credit;
  Deposit *deposit;
  QString str;
  int number;
  int open_bracket;
  int close_bracket;
  int point;
  int trig_func;
  int math_func;
  int zero_first;
  int error;
  int x_symbol;
  int x_line;
  int x_dot;
  int x_number;
  int x_minus;
  int x_zero;

 signals:
  void signal(QString str);

 private slots:
  void digits_numbers();
  void zero();
  void on_pushButton_dot_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_x_clicked();
  void math_operations();
  void minus();
  void mul_before_num();
  void trigonometry();
  void brackets();
  void init_flags();
  void check_emptiness();
  void check_error();
  void flags_for_x();
  void on_pushButton_x_num_clicked();
  void on_pushButton_ok_clicked();
  void on_pushButton_graph_clicked();
  void on_credit_clicked();
  void on_deposit_clicked();
};
#endif  // MAINWINDOW_H
