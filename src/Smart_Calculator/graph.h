#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>
#include <QDoubleValidator>

extern "C" { // Connect C file externally
#include "../s21_smartcalc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

private:
    Ui::Graph *ui;
    double xBegin, xEnd, yBegin, yEnd, h, X, Y;
    QVector<double> x, y;
    QString exp_for_graph;
    QDoubleValidator validator;


public slots:
    void slot(QString str);

private slots:
    void on_Apply_clicked();
};

#endif // GRAPH_H
