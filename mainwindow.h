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



private:
    Ui::MainWindow *ui;
    class event e;


};
#endif // MAINWINDOW_H
