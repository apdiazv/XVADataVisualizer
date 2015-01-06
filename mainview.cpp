#include "mainview.h"
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
    QString aux = dir.absoluteFilePath("C:/Creasys/XVA/cva_data.sqlite");
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
    commands = scriptToString(informe);
    for (int i = 0; i < commands.size() - 1; ++i)
    {
        q.exec(commands.at(i));
    }

    QString strQuery;
    strQuery = commands.at(commands.size() - 1);
    qryInforme->setQuery(strQuery);
    ui->tblVwConsulta->setModel(qryInforme);
    ui->tblVwConsulta->show();

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
