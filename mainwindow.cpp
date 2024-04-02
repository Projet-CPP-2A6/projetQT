#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statsdialog.h"
#include "smtp.h"
#include <QStringList>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QInputDialog>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include "event.h"
#include "eventmodel.h"
#include <QRegExpValidator>
#include <qsqldatabase.h>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QSqlQueryModel>
#include <QSqlQuery>
#define file_tx "^[A-Za-z ]+$"
#define file_ex "^[0-9]+$"
#include <QtLocation>
#include <QSqlRecord>
#include <QResource>
#include <iostream>
#include <QRegularExpression>
#include "association.h"
#include "qrcode.h"
ArtNexus::ArtNexus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->tri_r, &QPushButton::clicked, this, &ArtNexus::on_tri_r_clicked);
    connect(ui->historique_r, &QPushButton::clicked, this, &ArtNexus::on_historique_r_clicked);
 ui->tableView->setModel(Etmp.afficher());

   class event e;

   QRegExpValidator *dateValidator = new QRegExpValidator(QRegExp("[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}"), this);
       ui->ledate->setValidator(dateValidator);
        ui->ledate_3->setValidator(dateValidator);
         QMetaObject::invokeMethod(this, "on_pbrefresh_clicked", Qt::QueuedConnection);
ui->pbrefresh->setVisible(false);
QRegExpValidator *phoneValidator = new QRegExpValidator(QRegExp("[0-9]{8}"));
    ui->telA->setValidator(phoneValidator);  // Set the validator for the telA field
ui->tableView_Association->setModel(Ctemp.afficher());

ui->lineEdit_price->setValidator(new QIntValidator(0,9999,this));//cs
     QRegularExpressionValidator *stringValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9]+"), this);
     ui->lineEdit_name->setValidator(stringValidator);
     ui->tableView_oeuvre->setModel(otmp.afficher());
     ui->stackedWidget_ALL->setCurrentIndex(0);


}

ArtNexus::~ArtNexus()
{
    delete ui;
}
/************************************************************PARTIE EVENT**************************************************************/
void ArtNexus::on_pbconfirm_clicked()
{
    QString nom_event=ui->lename->text();
    QString descript_event=ui->ledesc->toPlainText();
    QString location=ui->lelocation->text();
    QString date_event=ui->ledate->text();

    QSqlQuery query;
      class event e (nom_event,descript_event,location,date_event);
    bool test=e.ajouter();
    if (test)
    {
        ui->tableView->setModel(etmp.afficher());
      ui->stackedWidget->setCurrentIndex(0);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        ui->lename->clear();
        ui->ledesc->clear();
        ui->lelocation->clear();
        ui->ledate->clear();


    }else QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                QObject::tr("Ajout non effectué.\n"
                                            "Click Cancel to exit."),QMessageBox::Cancel);

}







void ArtNexus::on_tableView_clicked(const QModelIndex &index)
{

    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();

        QSqlQuery qry;
        qry.prepare("select id_event,nom_event, descript_event, location, date_event from event where event='"+val+"' " );
        if(qry.exec())
        {
            while(qry.next())
            {

                ui->lename->setText(qry.value(1).toString());
                ui->ledesc->setText(qry.value(2).toString());
                ui->lelocation->setText(qry.value(3).toString());
                ui->ledate->setText(qry.value(4).toString());

            }
}
}


void ArtNexus::on_pbdeleteall_clicked()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer tous les éléments ?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            class event e;
            bool test = e.supprimerTous();

            if (test)
            {
                ui->tableView->setModel(e.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Suppression de tous les éléments effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                        QObject::tr("Suppression de tous les éléments non effectuée.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}

void ArtNexus::on_pbdelete_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {
            // Récupérer l'ID de la première colonne (id_event)
            int id_event = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

            class event e;
            bool test = e.supprimer(id_event);

            if (test)
            {
                ui->tableView->setModel(e.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Suppression de l'élément effectuée.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                        QObject::tr("Suppression de l'élément non effectuée.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Avertissement"),
                                 QObject::tr("Veuillez sélectionner un élément à supprimer."),
                                 QMessageBox::Cancel);
        }
}

void ArtNexus::on_pbaddevent_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pbconfirm->setVisible(true);
}

void ArtNexus::on_pbliste_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ArtNexus::on_pbupdate_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }
    ui->pbconfirm->setVisible(false);
  //  ui->pbconfirm_3->setVisible(true);
    int selectedRow = selectedIndexes.first().row();
    QString nom_event = ui->tableView->model()->index(selectedRow, 1).data().toString();
    QString descript_event = ui->tableView->model()->index(selectedRow, 2).data().toString();
    QString location = ui->tableView->model()->index(selectedRow, 3).data().toString();
    QString date_event = ui->tableView->model()->index(selectedRow, 4).data().toString();

    QString id_event = ui->tableView->model()->index(selectedRow, 0).data().toString();

    ui->lename_3->setText(nom_event);
    ui->ledesc_3->setText(descript_event);
    ui->lelocation_3->setText(location);
    ui->ledate_3->setText(date_event);

    ui->leid->setText(id_event);
    ui->stackedWidget->setCurrentIndex(2);
     ui->label_id2->setVisible(false);
      ui->leid->setVisible(false);
}
void ArtNexus::on_pbexportpdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

      if (!filePath.isEmpty()) {
          QPrinter printer(QPrinter::PrinterResolution);
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName(filePath);

          // Set the resolution for the printer, not the QPainter
          printer.setResolution(100);

          QPainter painter(&printer);

          // Remove the following line as setResolution is now applied to QPrinter
          // painter.setResolution(1200);

          ui->tableView->render(&painter);

          QMessageBox::information(this, "Export PDF", "PDF file exported successfully.");
      }
}


void ArtNexus::on_pbsearch_clicked()
{
    // Get the search string from the line edit
       QString searchStr = ui->lesearch->text().trimmed();

       // Check if the search string is not empty
       if (!searchStr.isEmpty()) {
           // Create a filter for the SQL query
           QString filter = QString("nom_event LIKE '%%1%' OR descript_event LIKE '%%1%' OR location LIKE '%%1%' OR date_event LIKE '%%1%'")
                                .arg(searchStr);

           // Apply the filter to the SQL query
           QSqlQueryModel *filteredModel = new QSqlQueryModel();
           filteredModel->setQuery("SELECT id_event, nom_event, descript_event, location, date_event FROM event WHERE " + filter);

           // Set the filtered model to the table view
           ui->tableView->setModel(filteredModel);

           // Update the view
           ui->tableView->update();
       } else {
           // If the search string is empty, display all data
           ui->tableView->setModel(etmp.afficher());
       }
}

void ArtNexus::on_pbtri_clicked()
{
 ui->tableView->setModel(e.triNom());
}
void ArtNexus::on_pbtri_loc_clicked()
{
    ui->tableView->setModel(e.triLocation());
}

void ArtNexus::on_pbtri_id_clicked()
{
    ui->tableView->setModel(e.triId());
}


void ArtNexus::on_pbrefresh_clicked()
{
    // Get the search string from the line edit
       QString searchStr = ui->lesearch->text().trimmed();

       // Check if the search string is not empty
       if (!searchStr.isEmpty()) {
           // Create a filter for the SQL query
           QString filter = QString("nom_event LIKE '%%1%' OR descript_event LIKE '%%1%' OR location LIKE '%%1%' OR date_event LIKE '%%1%'")
                                .arg(searchStr);

           // Apply the filter to the SQL query
           QSqlQueryModel *filteredModel = new QSqlQueryModel();
           filteredModel->setQuery("SELECT id_event, nom_event, descript_event, location, date_event FROM event WHERE " + filter);

           // Set the filtered model to the table view
           ui->tableView->setModel(filteredModel);

           // Update the view
           ui->tableView->update();
       } else {
           // If the search string is empty, display all data
           ui->tableView->setModel(etmp.afficher());
       }
       ui->pbrefresh->setVisible(false);
}

void ArtNexus::on_pbconfirm_5_clicked()
{
    int id_event = ui->leid->text().toInt();
       QString nom_event = ui->lename_3->text();
       QString descript_event = ui->ledesc_3->toPlainText();
       QString location = ui->lelocation_3->text();
       QString date_event = ui->ledate_3->text();

     class  event e (id_event,nom_event, descript_event, location,date_event);
       bool test = e.modifier();
       if(test) {
           ui->tableView->setModel(etmp.afficher());
           ui->stackedWidget->setCurrentIndex(0);
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("UPDATE SUCCES\n"),QMessageBox::Cancel);

       }
       else {
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr(" UPDATE FAILED.\n"),QMessageBox::Cancel);
       }
}

void ArtNexus::on_pbstat_clicked()
{
    QSqlQuery query;
        query.prepare("SELECT location, COUNT(*) FROM event GROUP BY location");
        if (query.exec())
        {
            QMap<QString, QList<int>> data;

            while (query.next())
            {
                QString location = query.value(0).toString();
                int count = query.value(1).toInt();
                data[location].append(count);
            }

            Dialog *Dialog = new class Dialog(this);
            Dialog->setChartData(data);
            Dialog->exec();
        }
}
void ArtNexus::sendMail()
{
    Smtp* smtp = new Smtp("slimdiber@gmail.com","eibh bqld rkrq ykhn", "smtp.gmail.com");
 connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));

        smtp->sendMail("slimdiber@gmail.com", ui->lerecepientmail->text() , ui->lesubjectmail->text(),ui->contentmail->toPlainText());
}
void   ArtNexus::mailsent(QString status)
{

    if(status == "Message sent")
    {
        QMessageBox::information(nullptr,QObject::tr("MAIL Sent!"),
                              QObject::tr("Done ! \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
    ui->lerecepientmail->clear();
    ui->lesubjectmail->clear();
    ui->contentmail->clear();
}
void ArtNexus::on_pbmailing_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void ArtNexus::on_pb_sendmail_clicked()
{
  sendMail();
}
void ArtNexus::on_pb_back_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
void ArtNexus::on_pb_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ArtNexus::on_pushButton_3_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(3);
}
void ArtNexus::on_pushButton_clicked()
{
     ui->stackedWidget_ALL->setCurrentIndex(4);
}

void ArtNexus::on_sendchatbtn_clicked()
{
    QString text, space = "";
       float rassemblance = 0;
       int tr = 0;
       QString msg = ui->inputchatbot->text();
       ui->chatbot->appendPlainText("User:     " + msg); // Prefix user input with "User: "
       QSqlQuery qry, query;

       if (msg[0] != "#") {
           qry.prepare("SELECT * FROM chatbot");
           qry.exec();

           while (qry.next() && tr == 0) {
               QString quest = qry.value(0).toString();
               int eq = 0, dif = 0;

               for (int i = 0; i < msg.size(); i++) {
                   if (quest[i] == msg[i])
                       eq++;
                   else
                       dif++;
               }

               rassemblance = (eq / static_cast<float>(msg.size())) * 100;

               if (rassemblance > 80) {
                   ui->chatbot->appendPlainText("Chatbot:  " + qry.value(1).toString()); // Prefix chatbot response with "Chatbot: "
                   tr = 1;
               }
           }

           if (tr == 0) {
               ui->chatbot->appendPlainText("Chatbot: Voulez-vous ajouter un nouveau mot ? Écrivez votre réponse avec un # au début.");
               ui->labelCache->setText(msg);
           }
       } else if (msg[0] == "#") {
           QString msg1 = msg.mid(1, msg.length() - 1);
           query.prepare("INSERT INTO chatbot (quest, rep) VALUES (:quest, :rep)");
           query.bindValue(":quest", ui->labelCache->text());
           query.bindValue(":rep", msg1);

           if (query.exec()) {
               ui->chatbot->appendPlainText("Chatbot: Merci ! Pour cette information");
           } else {
               QMessageBox::critical(this, "Error", "Failed to add new entry to chatbot database.");
           }
       }

       // Clear input field after sending message
       ui->inputchatbot->clear();

       // Scroll to the bottom of the chat window
       ui->chatbot->verticalScrollBar()->setValue(ui->chatbot->verticalScrollBar()->maximum());
}

void ArtNexus::on_pbbot_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

/************************************************************PARTIE ARTISTE**************************************************************/

bool ArtNexus::controlSaisie()
{

    if (ui->sexe_r->currentText().isEmpty() ||
        ui->contact_r->text().isEmpty() ||
        ui->nationalite_r->text().isEmpty() ||
        ui->Id_r->text().isEmpty() ||
        ui->nom_r->text().isEmpty() ||
        ui->prenom_r->text().isEmpty()
    )
    {
        return false;
    }

    QRegularExpression contactRegex("[0-9]+");
    if (!contactRegex.match(ui->contact_r->text()).hasMatch()) {
        return false;
    }



    QRegularExpression prenomRegex("^[^0-9]+$");
    if (!prenomRegex.match(ui->prenom_r->text()).hasMatch()) {
        return false;
    }

    QRegularExpression nationaliteRegex("^[^0-9]+$");
    if (!nationaliteRegex.match(ui->nationalite_r->text()).hasMatch()) {
        return false;
    }
    QRegularExpression nomRegex("^[^0-9@*\\\\]+$");
        if (!nomRegex.match(ui->nom_r->text()).hasMatch()) {
            return false;
        }


    return true;
}

void ArtNexus::on_add_r_clicked()
{
    QMessageBox msgBox;
    if (controlSaisie())
    {
        QString id = ui->Id_r->text();

        if (art.artisteExists(id.toInt()))
        {
            msgBox.setText("Artiste with ID " + id + " already exists.");
        }
        else
        {
            art.setId(id.toInt());
            art.setNom(ui->nom_r->text());
            art.setPrenom(ui->prenom_r->text());
            art.setNationalite(ui->nationalite_r->text());
            art.setContact(ui->contact_r->text().toInt());
            art.setSexe(ui->sexe_r->currentText());
            bool test = art.ADD();
            if (test) {
                msgBox.setText("Added successfully.");
                ui->stackedWidget->setCurrentIndex(1);
            } else
                msgBox.setText("!! Addition failed !!");
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Please fill all fields correctly.\n"), QMessageBox::Cancel);
    }

    ui->tableArtiste->setModel(art.GETALL());
    msgBox.exec();
}

void ArtNexus::on_update_r_clicked()
{
    {

        QMessageBox msgBox;


        if (controlSaisie())
        {
            bool ok;
            int id = ui->Id_r->text().toInt(&ok);

            if (ok)
            {
                if (art.artisteExists(id))
                {

                    art.setId(id);
                    art.setNom(ui->nom_r->text());
                    art.setPrenom(ui->prenom_r->text());
                    art.setNationalite(ui->nationalite_r->text());
                    art.setContact(ui->contact_r->text().toInt());
                    art.setSexe(ui->sexe_r->currentText());

                     ui->tableArtiste->setModel(art.GETALL());

                     bool test = art.UPDATE();

                     if (test)
                     {
                        msgBox.setText("Modification successful.");
                        ui->stackedWidget->setCurrentIndex(1);
                     }
                     else
                     {
                        msgBox.setText("!! Modification failed !!");
                     }
                }
                else
                {

                    msgBox.setText("Artiste with numero " + QString::number(id) + " does not exist.\nCannot modify.");
                }
            }
            else
            {

                msgBox.setText("Veuillez entrer un id de l'artiste valide.");
            }
        }
        else
        {

            msgBox.setText("Veuillez remplir tous les champs.");
        }
        msgBox.exec();
        ui->tableArtiste->setModel(art.GETALL());
    }
}

void ArtNexus::on_delete_r_clicked()
{
    // Récupère l'ID de l'artiste à supprimer à partir de l'interface
    int id_artiste = ui->artistesup->text().toInt();

    QMessageBox msgBox;
    if (art.artisteExists(id_artiste))
    {
        // L'artiste existe, procède à la suppression

        // Récupère les données de l'artiste avant la suppression en utilisant la méthode findbyid()
        QSqlQueryModel *model = art.findbyid(id_artiste);

        // Attribue les données récupérées à l'objet artiste
        art.setNom(model->record(0).value("nom").toString());
        art.setPrenom(model->record(0).value("prenom").toString());
        art.setNationalite(model->record(0).value("nationalite").toString());
        art.setContact(model->record(0).value("contact").toInt());
        art.setSexe(model->record(0).value("sexe").toString());

        // Sauvegarde les données de l'artiste dans un fichier
        QFile file("backup_artiste.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out << "ID: " << id_artiste << "\n";
            out << "Nom: " << art.getNom() << "\n";
            out << "Prenom: " << art.getPrenom() << "\n";
            out << "Nationalite: " << art.getNationalite() << "\n";
            out << "Contact: " << art.getContact() << "\n";
            out << "Sexe: " << art.getSexe() << "\n";
            out << "----------------------------------------\n";  // Ligne de séparation
            file.close();
        }

        // Tente de supprimer l'artiste en appelant la méthode DELETEE()
        bool deletionResult = art.DELETEE(id_artiste);

        if (deletionResult)
        {
            msgBox.setText("Suppression réussie.");
            // Met à jour le modèle de la table affichant les artistes
            ui->tableArtiste->setModel(art.GETALL());
        }
        else
        {
            msgBox.setText("La suppression a échoué.");
        }

        // Affiche la boîte de message
        msgBox.exec();
    }
    else
    {
        // L'artiste n'existe pas, affiche un message d'avertissement
        QMessageBox::warning(this, "Artiste introuvable", "L'artiste avec l'ID " + QString::number(id_artiste) + " n'existe pas.\nImpossible de supprimer.");
    }
}

void ArtNexus::on_next_r_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->tableArtiste->setModel(art.GETALL());
}

void ArtNexus::on_tableArtiste_activated(const QModelIndex &index)
{
    ui->tableArtiste->setModel(art.GETALL());

}

void ArtNexus::on_back_r_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

}


void ArtNexus::on_search_bouton_clicked()
{

        // Get the search string from the line edit
           QString searchStr = ui->search_1->text().trimmed();

           // Check if the search string is not empty
           if (!searchStr.isEmpty()) {
               // Create a filter for the SQL query
               QString filter = QString("nom LIKE '%%1%' OR prenom LIKE '%%1%' OR nationalite LIKE '%%1%' OR contact LIKE '%%1%'")
                                    .arg(searchStr);

               // Apply the filter to the SQL query
               QSqlQueryModel *filteredModel = new QSqlQueryModel();
               filteredModel->setQuery("SELECT id, nom, prenom, nationalite, contact, sexe FROM artiste WHERE " + filter);

               // Set the filtered model to the table view
               ui->tableArtiste->setModel(filteredModel);

               // Update the view
               ui->tableArtiste->update();
           } else {
               // If the search string is empty, display all data
               ui->tableArtiste->setModel(art.GETALL());
           }

}

void ArtNexus::on_search_bouton_2_clicked()
{
    // Get the search string from the line edit
       QString searchStr = ui->search_2->text().trimmed();

       // Check if the search string is not empty
       if (!searchStr.isEmpty()) {
           // Create a filter for the SQL query
           QString filter = QString("nom LIKE '%%1%' OR prenom LIKE '%%1%' OR nationalite LIKE '%%1%' OR contact LIKE '%%1%'")
                                .arg(searchStr);

           // Apply the filter to the SQL query
           QSqlQueryModel *filteredModel = new QSqlQueryModel();
           filteredModel->setQuery("SELECT id, nom, prenom, nationalite, contact, sexe FROM artiste WHERE " + filter);

           // Set the filtered model to the table view
           ui->tableArtiste->setModel(filteredModel);

           // Update the view
           ui->tableArtiste->update();
       } else {
           // If the search string is empty, display all data
           ui->tableArtiste->setModel(art.GETALL());
       }
}


void ArtNexus::on_tri_r_clicked()
{
    ui->tableArtiste->setModel(art.triNom());
}

void ArtNexus::on_pdf_r_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

          if (!filePath.isEmpty()) {
              QPrinter printer(QPrinter::PrinterResolution);
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName(filePath);

              // Set the resolution for the printer, not the QPainter
              printer.setResolution(100);

              QPainter painter(&printer);

              // Remove the following line as setResolution is now applied to QPrinter
              // painter.setResolution(1200);

              ui->tableArtiste->render(&painter);

              QMessageBox::information(this, "Export PDF", "PDF file exported successfully.");
          }

}


// bouton li thezz l page gestion artiste
void ArtNexus::on_gestion_artistepb_clicked()
{
   ui->stackedWidget_ALL->setCurrentIndex(1);
}

// bouton li thezz l page gestion event
void ArtNexus::on_pushButton_21_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(0);
}


void ArtNexus::on_pushButton_22_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(3);
}
void ArtNexus::on_pushButton_25_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(4);
}
void ArtNexus::on_qrcode_clicked()
{
    QString id_str = ui->id_artiste_2->text();
    int id_artiste = id_str.toInt();

    QSqlQuery query;
    query.prepare("SELECT * FROM artiste WHERE id = :id");
    query.bindValue(":id", id_artiste);

    if (query.exec() && query.next()) {
        QString text = "Détails de l'artiste :\n"
                "ID : " + query.value(0).toString() + "\n"
                "NOM : " + query.value(1).toString() + "\n"
                "PRÉNOM : " + query.value(2).toString() + "\n"
                "NATIONALITÉ : " + query.value(3).toString() + "\n"
                "CONTACT : " + query.value(4).toString() + "\n"
                "SEXE : " + query.value(5).toString() + "\n"; // Ajout de sauts de ligne à la fin

        using namespace qrcodegen;
        QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);
        qint32 sz = qr.getSize();
        QImage im(sz, sz, QImage::Format_RGB32);
        QRgb black = qRgb(0, 0, 0);
        QRgb white = qRgb(255, 255, 255);

        for (int y = 0; y < sz; y++)
            for (int x = 0; x < sz; x++)
                im.setPixel(x, y, qr.getModule(x, y) ? black : white);
      //  ui->qr_code->setPixmap(QPixmap::fromImage(im.scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));;
        ui->qr_code->setPixmap(QPixmap::fromImage(im.scaled(128, 128, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));

    } else {
        QMessageBox::information(this, "Erreur", "L'ID de l'artiste n'existe pas dans la base de données.");
    }
}
void ArtNexus::on_tri_r_id_clicked()
{
    ui->tableArtiste->setModel(art.triId());
}


void ArtNexus::on_tri_r_id_2_clicked()
{
    ui->tableArtiste->setModel(art.triNat());
}

void ArtNexus::on_historique_r_clicked()
{
    QString filePath = "backup_artiste.txt";

        // Ouvrir le fichier en utilisant le programme par défaut associé aux fichiers texte
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
void ArtNexus::afficherGraphiqueCirculaire_2(QMap<QString, int> statistiques)
{
    QPieSeries *series = new QPieSeries();

    for (auto it = statistiques.begin(); it != statistiques.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());
        slice->setLabelVisible();
        slice->setLabel(QString("%1: %2 artiste (%3%)").arg(it.key()).arg(it.value()).arg(QString::number(100.0 * slice->percentage(), 'f', 1)));
    }

    // Ajouter une annotation pour la partie "femmes" avec une couleur spécifique
    QPieSlice *femmesSlice = series->slices().at(0);  // Remplacez 0 par l'index de la partie "femmes"
    femmesSlice->setExploded();
    femmesSlice->setLabelVisible();
    femmesSlice->setLabel(QString("Femmes (%1%)").arg(QString::number(100.0 * femmesSlice->percentage(), 'f', 1)));
    femmesSlice->setBrush(QColor("#f37b78"));  // Couleur spécifique pour "femmes"

    // Ajouter une annotation pour la partie "homme" avec une couleur spécifique
    QPieSlice *hommeSlice = series->slices().at(1);  // Remplacez 1 par l'index de la partie "homme"
    hommeSlice->setExploded();
    hommeSlice->setLabelVisible();
    hommeSlice->setLabel(QString("Hommes (%1%)").arg(QString::number(100.0 * hommeSlice->percentage(), 'f', 1)));
    hommeSlice->setBrush(QColor("#663333"));  // Couleur spécifique pour "homme"

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques ");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajuster la taille de la fenêtre du graphique circulaire
    chartView->resize(900, 800);  // Ajustez les dimensions selon vos besoins

    // Afficher la fenêtre du graphique circulaire
    chartView->show();

}

void ArtNexus::on_stat_r_clicked()
{

    QSqlQuery query;
    if (query.exec("SELECT sexe, COUNT(*) FROM artiste GROUP BY sexe"))
    {
        QMap<QString, int> statistiques;
        while (query.next())
        {
            QString sexe = query.value(0).toString();
            int count = query.value(1).toInt();
            statistiques.insert(sexe, count);
        }


        afficherGraphiqueCirculaire_2(statistiques);
    }
    else
    {
        qDebug() << "Erreur lors de la récupération des statistiques : " << query.lastError().text();
    }

}
/************************************************************PARTIE ASSOCIATION **************************************************************/


void ArtNexus::on_AjoutButton_clicked()
{
    // Move to the next page in the stacked widget (Ajout page)
    ui->stackedWidget_3->setCurrentIndex(1);
    ui->tableView_Association->setModel(Ctemp.afficher());

}

void ArtNexus::on_ModifierButton_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget_3->setCurrentIndex(2);
    ui->tableView_Association->setModel(Ctemp.afficher());

}
void ArtNexus::on_BackAjout_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->tableView_Association->setModel(Ctemp.afficher());

}
void ArtNexus::on_BackSupprimer_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->tableView_Association->setModel(Ctemp.afficher());

}
void ArtNexus::on_SupprimerButton_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(3);
}
void ArtNexus::on_BackModifier_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->tableView_Association->setModel(Ctemp.afficher());

}


void ArtNexus::on_validerAjout_clicked()
{
    // Retrieve client data from input fields
    QString nom = ui->nomA->text();
    QString adresse = ui->adresseA->text();
    QString tel = ui->telA->text();
    QString domaine = ui->domaineA->text();
    float montant = ui->montantA->text().toFloat();
    QStringList validDomains = {"santé", "environnement", "social"};
        if (!validDomains.contains(domaine)) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Le domaine doit être 'santé', 'environnement' ou 'social'."),
                                  QMessageBox::Cancel);
            return; // Stop further processing if domain is invalid
        }
            Association association(nom,adresse,tel,domaine,montant);

        bool test=association.ajouter();
        if (test)
        {
           ui->tableView_Association->setModel(Ctemp.afficher());
ui->stackedWidget_3->setCurrentIndex(0);
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("ajout effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            ui->nomA->clear();
            ui->adresseA->clear();
            ui->telA->clear();
            ui->domaineA->clear();
            ui->montantA->clear();
        }else QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                    QObject::tr("Ajout non effectué.\n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
}

void ArtNexus::on_validerModifier_clicked()
{
    int id = ui->idM->text().toInt();
    QString nom = ui->nomM->text();
    QString adresse = ui->adresseM->text();
    QString tel = ui->telM->text();
    QString domaine = ui->domaineM->text();
    float montant = ui->montantM->text().toFloat();

    Association association(id,nom,adresse,tel,domaine,montant);
    bool test = association.modifier();

    QMessageBox msgBox;

    if (test) {
        msgBox.setText("Modification avec succes.");
        ui->tableView_Association->setModel(association.afficher());
    } else {
        msgBox.setText("Echec de Modification. Veuillez consulter la console pour plus de détails.");
    }

    msgBox.exec();
}

void ArtNexus::on_ValiderSupprimer_clicked()
{
        QMessageBox msgBox;

        // Retrieve the client ID from the QLineEdit widget
        int id = ui->idS->text().toInt();
        bool test = Ctemp.supprimer(id);

        if(test)
        {
            ui->tableView_Association->setModel(Ctemp.afficher());
            msgBox.setText("Suppression réussie pour le CIN : " + QString::number(id));
        }
        else
        {
            msgBox.setText("Échec de suppression pour le CIN : " + QString::number(id) + ". Vérifiez les erreurs.");

            // Retrieve the error message from the QSqlQuery object

        }

        msgBox.exec();



}

void ArtNexus::on_pushButton_13_clicked()
{
    ui->tableView_Association->setModel(Ctemp.tri());
}


void ArtNexus::on_recherche_clicked()
{
    // Get the search string from the line edit
            QString searchStr = ui->lesearch->text().trimmed();
            // Check if the search string is not empty
            if (!searchStr.isEmpty()) {
                // Create a filter for the SQL query
                QString filter = QString("id_association LIKE '%%1%' OR nom_association LIKE '%%1%' OR adresse_association LIKE '%%1%' OR tel_association LIKE '%%1%' OR domaine_association LIKE '%%1%' OR montant_association LIKE '%%1%' ") .arg(searchStr);
                // Apply the filter to the SQL query
                QSqlQueryModel *filteredModel = new QSqlQueryModel();
                filteredModel->setQuery("SELECT id_association, nom_association, adresse_association,  tel_association, domaine_association,montant_association FROM ASSOCIATIONS WHERE " + filter);
                // Set the filtered model to the table view
                ui->tableView_Association->setModel(filteredModel);
                // Update the view
                ui->tableView_Association->update();
            } else {
                // If the search string is empty, display all data
                ui->tableView_Association->setModel(Ctemp.afficher()); }
}





void ArtNexus::on_pushButton_12_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

          if (!filePath.isEmpty()) {
              QPrinter printer(QPrinter::PrinterResolution);
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName(filePath);

              // Set the resolution for the printer, not the QPainter
              printer.setResolution(100);

              QPainter painter(&printer);

              // Remove the following line as setResolution is now applied to QPrinter
              // painter.setResolution(1200);

              ui->tableView->render(&painter);

              QMessageBox::information(this, "Export PDF", "PDF file exported successfully.");
          }
}

void ArtNexus::on_pushButton_4_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(2);
}

void ArtNexus::on_pushButton_7_clicked()
{
ui->stackedWidget_ALL->setCurrentIndex(1);
}

void ArtNexus::on_pushButton_8_clicked()
{
ui->stackedWidget_ALL->setCurrentIndex(0);
}

void ArtNexus::on_pushButton_23_clicked()
{
     ui->stackedWidget_ALL->setCurrentIndex(2);
}
void ArtNexus::on_pushButton_2_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(3);
}
void ArtNexus::on_pushButton_9_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(4);
}

/************************************************************PARTIE OEUVRE **************************************************************/

void ArtNexus::on_pushButton_18_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);

}
void ArtNexus::on_btn_confirmer_clicked()

{


    QString ref=ui->lineEdit_reference->text();
   QString nom=ui->lineEdit_name->text();
   int price=ui->lineEdit_price->text().toInt();
   QString desc=ui->lineEdit_desc->text();
   QDate DATEC=ui->dateEdit->date();
   QString TYPE=ui->comboBox->currentText();
   QString POSITION=ui->comboBox_2->currentText();
   QString ETAT=ui->comboBox_3->currentText();
   QSqlQuery qry ;
   qry.prepare("select * from oeuvres where REFERENCE='"+ref+"' " );
   qry.exec();
   if(qry.next()){ QMessageBox::critical(nullptr, QObject::tr("add"),
                                            QObject::tr(" reference already exist .\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);}
   else{
       if(ref==0 || nom=="" || price ==0 ||desc =="" || POSITION == "" || ETAT=="" || TYPE == ""){QMessageBox::warning(nullptr, QObject::tr("add"),
                                                                            QObject::tr(" tous les champs sont obligatoires .\n"
                                                                                      "Click Cancel to exit."), QMessageBox::Cancel);}
                                   else{
   Oeuvre o(ref,nom,price,desc,DATEC,TYPE,POSITION,ETAT);
   bool test=o.ajouter();
   if (test)
   {

       ui->tableView_oeuvre->setModel(otmp.afficher());

        ui->stackedWidget_4->setCurrentIndex(0);
       QMessageBox::information(nullptr, QObject::tr("add"),
                  QObject::tr(" successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

       ui->lineEdit_reference->clear();
       ui->lineEdit_name->clear();
       ui->lineEdit_price->clear();
       ui->lineEdit_desc->clear();
       ui->dateEdit->clear();
       ui->comboBox->currentText();
       ui->comboBox_2->currentText();
       ui->comboBox_3->currentText();

   }
   else{

       QMessageBox::critical(nullptr, QObject::tr("add"),
                   QObject::tr(" failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }
}}
}
void ArtNexus::on_tableView_oeuvre_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView_oeuvre->model()->data(in).toString();
        QSqlQuery qry;
        qry.prepare("select REFERENCE,NOM,PRICE,DESCRIPTION,DATEC,TYPE,POSITION,ETAT from OEUVRES where REFERENCE='"+val+"' " );
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_reference_update->setText(qry.value(0).toString());
                ui->lineEdit_name_update->setText(qry.value(1).toString());
                ui->lineEdit_price_update->setText(qry.value(2).toString());
                ui->lineEdit_desc_update->setText(qry.value(3).toString());
                ui->dateEdit_update->setDate(qry.value(4).toDate());
                ui->comboBox_update->setCurrentText(qry.value(6).toString());
                ui->comboBox_update_2->setCurrentText(qry.value(5).toString());
                ui->comboBox_update_3->setCurrentText(qry.value(7).toString());

            }
}
}
void ArtNexus::on_pushButton_10_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(4);

}

void ArtNexus::on_pushButton_16_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(2);
}

void ArtNexus::on_pushButton_17_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(1);
}

void ArtNexus::on_pushButton_15_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(0);
}

void ArtNexus::on_pushButton_11_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(3);
}

void ArtNexus::on_btn_modifier_clicked()

{
    QModelIndexList selectedIndexes = ui->tableView_oeuvre->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }
    ui->stackedWidget_4->setCurrentIndex(2);
}
void ArtNexus::on_btn_supprimer_clicked()
{
    {
        int i;
            QModelIndex index=ui->tableView_oeuvre->currentIndex();
        i=index.row();
        QModelIndex in=index.sibling(i,0);

        QString val=ui->tableView_oeuvre->model()->data(in).toString();

            bool test=otmp.supprimer(val);
            if (test)
            {

                ui->tableView_oeuvre->setModel(otmp.afficher());
                ui->lineEdit_reference->clear();
                ui->lineEdit_name->clear();
                ui->lineEdit_price->clear();
                ui->lineEdit_desc->clear();
                ui->dateEdit->clear();
                ui->comboBox->currentText();
                ui->comboBox_2->currentText();
                ui->comboBox_3->currentText();


        }
    }
}

void ArtNexus::on_btn_confirmer_2_clicked()
    {
        ui->stackedWidget_4->setCurrentIndex(0);
    }
void ArtNexus::on_returnOvrBtn_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void ArtNexus::on_updateOvrBtn_clicked()
{

    QString ref = ui->lineEdit_reference_update->text();
    QString nom = ui->lineEdit_name_update->text();
    int price = ui->lineEdit_price_update->text().toInt();
    QString desc = ui->lineEdit_desc_update->text();
    QDate DATEC=ui->dateEdit_update->date();
    QString TYPE=ui->comboBox_update->currentText();
    QString POSITION=ui->comboBox_update_2->currentText();
    QString ETAT=ui->comboBox_update_3->currentText();

    if( nom=="" || price ==0 ||desc =="" || POSITION == "" || ETAT=="" || TYPE == ""){QMessageBox::warning(nullptr, QObject::tr("add"),
                                                                         QObject::tr(" tous les champs sont obligatoires .\n"
                                                                                   "Click Cancel to exit."), QMessageBox::Cancel);}
                                else{
    Oeuvre o(ref, nom, price, desc,DATEC,TYPE,POSITION,ETAT);
    bool test = o.modifier(ref);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Update"),
                                 QObject::tr("Update successful.\nClick OK to return."),
                                 QMessageBox::Ok);

        ui->lineEdit_reference_update->clear();
        ui->lineEdit_name_update->clear();
        ui->lineEdit_price_update->clear();
        ui->lineEdit_desc_update->clear();
        ui->dateEdit_update->clear();
        ui->comboBox_update->currentText();
        ui->comboBox_update_2->currentText();
        ui->comboBox_update_3->currentText();
        ui->stackedWidget_4->setCurrentIndex(0);
        ui->tableView_oeuvre->setModel(otmp.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Update"),
                              QObject::tr("Update failed.\nClick OK to return."),
                              QMessageBox::Ok);
    }}
}

void ArtNexus::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    if(arg1 != "")
    {
       ui->tableView_oeuvre->setModel(otmp.triOEUVRES(arg1));
    }
    else
    {
        ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));
    }

}

void ArtNexus::on_lineEdit_6_textChanged(const QString &arg1)
{
    if(arg1!="")
    {
    ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));}
    else if(arg1 == "REFERENCE")
    { ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));}
    else if (arg1 == "NOM"){
    ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));}
    else if (arg1 == "PRICE")
    {ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));}
    else if (arg1 == "DESCRIPTION")
    {ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));}
    else
    {ui->tableView_oeuvre->setModel(otmp.rechercherOEUVRES(arg1));}


}

void ArtNexus::on_pushButton_19_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("C:/Users/salem/Downloads/listeOeuvres.pdf"); // Chemin du fichier
    QPdfWriter pdf(filePath); // Création du fichier PDF

    QPainter painter(&pdf); // Création d'un peintre pour le PDF
    int i = 4100;

    QColor dateColor(0x4a5bcf); // Couleur pour la date
    painter.setPen(dateColor);
    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400, 250, cd.toString("Tunis")); // Entête de la date
    painter.drawText(8100, 500, cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763); // Couleur pour le titre
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));
    painter.drawText(3000, 2700, "Liste des OEUVRES"); // Titre

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 12));

    // Dessiner le cadre du tableau
    painter.drawRect(100, 3300, 9400, 500);

    // Dessiner les en-têtes des colonnes
    painter.drawText(100, 3550, "REFERENCE");
    painter.drawText(1300, 3550, "NOM");
    painter.drawText(2000, 3550,"PRICE" );
    painter.drawText(3000, 3550,"DESCRIPTION" );
    painter.drawText(4400, 3550, "DATEC");
    painter.drawText(6000, 3550, "TYPE");
    painter.drawText(7200, 3550, "POSITION");
    painter.drawText(8500, 3550, "ETAT");

    painter.setFont(QFont("Time New Roman", 10));

    // Exécuter la requête SQL pour sélectionner tous les enregistrements de la table "OEUVRES"
    QSqlQuery query;
    query.prepare("SELECT * FROM OEUVRES");
    query.exec();

    // Afficher les données dans le PDF
    int y = 3800; // Position verticale initiale
    while (query.next())
    {
        painter.drawLine(100, y, 9490, y); // Dessiner une ligne horizontale
        y += 300; // Augmenter la position verticale pour la prochaine ligne

        painter.drawText(500, i, query.value(0).toString()); // REFERENCE
        painter.drawText(1000, i, query.value(1).toString()); // NOM
        painter.drawText(2000, i, query.value(2).toString()); // DESCRIPTION
        painter.drawText(3000, i, query.value(3).toString()); // PRICE
        painter.drawText(4000, i, query.value(4).toString()); // DATEC
        painter.drawText(6000, i, query.value(5).toString()); // TYPE
        painter.drawText(7500, i, query.value(6).toString()); // POSITION
        painter.drawText(8500, i, query.value(7).toString()); // ETAT

        i = i + 300; // Augmenter la position verticale pour la prochaine ligne
    }

    // Afficher un message de confirmation
    QMessageBox::information(nullptr, QObject::tr("PDF créé"),
                             QObject::tr("Fichier créé avec succès.\n"), QMessageBox::Ok);

}

void ArtNexus::on_pushButton_26_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(3);
    QSqlQueryModel * model= new QSqlQueryModel();
                     model->setQuery("select * from OEUVRES where PRICE < 500 ");
                     float PRICE=model->rowCount();
                     model->setQuery("select * from OEUVRES where PRICE  between 500 and 5000 ");
                     float PRICE1=model->rowCount();
                     model->setQuery("select * from OEUVRES where PRICE >5000 ");
                     float PRICE2=model->rowCount();
                     float total=PRICE+PRICE1+PRICE2;
                     QString a=QString("moins de 500 \t"+QString::number((PRICE*100)/total,'f',2)+"%" );
                     QString b=QString("entre 500 et 5000 \t"+QString::number((PRICE1*100)/total,'f',2)+"%" );
                     QString c=QString("+5000 \t"+QString::number((PRICE2*100)/total,'f',2)+"%" );
                     QPieSeries *series = new QPieSeries();
                     series->append(a,PRICE);
                     series->append(b,PRICE1);
                     series->append(c,PRICE2);
             if (PRICE!=0)
             {

                 QPieSlice *slice = series->slices().at(0);
                   slice->setBrush(QColor(164, 133, 105));
                   slice->setLabelVisible();
                   slice->setPen(QPen());;

             }
             if ( PRICE1!=0)
             {
                 QPieSlice *slice1 = series->slices().at(1);
                 slice1->setBrush(QColor(232, 215, 198));
                 slice1->setLabelVisible();
             }
             if(PRICE2!=0)
             {
                 QPieSlice *slice2 = series->slices().at(2);
                  slice2->setBrush(QColor("#C29E7E")); // Utilisation de la valeur hexadécimale
                  slice2->setLabelVisible();
             }
                     QChart *chart = new QChart();
                         chart->addSeries(series);
                         chart->setTitle("");
                        chart->setBackgroundVisible(false);
                     chart->setVisible(true);
                     chart->legend()->setAlignment(Qt::AlignBottom);
                     QChartView *chartView = new QChartView(chart);
                     chartView->setRenderHint(QPainter::Antialiasing);
                     QPalette pal = qApp->palette();
                     chartView->setMaximumWidth(741);
                     chartView->setMaximumHeight(451);
                     chartView->setMinimumWidth(741);
                     chartView->setMinimumHeight(451);
                     chartView->setParent(ui->label_stat_oeuvre);
                     chartView->show();

}

void ArtNexus::on_returnOvrBtn_2_clicked()
{
     ui->stackedWidget_4->setCurrentIndex(0);
}



/************************************************************PARTIE EMPLOYE **************************************************************/

void ArtNexus::on_confirmer_clicked() {
    // Récupérer les valeurs des champs de saisie
    int id_e = ui->id->text().toInt();
    QString nom_e = ui->nom->text();
    QString prenom_e = ui->prenom->text();
    QString tel_e_str = ui->telephone->text();
    QString salaire_e_str = ui->salaire->text();
    QString role_e = ui->role->text();
    QDate debut_conge = ui->debut_conge->date();
    QDate fin_conge = ui->fin_conge->date();
    QString email = ui->email->text();
    QString mdp = ui->mdp->text();

    // Définition des expressions régulières pour la validation
    QRegExp telRegex("\\d{8}"); // Un numéro de téléphone français à 10 chiffres
    QRegExp emailRegex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}"); // Validation d'une adresse email

    // Vérification des champs
    QString invalidFields;
    if (nom_e.isEmpty()) {
        invalidFields += "Nom, ";
    }
    if (prenom_e.isEmpty()) {
        invalidFields += "Prénom, ";
    }
    if (!telRegex.exactMatch(tel_e_str)) {
        invalidFields += "Téléphone, ";
    }
    if (salaire_e_str.toInt() <= 0) {
        invalidFields += "Salaire, ";
    }
    if (debut_conge > fin_conge) {
        invalidFields += "Dates de congé, ";
    }
    if (!emailRegex.exactMatch(email)) {
        invalidFields += "Email, ";
    }

    if (!invalidFields.isEmpty()) {
        invalidFields.chop(2); // Supprimer la virgule et l'espace en trop à la fin
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"),
                             QObject::tr("Veuillez vérifier les champs suivants : %1").arg(invalidFields),
                             QMessageBox::Cancel);
        return;
    }

    // Créer un nouvel employé et l'ajouter
    Employe* e = new Employe(id_e, nom_e, prenom_e, tel_e_str.toInt(), salaire_e_str.toInt(), role_e, debut_conge, fin_conge, email, mdp);
    bool test = e->ajouter();

    if (test) {
        ui->tableView_emp->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué avec succès\nCliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Ajout non effectué\nCliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

void ArtNexus::on_SUPPRIMER_clicked() {
    int id_e = ui->id_a_supp->text().toInt();
    bool test = Etmp.supprimer(id_e);
    if (test) {
        ui->tableView_emp->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuee\nCliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Suppression non effectuee\nCliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

void ArtNexus::on_confirmer_update_clicked() {
    // Vérifier la saisie avant de continuer
    // (code de validation à insérer ici)

    // Récupérer les valeurs des champs de saisie
    int id_e = ui->id_update->text().toInt();
    QString nom_e = ui->nom_update->text();
    QString prenom_e = ui->prenom_update->text();
    QString tel_e_str = ui->telephone_update->text();
    QString salaire_e_str = ui->salaire_update->text();
    QString role_e = ui->role_update->text();
    QDate debut_conge = ui->debut_conge->date();
    QDate fin_conge = ui->fin_conge_update->date();
    QString email = ui->email_update->text();
    QString mdp = ui->mdp_update->text();

    // Créer un employé avec les nouvelles valeurs
    Employe e(id_e, nom_e, prenom_e, tel_e_str.toInt(), salaire_e_str.toInt(), role_e, debut_conge, fin_conge, email, mdp);
    bool test = e.modifier(id_e);

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Update"),
                                 QObject::tr("Update successful.\nClick OK to return."),
                                 QMessageBox::Ok);

        // Effacer les champs après la modification
        ui->id_update->clear();
        ui->nom_update->clear();
        ui->prenom_update->clear();
        ui->telephone_update->clear();
        ui->salaire_update->clear();
        ui->role_update->clear();
        ui->debut_conge->clear();
        ui->fin_conge_update->clear();
        ui->email_update->clear();
        ui->mdp_update->clear();

        ui->tableView_emp->setModel(Etmp.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Update"),
                              QObject::tr("Update failed.\nClick OK to return."),
                              QMessageBox::Ok);
    }
}

void ArtNexus::on_modifier_3_clicked() {
    QModelIndexList selectedIndexes = ui->tableView_emp->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }

    ui->stackedWidget_5->setCurrentIndex(1);
}

void ArtNexus::on_tableView_emp_clicked(const QModelIndex &index) {
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView_emp->model()->data(in).toString();
    QSqlQuery qry;
    qry.prepare("select id_e,nom_e,prenom_e,tel_e,salaire_e,role_e,debut_conge,fin_conge,email,mdp from EMPLOYE where id_e='"+val+"' " );
    if(qry.exec()) {
        while(qry.next()) {
            ui->id_update->setText(qry.value(0).toString());
            ui->nom_update->setText(qry.value(1).toString());
            ui->prenom_update->setText(qry.value(2).toString());
            ui->telephone_update->setText(qry.value(3).toString());
            ui->salaire_update->setText(qry.value(4).toString());
            ui->role_update->setText(qry.value(6).toString());
                    ui->debut_conge_update->setDate(qry.value(5).toDate());
                    ui->fin_conge_update->setDate(qry.value(7).toDate());
                    ui->email_update->setText(qry.value(0).toString());
                    ui->mdp_update->setText(qry.value(0).toString());

                }
    }
}


void ArtNexus::on_pb_add_employe_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(3);

}

void ArtNexus::on_pb_update_employe_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(1);

}

void ArtNexus::on_pb_delete_employe_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(2);

}


void ArtNexus::on_pb_list_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);

}


void ArtNexus::on_pb_add_employe_2_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(3);

}

void ArtNexus::on_pb_delete_employe_2_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(2);

}

void ArtNexus::on_pb_list_2_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);

}

void ArtNexus::on_pb_add_employe_3_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(3);

}

void ArtNexus::on_pb_update_employe_2_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(1);

}


void ArtNexus::on_liste_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);

}


void ArtNexus::on_pb_update_employe_3_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(1);

}

void ArtNexus::on_pb_delete_employe_3_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(2);

}

void ArtNexus::on_tri_clicked()
{
    ui->tableView_emp->setModel(Etmp
                            .tri());

}

void ArtNexus::on_recherche_emp_clicked()
{

        // Get the search string from the line edit
           QString searchStr = ui->a_rechercher->text().trimmed();

           // Check if the search string is not empty
           if (!searchStr.isEmpty()) {
               // Create a filter for the SQL query
               QString filter = QString("nom_e LIKE '%%1%' OR id_e LIKE '%%1%' OR prenom_e LIKE '%%1%' OR tel_e LIKE '%%1%' OR salaire_e LIKE '%%1%' OR role_e LIKE '%%1%' OR debut_conge LIKE '%%1%' OR fin_conge LIKE '%%1%' OR email LIKE '%%1%' OR mdp LIKE '%%1%'")
                                    .arg(searchStr);

               // Apply the filter to the SQL query
               QSqlQueryModel *filteredModel = new QSqlQueryModel();
               filteredModel->setQuery("SELECT id_e, nom_e, prenom_e, tel_e, salaire_e, role_e, debut_conge, fin_conge, email, mdp FROM employe WHERE " + filter);

               // Set the filtered model to the table view
               ui->tableView_emp->setModel(filteredModel);

               // Update the view
               ui->tableView_emp->update();
           } else {
               // If the search string is empty, display all data
               ui->tableView_emp->setModel(Etmp.afficher());
           }

}

void ArtNexus::on_pdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

          if (!filePath.isEmpty()) {
              QPrinter printer(QPrinter::PrinterResolution);
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName(filePath);

              // Set the resolution for the printer, not the QPainter
              printer.setResolution(100);

              QPainter painter(&printer);

              // Remove the following line as setResolution is now applied to QPrinter
              // painter.setResolution(1200);

              ui->tableView_emp->render(&painter);

              QMessageBox::information(this, "Export PDF", "PDF file exported successfully.");
          }
}








void ArtNexus::on_artistes_clicked()
{
     ui->stackedWidget_ALL->setCurrentIndex(1);
}

void ArtNexus::on_ouevres_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(3);
}

void ArtNexus::on_associations_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(2);
}

void ArtNexus::on_events_clicked()
{
    ui->stackedWidget_ALL->setCurrentIndex(0);
}







