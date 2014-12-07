/********************************************************************************
** Form generated from reading UI file 'osd.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSD_H
#define UI_OSD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSD
{
public:
    QLabel *titleLabel;
    QLabel *timeLabel;

    void setupUi(QWidget *OSD)
    {
        if (OSD->objectName().isEmpty())
            OSD->setObjectName(QStringLiteral("OSD"));
        OSD->resize(360, 160);
        titleLabel = new QLabel(OSD);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setGeometry(QRect(40, 30, 281, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QStringLiteral("color: white;"));
        titleLabel->setAlignment(Qt::AlignCenter);
        timeLabel = new QLabel(OSD);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(40, 80, 281, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(26);
        font1.setBold(true);
        font1.setWeight(75);
        timeLabel->setFont(font1);
        timeLabel->setStyleSheet(QStringLiteral("color: white;"));
        timeLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(OSD);

        QMetaObject::connectSlotsByName(OSD);
    } // setupUi

    void retranslateUi(QWidget *OSD)
    {
        OSD->setWindowTitle(QApplication::translate("OSD", "SPOSD", 0));
        titleLabel->setText(QApplication::translate("OSD", "\346\240\207\351\242\230\344\277\241\346\201\257", 0));
        timeLabel->setText(QApplication::translate("OSD", "0:00", 0));
    } // retranslateUi

};

namespace Ui {
    class OSD: public Ui_OSD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSD_H
