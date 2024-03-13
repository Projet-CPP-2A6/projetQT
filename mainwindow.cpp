#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_confirmer_clicked() {
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
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué avec succès\nCliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Ajout non effectué\nCliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_SUPPRIMER_clicked() {
    int id_e = ui->id_a_supp->text().toInt();
    bool test = Etmp.supprimer(id_e);
    if (test) {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuee\nCliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Suppression non effectuee\nCliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_confirmer_update_clicked() {
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

        ui->tableView->setModel(Etmp.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Update"),
                              QObject::tr("Update failed.\nClick OK to return."),
                              QMessageBox::Ok);
    }
}

void MainWindow::on_modifier_3_clicked() {
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                             QObject::tr("Please select an item to update."),
                             QMessageBox::Ok);
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();
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


void MainWindow::on_pb_add_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_pb_update_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pb_delete_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_pb_list_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pb_add_employe_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_pb_delete_employe_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_pb_list_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pb_add_employe_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_pb_update_employe_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_liste_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pb_update_employe_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pb_delete_employe_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_tri_clicked()
{
    ui->tableView->setModel(Etmp
                            .tri());

}

void MainWindow::on_recherche_clicked()
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
               ui->tableView->setModel(filteredModel);

               // Update the view
               ui->tableView->update();
           } else {
               // If the search string is empty, display all data
               ui->tableView->setModel(Etmp.afficher());
           }

}

void MainWindow::on_pdf_clicked()
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
