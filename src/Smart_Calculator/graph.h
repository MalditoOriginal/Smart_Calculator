#ifndef GRAPH_H
#define GRAPH_H

#include <QDoubleValidator>
#include <QVector>
#include <QWidget>

extern "C" {  // Connect C file externally
#include "../s21_smartcalc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 private:
  Ui::Graph *ui;
  double h, X, Y;
  QVector<double> x, y;
  QDoubleValidator validator;
  QString exp_for_graph;

 private slots:
  void on_Apply_clicked();
  void updateGraph();

 public slots:
  void slot(QString str);
};

#endif  // GRAPH_H
