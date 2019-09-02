#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"AVLtree.h"
#include<QFile>
#include<QTextStream>
#include<QListWidgetItem>
#include<QListWidget>
#include<QDebug>
#include<QMessageBox>
#include<QFileDialog>
#include<QTextToSpeech>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    Ui::MainWindow *ui;
    AVLTree *tree;
    bool Init();

    std::vector<WordNode> WordList;
    std::list<WordNode> History;//存放历史纪录
    QString word;//当前选中单词
    QTextToSpeech *tts;
private slots:
    void on_btn_search_clicked();
    void on_listWidget_itemSelectionChanged();
    void on_btn_delete_clicked();
    void on_lw_history_itemSelectionChanged();
    void on_btn_all_clicked();
    void on_btn_alter_clicked();
    void on_btn_add_clicked();
    void on_action_triggered();
    void on_btn_audio_clicked();
    void on_action_2_triggered();
};

#endif // MAINWINDOW_H
