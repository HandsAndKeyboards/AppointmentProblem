/********************************************************************************
** Form generated from reading UI file 'helper.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPER_H
#define UI_HELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helper
{
public:
    QTextBrowser *HelpDisplayBox;

    void setupUi(QWidget *helper)
    {
        if (helper->objectName().isEmpty())
            helper->setObjectName(QString::fromUtf8("helper"));
        helper->resize(996, 675);
        HelpDisplayBox = new QTextBrowser(helper);
        HelpDisplayBox->setObjectName(QString::fromUtf8("HelpDisplayBox"));
        HelpDisplayBox->setGeometry(QRect(0, 0, 991, 671));

        retranslateUi(helper);

        QMetaObject::connectSlotsByName(helper);
    } // setupUi

    void retranslateUi(QWidget *helper)
    {
        helper->setWindowTitle(QCoreApplication::translate("helper", "helper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class helper: public Ui_helper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPER_H
