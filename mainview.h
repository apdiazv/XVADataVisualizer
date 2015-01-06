#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QTableView>
#include <QComboBox>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QSqlDatabase>

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    void openDb();
    QString getInforme() const;
    QStringList scriptToString(QString pathToScript);

private slots:
    void setInforme(QString value);
    void generaInforme();

private:
    Ui::MainView *ui;
    QSqlDatabase db;
    QString informe;
    QSqlQueryModel* qryInforme;
    void waitCursor();
    void restoreCursor();
    void debugMessageBox(QString msg);
};

#endif // MAINVIEW_H
