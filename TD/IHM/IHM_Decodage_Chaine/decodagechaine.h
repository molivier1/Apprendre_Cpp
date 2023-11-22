#ifndef DECODAGECHAINE_H
#define DECODAGECHAINE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DecodageChaine; }
QT_END_NAMESPACE

class DecodageChaine : public QWidget
{
    Q_OBJECT

public:
    DecodageChaine(QWidget *parent = nullptr);
    ~DecodageChaine();

private slots:
    void on_pushButtonDecoder_clicked();

private:
    Ui::DecodageChaine *ui;
};
#endif // DECODAGECHAINE_H
