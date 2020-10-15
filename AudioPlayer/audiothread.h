#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>
#include <QDebug>
#include <QTimer>
#include "bass24/c/bass.h"
#include <bass24/c/bassflac24/bassflac.h>
#include <tags.h>
#include <QDir>
#include "xmlbuilder.h"

void __stdcall syncFunc(HSYNC handle, DWORD channel, DWORD data, void *user);

class AudioThread : public QThread
{
    Q_OBJECT
public:
    explicit AudioThread(QObject *parent = 0);

    void run();

private:
    int mGmtDelta;

    int HZ = 44100;
    bool InitDefaultDevice;
    QList<int> plagins;
    bool playing;
    bool isStoped;
    bool EndPlaylist;
    float Volume;
    unsigned long stream;
    QTimer *t;
    int pos;

    QString f_name;


signals:
    void endOfPlayback();
    void curPos(double Position, double Total);
    void file_data(QString, QString, QString,QString,uchar*,int);
    void GetNextTrack(bool);

public slots:
    void play(QString filepath);
    void pause();
    void resume();
    void stop();
    void signalUpdate();
    void changePosition(int position);
    void SetVolume(int vol);

    bool InitBass(int hz);
    int GetPosOfStream();
    void SetPosOfScroll(int pos);
    int GetTimeOfStream();
    void InitPlagin();
};


#endif // AUDIOTHREAD_H
