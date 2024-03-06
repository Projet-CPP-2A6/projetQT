#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTableView>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ArtNexus : public QMainWindow
{
    Q_OBJECT

public:
    ArtNexus(QWidget *parent = nullptr);
    ~ArtNexus();

private slots:

    void on_pbconfirm_clicked();



    void on_tableView_clicked(const QModelIndex &index);

    void on_pbdeleteall_clicked();

    void on_pbdelete_clicked();

    void on_pbaddevent_clicked();

    void on_pbliste_clicked();

    void on_pbupdate_clicked();



    void on_pbexportpdf_clicked();


      void on_pbsearch_clicked();

    void on_pbtri_clicked();
void on_pbrefresh_clicked();

    void on_pbconfirm_5_clicked();



    void on_pbstat_clicked();

private:
    Ui::MainWindow *ui;
    int selected;

    class event e;
    class event etmp;
QStandardItemModel *model;
QSortFilterProxyModel *proxyModel;

};
#endif // MAINWINDOW_H
