#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QTableWidget>
#include <QtGui>
#include <QList>
#include "track.h"
#include "trackview.h"
#include <QHeaderView>
#include <QMenu>
#include <QMessageBox>
#include <QStringList>
#include <QDateTime>
#include "xmlbuilder.h"
#include "metadatafacade.h"

class PlayList : public QTableWidget
{
    Q_OBJECT
public:
    PlayList(QWidget *parent = 0);
    QString name;

    quint32 length_all_track;
    double size_all_track;

    ~PlayList();

    void setName(QString);
    QStringList get_file_data(int i);
    QPixmap get_file_cover(int i);
    QString getFileName();
    void setcolor(QString, int);
    int popsize();
    bool trackckek(int);
    void all_cpec();
    void AllClear();

    void savestate();
    void getdata(QString path);
    void deletelist();

    bool validformat(QString);

public slots:
    void add_file(const QMimeData *);
    void add_file(QStringList f_path);
    void clear();

    void slotCustomMenuRequested(QPoint pos);
    void slotRemoveRecord();
signals:
    void push_file_data(QString artist, QString title, QString album, QString spec,  QPixmap pic);
    void changed(const QMimeData *mimeData = 0);
    void dropped(const QMimeData *mimeData = 0);
    void set_all_spec(quint32, double);


protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QList<Track*> track_list;
    static int k;
};

#endif // PLAYLIST_H
