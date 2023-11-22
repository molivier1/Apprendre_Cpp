#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QDataStream>
#include <QPointF>


#include "experience.h"

Experience::Experience(QObject *parent) : QObject(parent)
  , vitesseMaxi(0)
  , nbEchantillons(0)
  , origine(0)
  , vitesse(0)
  , mesuresBrutes(nullptr)
{
    LireFichierIni();
}

void Experience::LireFichierIni()
{
    QString nomFichierIni = "equilibreuse.ini";
    QFileInfo fichierIni(nomFichierIni);
    if (fichierIni.exists() && fichierIni.isFile())
    {
        // à compléter la lecture du fichier
    }
    else
    {
        // si le fichier n’existe pas, il est créé avec les valeurs par défaut
        // il est ensuite enregistré
    }
}

void Experience::EnregistreFichierIni(const typePalier _paliers[])
{
    // à compléter l’enregistrement du fichier
}

typePalier *Experience::ObtenirCarateristiquesPaliers()
{
    return paliers;
}

void Experience::LireMesuresBrutes(QString &_nomFichier)
{
    // à completer dans le TD2
    QFile file(_nomFichier);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Le fichier " << _nomFichier << " ne veut pas s'ouvrir";
    }
    else
    {
        quint16 nbAcquisition;
        QDataStream flux(&file);
        flux >> nbAcquisition;
        if(nbAcquisition== 0){
            flux >> nbAcquisition;
        }
        flux >> vitesse >> origine;
        if(nbAcquisition != nbEchantillons && mesuresBrutes != nullptr){
            delete[] mesuresBrutes;
            mesuresBrutes = nullptr;
        }
        nbEchantillons = nbAcquisition;
        if(mesuresBrutes == nullptr){
            mesuresBrutes = new double[nbEchantillons];
        }
        for(int i = 0; i < nbEchantillons; i++){
            flux >> mesuresBrutes[i];
        }
        file.close();
    }
}

void Experience::InitiliserCourbes()
{
    int indiceFin = nbEchantillons / 2 ;
    int indiceA = 0;
    int indiceO = nbEchantillons /2 ;

    courbeA.clear();
    courbeO.clear();
    PointDeCourbe unPoint;
    for(int i = 0 ; i < indiceFin ; i++)
    {
        unPoint.setX(i);
        unPoint.setY(mesuresBrutes[indiceA++]);
        courbeA.append(unPoint);
        unPoint.setY(mesuresBrutes[indiceO++]);
        courbeO.append(unPoint);
    }
}

QList<QPointF> *Experience::ObtenirCourbeA()
{
    return (QList<QPointF>*) &courbeA;
}

QList<QPointF> *Experience::ObtenirCourbeO()
{
    return (QList<QPointF>*) &courbeO;
}

void Experience::ObtenirTypeAffichage(bool &_newton, bool &_pointCodeur)
{
    _newton = false;
    _pointCodeur = true;
}

/**
 * @brief Experience::RechercherEffortMax
 * @param courbe définit sur qu'elle courbe la recherche est effectuée 'A' ou 'O'
 * @return Le point possedant la valeur de l'effort le plus grand
 * @details Recherche le point dont l'amplitude est la plus grande sur l'une des 2 courbes.
 */
QPointF Experience::RechercherEffortMax(QChar courbe)
{
    QList<PointDeCourbe> *laCourbe = &courbeO;
    if(courbe =='A')
        laCourbe = &courbeA;

    QList<PointDeCourbe>::iterator max = std::max_element(laCourbe->begin(), laCourbe->end());
    return *max;
}

/**
 * @brief Experience::RechercherEffortAzero
 * @param courbe définit sur qu'elle courbe la recherche est effectuée 'A' ou 'O'
 * @return la valeur de l'effort pour à l'origine de la courbe
 */
double Experience::RechercherEffortAzero(QChar courbe)
{
    QList<PointDeCourbe> *laCourbe = &courbeO;
    if(courbe =='A')
        laCourbe = &courbeA;
    return laCourbe->at(0).y();
}

/**
 * @brief Experience::RechercherEffortAquatreVingtDix
 * @param courbe définit sur qu'elle courbe la recherche est effectuée 'A' ou 'O'
 * @return la valeur de l'effort à 90°
 */
double Experience::RechercherEffortAquatreVingtDix(QChar courbe)
{
    QList<PointDeCourbe> *laCourbe = &courbeO;
    if(courbe =='A')
        laCourbe = &courbeA;
    return laCourbe->at(250).y();   // 90° * 1000 ptsCodeur / 360°
}

/**
 * @brief Experience::ObtenirVitesse
 * @return La vitesse de l'expérience courante
 */
qint16 Experience::ObtenirVitesse()
{
    return vitesse;
}
