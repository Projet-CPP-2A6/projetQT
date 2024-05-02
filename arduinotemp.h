#ifndef ARDUINOTEMP_H
#define ARDUINOTEMP_H

#include "arduino.h"
#include <QDialog>

namespace Ui {
class arduinotemp;
}

class arduinotemp : public QDialog
{
    Q_OBJECT

public:
    explicit arduinotemp(QWidget *parent = nullptr);
    ~arduinotemp();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::arduinotemp *ui;
    QTimer *timer;
    int i  = 0 ;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire

    void update_label(); // Declaring update_label as a private member function
    void displayArtworks(const QStringList &artworks); // Declaring displayArtworks as a private member function
    void update_label2(); // Function to update label_etat2

};

#endif // ARDUINOTEMP_H
