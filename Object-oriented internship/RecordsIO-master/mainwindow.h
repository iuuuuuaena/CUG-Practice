#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int readfromfile();
    void writetofile(QString record);

private slots:
    void on_btn_open_clicked();

    void on_btn_cancel_clicked();

    void on_btn_ok_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QList<QString> records;
    void display(int row, QStringList subs);
};

#endif // MAINWINDOW_H
