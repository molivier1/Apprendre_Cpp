#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_pushButtonChooseFile_clicked();
    void on_pushButtonPlayExternalSound_clicked();

    void onQMediaPlayer_errorOccured(QMediaPlayer::Error error, const QString &errorString);
    void onQMediaPlayer_playbackStateChanged(QMediaPlayer::PlaybackState newState);


private:
    Ui::Widget *ui;

    QString nomFichier;
    QMediaPlayer player;
    QAudioOutput sortieAudio;
};
#endif // WIDGET_H
