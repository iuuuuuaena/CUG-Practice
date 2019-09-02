#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_btn_ok_clicked();
    void on_le_input_textEdited(const QString &arg1);

    //void on_le_input_editingFinished();

private:
    Ui::MainWindow *ui;
    int QcharToInt(QChar c);
    bool isZero(QString str);
};

#endif // MAINWINDOW_H
