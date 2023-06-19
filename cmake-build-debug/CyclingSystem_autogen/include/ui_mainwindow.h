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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *labelMap;
    QTextBrowser *tbInfoOut;
    QGroupBox *gbChoose;
    QFormLayout *formLayout;
    QLabel *labelStart;
    QComboBox *comboS;
    QLabel *labelEnd;
    QComboBox *comboE;
    QLabel *labelS;
    QLabel *labelE;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbShowStation;
    QPushButton *pbRecharge;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1034, 654);
        labelMap = new QLabel(MainWindow);
        labelMap->setObjectName(QString::fromUtf8("labelMap"));
        labelMap->setGeometry(QRect(20, 120, 791, 511));
        labelMap->setPixmap(QPixmap(QString::fromUtf8(":/img/image/map.png")));
        labelMap->setScaledContents(true);
        tbInfoOut = new QTextBrowser(MainWindow);
        tbInfoOut->setObjectName(QString::fromUtf8("tbInfoOut"));
        tbInfoOut->setGeometry(QRect(10, 10, 591, 91));
        gbChoose = new QGroupBox(MainWindow);
        gbChoose->setObjectName(QString::fromUtf8("gbChoose"));
        gbChoose->setGeometry(QRect(620, 10, 401, 101));
        QFont font;
        font.setFamilies({QString::fromUtf8("OPPOSans B")});
        font.setPointSize(9);
        gbChoose->setFont(font);
        gbChoose->setMouseTracking(false);
        formLayout = new QFormLayout(gbChoose);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelStart = new QLabel(gbChoose);
        labelStart->setObjectName(QString::fromUtf8("labelStart"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelStart);

        comboS = new QComboBox(gbChoose);
        comboS->setObjectName(QString::fromUtf8("comboS"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboS);

        labelEnd = new QLabel(gbChoose);
        labelEnd->setObjectName(QString::fromUtf8("labelEnd"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelEnd);

        comboE = new QComboBox(gbChoose);
        comboE->setObjectName(QString::fromUtf8("comboE"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboE);

        labelS = new QLabel(MainWindow);
        labelS->setObjectName(QString::fromUtf8("labelS"));
        labelS->setGeometry(QRect(20, 110, 31, 31));
        labelS->setPixmap(QPixmap(QString::fromUtf8(":/img/image/start.png")));
        labelS->setScaledContents(true);
        labelE = new QLabel(MainWindow);
        labelE->setObjectName(QString::fromUtf8("labelE"));
        labelE->setGeometry(QRect(50, 110, 21, 31));
        labelE->setPixmap(QPixmap(QString::fromUtf8(":/img/image/end.png")));
        labelE->setScaledContents(true);
        scrollArea = new QScrollArea(MainWindow);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(830, 120, 171, 101));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 169, 99));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbShowStation = new QRadioButton(scrollAreaWidgetContents);
        rbShowStation->setObjectName(QString::fromUtf8("rbShowStation"));

        verticalLayout->addWidget(rbShowStation);

        pbRecharge = new QPushButton(scrollAreaWidgetContents);
        pbRecharge->setObjectName(QString::fromUtf8("pbRecharge"));

        verticalLayout->addWidget(pbRecharge);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelMap->setText(QString());
        gbChoose->setTitle(QCoreApplication::translate("MainWindow", "Choose", nullptr));
        labelStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        labelEnd->setText(QCoreApplication::translate("MainWindow", "End", nullptr));
        labelS->setText(QString());
        labelE->setText(QString());
        rbShowStation->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\211\200\346\234\211\347\253\231\347\202\271", nullptr));
        pbRecharge->setText(QCoreApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
