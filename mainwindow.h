#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTableView>
#include <QSortFilterProxyModel>
#include "artiste.h"
#include "association.h"
#include "oeuvre.h"
#include "employe.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtWidgets>
#include <QQuickWidget>
#include <QFileDialog>
#include "notification.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ArtNexus : public QMainWindow
{
    Q_OBJECT

public:
    ArtNexus(QWidget *parent = nullptr);
    ~ArtNexus();

 void afficherchatboxx();
 QString affichermsg(QString RECEIVER);
public slots:
  void on_messagePreviewClicked(const QModelIndex &index);
private slots:
    bool  controlSaisie();
    void on_add_r_clicked();
    void input();
    void on_arduinoButtonClicked();
        void sortData(int index);
void checkRFIDCard();
    void on_next_r_clicked();

    void on_tableArtiste_activated(const QModelIndex &index);

    void on_back_r_clicked();

    void on_delete_r_clicked();
void on_stat_r_clicked();
void afficherGraphiqueCirculaire_2(QMap<QString, int> statistiques);
    void on_update_r_clicked();

    void on_tri_r_clicked();
    void on_tri_r_id_clicked();

    void on_tri_r_id_2_clicked();

    void on_historique_r_clicked();

  //  void on_search_bouton_clicked();

    void on_search_bouton_2_clicked();

    void on_pdf_r_clicked();
    void on_pbconfirm_clicked();

void on_qrcode_clicked();

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

    void sendMail();
    void mailsent(QString status);

    void on_pbstat_clicked();

    void on_pbmailing_clicked();

   // void on_pb_sendmail_clicked();

    void on_pb_sendmail_clicked();



    void on_gestion_artistepb_clicked();

    void on_calendarWidget_selectionChanged();

    void on_show_all_btn_clicked();

    void on_pbsign_clicked();




    void on_pushButton_21_clicked();

    void on_pb_back_clicked();
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

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_23_clicked();
    void on_pushButton_18_clicked();
    void on_tableView_oeuvre_clicked(const QModelIndex &index);

    void on_btn_confirmer_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_11_clicked();

    void on_btn_confirmer_2_clicked();

    void on_btn_modifier_clicked();

    void on_btn_supprimer_clicked();

    void on_returnOvrBtn_clicked();

    void on_updateOvrBtn_clicked();

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_pushButton_19_clicked();

    void on_pushButton_26_clicked();

    void on_returnOvrBtn_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_22_clicked();

    void on_confirmer_clicked();

    void on_SUPPRIMER_clicked();

    void on_confirmer_update_clicked();

    void on_modifier_3_clicked();

    void on_tableView_emp_clicked(const QModelIndex &index);



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

    void on_recherche_emp_clicked();

    void on_pdf_clicked();

    void on_pushButton_clicked();

    void on_artistes_clicked();

    void on_ouevres_clicked();

    void on_associations_clicked();

    void on_events_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_25_clicked();



    void on_sendchatbtn_clicked();

    void on_pbbot_clicked();

    void on_pb_back_2_clicked();

    void on_pbtri_loc_clicked();

    void on_pbtri_id_clicked();

    void on_lesearch_textChanged(const QString &arg1);

    void on_stats_clicked();

void on_pbps_clicked();
void on_pushButton_27_clicked();

void displayReceivedMessages(QString receiver);

void on_BackSupprimer_5_clicked();

void on_ChatBoxButton_3_clicked();
void on_pushButton_send_2_clicked();
void on_btn_addvd_clicked();
void on_pushButton_pvd_3_clicked();
void playeVd(QPushButton *p );
void on_verticalSlider_3_sliderMoved(int position);
void on_horizontalSlider_3_sliderMoved(int position);
void on_positionChanged(qint64 position);
void on_durationChanged(qint64 position);
void on_closeVdBtn_3_clicked();
void on_pushButton_20_clicked();

void on_pushButton_28_clicked();

void on_pushButton_29_clicked();

void on_pushButton_30_clicked();

void on_pushButton_31_clicked();


void on_pushButton_intev_clicked();
void seConnecter();


//void on_arduino_clicked();

//void on_pushButton_14_clicked();

void on_stats_2_clicked();

void on_lesearch_2_textChanged(const QString &arg1);

void on_employees_clicked();

void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    int selected;
 void sendConfirmationEmail(const QString &recipient, const QString &eventName, const QString &eventDescription, const QString &eventLocation, const QString &eventDate);
  void emailStatus(const QString &status);
 class event e;
    class event etmp;
      Association Ctemp;
          Oeuvre otmp;
           Employe Etmp,empConnected;
QStandardItemModel *model;
QSortFilterProxyModel *proxyModel;
artiste art;
notification notif;
QString FILEPATH;
QMediaPlayer *player = new QMediaPlayer;
 QVideoWidget *videoWidget = new QVideoWidget;
 Arduino A;
 QByteArray data;
};
#endif // MAINWINDOW_H
