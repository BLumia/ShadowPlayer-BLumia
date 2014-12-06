#ifndef MINI_H
#define MINI_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "player.h"

namespace Ui {
class miniForm;
}

class miniForm : public QWidget
{
    Q_OBJECT

public:
    explicit miniForm(QWidget *parent = 0, Player *plr = 0);//第二的参数应该是player
    ~miniForm();
    void showMiniForm();   

signals:
    void on_playBtn_clicked();
    void on_playNextBtn_clicked();
    void on_playPrevBtn_clicked();
    void on_playModeBtn_clicked();
    void on_muteBtn_clicked();
    void showMainPlayer(QSystemTrayIcon::ActivationReason reason);
    void nowPlayValue(int value);

private:
    Ui::miniForm *ui;
    bool clickOnFrame;
    int miRPos;//记录mini窗口右上角坐标的x坐标（即右侧坐标）用，动画部分会用到
    Player *player;
    QPoint pos;//用于窗口拖动，存储鼠标坐标
    QPixmap backGround;
    QPropertyAnimation *hideAnimation;
    QPropertyAnimation *sizeSlideAnimation;
    //QPropertyAnimation *timeAnimation;

private slots:

    void refreshTitle(QString curTitle);
    void on_mainPlayerBtn_clicked();
    void hideMiniUi();
    void setSliderValue(int intvalue);
    void setSliderValueClick(int intvalue);

protected:
    //void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MINI_H
