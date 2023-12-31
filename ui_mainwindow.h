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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *labelMap;
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
    QPushButton *pbRoute;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLCDNumber *lcdStartTotal;
    QLabel *labelBikeStart;
    QLCDNumber *lcdStartService;
    QLCDNumber *lcdEndTotal;
    QLabel *labelBikeEnd;
    QLCDNumber *lcdEndService;
    QGroupBox *gbBikeStatus;
    QLabel *labelBikeStartBad;
    QLabel *labelBikeEndBad;
    QLabel *labelBikeStartGood;
    QLabel *labelBikeEndGood;
    QGraphicsView *gvMap;
    QLabel *labelScale;
    QLabel *labelBikeTotal;
    QLabel *label;

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
        labelS->setGeometry(QRect(20, 121, 16, 16));
        labelS->setPixmap(QPixmap(QString::fromUtf8(":/img/image/start.png")));
        labelS->setScaledContents(true);
        labelE = new QLabel(MainWindow);
        labelE->setObjectName(QString::fromUtf8("labelE"));
        labelE->setGeometry(QRect(60, 130, 16, 16));
        labelE->setPixmap(QPixmap(QString::fromUtf8(":/img/image/end.png")));
        labelE->setScaledContents(true);
        scrollArea = new QScrollArea(MainWindow);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(830, 130, 171, 131));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 169, 129));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbShowStation = new QRadioButton(scrollAreaWidgetContents);
        rbShowStation->setObjectName(QString::fromUtf8("rbShowStation"));

        verticalLayout->addWidget(rbShowStation);

        pbRecharge = new QPushButton(scrollAreaWidgetContents);
        pbRecharge->setObjectName(QString::fromUtf8("pbRecharge"));

        verticalLayout->addWidget(pbRecharge);

        pbRoute = new QPushButton(scrollAreaWidgetContents);
        pbRoute->setObjectName(QString::fromUtf8("pbRoute"));

        verticalLayout->addWidget(pbRoute);

        scrollArea->setWidget(scrollAreaWidgetContents);
        frame = new QFrame(MainWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 20, 391, 91));
        frame->setCursor(QCursor(Qt::ArrowCursor));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lcdStartTotal = new QLCDNumber(frame);
        lcdStartTotal->setObjectName(QString::fromUtf8("lcdStartTotal"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        QBrush brush1(QColor(227, 227, 227, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush);
#endif
        lcdStartTotal->setPalette(palette);
        QFont font1;
        font1.setBold(true);
        lcdStartTotal->setFont(font1);
        lcdStartTotal->setCursor(QCursor(Qt::ArrowCursor));
        lcdStartTotal->setMouseTracking(false);
        lcdStartTotal->setTabletTracking(false);
        lcdStartTotal->setAcceptDrops(false);
        lcdStartTotal->setLayoutDirection(Qt::LeftToRight);
        lcdStartTotal->setAutoFillBackground(false);
        lcdStartTotal->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    color: black;\n"
"}\n"
""));
        lcdStartTotal->setFrameShape(QFrame::WinPanel);
        lcdStartTotal->setFrameShadow(QFrame::Raised);
        lcdStartTotal->setLineWidth(2);
        lcdStartTotal->setMidLineWidth(4);
        lcdStartTotal->setSmallDecimalPoint(true);
        lcdStartTotal->setDigitCount(8);
        lcdStartTotal->setMode(QLCDNumber::Dec);
        lcdStartTotal->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdStartTotal, 0, 2, 1, 1);

        labelBikeStart = new QLabel(frame);
        labelBikeStart->setObjectName(QString::fromUtf8("labelBikeStart"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        labelBikeStart->setFont(font2);
        labelBikeStart->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout->addWidget(labelBikeStart, 0, 0, 1, 1);

        lcdStartService = new QLCDNumber(frame);
        lcdStartService->setObjectName(QString::fromUtf8("lcdStartService"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush);
#endif
        lcdStartService->setPalette(palette1);
        lcdStartService->setFont(font1);
        lcdStartService->setCursor(QCursor(Qt::ArrowCursor));
        lcdStartService->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    color: black;\n"
"}\n"
""));
        lcdStartService->setFrameShape(QFrame::WinPanel);
        lcdStartService->setFrameShadow(QFrame::Raised);
        lcdStartService->setLineWidth(2);
        lcdStartService->setMidLineWidth(4);
        lcdStartService->setSmallDecimalPoint(true);
        lcdStartService->setDigitCount(8);
        lcdStartService->setMode(QLCDNumber::Dec);
        lcdStartService->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdStartService, 0, 3, 1, 1);

        lcdEndTotal = new QLCDNumber(frame);
        lcdEndTotal->setObjectName(QString::fromUtf8("lcdEndTotal"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush);
#endif
        lcdEndTotal->setPalette(palette2);
        lcdEndTotal->setFont(font1);
        lcdEndTotal->setCursor(QCursor(Qt::ArrowCursor));
        lcdEndTotal->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    color: black;\n"
"}\n"
""));
        lcdEndTotal->setFrameShape(QFrame::WinPanel);
        lcdEndTotal->setFrameShadow(QFrame::Raised);
        lcdEndTotal->setLineWidth(2);
        lcdEndTotal->setMidLineWidth(4);
        lcdEndTotal->setSmallDecimalPoint(true);
        lcdEndTotal->setDigitCount(8);
        lcdEndTotal->setMode(QLCDNumber::Dec);
        lcdEndTotal->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdEndTotal, 3, 2, 1, 1);

        labelBikeEnd = new QLabel(frame);
        labelBikeEnd->setObjectName(QString::fromUtf8("labelBikeEnd"));
        labelBikeEnd->setFont(font2);
        labelBikeEnd->setCursor(QCursor(Qt::ArrowCursor));

        gridLayout->addWidget(labelBikeEnd, 3, 0, 1, 1);

        lcdEndService = new QLCDNumber(frame);
        lcdEndService->setObjectName(QString::fromUtf8("lcdEndService"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush);
#endif
        lcdEndService->setPalette(palette3);
        lcdEndService->setFont(font1);
        lcdEndService->setCursor(QCursor(Qt::ArrowCursor));
        lcdEndService->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    color: black;\n"
"}\n"
""));
        lcdEndService->setFrameShape(QFrame::WinPanel);
        lcdEndService->setFrameShadow(QFrame::Raised);
        lcdEndService->setLineWidth(2);
        lcdEndService->setMidLineWidth(4);
        lcdEndService->setSmallDecimalPoint(true);
        lcdEndService->setDigitCount(8);
        lcdEndService->setMode(QLCDNumber::Dec);
        lcdEndService->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdEndService, 3, 3, 1, 1);

        gbBikeStatus = new QGroupBox(MainWindow);
        gbBikeStatus->setObjectName(QString::fromUtf8("gbBikeStatus"));
        gbBikeStatus->setGeometry(QRect(420, 10, 81, 101));
        gbBikeStatus->setFont(font2);
        labelBikeStartBad = new QLabel(gbBikeStatus);
        labelBikeStartBad->setObjectName(QString::fromUtf8("labelBikeStartBad"));
        labelBikeStartBad->setEnabled(true);
        labelBikeStartBad->setGeometry(QRect(50, 30, 21, 21));
        labelBikeStartBad->setPixmap(QPixmap(QString::fromUtf8(":/img/image/bad.png")));
        labelBikeStartBad->setScaledContents(true);
        labelBikeEndBad = new QLabel(gbBikeStatus);
        labelBikeEndBad->setObjectName(QString::fromUtf8("labelBikeEndBad"));
        labelBikeEndBad->setEnabled(true);
        labelBikeEndBad->setGeometry(QRect(50, 70, 21, 21));
        labelBikeEndBad->setPixmap(QPixmap(QString::fromUtf8(":/img/image/bad.png")));
        labelBikeEndBad->setScaledContents(true);
        labelBikeStartGood = new QLabel(gbBikeStatus);
        labelBikeStartGood->setObjectName(QString::fromUtf8("labelBikeStartGood"));
        labelBikeStartGood->setEnabled(true);
        labelBikeStartGood->setGeometry(QRect(10, 30, 21, 21));
        labelBikeStartGood->setPixmap(QPixmap(QString::fromUtf8(":/img/image/damuzhi.png")));
        labelBikeStartGood->setScaledContents(true);
        labelBikeEndGood = new QLabel(gbBikeStatus);
        labelBikeEndGood->setObjectName(QString::fromUtf8("labelBikeEndGood"));
        labelBikeEndGood->setEnabled(true);
        labelBikeEndGood->setGeometry(QRect(10, 70, 21, 21));
        labelBikeEndGood->setPixmap(QPixmap(QString::fromUtf8(":/img/image/damuzhi.png")));
        labelBikeEndGood->setScaledContents(true);
        gvMap = new QGraphicsView(MainWindow);
        gvMap->setObjectName(QString::fromUtf8("gvMap"));
        gvMap->setGeometry(QRect(830, 390, 181, 241));
        gvMap->setFrameShadow(QFrame::Sunken);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        gvMap->setForegroundBrush(brush2);
        labelScale = new QLabel(MainWindow);
        labelScale->setObjectName(QString::fromUtf8("labelScale"));
        labelScale->setGeometry(QRect(850, 350, 171, 41));
        labelScale->setFont(font2);
        labelBikeTotal = new QLabel(MainWindow);
        labelBikeTotal->setObjectName(QString::fromUtf8("labelBikeTotal"));
        labelBikeTotal->setGeometry(QRect(200, 10, 119, 16));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        labelBikeTotal->setFont(font3);
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(310, 10, 91, 16));
        label->setFont(font3);

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
        pbRoute->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\346\234\200\347\237\255\350\267\257\345\276\204", nullptr));
        labelBikeStart->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        labelBikeEnd->setText(QCoreApplication::translate("MainWindow", "END", nullptr));
        gbBikeStatus->setTitle(QCoreApplication::translate("MainWindow", "STATUS", nullptr));
        labelBikeStartBad->setText(QString());
        labelBikeEndBad->setText(QString());
        labelBikeStartGood->setText(QString());
        labelBikeEndGood->setText(QString());
        labelScale->setText(QCoreApplication::translate("MainWindow", "\345\234\260\345\233\276\347\274\251\346\224\276\346\230\276\347\244\272(+ or -)", nullptr));
        labelBikeTotal->setText(QCoreApplication::translate("MainWindow", "\350\275\246\344\275\215\346\225\260\351\207\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\275\246\344\275\215\345\267\262\350\242\253\344\275\277\347\224\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
