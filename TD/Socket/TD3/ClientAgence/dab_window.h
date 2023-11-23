#ifndef DAB_WINDOW_H
#define DAB_WINDOW_H

#include <QWidget>
#include  <QTcpSocket>
#include <QRadioButton>

#include "vol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DAB_Window; }
QT_END_NAMESPACE

class DAB_Window : public QWidget
{
    Q_OBJECT

public:
    DAB_Window(QWidget *parent = nullptr);
    ~DAB_Window();

private slots:
    void on_pushButtonConnexion_clicked();

    void on_pushButtonValider_clicked();

private:
    Ui::DAB_Window *ui;

    QRadioButton places[15];

    QTcpSocket *socketClientAgence;

    void onQTcpSocket_connected();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError);

    void mettreAJourVols(QList<vol> lesVols);
    void mettreAJourOccupation(QList<int> placesOccupees);
    void demanderPlacesDisponibles(int ref);
    void reserver(int ref, int place, QString nom, QString prenom, QString email);

    void onQComboBox_currentIndexChanged(int index);
};
#endif // DAB_WINDOW_H
