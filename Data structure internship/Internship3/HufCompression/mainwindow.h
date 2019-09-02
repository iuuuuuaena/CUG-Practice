#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QFileDialog>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QMimeData>
#include<QUrl>
#include"huffmanpress.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_Compression_clicked();

    void on_btn_Decompression_clicked();
protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

private:
    Ui::MainWindow *ui;
    QString fileName;
    HuffCode *newPress;
};

#endif // MAINWINDOW_H
