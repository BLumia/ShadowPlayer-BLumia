/********************************************************************************
** Form generated from reading UI file 'playlist.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYLIST_H
#define UI_PLAYLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayList
{
public:
    QTableWidget *playListTable;
    QPushButton *listOptionButton;
    QComboBox *playListCombo;
    QPushButton *musicOptionButton;
    QPushButton *fliterOptionButton;
    QFrame *finderFlame;
    QLineEdit *searchEdit;
    QCheckBox *isCaseSensitive;
    QPushButton *searchButton;
    QPushButton *searchNextButton;

    void setupUi(QWidget *PlayList)
    {
        if (PlayList->objectName().isEmpty())
            PlayList->setObjectName(QStringLiteral("PlayList"));
        PlayList->resize(331, 361);
        PlayList->setAcceptDrops(true);
        PlayList->setStyleSheet(QLatin1String("QScrollBar:vertical {\n"
"    /*border: 1px solid white;*/\n"
"    /*background: rgba(255, 255, 255, 80);*/\n"
"	background: transparent;\n"
"    width: 18px;\n"
"    margin: 18px 0 18px 0;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: rgba(0, 0, 0, 128);\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover\n"
"{\n"
"	background: rgba(0, 255, 0, 128);\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical {\n"
"    border: 0px solid grey;\n"
"    background: rgba(255, 255, 255, 128);\n"
"    height: 18px;\n"
"    subcontrol-position: bottom;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical {\n"
"    border: 0px solid grey;\n"
"    background: rgba(255, 255, 255, 128);\n"
"    height: 18px;\n"
"    subcontrol-position: top;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
"    border: 1px solid grey;\n"
"	border-radius: 2px;\n"
"    width: 3px;\n"
"    height: 3px;\n"
"    background: gr"
                        "ey;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical\n"
"{\n"
"    background:rgba(255, 255, 255, 128);\n"
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
"QPushButton#fliterOptionButton {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton#fliterOptionButton:hover {\n"
"	background-color: rgba(0, 85, 255, 120);\n"
"}"));
        playListTable = new QTableWidget(PlayList);
        if (playListTable->columnCount() < 2)
            playListTable->setColumnCount(2);
        playListTable->setObjectName(QStringLiteral("playListTable"));
        playListTable->setGeometry(QRect(0, 25, 331, 297));
        playListTable->setStyleSheet(QLatin1String("* {\n"
"	gridline-color: rgba(255, 255, 255, 200);\n"
"}\n"
"QTableWidget{\n"
"	border: none;\n"
"	background: rgba(255, 255, 255, 100);\n"
"}\n"
"QTableWidget::item:selected{\n"
"	color: black;\n"
"	background: rgba(255, 255, 255, 128);    \n"
"}\n"
"QHeaderView {\n"
"	color: white;\n"
"	font: bold 10pt;\n"
"	background-color: rgba(255, 255, 255, 80);\n"
"	border: 0px solid rgb(144, 144, 144);\n"
"	border:0px solid rgb(191,191,191);\n"
"	border-left-color: rgba(255, 255, 255, 0);\n"
"	border-top-color: rgba(255, 255, 255, 0);\n"
"	border-radius:0px;\n"
"	min-height:29px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"	color: black;\n"
"	background-color: rgba(255, 255, 255, 100);\n"
"	border: 3px solid #000000;\n"
"	border-radius:0px;\n"
"	border-color: rgba(255, 255, 255, 0);\n"
"}"));
        playListTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        playListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        playListTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        playListTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        playListTable->setGridStyle(Qt::SolidLine);
        playListTable->setRowCount(0);
        playListTable->setColumnCount(2);
        playListTable->horizontalHeader()->setVisible(false);
        playListTable->horizontalHeader()->setDefaultSectionSize(235);
        playListTable->verticalHeader()->setDefaultSectionSize(18);
        playListTable->verticalHeader()->setMinimumSectionSize(18);
        listOptionButton = new QPushButton(PlayList);
        listOptionButton->setObjectName(QStringLiteral("listOptionButton"));
        listOptionButton->setGeometry(QRect(230, 0, 75, 23));
        playListCombo = new QComboBox(PlayList);
        playListCombo->setObjectName(QStringLiteral("playListCombo"));
        playListCombo->setGeometry(QRect(0, 0, 111, 23));
        playListCombo->setStyleSheet(QLatin1String("/* Guide of Qt css :\n"
"http://qt-project.org/doc/qt-4.8/stylesheet-examples.html#customizing-qcombobox \n"
"*/\n"
"QComboBox {\n"
"     border: 1px solid rgb(0, 170, 255);\n"
"     border-radius: 3px;\n"
"     padding: 1px 18px 1px 3px;\n"
"     min-width: 6em;\n"
"     background: rgba(255, 255, 255, 100);\n"
"}\n"
"\n"
" QComboBox:on { /* shift the text when the popup opens */\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
" }\n"
"\n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"     border-left-width: 1px;\n"
"     border-left-color: rgb(0, 170, 255);\n"
"     border-left-style: solid; /* just a single line */\n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 3px;\n"
" }\n"
"\n"
"QComboBox::down-arrow {\n"
"     image: url(/image/music.png);\n"
" }\n"
"\n"
" QAbstractItemView\n"
"/* DropDown Menu Iten & Text*/\n"
" {  \n"
"	background-color: rgba(255, "
                        "255, 255, 100);\n"
"	selection-background-color: rgba(0, 170, 255, 150);\n"
" } \n"
""));
        musicOptionButton = new QPushButton(PlayList);
        musicOptionButton->setObjectName(QStringLiteral("musicOptionButton"));
        musicOptionButton->setGeometry(QRect(152, 0, 75, 23));
        fliterOptionButton = new QPushButton(PlayList);
        fliterOptionButton->setObjectName(QStringLiteral("fliterOptionButton"));
        fliterOptionButton->setGeometry(QRect(308, 0, 23, 23));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ICO/Fliter.png"), QSize(), QIcon::Normal, QIcon::Off);
        fliterOptionButton->setIcon(icon);
        finderFlame = new QFrame(PlayList);
        finderFlame->setObjectName(QStringLiteral("finderFlame"));
        finderFlame->setGeometry(QRect(0, 330, 331, 31));
        finderFlame->setFrameShape(QFrame::StyledPanel);
        finderFlame->setFrameShadow(QFrame::Raised);
        searchEdit = new QLineEdit(finderFlame);
        searchEdit->setObjectName(QStringLiteral("searchEdit"));
        searchEdit->setGeometry(QRect(5, 0, 121, 21));
        searchEdit->setStyleSheet(QLatin1String("QLineEdit {\n"
"	border: 1px solid rgb(0, 170, 255);\n"
"	border-radius: 2px;\n"
"	background: rgba(255, 255, 255, 255);\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"	border: 1px solid rgb(0, 170, 255);\n"
"	border-radius: 2px;\n"
"	background: rgb(230, 239, 255);\n"
"}"));
        isCaseSensitive = new QCheckBox(finderFlame);
        isCaseSensitive->setObjectName(QStringLiteral("isCaseSensitive"));
        isCaseSensitive->setGeometry(QRect(135, 0, 81, 21));
        isCaseSensitive->setStyleSheet(QLatin1String("QCheckBox {\n"
"    spacing: 3px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 13px;\n"
"    height: 13px;\n"
"	border: 1px solid rgb(0, 170, 255);\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"    background-color: white;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background-color: rgb(178, 203, 255);\n"
"}"));
        searchButton = new QPushButton(finderFlame);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(225, 0, 41, 21));
        searchNextButton = new QPushButton(finderFlame);
        searchNextButton->setObjectName(QStringLiteral("searchNextButton"));
        searchNextButton->setGeometry(QRect(275, 0, 51, 21));

        retranslateUi(PlayList);

        playListCombo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PlayList);
    } // setupUi

    void retranslateUi(QWidget *PlayList)
    {
        PlayList->setWindowTitle(QApplication::translate("PlayList", "\346\222\255\346\224\276\345\210\227\350\241\250\357\274\210\346\213\226\345\205\245\346\226\207\344\273\266\346\267\273\350\207\263\346\234\253\345\260\276\357\274\214\345\217\214\345\207\273\345\220\257\345\212\250\346\222\255\346\224\276\357\274\211", 0));
        listOptionButton->setText(QApplication::translate("PlayList", "\345\210\227\350\241\250\351\200\211\351\241\271", 0));
        playListCombo->clear();
        playListCombo->insertItems(0, QStringList()
         << QApplication::translate("PlayList", "\351\273\230\350\256\244\345\210\227\350\241\250", 0)
         << QApplication::translate("PlayList", "\347\272\242\345\277\203\345\210\227\350\241\250", 0)
        );
        playListCombo->setCurrentText(QApplication::translate("PlayList", "\351\273\230\350\256\244\345\210\227\350\241\250", 0));
        musicOptionButton->setText(QApplication::translate("PlayList", "\346\255\214\346\233\262\351\200\211\351\241\271", 0));
        fliterOptionButton->setText(QString());
        isCaseSensitive->setText(QApplication::translate("PlayList", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", 0));
        searchButton->setText(QApplication::translate("PlayList", "\346\237\245\346\211\276", 0));
        searchNextButton->setText(QApplication::translate("PlayList", "\344\270\213\344\270\200\344\270\252", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayList: public Ui_PlayList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYLIST_H
