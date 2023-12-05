#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph), validator(-999999, 999999, 7, this)
{
    // Initialize the user interface
    ui->setupUi(this);

    // Set up validators for input fields
    validator.setNotation(QDoubleValidator::StandardNotation);
    ui->x_min->setValidator(&validator);
    ui->x_max->setValidator(&validator);
    ui->y_min->setValidator(&validator);
    ui->y_max->setValidator(&validator);

    // Connect signals and slots for input fields to update the graph dynamically
    connect(ui->x_min, &QLineEdit::textChanged, this, &Graph::updateGraph);
    connect(ui->x_max, &QLineEdit::textChanged, this, &Graph::updateGraph);
    connect(ui->y_min, &QLineEdit::textChanged, this, &Graph::updateGraph);
    connect(ui->y_max, &QLineEdit::textChanged, this, &Graph::updateGraph);

    // Initial update of the graph based on input field values
    updateGraph();
}

void Graph::updateGraph()
{
    // Update the range of the x and y axes based on input field values
    double xBegin = ui->x_min->text().toDouble();
    double xEnd = ui->x_max->text().toDouble();
    double yBegin = ui->y_min->text().toDouble();
    double yEnd = ui->y_max->text().toDouble();

    // Set the range of the x and y axes in the graph
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
    // Set a fixed step size
    h = 0.01;

    // Convert the QString to a const char* for compatibility with smartcalc functions
    QByteArray ba_1 = exp_for_graph.toLocal8Bit();
    const char *cstr = ba_1.data();  // Ensure cstr is const

    // Clear existing graphs in the plot
    ui->graphic->clearGraphs();

    // Get the range of the x and y axes from input fields
    double xBegin = ui->x_min->text().toDouble();
    double xEnd = ui->x_max->text().toDouble();
    double yBegin = ui->y_min->text().toDouble();
    double yEnd = ui->y_max->text().toDouble();
    
    // Set the range of the x and y axes in the graph
    ui->graphic->xAxis->setRange(xBegin, xEnd);
    ui->graphic->yAxis->setRange(yBegin, yEnd);

    // Check if the range is valid
    if (xBegin < xEnd && yBegin < yEnd) {
        // Iterate over the x range and calculate corresponding y value
        for (X = xBegin; X <= xEnd; X += h) {
            Y = smart_calc(cstr, X);
            // Include points that fall within the specified y range
            if (Y >= yBegin && Y <= yEnd) {
                x.push_back(X);
                y.push_back(Y);
            }
        }

        // Add a graph to the plot and set its data
        ui->graphic->addGraph();
        ui->graphic->graph(0)->addData(x, y);

        // Drawing graph with dots
        ui->graphic->graph(0)->setPen(QColor(250, 50, 50, 255)); // Dot colour
        ui->graphic->graph(0)->setLineStyle(QCPGraph::lsNone); // Take away lines
        ui->graphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1)); // Dot size

        // Redraw the graph
        ui->graphic->replot();

        // Clear and squeeze the vectors to release memory
        x.clear();
        y.clear();
        x.squeeze();
        y.squeeze();
    }
}
