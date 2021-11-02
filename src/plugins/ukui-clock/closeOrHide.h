#ifndef CLOSE_OR_HIDE_H
#define CLOSE_OR_HIDE_H

#include <QDialog>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QGSettings/qgsettings.h>

namespace Ui {
class close_or_hide;
}
class Clock;
class close_or_hide : public QDialog
{
    Q_OBJECT

public:
    explicit close_or_hide(QWidget *parent = nullptr);
    ~close_or_hide();

    //绘制底部阴影
    // Draw bottom shadow
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    int close_flag;
private slots:
    void on_closebtn_clicked();

    void on_surebtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::close_or_hide *ui;
    QPoint dragPosition;                                            //拖动坐标
    bool mousePressed;                                              //鼠标是否按下
};

#endif // CLOSE_OR_HIDE_H
