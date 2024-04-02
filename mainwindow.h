#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include "artiste.h"
#include"qrcode.h"
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
    bool  controlSaisie();
    void on_add_r_clicked();

    void on_next_r_clicked();

    void on_tableArtiste_activated(const QModelIndex &index);

    void on_back_r_clicked();

    void on_delete_r_clicked();

    void on_update_r_clicked();

    void on_tri_r_clicked();

    void on_search_bouton_clicked();

    void on_search_bouton_2_clicked();

    void on_pdf_r_clicked();

    void on_qrcode_clicked();

    void afficherGraphiqueCirculaire_2(QMap<QString, int> statistiques);


    void on_stat_r_clicked();

private:
    Ui::MainWindow *ui;
    artiste art;
    QTextEdit *chat;
    QLineEdit *user_input;
};
#endif // MAINWINDOW_H
