#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph), validator(-999999, 999999, 7, this)
{
    ui->setupUi(this);

    validator.setNotation(QDoubleValidator::StandardNotation);
    ui->x_min->setValidator(&validator);
    ui->x_max->setValidator(&validator);
    ui->y_min->setValidator(&validator);
    ui->y_max->setValidator(&validator);

    xBegin = ui->x_min->text().toDouble();
    xEnd = ui->x_max->text().toDouble();
    yBegin = ui->y_min->text().toDouble();
    yEnd = ui->y_max->text().toDouble();

    ui->graphic->xAxis->setRange(xBegin, xEnd);
    ui->graphic->yAxis->setRange(yBegin, yEnd);
}

Graph::~Graph()
{
    delete ui;
}

void Graph::slot(QString str)
{
    exp_for_graph = str;
    ui->expression->setText(ui->expression->text() + str);

}

void Graph::on_Apply_clicked()
{
    h = 0.01;

    QByteArray ba_1 = exp_for_graph.toLocal8Bit();
    char *cstr = ba_1.data();

    ui->graphic->clearGraphs();
    xBegin = ui->x_min->text().toDouble();
    xEnd = ui->x_max->text().toDouble();
    yBegin = ui->y_min->text().toDouble();
    yEnd = ui->y_max->text().toDouble();

    ui->graphic->xAxis->setRange(xBegin, xEnd);
    ui->graphic->yAxis->setRange(yBegin, yEnd);

    if (xBegin < xEnd && yBegin < yEnd) {


        for(X = xBegin; X <= xEnd; X += h)
        {
            Y = smart_calc(cstr, X);
            if(Y >= yBegin && Y <= yEnd) {
                x.push_back(X);
                y.push_back(Y);
            }

        }
        ui->graphic->addGraph();
        ui->graphic->graph(0)->addData(x, y);

        // для отрисовки графика точками
        ui->graphic->graph(0)->setPen(QColor(250, 50, 50, 255)); // Dot colour
        ui->graphic->graph(0)->setLineStyle(QCPGraph::lsNone); // Take away lines
        ui->graphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1)); // Dot size

        ui->graphic->replot();
        x.clear();
        y.clear();
        x.squeeze();
        y.squeeze();
    }
}
