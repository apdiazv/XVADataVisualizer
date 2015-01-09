#include "mainview.h"
#include "dataplot.h"
#include "ui_mainview.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
#include <QDir>
#include <QStringList>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    openDb();
    qryInforme = new QSqlQueryModel;

    //Connect Signals to Slots
    connect(ui->lineNombreScriptConsulta, SIGNAL(textChanged(QString)), SLOT(setInforme(QString)));
    connect(ui->btnEjecutaConsulta, SIGNAL(clicked()), SLOT(generaInforme()));
}

MainView::~MainView()
{
    delete ui;
}

void MainView::openDb()
{
    db =  QSqlDatabase::addDatabase("QSQLITE");
    QDir dir;
    //Para Windows
    //QString aux = dir.absoluteFilePath("C:/Creasys/XVA/cva_data.sqlite");
    //Para Mac
    QString aux = dir.absoluteFilePath("/Users/nicolasbacquet/Desktop/XVA/DATABASE/cva_data.sqlite");
    db.setDatabaseName(aux);
    db.open();

}
QString MainView::getInforme() const
{
    return informe;
}

void MainView::setInforme(QString value)
{
    informe = value;
}


void MainView::generaInforme()
{
    waitCursor();

    QSqlQuery q;
    QStringList commands;
    QVector<double> data;
    QVector<QVector<double> > dataList;
    double aux;

    commands = scriptToString(informe);

    for (int i = 0; i <= commands.size() - 1; i++)
    {
        q.exec(commands.at(i));
        aux = q.value(1).toDouble();
        while(q.next())
        {
            if(aux == q.value(1).toDouble())
            {
                data.push_back(q.value(0).toDouble());
            }
            else
            {
                aux = q.value(1).toDouble();
                dataList.push_back(data);
                data.clear();
                data.push_back(q.value(0).toDouble());
            }
        }
        dataList.push_back(data);
    }

    QString strQuery;
    strQuery = commands.at(commands.size() - 1);
    qryInforme->setQuery(strQuery);
    ui->tblVwConsulta->setModel(qryInforme);
    ui->tblVwConsulta->show();
    callGraph(dataList);
    restoreCursor();
}

QStringList MainView::scriptToString(QString pathToScript)
{
    QDir dir;
    QStringList result;
    pathToScript = dir.absoluteFilePath(pathToScript);
    QFile file(pathToScript);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result.insert(0, "");
        return result;
    }

    QString aux = "";
    QTextStream in(&file);
    while (!in.atEnd())
    {
        aux = in.readAll();
    }

    result = aux.split(';');
    return result;
}

void MainView::waitCursor()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
}

void MainView::restoreCursor()
{
    QApplication::restoreOverrideCursor();
}

void MainView::debugMessageBox(QString msg)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}


void MainView::callGraph(QVector<QVector<double> > dataList)
{
    DataPlot *formGraph = new DataPlot;
    formGraph->setVectors(dataList);
    formGraph->show();
}
