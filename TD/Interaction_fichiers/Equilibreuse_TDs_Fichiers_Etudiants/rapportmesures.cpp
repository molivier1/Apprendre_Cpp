#include "rapportmesures.h"


RapportMesures::RapportMesures(Experience &_experience, QChartView &_graphique, const QString &_nomDuFichier):
    QPdfWriter(_nomDuFichier), graphique(_graphique), experience(_experience)
{
    setPageSize(QPageSize(QPageSize::A4));
    setPageOrientation(QPageLayout::Portrait);
    setResolution(150);
    largeurPdf = width();
    hauteurPdf = height();
    qDebug() << "largeur : " << largeurPdf;
    qDebug() << "hauteur : " << hauteurPdf;
}

void RapportMesures::ConstruireRapport()
{

}

