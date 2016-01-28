#include "mini.h"
#include "ui_mini.h"

miniForm::miniForm(QWidget *parent, Player *plr) :
    QWidget(parent),
    ui(new Ui::miniForm)
{
    ui->setupUi(this);
	
    player = plr;//绝对不可以delete

    //动画部分，窗口渐隐
	hideAnimation = new QPropertyAnimation(this, "windowOpacity");
	hideAnimation->setDuration(600);
    hideAnimation->setStartValue(1);
    hideAnimation->setEndValue(0);
    connect(hideAnimation, SIGNAL(finished()), this, SLOT(hide()));//动画效果结束后隐藏
    //窗口调节大小动画
    sizeSlideAnimation = new QPropertyAnimation(this, "geometry");
    sizeSlideAnimation->setDuration(600);
    sizeSlideAnimation->setEasingCurve(QEasingCurve::OutCirc);

    //信号和槽
    connect(ui->miniuiSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueClick(int)));

    clickOnFrame = false;//是否点击到窗体（面板）上，用于解决点击控件后窗口瞬移的BUG

    if (!QFileInfo(QCoreApplication::applicationDirPath() + "/Stream.mod").exists()) {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        this->setAttribute(Qt::WA_TranslucentBackground);
    }

    QDesktopWidget * desktop = QApplication::desktop();
    QRect rect = desktop->availableGeometry();
    miRPos = rect.width();//初始为屏幕宽度
    curMonitor = -1;
    this->setGeometry(miRPos - this->width() , rect.y() + 25, this->width(), this->height());//win标题栏高度预留25，点x用
}

miniForm::~miniForm()
{
    delete ui;
    delete hideAnimation;
    delete sizeSlideAnimation;
}

void miniForm::showMiniForm(int monitorID)
{
    hideAnimation->stop();//如果正在淡出窗口，中止淡出动画

    //移动窗体到指定监视器
    this->curMonitor = monitorID;
    QDesktopWidget * desktop = QApplication::desktop();
    QRect rect = desktop->availableGeometry(this->curMonitor);
    miRPos = rect.x() + rect.width();
    this->setGeometry(miRPos - this->width() , rect.y() + 25, this->width(), this->height());

    this->setWindowOpacity(1);

    this->show();
    this->update();
}

void miniForm::on_mainPlayerBtn_clicked()
{
    QSystemTrayIcon::ActivationReason a = QSystemTrayIcon::DoubleClick;
    emit showMainPlayer(a);
}

void miniForm::hideMiniUi()
{
    //从外部接受关闭动画信号来关闭
    hideAnimation->start();
}

void miniForm::refreshTitle(QString curTitle)
{
    //设置迷你窗口标题
    ui->titleLabel->setText(curTitle);

    QDesktopWidget * desktop = QApplication::desktop();
    QRect rect = desktop->availableGeometry(this->curMonitor);
    miRPos = rect.x() + rect.width();

    //动画相关
    QFontMetrics titleFontMetrics(ui->titleLabel->font());
    int miX,miY,miWidth,miHeight;//均为根据标题长度而定的新数据
    miX = miRPos - (titleFontMetrics.width(curTitle) + 110);
    miY = this->geometry().y();
    miWidth = titleFontMetrics.width(curTitle) + 110;
    miHeight = this->geometry().height();
    if ((titleFontMetrics.width(curTitle) > 146) &&(titleFontMetrics.width(curTitle) < 572))
    {
        sizeSlideAnimation->stop();
        sizeSlideAnimation->setStartValue(QRect(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height()));
        sizeSlideAnimation->setEndValue(QRect(miX, miY, miWidth, miHeight));
        sizeSlideAnimation->start();
    } else {
        sizeSlideAnimation->stop();
        sizeSlideAnimation->setStartValue(QRect(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height()));
        if (titleFontMetrics.width(curTitle) <= 146)
            sizeSlideAnimation->setEndValue(QRect(miRPos - 256, miY, 256, miHeight));
        else
            sizeSlideAnimation->setEndValue(QRect(miRPos - 682, miY, 682, miHeight));
        sizeSlideAnimation->start();
    }
}

//窗口拖动相关
void miniForm::mousePressEvent(QMouseEvent *event)
{
    //如果点击到控件上的话，pos无法取得数值，窗口会瞬移……
    //于是稍作修改
    if (event->button() == Qt::LeftButton) //只处理左键+x坐标大于10的情况
    {
        //下一行解决点击控件瞬移BUG
        pos = event->pos();
        clickOnFrame = true;//点击到窗口框架上才会变成true，改动之后新增功能：判断点击是否在边框右侧
        event->accept();
    }
}

void miniForm::mouseReleaseEvent(QMouseEvent *)
{
    clickOnFrame = false;//弹起鼠标按键时，恢复

    //移动后更新窗体所在屏幕
    QDesktopWidget * desktop = QApplication::desktop();
    this->curMonitor = desktop->screenNumber ( this );
    /* Debug
    QRect rect = desktop->availableGeometry(this->curMonitor);
    miRPos = rect.width();//初始为屏幕宽度
    QMessageBox::information(this, "Debug<Monitor "+QString::number(curMonitor, 10)+">",
                             "rect.width"+QString::number(rect.width(), 10)+"rect.x"+QString::number(rect.x(), 10)+
                             "\nrect.height"+QString::number(rect.height(), 10)+"rect.y"+QString::number(rect.y(), 10));
    */
}

void miniForm::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && clickOnFrame)
    {
        move(event->globalPos() - pos);
        event->accept();
    }
}

void miniForm::resizeEvent(QResizeEvent *)
{
    ui->groupBox->setGeometry(width() - 250, 30, 250, 50);
    ui->nowPlayingBackground->setGeometry(0, 0, width(), 31);
    ui->titleLabel->setGeometry(100, 0, width()-110, 31);//文本框左侧空100px右侧空10px
}

void miniForm::setSliderValueClick(int value)
{
    if (qAbs(player->getPos() - value) > 2)
    {
        emit nowPlayValue(value);
    }
}

void miniForm::setSliderValue(int value)
{
    ui->miniuiSlider->setValue(value);
}

