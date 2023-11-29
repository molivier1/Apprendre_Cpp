#include "client.h"

Client::Client()
{

}

int Client::getReferenceVol() const
{
    return referenceVol;
}

void Client::setReferenceVol(int newReferenceVol)
{
    referenceVol = newReferenceVol;
}

int Client::getNumeroPlace() const
{
    return numeroPlace;
}

void Client::setNumeroPlace(int newNumeroPlace)
{
    numeroPlace = newNumeroPlace;
}

const QString &Client::getNom() const
{
    return nom;
}

void Client::setNom(const QString &newNom)
{
    nom = newNom;
}

const QString &Client::getPrenom() const
{
    return prenom;
}

void Client::setPrenom(const QString &newPrenom)
{
    prenom = newPrenom;
}

const QString &Client::getEmail() const
{
    return email;
}

void Client::setEmail(const QString &newEmail)
{
    email = newEmail;
}

QTcpSocket *Client::getSockClient() const
{
    return sockClient;
}

void Client::setSockClient(QTcpSocket *newSockClient)
{
    sockClient = newSockClient;
}
