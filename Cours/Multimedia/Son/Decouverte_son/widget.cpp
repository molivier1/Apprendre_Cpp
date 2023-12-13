#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&player,&QMediaPlayer::errorOccurred,this,&Widget::onQMediaPlayer_errorOccured);
    connect(&player,&QMediaPlayer::playbackStateChanged,this,&Widget::onQMediaPlayer_playbackStateChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonChooseFile_clicked()
{
    nomFichier=QFileDialog::getOpenFileName();
}

void Widget::on_pushButtonPlayExternalSound_clicked()
{
    player.setAudioOutput(&sortieAudio);
    //player.setSource(QUrl::fromLocalFile(nomFichier));
    player.setSource(QUrl::fromLocalFile("/home/mateo/Documents/SNIR_2/Code/Apprendre_Cpp/Cours/Multimedia/Son/Decouverte_son/WhyAreYouRunning.mp3"));
    sortieAudio.setVolume(50);
    player.play();
}

void Widget::onQMediaPlayer_errorOccured(QMediaPlayer::Error error, const QString &errorString)
{
    qDebug()<<errorString;
}

void Widget::onQMediaPlayer_playbackStateChanged(QMediaPlayer::PlaybackState newState)
{
    QString etat;
    switch (newState) {
    case QMediaPlayer::StoppedState :
        etat="Stopped";
        break;
    case QMediaPlayer::PlayingState :
        etat="Playing";
        break;
    case QMediaPlayer::PausedState :
        etat="Paused";
        break;
    }
    qDebug()<<etat;
}
