#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <trackview.h>
#include <QDateTime>
#include <QBuffer>
class Track
{
protected:
    QStringList _list;
    int _num;
public:
    Track();
    Track(const QStringList &list, const int &num):_list(list),_num(num)
    {
        track_view = new TrackView();
        track_view->setFocusPolicy(Qt::ClickFocus);
        track_view->setAttribute(Qt::WA_StyledBackground, true);
        this->set_meta_data(_list, _num);
    }
    ~Track();
    void set_meta_data(QStringList,int);
    void set_cover_album(QPixmap);
    QString file_path;
    QString file_name;
    QString file_format;
    QString file_dir;
    QString artist;
    QString title;
    QString album;
    QString bitrate;
    QString channels;
    QString spec;
    QPixmap pic;
    double length;
    double file_size;

    TrackView* track_view;
};

#endif // TRACK_H
