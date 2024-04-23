#ifndef ARDUINOAFFICHER_H
#define ARDUINOAFFICHER_H

#include "arduino.h"

#include <QDialog>

namespace Ui {
class arduinoafficher;
}

class arduinoafficher : public QDialog
{
    Q_OBJECT

public:
    explicit arduinoafficher(QWidget *parent = nullptr);
    ~arduinoafficher();

private:
    Ui::arduinoafficher *ui;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
private slots:
    void update_label();
    void on_onlcd_clicked();
    void on_offlcd_clicked();
};

#endif // ARDUINOAFFICHER_H
