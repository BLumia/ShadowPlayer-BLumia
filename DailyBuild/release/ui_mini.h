/********************************************************************************
** Form generated from reading UI file 'mini.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINI_H
#define UI_MINI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "spslider.h"

QT_BEGIN_NAMESPACE

class Ui_miniForm
{
public:
    QLabel *titleLabel;
    QGroupBox *groupBox;
    QPushButton *playBtn;
    QPushButton *playNextBtn;
    QPushButton *stopBtn;
    QPushButton *muteBtn;
    QPushButton *playPrevBtn;
    QPushButton *mainPlayerBtn;
    SPSlider *miniuiSlider;
    QLabel *nowPlayingBackground;

    void setupUi(QWidget *miniForm)
    {
        if (miniForm->objectName().isEmpty())
            miniForm->setObjectName(QStringLiteral("miniForm"));
        miniForm->resize(256, 80);
        miniForm->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	font-family: \"Arial\", \"\345\256\213\344\275\223\", \"Segoe UI\", \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: black;\n"
"}\n"
"\n"
"QLabel#curTimeLabel {\n"
"	color: white;\n"
"	font-family: \"Segoe UI\";\n"
"	font-size :20px;\n"
"}\n"
"\n"
"QLabel#totalTimeLabel {\n"
"	color: white;\n"
"	font-family: \"Segoe UI\";\n"
"	font-size :20px;\n"
"}\n"
"\n"
"QLabel#lrcLabel_1 {\n"
"	color: rgba(0, 0, 0, 128);\n"
"}\n"
"\n"
"QLabel#lrcLabel_4 {\n"
"	font-weight: 500;\n"
"	color: rgb(85, 0, 255);\n"
"}\n"
"\n"
"QLabel#lrcLabel_7 {\n"
"	color: rgba(0, 0, 0, 128);\n"
"}\n"
"\n"
"/*\344\273\245\344\270\212\344\270\272\345\255\227\344\275\223\350\256\276\347\275\256*/\n"
"\n"
"QToolTip {\n"
"    opacity: 220;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	border: 1px solid grey;\n"
"	border-radius: 3px;\n"
"	height: 4px;\n"
"	margin: 0px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"/*\n"
"	border-radius: 3px;\n"
"	margin: -5px -5px -5px -5px;\n"
"	left: 5px; right: 5px;\n"
"*/"
                        "\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"/*\n"
"	border-radius: 3px;\n"
"	margin: -5px -5px -5px -5px;\n"
"	left: 5px; right: 5px;\n"
"*/\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"	border-radius: 3px;\n"
"	background: rgb(69, 251, 255);\n"
"}\n"
"\n"
"QSlider::groove:vertical {\n"
"	border: 1px solid grey;\n"
"	border-radius: 3px;\n"
"	width: 4px;\n"
"	margin: 0px 0;\n"
"} \n"
"\n"
"QSlider::handle:vertical {\n"
"	border-radius: 3px;\n"
"	border: 0px solid #5c5c5c;\n"
"	background: rgb(69, 251, 255);\n"
"	margin: -5px -5px -5px -5px;\n"
"	top: 5px; bottom: 5px;\n"
"}\n"
"\n"
"QSlider::handle:vertical:hover {\n"
"	border-radius: 3px;\n"
"	border: 0px solid #5c5c5c;\n"
"	background: rgb(75, 251, 255);\n"
"	margin: -5px -5px -5px -5px;\n"
"	top: 5px; bottom: 5px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"	border-radius: 3px;\n"
"	background: rgb(69, 251, 255);\n"
"}\n"
"\n"
"QSlider::add-page {\n"
"/*\347\251\272\347\231\275\351\203\250\345\210\206\345\241\253\345\205\205\347\224\250\357"
                        "\274\214\344\273\245\345\205\215\351\200\217\346\230\216\347\202\271\344\270\215\347\235\200*/\n"
"	background: rgba(69, 251, 255, 3);\n"
"}\n"
"\n"
"QLabel {\n"
"	background: transparent;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"	/*background: rgba(255, 255, 255, 180);*/\n"
"}\n"
"\n"
"QLabel#tagLabel {\n"
"	color: white;\n"
"	font-family: \"Segoe UI\", \"\345\256\213\344\275\223\";\n"
"	background: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QLabel#coverLabel{\n"
"	border: 1px solid grey;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"/*\345\275\223\345\211\215\346\255\243\345\234\250\346\222\255\346\224\276\344\271\213\346\240\207\351\242\230\346\241\206\347\232\204\347\231\275\345\255\227*/\n"
"	color: white;\n"
"	font-family: \"Segoe UI\", \"\345\256\213\344\275\223\";\n"
"	background: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QGroupBox {\n"
"/*GroupBox\347\232\204\346\240\267\345\274\217\350\241\250\344\270\215\347\237\245\351\201\223\346\200\216\344\271\210\346\224\271\357\274\214\346\200\273\344\271\213\345\205\210\346\212\212"
                        "\344\270\213\351\235\242\351\200\217\346\230\216\345\272\246\346\224\271\346\210\2200\345\206\215\350\257\264*/\n"
"	background: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QGroupBox#eqGroupBox {\n"
"	background: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(255, 255, 255, 150), stop:1 rgba(255, 255, 255, 70));\n"
"}\n"
"\n"
"QGroupBox {\n"
"	border: 0px solid white;\n"
"	border-radius: 5px;\n"
"	margin-top: 0ex; /* leave space at the top for the title */\n"
"}\n"
"\n"
"QProgressBar{\n"
"/*\350\277\233\345\272\246\346\235\241\345\244\226\346\241\206*/\n"
"	border-radius: 0px;\n"
"	background: transparent;\n"
"	text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"/*\350\277\233\345\272\246\346\235\241\345\206\205\345\256\271*/\n"
"	border-radius: 0px;\n"
"/*border: 1px solid black;*/\n"
"	background: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(85, 130, 255, 255), stop:1 rgba(170, 255, 236, 255));\n"
"}\n"
"\n"
"QProgressBar:horizontal {\n"
"	border-radius: 0px;\n"
"	bord"
                        "er: 1px solid grey;\n"
"	background: transparent;\n"
"	text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk:horizontal {\n"
"/*\346\260\264\345\271\263\350\277\233\345\272\246\346\235\241\345\206\205\345\256\271*/\n"
"	border-radius: 0px;\n"
"	background: rgb(69, 251, 255);\n"
"}\n"
"\n"
"QProgressBar#leftdB:horizontal {\n"
"	border-radius: 0px;\n"
"	border: 1px solid grey;\n"
"	background: rgba(255, 255, 255, 120);\n"
"	text-align: center;\n"
"}\n"
"\n"
"QProgressBar#leftdB::chunk:horizontal {\n"
"	border-radius: 0px;\n"
"	background: rgb(69, 251, 255);\n"
"}\n"
"\n"
"QProgressBar#rightdB:horizontal {\n"
"	border-radius: 0px;\n"
"	border: 1px solid grey;\n"
"	background: rgba(255, 255, 255, 120);\n"
"	text-align: center;\n"
"}\n"
"\n"
"QProgressBar#rightdB::chunk:horizontal {\n"
"	border-radius: 0px;\n"
"	background: rgb(69, 251, 255);\n"
"}\n"
"\n"
"QPushButton {\n"
"	border: 0px solid grey;\n"
"	background-color: rgba(255, 255, 255, 170);\n"
"	padding: -8px -8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	ba"
                        "ckground-color: rgba(255, 255, 255, 220);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: rgba(255, 255, 255, 250);\n"
"}\n"
"\n"
"QPushButton#closeButton {\n"
"	color: white;\n"
"	background-color: rgb(230, 0, 0);\n"
"}\n"
"\n"
"QPushButton#closeButton:hover {\n"
"	background-color: rgb(255, 0, 0);\n"
"}\n"
"\n"
"QPushButton#mainPlayerBtn {\n"
"/*\351\200\200\345\207\272\350\277\267\344\275\240\346\250\241\345\274\217\346\214\211\351\222\256*/\n"
"	color: white;\n"
"	background-color: transparent;\n"
"	border-width: 0px;\n"
"}\n"
"\n"
"QPushButton#mainPlayerBtn:hover {\n"
"	color: white;\n"
"	background-color: rgb(0, 85, 255);\n"
"	border-width: 0px;\n"
"}\n"
"\n"
"QPushButton#setSkinButton:hover {\n"
"	background-color: rgb(0, 85, 255);\n"
"}\n"
"\n"
"QPushButton#setSkinButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playBtn {\n"
"/*\346\222\255\346\224\276\346\214\211\351\222\256*/\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playBtn:hover {\n"
"	backgro"
                        "und-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#stopBtn {\n"
"/*\345\201\234\346\255\242\346\214\211\351\222\256*/\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#stopBtn:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#openButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#openButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#muteBtn {\n"
"/*\351\237\263\351\207\217\346\214\211\351\222\256*/\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#muteBtn:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playModeBtn {\n"
"/*\346\250\241\345\274\217\346\214\211\351\222\256*/\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playModeBtn:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playPrevBtn {\n"
"/*\344\270\212\346\233\262\346\214\211\351\222\256*/\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButt"
                        "on#playPrevBtn:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playNextBtn {\n"
"/*\344\270\213\346\233\262\346\214\211\351\222\256*/\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playNextBtn:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playListButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playListButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
""));
        titleLabel = new QLabel(miniForm);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setGeometry(QRect(100, 0, 156, 31));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);
        titleLabel->setStyleSheet(QStringLiteral("font: 75 11pt \"Tahoma\";"));
        titleLabel->setTextFormat(Qt::AutoText);
        titleLabel->setScaledContents(false);
        groupBox = new QGroupBox(miniForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 30, 250, 40));
        playBtn = new QPushButton(groupBox);
        playBtn->setObjectName(QStringLiteral("playBtn"));
        playBtn->setGeometry(QRect(130, 0, 30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ICO/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        playBtn->setIcon(icon);
        playBtn->setIconSize(QSize(22, 22));
        playNextBtn = new QPushButton(groupBox);
        playNextBtn->setObjectName(QStringLiteral("playNextBtn"));
        playNextBtn->setGeometry(QRect(190, 0, 30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ICO/Next.png"), QSize(), QIcon::Normal, QIcon::Off);
        playNextBtn->setIcon(icon1);
        playNextBtn->setIconSize(QSize(22, 22));
        stopBtn = new QPushButton(groupBox);
        stopBtn->setObjectName(QStringLiteral("stopBtn"));
        stopBtn->setGeometry(QRect(160, 0, 30, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ICO/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopBtn->setIcon(icon2);
        stopBtn->setIconSize(QSize(22, 22));
        muteBtn = new QPushButton(groupBox);
        muteBtn->setObjectName(QStringLiteral("muteBtn"));
        muteBtn->setGeometry(QRect(220, 0, 30, 30));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/ICO/Mute.png"), QSize(), QIcon::Normal, QIcon::Off);
        muteBtn->setIcon(icon3);
        muteBtn->setIconSize(QSize(22, 22));
        playPrevBtn = new QPushButton(groupBox);
        playPrevBtn->setObjectName(QStringLiteral("playPrevBtn"));
        playPrevBtn->setGeometry(QRect(100, 0, 30, 30));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/ICO/Pre.png"), QSize(), QIcon::Normal, QIcon::Off);
        playPrevBtn->setIcon(icon4);
        playPrevBtn->setIconSize(QSize(22, 22));
        mainPlayerBtn = new QPushButton(groupBox);
        mainPlayerBtn->setObjectName(QStringLiteral("mainPlayerBtn"));
        mainPlayerBtn->setGeometry(QRect(70, 0, 30, 30));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/ICO/61Player.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainPlayerBtn->setIcon(icon5);
        mainPlayerBtn->setIconSize(QSize(22, 22));
        miniuiSlider = new SPSlider(groupBox);
        miniuiSlider->setObjectName(QStringLiteral("miniuiSlider"));
        miniuiSlider->setGeometry(QRect(70, 20, 170, 30));
        miniuiSlider->setMaximum(1000);
        miniuiSlider->setSingleStep(0);
        miniuiSlider->setPageStep(0);
        miniuiSlider->setOrientation(Qt::Horizontal);
        nowPlayingBackground = new QLabel(miniForm);
        nowPlayingBackground->setObjectName(QStringLiteral("nowPlayingBackground"));
        nowPlayingBackground->setGeometry(QRect(0, 0, 256, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nowPlayingBackground->sizePolicy().hasHeightForWidth());
        nowPlayingBackground->setSizePolicy(sizePolicy1);
        nowPlayingBackground->setPixmap(QPixmap(QString::fromUtf8(":/image/image/menu-np.png")));
        nowPlayingBackground->raise();
        groupBox->raise();
        titleLabel->raise();

        retranslateUi(miniForm);

        QMetaObject::connectSlotsByName(miniForm);
    } // setupUi

    void retranslateUi(QWidget *miniForm)
    {
        miniForm->setWindowTitle(QApplication::translate("miniForm", "MiniPlayer", 0));
        titleLabel->setText(QApplication::translate("miniForm", "\350\277\231\351\207\214\346\230\276\347\244\272\346\233\262\347\233\256~", 0));
        groupBox->setTitle(QString());
        playBtn->setText(QString());
        playNextBtn->setText(QString());
        stopBtn->setText(QString());
        muteBtn->setText(QString());
        mainPlayerBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        miniuiSlider->setToolTip(QApplication::translate("miniForm", "\346\222\255\346\224\276\350\277\233\345\272\246", 0));
#endif // QT_NO_TOOLTIP
        nowPlayingBackground->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class miniForm: public Ui_miniForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINI_H
