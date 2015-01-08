#include "dataplot.h"
#include "ui_dataplot.h"

DataPlot::DataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPlot)
{
    ui->setupUi(this);

    //dataGraph(ui->customPlot,x,y);
}

DataPlot::~DataPlot()
{
    delete ui;
}

void DataPlot::dataGraph(QCustomPlot *customPlot, QVector<double> x, QVector<double> y)
{
   customPlot->addGraph();
   customPlot->graph(0)->setData(x,y);
   customPlot->graph(0)->rescaleAxes();
   customPlot->setInteraction(QCP::iRangeDrag,true);
   customPlot->setInteraction(QCP::iRangeZoom,true);
   customPlot->replot();
}

void DataPlot::setVectors(QVector<double> _y)
{
    for(int i = 0; i<_y.size(); i++)
    {
        x.push_front(i);
        y.push_front(_y[i]);
    }
}

void DataPlot::on_btnActualizar_clicked()
{
    dataGraph(ui->customPlot,x,y);

}
