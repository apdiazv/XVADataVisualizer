#ifndef DATAPLOT_H
#define DATAPLOT_H

#include <QWidget>
#include <qcustomplot.h>

namespace Ui {
class DataPlot;
}

class DataPlot : public QWidget
{
    Q_OBJECT

public:
    explicit DataPlot(QWidget *parent = 0);

    ~DataPlot();


    void dataGraph(QCustomPlot *customPlot, QVector<double> x, QVector<QVector<double> > dataList);

    void setVectors(QVector<QVector<double> > dataList);

private slots:
    void on_btnActualizar_clicked();

    void on_btnBorrar_clicked();

private:
    Ui::DataPlot *ui;
    QVector<double> x;

    QVector<QVector<double> > _dataList;

};

#endif // DATAPLOT_H
