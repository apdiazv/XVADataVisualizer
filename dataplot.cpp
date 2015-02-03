#include "dataplot.h"
#include "ui_dataplot.h"

DataPlot::DataPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPlot)
{
    ui->setupUi(this);
}

DataPlot::~DataPlot()
{
    delete ui;
}

void DataPlot::dataGraph(QCustomPlot *customPlot, QVector<double> x, QVector<QVector<double> > dataList)
{
    QPen pen;
    for(int i = 0; i<dataList.size(); i++)
    {
        pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
        customPlot->addGraph();
        customPlot->graph()->setData(x,dataList[i]);
        customPlot->graph()->rescaleAxes();
        customPlot->graph()->setPen(pen);
    }
    customPlot->setInteractions(QCP::iSelectPlottables | QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->replot();
}

void DataPlot::setVectors(QVector<QVector<double> > dataList)
{
    for(int i = 0; i<dataList.size(); i++)
    {
        _dataList.push_front(dataList[i]);
    }
    for(int i = 0; i < dataList[0].size();i++)
    {
        x.push_back(i);
    }
}

void DataPlot::on_btnActualizar_clicked()
{
    dataGraph(ui->customPlot,x,_dataList);
}

void DataPlot::on_btnBorrar_clicked()
{
    ui->customPlot->removeGraph(ui->customPlot->selectedGraphs().first());
    ui->customPlot->replot();
}
