#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTableView>
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

    void on_pbconfirm_clicked();



    void on_tableView_clicked(const QModelIndex &index);

    void on_pbdeleteall_clicked();

    void on_pbdelete_clicked();

    void on_pbaddevent_clicked();

    void on_pbliste_clicked();

    void on_pbupdate_clicked();

private:
    Ui::MainWindow *ui;
    class event e;
    class event etmp;
QStandardItemModel *model;

};
#endif // MAINWINDOW_H
