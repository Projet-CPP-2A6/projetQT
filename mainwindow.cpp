#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#define file_tx "^[A-Za-z ]+$"
#define file_ex "^[0-9]+$"
#include <QtLocation>
#include <QSqlRecord>
#include <QResource>
#include <iostream>
#include <QRegularExpression>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include "artiste.h"
#include "qrcode.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#define file_tx "^[A-Za-z ]+$"
#define file_ex "^[0-9]+$"
#include <QtLocation>
#include <QSqlRecord>
#include <QResource>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <iostream>
#include <QPainter>
#include <QLineEdit>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tri_r, &QPushButton::clicked, this, &MainWindow::on_tri_r_clicked);
connect(ui->historique_r, &QPushButton::clicked, this, &MainWindow::on_historique_r_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::controlSaisie()
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

void MainWindow::on_add_r_clicked()
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

void MainWindow::on_update_r_clicked()
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

void MainWindow::on_delete_r_clicked()
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

void MainWindow::on_next_r_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableArtiste->setModel(art.GETALL());
}

void MainWindow::on_tableArtiste_activated(const QModelIndex &index)
{
    ui->tableArtiste->setModel(art.GETALL());

}

void MainWindow::on_back_r_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_search_bouton_clicked()
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

void MainWindow::on_search_bouton_2_clicked()
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


void MainWindow::on_tri_r_clicked()
{
    ui->tableArtiste->setModel(art.triNom());
}

void MainWindow::on_pdf_r_clicked()
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

void MainWindow::on_qrcode_clicked()
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
        ui->qr_code->setPixmap(QPixmap::fromImage(im.scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));;
    } else {
        QMessageBox::information(this, "Erreur", "L'ID de l'artiste n'existe pas dans la base de données.");
    }
}
void MainWindow::afficherGraphiqueCirculaire_2(QMap<QString, int> statistiques)
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

void MainWindow::on_stat_r_clicked()
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

void MainWindow::on_tri_r_id_clicked()
{
    ui->tableArtiste->setModel(art.triId());
}


void MainWindow::on_tri_r_id_2_clicked()
{
    ui->tableArtiste->setModel(art.triNat());
}

void MainWindow::on_historique_r_clicked()
{
    QString filePath = "backup_artiste.txt";

        // Ouvrir le fichier en utilisant le programme par défaut associé aux fichiers texte
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
