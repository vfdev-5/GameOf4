/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 6. Oct 04:35:36 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QSpinBox *fieldSizeX;
    QSpinBox *fieldSizeY;
    QPushButton *startButton;
    QLabel *player1TypeL;
    QLabel *player2TypeL;
    QLineEdit *player2ColorLE;
    QLineEdit *player1ColorLE;
    QPushButton *swapB;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(309, 276);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 5, 1, 2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 2);

        fieldSizeX = new QSpinBox(centralwidget);
        fieldSizeX->setObjectName(QString::fromUtf8("fieldSizeX"));
        fieldSizeX->setMinimum(4);
        fieldSizeX->setMaximum(10);

        gridLayout->addWidget(fieldSizeX, 2, 5, 1, 1);

        fieldSizeY = new QSpinBox(centralwidget);
        fieldSizeY->setObjectName(QString::fromUtf8("fieldSizeY"));
        fieldSizeY->setMinimum(4);
        fieldSizeY->setMaximum(10);

        gridLayout->addWidget(fieldSizeY, 2, 6, 1, 1);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        gridLayout->addWidget(startButton, 3, 1, 1, 5);

        player1TypeL = new QLabel(centralwidget);
        player1TypeL->setObjectName(QString::fromUtf8("player1TypeL"));
        player1TypeL->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(player1TypeL, 1, 0, 1, 1);

        player2TypeL = new QLabel(centralwidget);
        player2TypeL->setObjectName(QString::fromUtf8("player2TypeL"));
        player2TypeL->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(player2TypeL, 1, 5, 1, 1);

        player2ColorLE = new QLineEdit(centralwidget);
        player2ColorLE->setObjectName(QString::fromUtf8("player2ColorLE"));
        player2ColorLE->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(player2ColorLE, 1, 6, 1, 1);

        player1ColorLE = new QLineEdit(centralwidget);
        player1ColorLE->setObjectName(QString::fromUtf8("player1ColorLE"));
        player1ColorLE->setAlignment(Qt::AlignCenter);
        player1ColorLE->setReadOnly(true);

        gridLayout->addWidget(player1ColorLE, 1, 1, 1, 1);

        swapB = new QPushButton(centralwidget);
        swapB->setObjectName(QString::fromUtf8("swapB"));

        gridLayout->addWidget(swapB, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 309, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Game Of 4", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Game mode:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Head to Head", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Human vs PC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "PC vs PC", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("MainWindow", "Battle field size:", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        player1TypeL->setText(QApplication::translate("MainWindow", "Head 1 =", 0, QApplication::UnicodeUTF8));
        player2TypeL->setText(QApplication::translate("MainWindow", "Head 2 =", 0, QApplication::UnicodeUTF8));
        player2ColorLE->setText(QApplication::translate("MainWindow", "Ao", 0, QApplication::UnicodeUTF8));
        player1ColorLE->setText(QApplication::translate("MainWindow", "Aka", 0, QApplication::UnicodeUTF8));
        swapB->setText(QApplication::translate("MainWindow", "swap", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
