#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client
{
public:
    Client();

    int getReferenceVol() const;
    void setReferenceVol(int newReferenceVol);
    int getNumeroPlace() const;
    void setNumeroPlace(int newNumeroPlace);
    const QString &getNom() const;
    void setNom(const QString &newNom);
    const QString &getPrenom() const;
    void setPrenom(const QString &newPrenom);
    const QString &getEmail() const;
    void setEmail(const QString &newEmail);
    QTcpSocket *getSockClient() const;
    void setSockClient(QTcpSocket *newSockClient);

private:

    int referenceVol;
    int numeroPlace;
    QString nom;
    QString prenom;
    QString email;
    QTcpSocket *sockClient;
};

#endif // CLIENT_H
