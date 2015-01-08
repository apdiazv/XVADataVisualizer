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

    void dataGraph(QCustomPlot *customPlot, QVector<double> x, QVector<double> y);
    void setVectors(QVector<double> _y);


private slots:
    void on_btnActualizar_clicked();

private:
    Ui::DataPlot *ui;
    QVector<double> y;
    QVector<double> x;

};

#endif // DATAPLOT_H
