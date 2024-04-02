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
public slots:
    void on_messagePreviewClicked(const QModelIndex &index);
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

    void on_pushButton_14_clicked();

    void on_pbps_clicked();

    void on_pushButton_11_clicked();

    void on_ChatBoxButton_clicked();
    void displayReceivedMessages(QString receiver);

    void on_pushButton_send_clicked();

    void on_BackSupprimer_2_clicked();
    void sortData(int index);



private:
    Ui::MainWindow *ui;
    Association Ctemp;
};
#endif // MAINWINDOW_H
