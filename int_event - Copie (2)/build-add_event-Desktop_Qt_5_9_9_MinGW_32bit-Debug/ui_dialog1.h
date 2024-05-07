/********************************************************************************
** Form generated from reading UI file 'dialog1.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG1_H
#define UI_DIALOG1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialogemp
{
public:
    QLabel *label;

    void setupUi(QDialog *Dialogemp)
    {
        if (Dialogemp->objectName().isEmpty())
            Dialogemp->setObjectName(QStringLiteral("Dialogemp"));
        Dialogemp->resize(1229, 687);
        label = new QLabel(Dialogemp);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 1211, 691));

        retranslateUi(Dialogemp);

        QMetaObject::connectSlotsByName(Dialogemp);
    } // setupUi

    void retranslateUi(QDialog *Dialogemp)
    {
        Dialogemp->setWindowTitle(QApplication::translate("Dialogemp", "Dialog", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialogemp: public Ui_Dialogemp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG1_H
