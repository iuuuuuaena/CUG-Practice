#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class Information;
}

class Information : public QWidget
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = 0);
    ~Information();
    QPixmap *pixmap;
    QString text;
    void setup(QString path, QString text);
    void paintEvent(QPaintEvent *);

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
