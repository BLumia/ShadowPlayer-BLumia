/********************************************************************************
** Form generated from reading UI file 'lrcbar.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LRCBAR_H
#define UI_LRCBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LrcBar
{
public:

    void setupUi(QWidget *LrcBar)
    {
        if (LrcBar->objectName().isEmpty())
            LrcBar->setObjectName(QStringLiteral("LrcBar"));
        LrcBar->setWindowModality(Qt::NonModal);
        LrcBar->resize(1000, 88);

        retranslateUi(LrcBar);

        QMetaObject::connectSlotsByName(LrcBar);
    } // setupUi

    void retranslateUi(QWidget *LrcBar)
    {
        LrcBar->setWindowTitle(QApplication::translate("LrcBar", "\346\255\214\350\257\215", 0));
    } // retranslateUi

};

namespace Ui {
    class LrcBar: public Ui_LrcBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LRCBAR_H
