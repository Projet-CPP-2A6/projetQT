#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "oeuvre.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>
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
    void on_pushButton_6_clicked();
    void on_tableView_clicked(const QModelIndex &index);

    void on_btn_confirmer_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_btn_confirmer_2_clicked();

    void on_btn_modifier_clicked();

    void on_btn_supprimer_clicked();

    void on_returnOvrBtn_clicked();

    void on_updateOvrBtn_clicked();

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_returnOvrBtn_2_clicked();

private:
    Ui::MainWindow *ui;
    Oeuvre etmp;
    QStandardItemModel *model;

};
#endif // MAINWINDOW_H
