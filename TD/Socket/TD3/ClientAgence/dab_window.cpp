#include "dab_window.h"
#include "ui_dab_window.h"

#include <QBuffer>

DAB_Window::DAB_Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DAB_Window)
{
    ui->setupUi(this);

    // ajout des places disponibles
    // dans le layout correspondant
    int index=0;
    for(int ligne=1;ligne<4;ligne++)
    {
        for(int colonne=1;colonne<6;colonne++)
        {
            places[index].setText(QString::number(index+1));
            ui->gridLayout->addWidget(&places[index],ligne,colonne);
            index++;
        }
    }

    socketClientAgence = new QTcpSocket(this);

    connect(socketClientAgence, &QTcpSocket::connected,
            this, &DAB_Window::onQTcpSocket_connected);
    connect(socketClientAgence, &QTcpSocket::disconnected,
            this, &DAB_Window::onQTcpSocket_disconnected);
    connect(socketClientAgence, &QTcpSocket::readyRead,
            this, &DAB_Window::onQTcpSocket_readyRead);
    connect(socketClientAgence, &QTcpSocket::errorOccurred,
            this, &DAB_Window::onQTcpSocket_errorOccured);

    ui->lineEditAdresse->insert("172.18.58.104");
}

DAB_Window::~DAB_Window()
{
    delete socketClientAgence;
    delete ui;
}


void DAB_Window::on_pushButtonConnexion_clicked()
{
    if (ui->pushButtonConnexion->text() == "Connexion")
    {
        socketClientAgence->connectToHost(ui->lineEditAdresse->text(), ui->spinBoxPort->value());
    }
    else
    {
        socketClientAgence->disconnectFromHost();
    }
}


void DAB_Window::on_pushButtonValider_clicked()
{
    QList <QRadioButton *>radios=this->findChildren<QRadioButton*>();
    int numeroPlace=-1;
    // récupérer la référence du vol
    int referenceVol=ui->comboBoxVols->itemData(ui->comboBoxVols->currentIndex()).toInt();

    // récupérer le numéro de siège coché
    foreach (QRadioButton *rad, radios) {
        if (rad->isChecked()){
            numeroPlace=rad->text().toInt();
        }
    }
    // si un siège est coché, faire la réservation auprès du serveur
    if (numeroPlace!=-1)
    {
        reserver(referenceVol, numeroPlace,
                 ui->lineEditNom->text(), ui->lineEditPrenom->text(), ui->lineEditEmail->text());
    }
}

void DAB_Window::onQTcpSocket_connected()
{
    ui->textEditEtat->append("Connecté au serveur : " + ui->lineEditAdresse->text());
    ui->groupBoxConnexion->setEnabled(false);
    ui->groupBoxInteraction->setEnabled(true);
}

void DAB_Window::onQTcpSocket_disconnected()
{
    ui->textEditEtat->append("Déconnecté du serveur : " + ui->lineEditAdresse->text());
    ui->groupBoxConnexion->setEnabled(true);
    ui->groupBoxInteraction->setEnabled(false);
}

void DAB_Window::onQTcpSocket_readyRead()
{
    quint16 taille=0;
    QChar commande;
    QList <vol> vols;
    QList <int> listePlaces;
    // Il y a au moins le champs taille d'arrive
    if (socketClientAgence->bytesAvailable() >= (qint64)sizeof(taille))
    {
        // Lecture de la taille de la trame
        QDataStream in(socketClientAgence);
        in >> taille;
        // Le reste de la trame est disponible
        if (socketClientAgence->bytesAvailable() >= (qint64)taille)
        {
            // Lecture de la commande
            in>>commande;
            switch (commande.toLatin1()) {
            case 'V':
                // Lecture de la liste des vols
                in>>vols;

                mettreAJourVols(vols);
                demanderPlacesDisponibles(vols.at(0).reference);
                break;

            case 'P':
                // Lecture de la liste des places
                in >> listePlaces;

                mettreAJourOccupation(listePlaces);
                break;
            }
        }
    }

}

void DAB_Window::onQTcpSocket_errorOccured(QAbstractSocket::SocketError socketError)
{
    ui->textEditEtat->append("errorOccured");
}

void DAB_Window::mettreAJourVols(QList<vol> lesVols)
{
    // Si la gestion de la comboBox existe dèjà, la désactiver
    if (ui->comboBoxVols->metaObject()->indexOfSignal(QMetaObject::normalizedSignature("currentIndexChanged(int)")) != -1
            &&
            metaObject()->indexOfSlot(QMetaObject::normalizedSignature("onQComboBox_currentIndexChanged(int)")) != -1)
    {
        disconnect(ui->comboBoxVols,
                   &QComboBox::currentIndexChanged,
                   this,
                   &DAB_Window::onQComboBox_currentIndexChanged);
    }
    // vider la liste des vols
    ui->comboBoxVols->clear();
    // remplir la liste des vols
    foreach (vol v, lesVols) {
        ui->comboBoxVols->addItem(v.denomination,v.reference);
    }
    // gérer le changement d'index dans la comboBoxVolsDisponibles
    connect(ui->comboBoxVols,
            &QComboBox::currentIndexChanged,
            this,
            &DAB_Window::onQComboBox_currentIndexChanged);
}

void DAB_Window::mettreAJourOccupation(QList<int> placesOccupees)
{
    qDebug()<<"places occupees : "<<placesOccupees;
    for (int i=0;i<15;i++)
    {
        places[i].setAutoExclusive(false);
        if (placesOccupees.contains(i+1))
        {
            places[i].setEnabled(false);
            places[i].setChecked(false);
            places[i].setStyleSheet("background-color: grey");
        }
        else
        {
            places[i].setEnabled(true);
            places[i].setChecked(false);
            places[i].setStyleSheet("background-color: white");
        }
        places[i].setAutoExclusive(true);
    }
}

void DAB_Window::demanderPlacesDisponibles(int ref)
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('P');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<ref;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    socketClientAgence->write(tampon.buffer());
}

void DAB_Window::reserver(int ref, int place, QString nom, QString prenom, QString email)
{
    quint16 taille=0;
    QBuffer tampon;
    QChar commande('R');
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out(&tampon);
    // construction de la trame
    out<<taille<<commande<<ref<<place<<nom<<prenom<<email;
    // calcul de la taille de la trame
    taille=(static_cast<quint16>(tampon.size()))-sizeof(taille);
    // placement sur la premiere position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    //modification de la trame avec la taille reel de la trame
    out << taille;
    // envoi du QByteArray du tampon via la socket
    socketClientAgence->write(tampon.buffer());
}

void DAB_Window::onQComboBox_currentIndexChanged(int index)
{
    // récupérer la référence du vol
    // ATTENTION index n'est pas la référence,
    // mais la position dans la liste
    int referenceVol=ui->comboBoxVols->itemData(index).toInt();
    // demander au serveur les places pour le vol sélectionné
    demanderPlacesDisponibles(referenceVol);
}
