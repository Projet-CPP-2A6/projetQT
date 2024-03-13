#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_confirmer_clicked();

    void on_SUPPRIMER_clicked();

    void on_confirmer_update_clicked();

    void on_modifier_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_ajouter_clicked();

    void on_pb_add_employe_clicked();

    void on_pb_update_employe_clicked();

    void on_pb_delete_employe_clicked();

    void on_pb_list_clicked();

    void on_pb_add_employe_2_clicked();

    void on_pb_delete_employe_2_clicked();

    void on_pb_list_2_clicked();

    void on_pb_add_employe_3_clicked();

    void on_pb_update_employe_2_clicked();

    void on_liste_clicked();

    void on_pb_update_employe_3_clicked();

    void on_pb_delete_employe_3_clicked();

    void on_tri_clicked();

    void on_recherche_clicked();

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;
    Employe Etmp;
};
#endif // MAINWINDOW_H
