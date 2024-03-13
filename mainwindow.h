#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include "association.h"

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_AjoutButton_clicked();
    void on_BackAjout_clicked();
    void on_ModifierButton_clicked();
    void on_BackModifier_clicked();
    void on_validerModifier_clicked();
    void on_SupprimerButton_clicked();
    void on_BackSupprimer_clicked();
    void on_validerAjout_clicked();
    void on_ValiderSupprimer_clicked();

    void on_pushButton_13_clicked();

    void on_recherche_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    Association Ctemp;
};
#endif // MAINWINDOW_H
