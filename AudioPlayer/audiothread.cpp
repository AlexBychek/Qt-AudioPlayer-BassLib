#include "audiothread.h"

bool endOfMusic;

void __stdcall syncFunc(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    BASS_ChannelRemoveSync(channel, handle);
    BASS_ChannelStop(channel);
    qDebug() << "End of playback!";
    endOfMusic = true;
}

bool AudioThread::InitBass(int hz)
{
    if(!InitDefaultDevice)
        InitDefaultDevice = BASS_Init (-1, 44100, 0, 0, NULL);
    if(InitDefaultDevice)
        this->InitPlagin();
    return InitDefaultDevice;
}

void AudioThread::InitPlagin()
{
    QString st = QDir::currentPath();
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_aac.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_ac3.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_adx.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_aix.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_ape.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_mpc.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_spx.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bass_tta.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bassalac.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/basscd.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bassdsd.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bassflac.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/basshls.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bassmidi.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/bassopus.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/basswebm.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/basswma.dll",0));
    plagins.push_back(BASS_PluginLoad(st.toUtf8() + "/Plagins/basswv.dll",0));

    int ErrorCount = 0;
    for(int i = 0; i < plagins.size(); i++)
        if(plagins[i] == 0)
            ErrorCount++;
    if(ErrorCount != 0)
        qDebug() << ErrorCount + " плагинов не было загружено";
    else
        qDebug() << "Все плагины загружены!";
    ErrorCount = 0;

}

AudioThread::AudioThread(QObject *parent) :
    QThread(parent)
{
    playing = false;
    isStoped = true;
    if (!InitBass(HZ))
        qDebug() << "Cannot initialize device";
    qDebug() << "initialize device";
    t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(signalUpdate()));
    endOfMusic = true;

        Volume = 0.5;
        pos = 0;
}

void AudioThread::play(QString filename)
{
        this->stop();
        if(InitDefaultDevice)
        {
            f_name = filename;

                if (!(stream = BASS_StreamCreateFile(false, f_name.unicode(), 0, 0 , BASS_UNICODE | BASS_SAMPLE_FLOAT ))
                    && !(stream = BASS_MusicLoad(false, f_name.unicode(), 0, 0, BASS_MUSIC_RAMP | BASS_SAMPLE_FLOAT | BASS_UNICODE, 1)))
                {
                    qDebug() << BASS_ErrorGetCode();
                    qDebug() << "Can't play file";
                }
                else
                {
                    endOfMusic = false;
                    t->start(100);
                    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, Volume);
                    BASS_ChannelPlay(stream, true);
                    BASS_ChannelSetSync(stream, BASS_SYNC_END, 0, &syncFunc, 0);
                    playing = true;
                    isStoped = false;
                }
          }
}

void AudioThread::pause()
{
    if(BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING)
    {
        BASS_ChannelPause(stream);
        t->stop();
        playing = false;
    }
}

void AudioThread::resume()
{
    if(BASS_ChannelIsActive(stream) == BASS_ACTIVE_PAUSED)
    {
    if (!BASS_ChannelPlay(stream, false))
        qDebug() << "Error resuming";
    else
    {
        t->start(98);
        playing = true;
        isStoped = false;
    }
    }else
        this->play(f_name);
}

void AudioThread::stop()
{
    BASS_ChannelStop(stream);
    BASS_StreamFree(stream);
    t->stop();
    playing = false;
    isStoped = true;
}

void AudioThread::signalUpdate()
{
    if (endOfMusic == false)
        emit curPos(BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetPosition(stream, BASS_POS_BYTE)),
                    BASS_ChannelBytes2Seconds(stream, BASS_ChannelGetLength(stream, BASS_POS_BYTE))); 
    else
    {
        emit endOfPlayback();
        t->stop();
        emit GetNextTrack(true);
        playing = false;
    }
}

void AudioThread::changePosition(int position)
{
    BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, position), BASS_POS_BYTE);
}

void AudioThread::run()
{
    while (1);
}

int AudioThread::GetPosOfStream()
{
    long pos = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
    int posSec = BASS_ChannelBytes2Seconds(stream, pos);
    return posSec;
}

void AudioThread::SetPosOfScroll(int pos)
{
    BASS_ChannelSetPosition(stream, pos, BASS_POS_BYTE);
}

int AudioThread::GetTimeOfStream()
{
    long TimeBytes = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    double Time = BASS_ChannelBytes2Seconds(stream, TimeBytes);
    return (int)Time;
}

void AudioThread::SetVolume(int vol)
{
    this->Volume = vol/(float)100;
    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, Volume);
}
