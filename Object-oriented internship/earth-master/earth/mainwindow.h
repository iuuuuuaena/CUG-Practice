#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <earth.h>

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
    void on_show_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
