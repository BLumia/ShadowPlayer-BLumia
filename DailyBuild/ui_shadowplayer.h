/********************************************************************************
** Form generated from reading UI file 'shadowplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHADOWPLAYER_H
#define UI_SHADOWPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "fftdisplay.h"
#include "shadowlabel.h"
#include "spslider.h"

QT_BEGIN_NAMESPACE

class Ui_ShadowPlayer
{
public:
    QWidget *centralWidget;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *setAbPointBtn;
    SPSlider *playSlider;
    SPSlider *volSlider;
    ShadowLabel *tagLabel;
    ShadowLabel *mediaInfoLabel;
    QPushButton *openButton;
    QPushButton *muteButton;
    QProgressBar *leftLevel;
    QProgressBar *rightLevel;
    QLabel *LLevelLabel;
    QLabel *RLevelLabel;
    QLabel *coverLabel;
    ShadowLabel *curTimeLabel;
    FFTDisplay *FFTGroupBox;
    SPSlider *freqSlider;
    QPushButton *resetFreqButton;
    QLabel *textLabel1;
    QGroupBox *eqGroupBox;
    QSlider *eqSlider_1;
    QSlider *eqSlider_2;
    QSlider *eqSlider_3;
    QSlider *eqSlider_4;
    QSlider *eqSlider_5;
    QSlider *eqSlider_6;
    QSlider *eqSlider_7;
    QSlider *eqSlider_8;
    QSlider *eqSlider_9;
    QSlider *eqSlider_10;
    QLabel *textLabel2_1;
    QLabel *textLabel2_2;
    QLabel *textLabel2_3;
    QLabel *textLabel2_4;
    QLabel *textLabel2_5;
    QLabel *textLabel2_6;
    QLabel *textLabel2_7;
    QLabel *textLabel2_8;
    QLabel *textLabel2_9;
    QLabel *textLabel2_10;
    QComboBox *eqComboBox;
    QDial *reverbDial;
    QCheckBox *eqEnableCheckBox;
    QGroupBox *lyricsBox;
    QLabel *lrcLabel_1;
    QLabel *lrcLabel_2;
    QLabel *lrcLabel_3;
    ShadowLabel *lrcLabel_4;
    QLabel *lrcLabel_5;
    QLabel *lrcLabel_6;
    QLabel *lrcLabel_7;
    QPushButton *showDskLrcButton;
    QPushButton *loadLrcButton;
    QSlider *offsetSlider;
    QPushButton *offsetLabel;
    QPushButton *extraButton;
    QPushButton *closeButton;
    QPushButton *setSkinButton;
    QPushButton *miniSizeButton;
    QPushButton *playModeButton;
    QPushButton *playPreButton;
    QPushButton *playNextButton;
    QPushButton *playListButton;
    QProgressBar *leftdB;
    QProgressBar *rightdB;
    QPushButton *reverseButton;
    QWidget *playerListArea;
    ShadowLabel *totalTimeLabel;
    QPushButton *setJumpButton;
    QPushButton *miniPlayer;

    void setupUi(QMainWindow *ShadowPlayer)
    {
        if (ShadowPlayer->objectName().isEmpty())
            ShadowPlayer->setObjectName(QStringLiteral("ShadowPlayer"));
        ShadowPlayer->resize(360, 400);
        ShadowPlayer->setMinimumSize(QSize(360, 400));
        ShadowPlayer->setMaximumSize(QSize(710, 400));
        ShadowPlayer->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
"	background: rgb(85, 170, 0);\n"
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
"	background: rgb(85, 170, 0);\n"
"	margin: -5px -5px -5px -5px;\n"
"	top: 5px; bottom: 5px;\n"
"}\n"
"\n"
"QSlider::handle:vertical:hover {\n"
"	border-radius: 3px;\n"
"	border: 0px solid #5c5c5c;\n"
"	background: rgb(85, 255, 0);\n"
"	margin: -5px -5px -5px -5px;\n"
"	top: 5px; bottom: 5px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"	border-radius: 3px;\n"
"	background: rgb(85, 170, 0);\n"
"}\n"
"\n"
"QLabel {\n"
"	background: transparent;\n"
"}\n"
"\n"
"QLabel:hover {\n"
"	/*background: rgba(255, 255, 255, 180);*/\n"
""
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
"QLabel#mediaInfoLabel {\n"
"	color: white;\n"
"	font-family: \"Segoe UI\", \"\345\256\213\344\275\223\";\n"
"	background: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"QGroupBox {\n"
"	background: rgba(255, 255, 255, 80);\n"
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
"/*\350\277\233\345\272\246\346\235\241\345"
                        "\206\205\345\256\271*/\n"
"	border-radius: 0px;\n"
"/*border: 1px solid black;*/\n"
"	background: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(85, 130, 255, 255), stop:1 rgba(170, 255, 236, 255));\n"
"}\n"
"\n"
"QProgressBar:horizontal {\n"
"	border-radius: 0px;\n"
"	border: 1px solid grey;\n"
"	background: transparent;\n"
"	text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk:horizontal {\n"
"/*\346\260\264\345\271\263\350\277\233\345\272\246\346\235\241\345\206\205\345\256\271*/\n"
"	border-radius: 0px;\n"
"	background: rgb(85, 170, 0);\n"
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
"	background: rgb(85, 200, 100);\n"
"}\n"
"\n"
"QProgressBar#rightdB:horizontal {\n"
"	border-radius: 0px;\n"
"	border: 1px solid grey;\n"
"	background: rgba(255, 255, 255, 120);\n"
"	text-align: center;\n"
""
                        "}\n"
"\n"
"QProgressBar#rightdB::chunk:horizontal {\n"
"	border-radius: 0px;\n"
"	background: rgb(85, 200, 100);\n"
"}\n"
"\n"
"QPushButton {\n"
"	border: 0px solid grey;\n"
"	background-color: rgba(255, 255, 255, 170);\n"
"	padding: -8px -8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgba(255, 255, 255, 220);\n"
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
"QPushButton#miniSizeButton {\n"
"	color: white;\n"
"	background-color: transparent;\n"
"	border-width: 0px;\n"
"}\n"
"\n"
"QPushButton#miniPlayer:hover {\n"
"	color: white;\n"
"	background-color: rgb(0, 85, 255);\n"
"	border-width: 0px;\n"
"}\n"
"QPushButton#miniPlayer {\n"
"	color: white;\n"
"	background-color: transparent;\n"
"	border-width: 0px;\n"
"}\n"
"\n"
"QPushButton#miniSizeButton:hover {\n"
"	colo"
                        "r: white;\n"
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
"QPushButton#playButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#stopButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#stopButton:hover {\n"
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
"QPushButton#muteButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#muteButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playModeButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#play"
                        "ModeButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playPreButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playPreButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#playNextButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#playNextButton:hover {\n"
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
"QPushButton#setAbPointBtn {\n"
"        background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#setAbPointBtn:hover {\n"
"        background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QPushButton#setJumpButton {\n"
"background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#setJumpButton:hover {\n"
"background-color: rgba(0, 85, 255, 120);\n"
"}\n"
"\n"
"QSlider::groove:horizontal#offsetSlider {\n"
"	border: 1px "
                        "solid grey;\n"
"	border-radius: 3px;\n"
"	height: 4px;\n"
"	margin: 0px 0;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal#offsetSlider {\n"
"	border-radius: 3px;\n"
"	background: rgba(85, 170, 0, 70);\n"
"}\n"
"\n"
"/* slider\345\244\226\350\276\271\346\241\206 */\n"
"QSlider::groove:vertical#offsetSlider {\n"
"	border: 1px solid rgba(85, 170, 0, 70);\n"
"	border-radius: 3px;\n"
"	width: 4px;\n"
"	margin: 0px 0;\n"
"} \n"
"\n"
"QSlider::groove:vertical:hover#offsetSlider {\n"
"	border: 1px solid rgba(85, 170, 0, 170);\n"
"	border-radius: 3px;\n"
"	width: 4px;\n"
"	margin: 0px 0;\n"
"} \n"
"\n"
"/* \346\213\226\345\212\250\346\214\211\351\222\256 */\n"
"QSlider::handle:vertical#offsetSlider {\n"
"	border-radius: 3px;\n"
"	border: 0px solid #5c5c5c;\n"
"	background: rgba(85, 150, 0, 70);\n"
"	margin: -5px -5px -5px -5px;\n"
"	top: 5px; bottom: 5px;\n"
"}\n"
"\n"
"QSlider::handle:vertical:hover#offsetSlider {\n"
"	border-radius: 3px;\n"
"	border: 0px solid #5c5c5c;\n"
"	background: rgba(95, 155, 0, 180);\n"
"	margin"
                        ": -5px -5px -5px -5px;\n"
"	top: 5px; bottom: 5px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical#offsetSlider {\n"
"	border-radius: 3px;\n"
"	background: rgba(85, 170, 0, 0);\n"
"}\n"
"\n"
"QPushButton#offsetLabel {\n"
"	color: rgba(95, 160, 0, 90);\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"	font-family: \"Segoe UI\";\n"
"	font-size :11px;\n"
"}\n"
"\n"
"QPushButton:hover#offsetLabel {\n"
"	color: rgba(95, 170, 0, 180);\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"	font-family: \"Segoe UI\";\n"
"	font-size :11px;\n"
"}"));
        centralWidget = new QWidget(ShadowPlayer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(130, 120, 31, 31));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ICO/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon);
        playButton->setIconSize(QSize(22, 22));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(170, 120, 31, 31));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ICO/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon1);
        stopButton->setIconSize(QSize(22, 22));
        setAbPointBtn = new QPushButton(centralWidget);
        setAbPointBtn->setObjectName(QStringLiteral("setAbPointBtn"));
        setAbPointBtn->setGeometry(QRect(290, 120, 31, 31));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ICO/Loop.png"), QSize(), QIcon::Normal, QIcon::Off);
        setAbPointBtn->setIcon(icon2);
        setAbPointBtn->setIconSize(QSize(22, 22));
        playSlider = new SPSlider(centralWidget);
        playSlider->setObjectName(QStringLiteral("playSlider"));
        playSlider->setGeometry(QRect(130, 90, 221, 22));
        playSlider->setMaximum(1000);
        playSlider->setSingleStep(0);
        playSlider->setPageStep(0);
        playSlider->setTracking(true);
        playSlider->setOrientation(Qt::Horizontal);
        volSlider = new SPSlider(centralWidget);
        volSlider->setObjectName(QStringLiteral("volSlider"));
        volSlider->setGeometry(QRect(290, 156, 61, 21));
        volSlider->setMaximum(100);
        volSlider->setValue(100);
        volSlider->setOrientation(Qt::Horizontal);
        tagLabel = new ShadowLabel(centralWidget);
        tagLabel->setObjectName(QStringLiteral("tagLabel"));
        tagLabel->setGeometry(QRect(130, 25, 221, 20));
        mediaInfoLabel = new ShadowLabel(centralWidget);
        mediaInfoLabel->setObjectName(QStringLiteral("mediaInfoLabel"));
        mediaInfoLabel->setGeometry(QRect(130, 45, 221, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI,\345\256\213\344\275\223"));
        mediaInfoLabel->setFont(font);
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(130, 150, 31, 31));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/ICO/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        openButton->setIcon(icon3);
        openButton->setIconSize(QSize(24, 24));
        muteButton = new QPushButton(centralWidget);
        muteButton->setObjectName(QStringLiteral("muteButton"));
        muteButton->setGeometry(QRect(250, 150, 31, 31));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(muteButton->sizePolicy().hasHeightForWidth());
        muteButton->setSizePolicy(sizePolicy);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/ICO/Vol.png"), QSize(), QIcon::Normal, QIcon::Off);
        muteButton->setIcon(icon4);
        muteButton->setIconSize(QSize(24, 24));
        leftLevel = new QProgressBar(centralWidget);
        leftLevel->setObjectName(QStringLiteral("leftLevel"));
        leftLevel->setGeometry(QRect(20, 130, 91, 16));
        leftLevel->setAcceptDrops(false);
        leftLevel->setAutoFillBackground(false);
        leftLevel->setMaximum(32768);
        leftLevel->setValue(10000);
        leftLevel->setTextVisible(false);
        rightLevel = new QProgressBar(centralWidget);
        rightLevel->setObjectName(QStringLiteral("rightLevel"));
        rightLevel->setGeometry(QRect(20, 150, 91, 16));
        rightLevel->setMaximum(32768);
        rightLevel->setValue(0);
        rightLevel->setTextVisible(false);
        LLevelLabel = new QLabel(centralWidget);
        LLevelLabel->setObjectName(QStringLiteral("LLevelLabel"));
        LLevelLabel->setGeometry(QRect(10, 129, 8, 21));
        RLevelLabel = new QLabel(centralWidget);
        RLevelLabel->setObjectName(QStringLiteral("RLevelLabel"));
        RLevelLabel->setGeometry(QRect(10, 149, 8, 21));
        coverLabel = new QLabel(centralWidget);
        coverLabel->setObjectName(QStringLiteral("coverLabel"));
        coverLabel->setGeometry(QRect(10, 10, 111, 111));
        curTimeLabel = new ShadowLabel(centralWidget);
        curTimeLabel->setObjectName(QStringLiteral("curTimeLabel"));
        curTimeLabel->setGeometry(QRect(130, 70, 71, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        curTimeLabel->setFont(font1);
        FFTGroupBox = new FFTDisplay(centralWidget);
        FFTGroupBox->setObjectName(QStringLiteral("FFTGroupBox"));
        FFTGroupBox->setGeometry(QRect(12, 70, 337, 321));
        freqSlider = new SPSlider(centralWidget);
        freqSlider->setObjectName(QStringLiteral("freqSlider"));
        freqSlider->setGeometry(QRect(10, 210, 341, 16));
        freqSlider->setMinimum(-5000);
        freqSlider->setMaximum(10000);
        freqSlider->setValue(0);
        freqSlider->setOrientation(Qt::Horizontal);
        freqSlider->setTickPosition(QSlider::NoTicks);
        freqSlider->setTickInterval(1000);
        resetFreqButton = new QPushButton(centralWidget);
        resetFreqButton->setObjectName(QStringLiteral("resetFreqButton"));
        resetFreqButton->setGeometry(QRect(10, 180, 31, 21));
        textLabel1 = new QLabel(centralWidget);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(50, 182, 111, 16));
        eqGroupBox = new QGroupBox(centralWidget);
        eqGroupBox->setObjectName(QStringLiteral("eqGroupBox"));
        eqGroupBox->setGeometry(QRect(370, 30, 331, 171));
        eqSlider_1 = new QSlider(eqGroupBox);
        eqSlider_1->setObjectName(QStringLiteral("eqSlider_1"));
        eqSlider_1->setGeometry(QRect(20, 30, 22, 111));
        eqSlider_1->setMinimum(-15);
        eqSlider_1->setMaximum(15);
        eqSlider_1->setPageStep(1);
        eqSlider_1->setValue(0);
        eqSlider_1->setOrientation(Qt::Vertical);
        eqSlider_1->setTickPosition(QSlider::TicksBothSides);
        eqSlider_1->setTickInterval(3);
        eqSlider_2 = new QSlider(eqGroupBox);
        eqSlider_2->setObjectName(QStringLiteral("eqSlider_2"));
        eqSlider_2->setGeometry(QRect(50, 30, 22, 111));
        eqSlider_2->setMinimum(-15);
        eqSlider_2->setMaximum(15);
        eqSlider_2->setPageStep(1);
        eqSlider_2->setOrientation(Qt::Vertical);
        eqSlider_2->setTickPosition(QSlider::TicksBothSides);
        eqSlider_2->setTickInterval(3);
        eqSlider_3 = new QSlider(eqGroupBox);
        eqSlider_3->setObjectName(QStringLiteral("eqSlider_3"));
        eqSlider_3->setGeometry(QRect(80, 30, 22, 111));
        eqSlider_3->setMinimum(-15);
        eqSlider_3->setMaximum(15);
        eqSlider_3->setPageStep(1);
        eqSlider_3->setOrientation(Qt::Vertical);
        eqSlider_3->setTickPosition(QSlider::TicksBothSides);
        eqSlider_3->setTickInterval(3);
        eqSlider_4 = new QSlider(eqGroupBox);
        eqSlider_4->setObjectName(QStringLiteral("eqSlider_4"));
        eqSlider_4->setGeometry(QRect(110, 30, 22, 111));
        eqSlider_4->setMinimum(-15);
        eqSlider_4->setMaximum(15);
        eqSlider_4->setPageStep(1);
        eqSlider_4->setOrientation(Qt::Vertical);
        eqSlider_4->setTickPosition(QSlider::TicksBothSides);
        eqSlider_4->setTickInterval(3);
        eqSlider_5 = new QSlider(eqGroupBox);
        eqSlider_5->setObjectName(QStringLiteral("eqSlider_5"));
        eqSlider_5->setGeometry(QRect(140, 30, 22, 111));
        eqSlider_5->setMinimum(-15);
        eqSlider_5->setMaximum(15);
        eqSlider_5->setPageStep(1);
        eqSlider_5->setOrientation(Qt::Vertical);
        eqSlider_5->setTickPosition(QSlider::TicksBothSides);
        eqSlider_5->setTickInterval(3);
        eqSlider_6 = new QSlider(eqGroupBox);
        eqSlider_6->setObjectName(QStringLiteral("eqSlider_6"));
        eqSlider_6->setGeometry(QRect(170, 30, 22, 111));
        eqSlider_6->setMinimum(-15);
        eqSlider_6->setMaximum(15);
        eqSlider_6->setPageStep(1);
        eqSlider_6->setOrientation(Qt::Vertical);
        eqSlider_6->setTickPosition(QSlider::TicksBothSides);
        eqSlider_6->setTickInterval(3);
        eqSlider_7 = new QSlider(eqGroupBox);
        eqSlider_7->setObjectName(QStringLiteral("eqSlider_7"));
        eqSlider_7->setGeometry(QRect(200, 30, 22, 111));
        eqSlider_7->setMinimum(-15);
        eqSlider_7->setMaximum(15);
        eqSlider_7->setPageStep(1);
        eqSlider_7->setOrientation(Qt::Vertical);
        eqSlider_7->setTickPosition(QSlider::TicksBothSides);
        eqSlider_7->setTickInterval(3);
        eqSlider_8 = new QSlider(eqGroupBox);
        eqSlider_8->setObjectName(QStringLiteral("eqSlider_8"));
        eqSlider_8->setGeometry(QRect(230, 30, 22, 111));
        eqSlider_8->setMinimum(-15);
        eqSlider_8->setMaximum(15);
        eqSlider_8->setPageStep(1);
        eqSlider_8->setOrientation(Qt::Vertical);
        eqSlider_8->setTickPosition(QSlider::TicksBothSides);
        eqSlider_8->setTickInterval(3);
        eqSlider_9 = new QSlider(eqGroupBox);
        eqSlider_9->setObjectName(QStringLiteral("eqSlider_9"));
        eqSlider_9->setGeometry(QRect(260, 30, 22, 111));
        eqSlider_9->setMinimum(-15);
        eqSlider_9->setMaximum(15);
        eqSlider_9->setPageStep(1);
        eqSlider_9->setOrientation(Qt::Vertical);
        eqSlider_9->setTickPosition(QSlider::TicksBothSides);
        eqSlider_9->setTickInterval(3);
        eqSlider_10 = new QSlider(eqGroupBox);
        eqSlider_10->setObjectName(QStringLiteral("eqSlider_10"));
        eqSlider_10->setGeometry(QRect(290, 30, 22, 111));
        eqSlider_10->setMinimum(-15);
        eqSlider_10->setMaximum(15);
        eqSlider_10->setPageStep(1);
        eqSlider_10->setOrientation(Qt::Vertical);
        eqSlider_10->setTickPosition(QSlider::TicksBothSides);
        eqSlider_10->setTickInterval(3);
        textLabel2_1 = new QLabel(eqGroupBox);
        textLabel2_1->setObjectName(QStringLiteral("textLabel2_1"));
        textLabel2_1->setGeometry(QRect(24, 140, 21, 16));
        textLabel2_2 = new QLabel(eqGroupBox);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(54, 140, 21, 16));
        textLabel2_3 = new QLabel(eqGroupBox);
        textLabel2_3->setObjectName(QStringLiteral("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(82, 140, 21, 16));
        textLabel2_4 = new QLabel(eqGroupBox);
        textLabel2_4->setObjectName(QStringLiteral("textLabel2_4"));
        textLabel2_4->setGeometry(QRect(112, 140, 21, 16));
        textLabel2_5 = new QLabel(eqGroupBox);
        textLabel2_5->setObjectName(QStringLiteral("textLabel2_5"));
        textLabel2_5->setGeometry(QRect(142, 140, 21, 16));
        textLabel2_6 = new QLabel(eqGroupBox);
        textLabel2_6->setObjectName(QStringLiteral("textLabel2_6"));
        textLabel2_6->setGeometry(QRect(174, 140, 21, 16));
        textLabel2_7 = new QLabel(eqGroupBox);
        textLabel2_7->setObjectName(QStringLiteral("textLabel2_7"));
        textLabel2_7->setGeometry(QRect(204, 140, 21, 16));
        textLabel2_8 = new QLabel(eqGroupBox);
        textLabel2_8->setObjectName(QStringLiteral("textLabel2_8"));
        textLabel2_8->setGeometry(QRect(234, 140, 21, 16));
        textLabel2_9 = new QLabel(eqGroupBox);
        textLabel2_9->setObjectName(QStringLiteral("textLabel2_9"));
        textLabel2_9->setGeometry(QRect(264, 140, 21, 16));
        textLabel2_10 = new QLabel(eqGroupBox);
        textLabel2_10->setObjectName(QStringLiteral("textLabel2_10"));
        textLabel2_10->setGeometry(QRect(292, 140, 22, 16));
        eqComboBox = new QComboBox(eqGroupBox);
        eqComboBox->setObjectName(QStringLiteral("eqComboBox"));
        eqComboBox->setGeometry(QRect(270, 0, 62, 22));
        eqComboBox->setStyleSheet(QLatin1String("QComboBox {\n"
"    border: 0px solid white;\n"
"    border-radius: 5px;\n"
"    padding: 0px 8px 0px 8px;\n"
"    min-width: 2em;\n"
"}\n"
"\n"
"QComboBox:editable {\n"
"    background: white;\n"
"}\n"
"\n"
"QComboBox:!editable, QComboBox::drop-down:editable {\n"
"    background: rgba(255, 255, 255, 170);\n"
"}\n"
"\n"
"/* QComboBox gets the \"on\" state when the popup is open */\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n"
"    background: rgba(255, 255, 255, 255);\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    \n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 0px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    \n"
"}\n"
"\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}"));
        eqComboBox->setMaxVisibleItems(15);
        reverbDial = new QDial(eqGroupBox);
        reverbDial->setObjectName(QStringLiteral("reverbDial"));
        reverbDial->setGeometry(QRect(240, 0, 31, 21));
        reverbDial->setMinimum(-20);
        reverbDial->setMaximum(0);
        reverbDial->setPageStep(5);
        reverbDial->setValue(-20);
        eqEnableCheckBox = new QCheckBox(eqGroupBox);
        eqEnableCheckBox->setObjectName(QStringLiteral("eqEnableCheckBox"));
        eqEnableCheckBox->setGeometry(QRect(50, 0, 16, 16));
        eqEnableCheckBox->setChecked(false);
        lyricsBox = new QGroupBox(centralWidget);
        lyricsBox->setObjectName(QStringLiteral("lyricsBox"));
        lyricsBox->setGeometry(QRect(370, 210, 331, 181));
        lrcLabel_1 = new QLabel(lyricsBox);
        lrcLabel_1->setObjectName(QStringLiteral("lrcLabel_1"));
        lrcLabel_1->setGeometry(QRect(10, 25, 311, 16));
        lrcLabel_1->setStyleSheet(QLatin1String("QLabel {\n"
"	color: rgba(0, 0, 0, 128);\n"
"}"));
        lrcLabel_1->setAlignment(Qt::AlignCenter);
        lrcLabel_2 = new QLabel(lyricsBox);
        lrcLabel_2->setObjectName(QStringLiteral("lrcLabel_2"));
        lrcLabel_2->setGeometry(QRect(10, 45, 311, 16));
        lrcLabel_2->setAlignment(Qt::AlignCenter);
        lrcLabel_3 = new QLabel(lyricsBox);
        lrcLabel_3->setObjectName(QStringLiteral("lrcLabel_3"));
        lrcLabel_3->setGeometry(QRect(10, 65, 311, 16));
        lrcLabel_3->setAlignment(Qt::AlignCenter);
        lrcLabel_4 = new ShadowLabel(lyricsBox);
        lrcLabel_4->setObjectName(QStringLiteral("lrcLabel_4"));
        lrcLabel_4->setGeometry(QRect(10, 85, 311, 16));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial,\345\256\213\344\275\223,Segoe UI,\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setBold(true);
        font2.setWeight(62);
        lrcLabel_4->setFont(font2);
        lrcLabel_4->setAlignment(Qt::AlignCenter);
        lrcLabel_5 = new QLabel(lyricsBox);
        lrcLabel_5->setObjectName(QStringLiteral("lrcLabel_5"));
        lrcLabel_5->setGeometry(QRect(10, 105, 311, 16));
        lrcLabel_5->setAlignment(Qt::AlignCenter);
        lrcLabel_6 = new QLabel(lyricsBox);
        lrcLabel_6->setObjectName(QStringLiteral("lrcLabel_6"));
        lrcLabel_6->setGeometry(QRect(10, 125, 311, 16));
        lrcLabel_6->setAlignment(Qt::AlignCenter);
        lrcLabel_7 = new QLabel(lyricsBox);
        lrcLabel_7->setObjectName(QStringLiteral("lrcLabel_7"));
        lrcLabel_7->setGeometry(QRect(10, 145, 311, 16));
        lrcLabel_7->setStyleSheet(QLatin1String("QLabel {\n"
"	color: rgba(0, 0, 0, 128);\n"
"}"));
        lrcLabel_7->setAlignment(Qt::AlignCenter);
        showDskLrcButton = new QPushButton(lyricsBox);
        showDskLrcButton->setObjectName(QStringLiteral("showDskLrcButton"));
        showDskLrcButton->setGeometry(QRect(270, 0, 61, 23));
        loadLrcButton = new QPushButton(lyricsBox);
        loadLrcButton->setObjectName(QStringLiteral("loadLrcButton"));
        loadLrcButton->setGeometry(QRect(200, 0, 61, 23));
        offsetSlider = new QSlider(lyricsBox);
        offsetSlider->setObjectName(QStringLiteral("offsetSlider"));
        offsetSlider->setGeometry(QRect(291, 27, 22, 131));
        offsetSlider->setMinimum(-9000);
        offsetSlider->setMaximum(9000);
        offsetSlider->setOrientation(Qt::Vertical);
        offsetLabel = new QPushButton(lyricsBox);
        offsetLabel->setObjectName(QStringLiteral("offsetLabel"));
        offsetLabel->setGeometry(QRect(272, 160, 61, 21));
        extraButton = new QPushButton(centralWidget);
        extraButton->setObjectName(QStringLiteral("extraButton"));
        extraButton->setGeometry(QRect(340, 0, 21, 21));
        extraButton->setStyleSheet(QStringLiteral("font-family: \"Microsoft Yahei\", \"Simsun\", \"Arial\";"));
        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(295, 0, 40, 21));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial,\345\256\213\344\275\223,Segoe UI,\345\276\256\350\275\257\351\233\205\351\273\221"));
        closeButton->setFont(font3);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/ICO/Close.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon5);
        closeButton->setIconSize(QSize(18, 18));
        setSkinButton = new QPushButton(centralWidget);
        setSkinButton->setObjectName(QStringLiteral("setSkinButton"));
        setSkinButton->setGeometry(QRect(245, 0, 25, 21));
        setSkinButton->setFont(font3);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/ICO/CSkin.png"), QSize(), QIcon::Normal, QIcon::Off);
        setSkinButton->setIcon(icon6);
        setSkinButton->setIconSize(QSize(24, 24));
        miniSizeButton = new QPushButton(centralWidget);
        miniSizeButton->setObjectName(QStringLiteral("miniSizeButton"));
        miniSizeButton->setGeometry(QRect(270, 0, 25, 21));
        miniSizeButton->setFont(font3);
        miniSizeButton->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/ICO/Mini.png"), QSize(), QIcon::Normal, QIcon::Off);
        miniSizeButton->setIcon(icon7);
        miniSizeButton->setIconSize(QSize(18, 18));
        playModeButton = new QPushButton(centralWidget);
        playModeButton->setObjectName(QStringLiteral("playModeButton"));
        playModeButton->setGeometry(QRect(210, 150, 31, 31));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/ICO/Order.png"), QSize(), QIcon::Normal, QIcon::Off);
        playModeButton->setIcon(icon8);
        playModeButton->setIconSize(QSize(24, 24));
        playPreButton = new QPushButton(centralWidget);
        playPreButton->setObjectName(QStringLiteral("playPreButton"));
        playPreButton->setGeometry(QRect(210, 120, 31, 31));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/ICO/Pre.png"), QSize(), QIcon::Normal, QIcon::Off);
        playPreButton->setIcon(icon9);
        playPreButton->setIconSize(QSize(22, 22));
        playNextButton = new QPushButton(centralWidget);
        playNextButton->setObjectName(QStringLiteral("playNextButton"));
        playNextButton->setGeometry(QRect(250, 120, 31, 31));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/ICO/Next.png"), QSize(), QIcon::Normal, QIcon::Off);
        playNextButton->setIcon(icon10);
        playNextButton->setIconSize(QSize(22, 22));
        playListButton = new QPushButton(centralWidget);
        playListButton->setObjectName(QStringLiteral("playListButton"));
        playListButton->setGeometry(QRect(170, 150, 31, 31));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icon/ICO/PlayList.png"), QSize(), QIcon::Normal, QIcon::Off);
        playListButton->setIcon(icon11);
        playListButton->setIconSize(QSize(24, 24));
        leftdB = new QProgressBar(centralWidget);
        leftdB->setObjectName(QStringLiteral("leftdB"));
        leftdB->setGeometry(QRect(20, 130, 91, 16));
        leftdB->setMinimum(-60);
        leftdB->setMaximum(0);
        leftdB->setValue(-20);
        leftdB->setTextVisible(false);
        rightdB = new QProgressBar(centralWidget);
        rightdB->setObjectName(QStringLiteral("rightdB"));
        rightdB->setGeometry(QRect(20, 150, 91, 16));
        rightdB->setMinimum(-60);
        rightdB->setMaximum(0);
        rightdB->setValue(-60);
        rightdB->setTextVisible(false);
        reverseButton = new QPushButton(centralWidget);
        reverseButton->setObjectName(QStringLiteral("reverseButton"));
        reverseButton->setGeometry(QRect(320, 180, 31, 21));
        playerListArea = new QWidget(centralWidget);
        playerListArea->setObjectName(QStringLiteral("playerListArea"));
        playerListArea->setGeometry(QRect(370, 0, 331, 21));
        playerListArea->setStyleSheet(QStringLiteral(""));
        totalTimeLabel = new ShadowLabel(centralWidget);
        totalTimeLabel->setObjectName(QStringLiteral("totalTimeLabel"));
        totalTimeLabel->setGeometry(QRect(290, 70, 61, 21));
        totalTimeLabel->setFont(font1);
        totalTimeLabel->setTextFormat(Qt::AutoText);
        totalTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        setJumpButton = new QPushButton(centralWidget);
        setJumpButton->setObjectName(QStringLiteral("setJumpButton"));
        setJumpButton->setGeometry(QRect(330, 120, 20, 31));
        miniPlayer = new QPushButton(centralWidget);
        miniPlayer->setObjectName(QStringLiteral("miniPlayer"));
        miniPlayer->setGeometry(QRect(220, 0, 25, 21));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icon/ICO/MiniPlayer.png"), QSize(), QIcon::Normal, QIcon::Off);
        miniPlayer->setIcon(icon12);
        miniPlayer->setIconSize(QSize(18, 18));
        ShadowPlayer->setCentralWidget(centralWidget);
        FFTGroupBox->raise();
        rightdB->raise();
        leftdB->raise();
        coverLabel->raise();
        playSlider->raise();
        volSlider->raise();
        tagLabel->raise();
        mediaInfoLabel->raise();
        leftLevel->raise();
        rightLevel->raise();
        LLevelLabel->raise();
        RLevelLabel->raise();
        curTimeLabel->raise();
        playButton->raise();
        stopButton->raise();
        openButton->raise();
        muteButton->raise();
        freqSlider->raise();
        resetFreqButton->raise();
        textLabel1->raise();
        eqGroupBox->raise();
        lyricsBox->raise();
        extraButton->raise();
        closeButton->raise();
        setSkinButton->raise();
        miniSizeButton->raise();
        playModeButton->raise();
        playPreButton->raise();
        playNextButton->raise();
        playListButton->raise();
        reverseButton->raise();
        playerListArea->raise();
        totalTimeLabel->raise();
        setAbPointBtn->raise();
        setJumpButton->raise();
        miniPlayer->raise();
        QWidget::setTabOrder(openButton, stopButton);
        QWidget::setTabOrder(stopButton, playButton);
        QWidget::setTabOrder(playButton, muteButton);
        QWidget::setTabOrder(muteButton, volSlider);
        QWidget::setTabOrder(volSlider, playListButton);
        QWidget::setTabOrder(playListButton, playPreButton);
        QWidget::setTabOrder(playPreButton, playNextButton);
        QWidget::setTabOrder(playNextButton, playModeButton);
        QWidget::setTabOrder(playModeButton, playSlider);
        QWidget::setTabOrder(playSlider, setSkinButton);
        QWidget::setTabOrder(setSkinButton, resetFreqButton);
        QWidget::setTabOrder(resetFreqButton, freqSlider);
        QWidget::setTabOrder(freqSlider, miniSizeButton);
        QWidget::setTabOrder(miniSizeButton, closeButton);
        QWidget::setTabOrder(closeButton, extraButton);
        QWidget::setTabOrder(extraButton, eqComboBox);
        QWidget::setTabOrder(eqComboBox, eqSlider_1);
        QWidget::setTabOrder(eqSlider_1, eqSlider_2);
        QWidget::setTabOrder(eqSlider_2, eqSlider_3);
        QWidget::setTabOrder(eqSlider_3, eqSlider_4);
        QWidget::setTabOrder(eqSlider_4, eqSlider_5);
        QWidget::setTabOrder(eqSlider_5, eqSlider_6);
        QWidget::setTabOrder(eqSlider_6, eqSlider_7);
        QWidget::setTabOrder(eqSlider_7, eqSlider_8);
        QWidget::setTabOrder(eqSlider_8, eqSlider_9);
        QWidget::setTabOrder(eqSlider_9, eqSlider_10);
        QWidget::setTabOrder(eqSlider_10, loadLrcButton);
        QWidget::setTabOrder(loadLrcButton, showDskLrcButton);

        retranslateUi(ShadowPlayer);

        QMetaObject::connectSlotsByName(ShadowPlayer);
    } // setupUi

    void retranslateUi(QMainWindow *ShadowPlayer)
    {
        ShadowPlayer->setWindowTitle(QApplication::translate("ShadowPlayer", "ShadowPlayer", 0));
#ifndef QT_NO_TOOLTIP
        playButton->setToolTip(QApplication::translate("ShadowPlayer", "\346\222\255\346\224\276\357\274\210Ctrl+F2\357\274\211", 0));
#endif // QT_NO_TOOLTIP
        playButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        stopButton->setToolTip(QApplication::translate("ShadowPlayer", "\345\201\234\346\255\242\357\274\210Ctrl+F3\357\274\211", 0));
#endif // QT_NO_TOOLTIP
        stopButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        setAbPointBtn->setToolTip(QApplication::translate("ShadowPlayer", "AB\345\276\252\347\216\257\346\264\227\350\204\221\346\234\272", 0));
#endif // QT_NO_TOOLTIP
        setAbPointBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        playSlider->setToolTip(QApplication::translate("ShadowPlayer", "\346\222\255\346\224\276\350\277\233\345\272\246", 0));
#endif // QT_NO_TOOLTIP
        tagLabel->setText(QApplication::translate("ShadowPlayer", "\342\206\220\350\277\231\351\207\214\350\203\275\346\230\276\347\244\272\347\233\256\345\275\225\344\270\213\347\232\204\344\270\223\350\276\221\345\260\201\351\235\242(cover)", 0));
        mediaInfoLabel->setText(QApplication::translate("ShadowPlayer", "\344\275\240\345\217\257\344\273\245\346\212\212\351\237\263\351\242\221\346\226\207\344\273\266\346\213\226\350\277\233\346\235\245\345\223\246~", 0));
#ifndef QT_NO_TOOLTIP
        openButton->setToolTip(QApplication::translate("ShadowPlayer", "\346\211\223\345\274\200", 0));
#endif // QT_NO_TOOLTIP
        openButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        muteButton->setToolTip(QApplication::translate("ShadowPlayer", "\351\235\231\351\237\263\357\274\210Ctrl+F4\357\274\211", 0));
#endif // QT_NO_TOOLTIP
        muteButton->setText(QString());
        LLevelLabel->setText(QApplication::translate("ShadowPlayer", "L", 0));
        RLevelLabel->setText(QApplication::translate("ShadowPlayer", "R", 0));
#ifndef QT_NO_TOOLTIP
        coverLabel->setToolTip(QApplication::translate("ShadowPlayer", "ShadowPlayer-BLumia\345\210\206\346\224\257", 0));
#endif // QT_NO_TOOLTIP
        coverLabel->setText(QString());
        curTimeLabel->setText(QApplication::translate("ShadowPlayer", "0:00", 0));
        FFTGroupBox->setTitle(QApplication::translate("ShadowPlayer", "\351\237\263\344\271\220 \346\212\233\351\235\242\351\245\274", 0));
        resetFreqButton->setText(QApplication::translate("ShadowPlayer", "\351\207\215\347\275\256", 0));
        textLabel1->setText(QApplication::translate("ShadowPlayer", "\345\233\236\346\224\276\351\200\237\345\272\246 (x1)", 0));
        eqGroupBox->setTitle(QApplication::translate("ShadowPlayer", "\345\235\207\350\241\241\345\231\250", 0));
        textLabel2_1->setText(QApplication::translate("ShadowPlayer", "31", 0));
        textLabel2_2->setText(QApplication::translate("ShadowPlayer", "62", 0));
        textLabel2_3->setText(QApplication::translate("ShadowPlayer", "125", 0));
        textLabel2_4->setText(QApplication::translate("ShadowPlayer", "250", 0));
        textLabel2_5->setText(QApplication::translate("ShadowPlayer", "500", 0));
        textLabel2_6->setText(QApplication::translate("ShadowPlayer", "1K", 0));
        textLabel2_7->setText(QApplication::translate("ShadowPlayer", "2K", 0));
        textLabel2_8->setText(QApplication::translate("ShadowPlayer", "4K", 0));
        textLabel2_9->setText(QApplication::translate("ShadowPlayer", "8K", 0));
        textLabel2_10->setText(QApplication::translate("ShadowPlayer", "16K", 0));
        eqComboBox->clear();
        eqComboBox->insertItems(0, QStringList()
         << QApplication::translate("ShadowPlayer", "\351\273\230\350\256\244", 0)
         << QApplication::translate("ShadowPlayer", "\346\265\201\350\241\214", 0)
         << QApplication::translate("ShadowPlayer", "\346\221\207\346\273\232", 0)
         << QApplication::translate("ShadowPlayer", "\347\224\265\345\255\220", 0)
         << QApplication::translate("ShadowPlayer", "\345\217\244\345\205\270", 0)
         << QApplication::translate("ShadowPlayer", "\351\207\221\345\261\236", 0)
         << QApplication::translate("ShadowPlayer", "\350\210\236\346\233\262", 0)
         << QApplication::translate("ShadowPlayer", "\344\271\241\346\235\221", 0)
         << QApplication::translate("ShadowPlayer", "\347\210\265\345\243\253", 0)
         << QApplication::translate("ShadowPlayer", "\345\270\203\351\262\201\346\226\257", 0)
         << QApplication::translate("ShadowPlayer", "\346\200\200\346\227\247", 0)
         << QApplication::translate("ShadowPlayer", "\346\255\214\345\211\247", 0)
         << QApplication::translate("ShadowPlayer", "\350\257\255\351\237\263", 0)
        );
#ifndef QT_NO_TOOLTIP
        reverbDial->setToolTip(QApplication::translate("ShadowPlayer", "\346\267\267\345\223\215", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        eqEnableCheckBox->setToolTip(QApplication::translate("ShadowPlayer", "\345\220\257\347\224\250\346\210\226\345\205\263\351\227\255\345\235\207\350\241\241\345\231\250", 0));
#endif // QT_NO_TOOLTIP
        eqEnableCheckBox->setText(QString());
        lyricsBox->setTitle(QApplication::translate("ShadowPlayer", "\346\255\214\350\257\215\347\247\200", 0));
        lrcLabel_1->setText(QString());
        lrcLabel_2->setText(QString());
        lrcLabel_3->setText(QString());
        lrcLabel_4->setText(QString());
        lrcLabel_5->setText(QString());
        lrcLabel_6->setText(QString());
        lrcLabel_7->setText(QString());
        showDskLrcButton->setText(QApplication::translate("ShadowPlayer", "\346\241\214\351\235\242\346\255\214\350\257\215", 0));
        loadLrcButton->setText(QApplication::translate("ShadowPlayer", "\351\200\211\346\213\251\346\226\207\344\273\266", 0));
        offsetLabel->setText(QApplication::translate("ShadowPlayer", "lrcOffset", 0));
        extraButton->setText(QApplication::translate("ShadowPlayer", "\342\206\222", 0));
        closeButton->setText(QString());
        setSkinButton->setText(QString());
        miniSizeButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        playModeButton->setToolTip(QApplication::translate("ShadowPlayer", "\351\241\272\345\272\217\346\222\255\346\224\276", 0));
#endif // QT_NO_TOOLTIP
        playModeButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        playPreButton->setToolTip(QApplication::translate("ShadowPlayer", "\344\270\212\344\270\200\346\233\262\357\274\210Ctrl+F5\357\274\211", 0));
#endif // QT_NO_TOOLTIP
        playPreButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        playNextButton->setToolTip(QApplication::translate("ShadowPlayer", "\344\270\213\344\270\200\346\233\262\357\274\210Ctrl+F6\357\274\211", 0));
#endif // QT_NO_TOOLTIP
        playNextButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        playListButton->setToolTip(QApplication::translate("ShadowPlayer", "\346\222\255\346\224\276\345\210\227\350\241\250", 0));
#endif // QT_NO_TOOLTIP
        playListButton->setText(QString());
        leftdB->setFormat(QApplication::translate("ShadowPlayer", "%vdB", 0));
        rightdB->setFormat(QApplication::translate("ShadowPlayer", "%vdB", 0));
        reverseButton->setText(QApplication::translate("ShadowPlayer", "\346\255\243\346\224\276", 0));
        totalTimeLabel->setText(QApplication::translate("ShadowPlayer", "0:00", 0));
#ifndef QT_NO_TOOLTIP
        setJumpButton->setToolTip(QApplication::translate("ShadowPlayer", "\347\262\276\347\241\256\350\256\276\347\275\256AB\346\264\227\350\204\221", 0));
#endif // QT_NO_TOOLTIP
        setJumpButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        miniPlayer->setToolTip(QApplication::translate("ShadowPlayer", "\350\277\233\345\205\245mini\346\250\241\345\274\217", 0));
#endif // QT_NO_TOOLTIP
        miniPlayer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShadowPlayer: public Ui_ShadowPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADOWPLAYER_H
