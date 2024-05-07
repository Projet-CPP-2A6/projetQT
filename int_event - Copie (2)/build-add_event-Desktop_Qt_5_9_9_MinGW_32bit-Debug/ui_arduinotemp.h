/********************************************************************************
** Form generated from reading UI file 'arduinotemp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARDUINOTEMP_H
#define UI_ARDUINOTEMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_arduinotemp
{
public:
    QLabel *label_14;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QPushButton *pushButton_3;

    void setupUi(QDialog *arduinotemp)
    {
        if (arduinotemp->objectName().isEmpty())
            arduinotemp->setObjectName(QStringLiteral("arduinotemp"));
        arduinotemp->resize(578, 400);
        arduinotemp->setStyleSheet(QLatin1String("background-color:#E8D7C6;\n"
"\n"
""));
        label_14 = new QLabel(arduinotemp);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(20, 30, 531, 61));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_14->setFont(font);
        label_14->setStyleSheet(QLatin1String("/* Style for the label */\n"
"background-color: rgb(232, 215, 198);\n"
"QLabel {\n"
"    font-size: 40px; /* Font size */\n"
"    font-weight: bold; /* Bold font */\n"
"    color: #ffffff; /* White text color */\n"
"    text-transform: uppercase; /* Uppercase text */\n"
"    letter-spacing: 2px; /* Letter spacing */\n"
"    padding: 10px 20px; /* Padding */\n"
" \n"
"    border-radius: 30px; /* Rounded corners */\n"
"    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1); /* Shadow */\n"
"    transition: background-color 0.3s ease; /* Smooth transition */\n"
"}\n"
"\n"
"\n"
""));
        widget = new QWidget(arduinotemp);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(185, 110, 191, 141));
        widget->setStyleSheet(QLatin1String("background-color :#FFF5E1 ;\n"
"border:1px solid black ; \n"
"border-radius:16px"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(145, 17, 21, 41));
        label->setStyleSheet(QLatin1String("border : 0 px  ; \n"
"font-size:25px "));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(46, 20, 101, 101));
        label_2->setStyleSheet(QLatin1String("border:0px ;\n"
"font-size:80px ;\n"
"font-weight : bold ; \n"
"balckground-color:transparent ; "));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(157, 17, 21, 41));
        label_3->setStyleSheet(QLatin1String("border : 0 px  ; \n"
"font-size:40px "));
        label_2->raise();
        label->raise();
        label_3->raise();
        pushButton = new QPushButton(arduinotemp);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(156, 312, 121, 41));
        pushButton->setStyleSheet(QLatin1String("#pushButton{\n"
"	background-color : #FFF5E1 ; \n"
"	border : 1px  solid black ; \n"
"	border-radius : 10px ; \n"
"	color : black ; \n"
"}\n"
"#pushButton:hover {\n"
"	background-color: #a48569 ; \n"
"	color : white ; \n"
"}"));
        pushButton_2 = new QPushButton(arduinotemp);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(288, 312, 121, 41));
        pushButton_2->setStyleSheet(QLatin1String("#pushButton_2{\n"
"	background-color : #FFF5E1 ; \n"
"	border : 1px  solid black ; \n"
"	border-radius : 10px ; \n"
"	color : black ; \n"
"}\n"
"#pushButton_2:hover {\n"
"	background-color: #a48569 ; \n"
"	color : white ; \n"
"}"));
        label_4 = new QLabel(arduinotemp);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(160, 269, 241, 31));
        label_4->setStyleSheet(QStringLiteral("font-size: 20 px ; "));
        pushButton_3 = new QPushButton(arduinotemp);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(420, 264, 81, 34));
        pushButton_3->setStyleSheet(QLatin1String("#pushButton_3{\n"
"	background-color : #FFF5E1 ; \n"
"	border : 1px  solid black ; \n"
"	border-radius : 10px ; \n"
"	color : black ; \n"
"}\n"
"#pushButton_3:hover {\n"
"	background-color: #a48569 ; \n"
"	color : white ; \n"
"}"));

        retranslateUi(arduinotemp);

        QMetaObject::connectSlotsByName(arduinotemp);
    } // setupUi

    void retranslateUi(QDialog *arduinotemp)
    {
        arduinotemp->setWindowTitle(QApplication::translate("arduinotemp", "Dialog", Q_NULLPTR));
        label_14->setText(QApplication::translate("arduinotemp", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; color:#a48569;\">Capteur temperature</span></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("arduinotemp", "\302\260", Q_NULLPTR));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("arduinotemp", "c", Q_NULLPTR));
        pushButton->setText(QApplication::translate("arduinotemp", "Stop", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("arduinotemp", "Start ", Q_NULLPTR));
        label_4->setText(QString());
        pushButton_3->setText(QApplication::translate("arduinotemp", "refresh", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class arduinotemp: public Ui_arduinotemp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARDUINOTEMP_H
