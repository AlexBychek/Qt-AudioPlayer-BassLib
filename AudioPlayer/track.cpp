#include "track.h"

Track::Track()
{
    track_view = new TrackView();
    track_view->setFocusPolicy(Qt::ClickFocus);
    track_view->setAttribute(Qt::WA_StyledBackground, true);
}


void Track::set_meta_data(QStringList list, int number)
{
    file_path = list[0];
    file_name = list[1];
    file_format = list[2];
    file_dir = list[3];
    artist = list[4];
    title = list[5];
    album = list[6];
    bitrate = list[7];
    channels = list[8];
    spec = list[9];
    file_size = list[10].toDouble();
    length = list[11].toDouble();

    if(this->title != "")
    track_view->setData(number,(this->artist + " - " + this->title ), this->spec, QDateTime::fromTime_t(this->length).toUTC().toString("hh:mm:ss"));
    else
    track_view->setData(number,this->file_name, this->spec, QDateTime::fromTime_t(this->length).toUTC().toString("hh:mm:ss"));
}

void Track::set_cover_album(QPixmap pic)
{
  this->pic = pic;
}

Track::~Track()
{
  delete track_view;
}
