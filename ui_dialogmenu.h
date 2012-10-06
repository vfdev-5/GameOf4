/********************************************************************************
** Form generated from reading UI file 'dialogmenu.ui'
**
** Created: Sat 6. Oct 01:42:41 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMENU_H
#define UI_DIALOGMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogMenu
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *menuCloseB;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QFrame *line_2;
    QPushButton *undoLastMoveB;
    QLineEdit *numOfRedFigLE;
    QLineEdit *numOfBlueFigLE;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *resetGameB;

    void setupUi(QDialog *DialogMenu)
    {
        if (DialogMenu->objectName().isEmpty())
            DialogMenu->setObjectName(QString::fromUtf8("DialogMenu"));
        DialogMenu->resize(332, 452);
        gridLayout = new QGridLayout(DialogMenu);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(126, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 2);

        menuCloseB = new QPushButton(DialogMenu);
        menuCloseB->setObjectName(QString::fromUtf8("menuCloseB"));

        gridLayout->addWidget(menuCloseB, 0, 3, 1, 1);

        label = new QLabel(DialogMenu);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 1, 1, 2);

        label_2 = new QLabel(DialogMenu);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 1, 1, 2);

        line = new QFrame(DialogMenu);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 4);

        line_2 = new QFrame(DialogMenu);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 5, 0, 1, 4);

        undoLastMoveB = new QPushButton(DialogMenu);
        undoLastMoveB->setObjectName(QString::fromUtf8("undoLastMoveB"));

        gridLayout->addWidget(undoLastMoveB, 6, 3, 1, 1);

        numOfRedFigLE = new QLineEdit(DialogMenu);
        numOfRedFigLE->setObjectName(QString::fromUtf8("numOfRedFigLE"));
        numOfRedFigLE->setAlignment(Qt::AlignCenter);
        numOfRedFigLE->setReadOnly(true);

        gridLayout->addWidget(numOfRedFigLE, 2, 3, 1, 1);

        numOfBlueFigLE = new QLineEdit(DialogMenu);
        numOfBlueFigLE->setObjectName(QString::fromUtf8("numOfBlueFigLE"));
        numOfBlueFigLE->setAlignment(Qt::AlignCenter);
        numOfBlueFigLE->setReadOnly(true);

        gridLayout->addWidget(numOfBlueFigLE, 3, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 2, 1, 1);

        resetGameB = new QPushButton(DialogMenu);
        resetGameB->setObjectName(QString::fromUtf8("resetGameB"));

        gridLayout->addWidget(resetGameB, 6, 0, 1, 1);

        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnMinimumWidth(1, 2);

        retranslateUi(DialogMenu);

        QMetaObject::connectSlotsByName(DialogMenu);
    } // setupUi

    void retranslateUi(QDialog *DialogMenu)
    {
        DialogMenu->setWindowTitle(QApplication::translate("DialogMenu", "Dialog", 0, QApplication::UnicodeUTF8));
        menuCloseB->setText(QApplication::translate("DialogMenu", "Close Menu", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogMenu", "Number of Red figures", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogMenu", "Number of Blue figures", 0, QApplication::UnicodeUTF8));
        undoLastMoveB->setText(QApplication::translate("DialogMenu", "Undo Last Move", 0, QApplication::UnicodeUTF8));
        numOfRedFigLE->setText(QApplication::translate("DialogMenu", "0", 0, QApplication::UnicodeUTF8));
        numOfBlueFigLE->setText(QApplication::translate("DialogMenu", "0", 0, QApplication::UnicodeUTF8));
        resetGameB->setText(QApplication::translate("DialogMenu", "Reset Game", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogMenu: public Ui_DialogMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMENU_H
