/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *readReferenceAction;
    QAction *readAboutProgramAction;
    QAction *audateAction;
    QAction *updateAction;
    QAction *taskLibrary;
    QAction *openLibrary;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *meetTimeGroupBox;
    QFormLayout *formLayout_2;
    QLabel *meetFromLabel;
    QTimeEdit *meetFromTimeEdit;
    QTimeEdit *meetUntilTimeEdit;
    QLabel *meetUntilLabel;
    QGroupBox *meetingProbabilityGroupBox;
    QFormLayout *formLayout_3;
    QLabel *probabilityPercentageLabel;
    QSpinBox *probabilityPercentageSpinBox;
    QGroupBox *waitTimeGroupBox;
    QFormLayout *formLayout;
    QLabel *waitingTimeLabel;
    QSpinBox *waitingTimeSpinBox;
    QGroupBox *amountOfPersonsGroupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *threePersonsCheckBox;
    QSpacerItem *horizontalSpacer;
    QGridLayout *libraryGroupBox;
    QPushButton *librarySolve;
    QSpinBox *chooseTask;
    QLabel *libraryLabel;
    QTextBrowser *libraryTask;
    QMenuBar *menubar;
    QMenu *helpMenu;
    QMenu *userActionsMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 515);
        readReferenceAction = new QAction(MainWindow);
        readReferenceAction->setObjectName(QString::fromUtf8("readReferenceAction"));
        readAboutProgramAction = new QAction(MainWindow);
        readAboutProgramAction->setObjectName(QString::fromUtf8("readAboutProgramAction"));
        audateAction = new QAction(MainWindow);
        audateAction->setObjectName(QString::fromUtf8("audateAction"));
        updateAction = new QAction(MainWindow);
        updateAction->setObjectName(QString::fromUtf8("updateAction"));
        taskLibrary = new QAction(MainWindow);
        taskLibrary->setObjectName(QString::fromUtf8("taskLibrary"));
        openLibrary = new QAction(MainWindow);
        openLibrary->setObjectName(QString::fromUtf8("openLibrary"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        meetTimeGroupBox = new QGroupBox(centralWidget);
        meetTimeGroupBox->setObjectName(QString::fromUtf8("meetTimeGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(meetTimeGroupBox->sizePolicy().hasHeightForWidth());
        meetTimeGroupBox->setSizePolicy(sizePolicy);
        meetTimeGroupBox->setMaximumSize(QSize(16777215, 16777215));
        meetTimeGroupBox->setBaseSize(QSize(0, 0));
        formLayout_2 = new QFormLayout(meetTimeGroupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        meetFromLabel = new QLabel(meetTimeGroupBox);
        meetFromLabel->setObjectName(QString::fromUtf8("meetFromLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(meetFromLabel->sizePolicy().hasHeightForWidth());
        meetFromLabel->setSizePolicy(sizePolicy1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, meetFromLabel);

        meetFromTimeEdit = new QTimeEdit(meetTimeGroupBox);
        meetFromTimeEdit->setObjectName(QString::fromUtf8("meetFromTimeEdit"));
        meetFromTimeEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(12, 0, 0)));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, meetFromTimeEdit);

        meetUntilTimeEdit = new QTimeEdit(meetTimeGroupBox);
        meetUntilTimeEdit->setObjectName(QString::fromUtf8("meetUntilTimeEdit"));
        meetUntilTimeEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(13, 0, 0)));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, meetUntilTimeEdit);

        meetUntilLabel = new QLabel(meetTimeGroupBox);
        meetUntilLabel->setObjectName(QString::fromUtf8("meetUntilLabel"));
        sizePolicy1.setHeightForWidth(meetUntilLabel->sizePolicy().hasHeightForWidth());
        meetUntilLabel->setSizePolicy(sizePolicy1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, meetUntilLabel);


        gridLayout->addWidget(meetTimeGroupBox, 0, 0, 1, 2);

        meetingProbabilityGroupBox = new QGroupBox(centralWidget);
        meetingProbabilityGroupBox->setObjectName(QString::fromUtf8("meetingProbabilityGroupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(meetingProbabilityGroupBox->sizePolicy().hasHeightForWidth());
        meetingProbabilityGroupBox->setSizePolicy(sizePolicy2);
        formLayout_3 = new QFormLayout(meetingProbabilityGroupBox);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        probabilityPercentageLabel = new QLabel(meetingProbabilityGroupBox);
        probabilityPercentageLabel->setObjectName(QString::fromUtf8("probabilityPercentageLabel"));
        probabilityPercentageLabel->setMaximumSize(QSize(16777215, 16777215));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, probabilityPercentageLabel);

        probabilityPercentageSpinBox = new QSpinBox(meetingProbabilityGroupBox);
        probabilityPercentageSpinBox->setObjectName(QString::fromUtf8("probabilityPercentageSpinBox"));
        probabilityPercentageSpinBox->setMaximum(100);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, probabilityPercentageSpinBox);


        gridLayout->addWidget(meetingProbabilityGroupBox, 3, 0, 1, 2);

        waitTimeGroupBox = new QGroupBox(centralWidget);
        waitTimeGroupBox->setObjectName(QString::fromUtf8("waitTimeGroupBox"));
        sizePolicy2.setHeightForWidth(waitTimeGroupBox->sizePolicy().hasHeightForWidth());
        waitTimeGroupBox->setSizePolicy(sizePolicy2);
        waitTimeGroupBox->setMaximumSize(QSize(16777215, 16777215));
        formLayout = new QFormLayout(waitTimeGroupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        waitingTimeLabel = new QLabel(waitTimeGroupBox);
        waitingTimeLabel->setObjectName(QString::fromUtf8("waitingTimeLabel"));

        formLayout->setWidget(1, QFormLayout::FieldRole, waitingTimeLabel);

        waitingTimeSpinBox = new QSpinBox(waitTimeGroupBox);
        waitingTimeSpinBox->setObjectName(QString::fromUtf8("waitingTimeSpinBox"));
        waitingTimeSpinBox->setValue(15);

        formLayout->setWidget(1, QFormLayout::LabelRole, waitingTimeSpinBox);


        gridLayout->addWidget(waitTimeGroupBox, 1, 0, 1, 2);

        amountOfPersonsGroupBox = new QGroupBox(centralWidget);
        amountOfPersonsGroupBox->setObjectName(QString::fromUtf8("amountOfPersonsGroupBox"));
        sizePolicy2.setHeightForWidth(amountOfPersonsGroupBox->sizePolicy().hasHeightForWidth());
        amountOfPersonsGroupBox->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(amountOfPersonsGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        threePersonsCheckBox = new QCheckBox(amountOfPersonsGroupBox);
        threePersonsCheckBox->setObjectName(QString::fromUtf8("threePersonsCheckBox"));

        horizontalLayout->addWidget(threePersonsCheckBox);


        gridLayout->addWidget(amountOfPersonsGroupBox, 2, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(550, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        libraryGroupBox = new QGridLayout();
        libraryGroupBox->setObjectName(QString::fromUtf8("libraryGroupBox"));
        libraryGroupBox->setSizeConstraint(QLayout::SetDefaultConstraint);
        libraryGroupBox->setContentsMargins(9, 9, 9, 9);
        librarySolve = new QPushButton(centralWidget);
        librarySolve->setObjectName(QString::fromUtf8("librarySolve"));

        libraryGroupBox->addWidget(librarySolve, 3, 0, 1, 1);

        chooseTask = new QSpinBox(centralWidget);
        chooseTask->setObjectName(QString::fromUtf8("chooseTask"));
        chooseTask->setAlignment(Qt::AlignCenter);
        chooseTask->setMinimum(1);
        chooseTask->setMaximum(4);

        libraryGroupBox->addWidget(chooseTask, 1, 0, 1, 1);

        libraryLabel = new QLabel(centralWidget);
        libraryLabel->setObjectName(QString::fromUtf8("libraryLabel"));
        libraryLabel->setAlignment(Qt::AlignCenter);

        libraryGroupBox->addWidget(libraryLabel, 0, 0, 1, 1);

        libraryTask = new QTextBrowser(centralWidget);
        libraryTask->setObjectName(QString::fromUtf8("libraryTask"));

        libraryGroupBox->addWidget(libraryTask, 2, 0, 1, 1);


        gridLayout->addLayout(libraryGroupBox, 0, 3, 4, 1);

        MainWindow->setCentralWidget(centralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 21));
        helpMenu = new QMenu(menubar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));
        userActionsMenu = new QMenu(menubar);
        userActionsMenu->setObjectName(QString::fromUtf8("userActionsMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(userActionsMenu->menuAction());
        menubar->addAction(helpMenu->menuAction());
        helpMenu->addAction(readReferenceAction);
        helpMenu->addAction(readAboutProgramAction);
        userActionsMenu->addAction(updateAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        readReferenceAction->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
#if QT_CONFIG(shortcut)
        readReferenceAction->setShortcut(QCoreApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        readAboutProgramAction->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
#if QT_CONFIG(shortcut)
        readAboutProgramAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        audateAction->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        audateAction->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        updateAction->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        updateAction->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        taskLibrary->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\321\203 \321\201 \320\267\320\260\320\264\320\260\321\207\320\260\320\274\320\270", nullptr));
        openLibrary->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\321\203 \320\267\320\260\320\264\320\260\321\207", nullptr));
        meetTimeGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\262\321\201\321\202\321\200\320\265\321\207\320\270", nullptr));
        meetFromLabel->setText(QCoreApplication::translate("MainWindow", "\320\241", nullptr));
        meetUntilLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276", nullptr));
        meetingProbabilityGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\320\276\321\217\321\202\320\275\320\276\321\201\321\202\321\214 \320\262\321\201\321\202\321\200\320\265\321\207\320\270", nullptr));
        probabilityPercentageLabel->setText(QCoreApplication::translate("MainWindow", "P(A) % =", nullptr));
        waitTimeGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\276\320\266\320\270\320\264\320\260\320\275\320\270\321\217", nullptr));
        waitingTimeLabel->setText(QCoreApplication::translate("MainWindow", "\320\274\320\270\320\275\321\203\321\202", nullptr));
        amountOfPersonsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\273\321\216\320\264\320\265\320\271", nullptr));
        threePersonsCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\270 \320\277\320\265\321\200\321\201\320\276\320\275\321\213", nullptr));
        librarySolve->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\210\320\270\321\202\321\214", nullptr));
        libraryLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\321\200\321\213 \320\267\320\260\320\264\320\260\321\207 ", nullptr));
        helpMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", nullptr));
        userActionsMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
