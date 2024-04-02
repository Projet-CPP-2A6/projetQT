#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "association.h"
#include "statdialog.h"
#include "chatbox.h"
#include <QMessageBox>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QModelIndex>
#include <QSqlRecord>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExpValidator *phoneValidator = new QRegExpValidator(QRegExp("[0-9]{8}"));
        ui->telA->setValidator(phoneValidator);  // Set the validator for the telA field
    ui->tableView->setModel(Ctemp.afficher());
    connect(ui->tableView2, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_messagePreviewClicked(const QModelIndex &)));
    // Assuming you have a combobox named sortComboBox in your UI
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::sortData);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::sortData(int index) {
    // Get the selected column name from the combobox
    QString columnName = ui->sortComboBox->itemText(index);

    // Sort the data by the selected column
    ui->tableView->setModel(Ctemp.tri(columnName));
}



void MainWindow::on_AjoutButton_clicked()
{
    // Move to the next page in the stacked widget (Ajout page)
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(Ctemp.afficher());

}

void MainWindow::on_ModifierButton_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableView->setModel(Ctemp.afficher());

}
void MainWindow::on_BackAjout_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableView->setModel(Ctemp.afficher());

}
void MainWindow::on_BackSupprimer_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableView->setModel(Ctemp.afficher());

}
void MainWindow::on_SupprimerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_BackModifier_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(1);
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
    QStringList validDomains = {"sante", "environnement", "social"};
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
    // Get the selected column name from the combobox
    QString columnName = ui->sortComboBox->currentText();

    // Sort the data by the selected column
    ui->tableView->setModel(Ctemp.tri(columnName));
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

void MainWindow::on_pushButton_14_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT domaine_association, SUM(montant_association) FROM associations GROUP BY domaine_association");
    if (query.exec())
    {
        QMap<QString, double> totalMontantPerDomain;

        while (query.next())
        {
            QString domain = query.value(0).toString();
            double montant = query.value(1).toDouble();
            totalMontantPerDomain[domain] = montant;
        }

        double totalMontant = 0.0;
        for (auto it = totalMontantPerDomain.begin(); it != totalMontantPerDomain.end(); ++it)
        {
            totalMontant += it.value();
        }

        QMap<QString, double> percentagePerDomain;
        for (auto it = totalMontantPerDomain.begin(); it != totalMontantPerDomain.end(); ++it)
        {
            QString domain = it.key();
            double montant = it.value();
            double percentage = (montant / totalMontant) * 100.0;
            percentagePerDomain[domain] = percentage;
        }

        Dialog *dialog = new class Dialog(this);
        dialog->setChartData(percentagePerDomain);
        dialog->exec();
    }
}





void MainWindow::on_pbps_clicked()
{
    // Fetch data from the database
    QSqlQuery query;
    query.prepare("SELECT domaine_association, montant_association FROM associations");
    if (query.exec())
    {
        QVector<double> montantData;
        QVector<QString> domaineData;

        while (query.next())
        {
            double montant = query.value(1).toDouble();
            QString domaine = query.value(0).toString();
            montantData.append(montant);
            domaineData.append(domaine);
        }

        // Perform linear regression
        // Your linear regression code goes here
        // You'll need to use montantData and domaineData to perform the regression
        // Once you have the predictive data, you can display it using the Dialog class

        Dialog *dialog = new Dialog(this);
        dialog->setPredictiveChartData(); // Call the method to set predictive data
        dialog->exec();
    }
}





void MainWindow::on_pushButton_11_clicked()
{
    // Retrieve email and password from input fields
        QString email = ui->nom->text();
        QString password = ui->mdp->text();

        // Check if email and password are not empty
        if (email.isEmpty() || password.isEmpty()) {
            QMessageBox::critical(this, "Error", "Email and password are required.");
            return;
        }

        // Perform login verification
        Association association;
        int result = association.login(email, password);

        // Check the result of the login attempt
        if (result > 0) {
            // Successful login
            QMessageBox::information(this, "Success", "Login successful.");
            // Move to the appropriate page after successful login
            ui->stackedWidget->setCurrentIndex(1); // Change index according to your application flow
            // Retrieve and display messages for the logged-in user
            displayReceivedMessages(email);
        } else {
            // Failed login
            QMessageBox::critical(this, "Error", "Invalid email or password.");
        }
}

//messagerie (chat Box)





void MainWindow::on_pushButton_send_clicked()
{
    QString receiver = ui->lineEdit_receiver->text();
    QString messageContent = ui->lineEdit_send->text();
    QString sender = ui->nom->text(); // Assuming 'nom' is the logged-in user's name
    Message m(sender, receiver, messageContent);
    bool success = m.sendmsg(sender, receiver); // Pass sender and receiver info

    if (success) {
        // Message sent successfully
        ui->lineEdit_send->clear();
        QMessageBox::information(this, "Success", "Message sent successfully.");

        // Update the conversation view with the latest messages
        displayReceivedMessages(receiver);

        // Immediately display the sent message in the chatbox
        QString formattedMessage = QString("<div align='right' style='color: blue;'>[%1] %2: %3</div>")
                                        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), sender, messageContent);
        ui->chatbox->append(formattedMessage);
    } else {
        // Failed to send message
        QMessageBox::critical(this, "Error", "Failed to send message. Please try again.");
    }
}


void MainWindow::on_ChatBoxButton_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableView->setModel(Ctemp.afficher());
}
void MainWindow::displayReceivedMessages(QString receiver) {
    Message messageModel;
    QSqlQueryModel *receivedMessages = messageModel.retrieveMessages(receiver);

    // Get the existing model from tableView2
    QAbstractItemModel *existingModel = ui->tableView2->model();

    if (existingModel) {
        // Iterate through each received message and update the corresponding preview message in the existing model
        for (int row = 0; row < receivedMessages->rowCount(); ++row) {
            QString sender = receivedMessages->record(row).value("sender").toString();
            QString message = receivedMessages->record(row).value("msg").toString();
            QString timestamp = receivedMessages->record(row).value("timestamp").toString();

            // Check if the sender already exists in the tableView2 model
            QModelIndexList matchList = existingModel->match(existingModel->index(0, 1), Qt::DisplayRole, sender);
            if (!matchList.isEmpty()) {
                // Update the last message and timestamp in the corresponding row
                int rowToUpdate = matchList.first().row();
                existingModel->setData(existingModel->index(rowToUpdate, 2), message); // Update msg column
                existingModel->setData(existingModel->index(rowToUpdate, 3), timestamp); // Update timestamp column
            } else {
                // Add a new row for the sender if not found
                int rowCount = existingModel->rowCount();
                existingModel->insertRow(rowCount);
                existingModel->setData(existingModel->index(rowCount, 1), sender); // Insert sender name
                existingModel->setData(existingModel->index(rowCount, 2), message); // Insert last message
                existingModel->setData(existingModel->index(rowCount, 3), timestamp); // Insert timestamp
            }
        }

        // Cleanup: Delete the receivedMessages model to avoid memory leaks
        delete receivedMessages;
    } else {
        // Set the model to the tableView2 if it's empty
        ui->tableView2->setModel(receivedMessages);
    }

    // Resize the columns to fit the content
    ui->tableView2->resizeColumnsToContents();
}





// Assuming ui->chatbox is a QTextBrowser widget

void MainWindow::on_messagePreviewClicked(const QModelIndex &index)
{
    QString receiver = ui->lineEdit_receiver->text();
    QString sender = ui->nom->text(); // Assuming 'nom' is the logged-in user's name

    // Retrieve the sender and receiver from the clicked item in tableView2
    QString otherParty = index.data(Qt::DisplayRole).toString();

    // Retrieve all messages between the sender and receiver
    Message messageModel;
    QSqlQueryModel *conversation = messageModel.retrieveFullConversation(sender, otherParty);

    if (conversation) {
        // Clear the chatbox before displaying the conversation
        ui->chatbox->clear();

        // Iterate through each message in the conversation and append it to the chatbox
        for (int i = 0; i < conversation->rowCount(); ++i)
        {
            QString messageSender = conversation->record(i).value("sender").toString();
            QString message = conversation->record(i).value("msg").toString();
            QString timestamp = conversation->record(i).value("timestamp").toString();

            // Format the message based on sender
            QString formattedMessage;
            if (messageSender == sender) {
                // Sent message
                formattedMessage = QString("<div align='right' style='color: blue;'>[%1] %2: %3</div>").arg(timestamp, messageSender, message);
            } else {
                // Received message
                formattedMessage = QString("<div align='left'>[%1] %2: %3</div>").arg(timestamp, messageSender, message);
            }

            // Append the formatted message to the chatbox
            ui->chatbox->append(formattedMessage);
        }

        // Cleanup: Delete the QSqlQueryModel to avoid memory leaks
        delete conversation;
    } else {
        // Handle the case where no conversation is found
        QMessageBox::information(this, "No Conversation", "No conversation found between the two parties.");
    }
}


void MainWindow::on_BackSupprimer_2_clicked()
{
    // Move to the previous page in the stacked widget (Page Gestion)
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableView->setModel(Ctemp.afficher());
}





