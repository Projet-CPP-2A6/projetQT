#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "association.h"
#include <QMessageBox>
#include <QtDebug>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExpValidator *phoneValidator = new QRegExpValidator(QRegExp("[0-9]{8}"));
        ui->telA->setValidator(phoneValidator);  // Set the validator for the telA field
    ui->tableView->setModel(Ctemp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_AjoutButton_clicked()
{
    // Move to the next page in the stacked widget (Ajout page)
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableView->setModel(Ctemp.afficher());

}

void MainWindow::on_ModifierButton_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(Ctemp.afficher());

}
void MainWindow::on_BackAjout_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setModel(Ctemp.afficher());

}
void MainWindow::on_BackSupprimer_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setModel(Ctemp.afficher());

}
void MainWindow::on_SupprimerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_BackModifier_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setModel(Ctemp.afficher());

}


void MainWindow::on_validerAjout_clicked()
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
           ui->tableView->setModel(Ctemp.afficher());
ui->stackedWidget->setCurrentIndex(0);
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

void MainWindow::on_validerModifier_clicked()
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
        ui->tableView->setModel(association.afficher());
    } else {
        msgBox.setText("Echec de Modification. Veuillez consulter la console pour plus de détails.");
    }

    msgBox.exec();
}

void MainWindow::on_ValiderSupprimer_clicked()
{
        QMessageBox msgBox;

        // Retrieve the client ID from the QLineEdit widget
        int id = ui->idS->text().toInt();
        bool test = Ctemp.supprimer(id);

        if(test)
        {
            ui->tableView->setModel(Ctemp.afficher());
            msgBox.setText("Suppression réussie pour le CIN : " + QString::number(id));
        }
        else
        {
            msgBox.setText("Échec de suppression pour le CIN : " + QString::number(id) + ". Vérifiez les erreurs.");

            // Retrieve the error message from the QSqlQuery object

        }

        msgBox.exec();



}

void MainWindow::on_pushButton_13_clicked()
{
    ui->tableView->setModel(Ctemp.tri());
}


void MainWindow::on_recherche_clicked()
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
                ui->tableView->setModel(filteredModel);
                // Update the view
                ui->tableView->update();
            } else {
                // If the search string is empty, display all data
                ui->tableView->setModel(Ctemp.afficher()); }
}





void MainWindow::on_pushButton_12_clicked()
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
