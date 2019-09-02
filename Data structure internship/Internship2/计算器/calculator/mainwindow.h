#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "linkedstack.h"
#include "cal.h"
#include <QClipboard>
#include<QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void clear();
    bool bracketMatch();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_btn_clear_clicked();

    void on_btn_0_clicked();

    void on_btn_point_clicked();

    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_plus_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_minus_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_time_clicked();

    void on_btn_left_clicked();

    void on_btn_right_clicked();

    void on_btn_mod_clicked();

    void on_btn_divide_clicked();

    void on_btn_sin_clicked();

    void on_btn_cos_clicked();

    void on_btn_tan_clicked();

    void on_btn_ln_clicked();

    void on_btn_Log_clicked();

    void on_btn_Sqrt_clicked();

    void on_btn_pow_clicked();

    void on_btn_delete_clicked();

    void on_btn_res_clicked();

    void on_action_triggered();

    void on_actioncopy_triggered();

private:
    Ui::MainWindow *ui;
    QString exp;
    QClipboard *clipboard;
};

#endif // MAINWINDOW_H
