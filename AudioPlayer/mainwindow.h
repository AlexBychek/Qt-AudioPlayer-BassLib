#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaType>
#include <QStandardItemModel>
#include <QProcess>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QtGui>
#include <QColor>
#include <QProxyStyle>
#include <QTime>
#include <QItemDelegate>
#include <QAbstractItemDelegate>
#include <taglib/tbytevector.h>
#include <QMenu>
#include <QMessageBox>
#include <QInputDialog>
#include "audiothread.h"
#include "track.h"
#include "trackview.h"
#include "playlist.h"
#include "xmlbuilder.h"

class MyStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return (Qt::LeftButton | Qt::MidButton | Qt::RightButton);
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    AudioThread *player;
    QString track_name;
    void savestate();
    void getdata();
    void createPList(QString);
    int generator(int,int);
signals:
      void startTrack(QString);
      void trackPos(int);
      void push_listFile(QStringList);

private slots:
    void on_Play_button_clicked();
    void on_Stop_button_clicked();
    void on_Pause_button_clicked();
    void updateTimer(double Position, double Total);
    void updateStepTimer();
    void get_file_data(QStringList ls, QPixmap pic);
    void plau_audio();
    void setTrackPos();
    void showTimePos(int);
    void showVolumeLevel(int);
    void showTitle();
    void toNextTrack(bool);
    void on_Next_file_clicked();
    void on_Previous_file_clicked();
    int countcheck();
    void setcurpl();
    void getallspec(quint32, double);
    void slotCustomMenuRequested(QPoint pos);
    void slotRemovePlist(int flag);
    void slotAddPlist();
    void slotCleanPlist();
    void on_Add_Track_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *step_timer;
    QString name_file;
    QString label_name;
    int pl;
    int current_pl;
    int index_track;
    QString artist;
    QString title;
    QString album;
    QString spec;
    QList<PlayList*> pl_list;
    QPixmap pic;

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
