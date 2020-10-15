#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QMargins>
#include <QLayout>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSizePolicy>
#include <QBoxLayout>
#include <QDebug>

class TrackView : public QWidget
{
    Q_OBJECT
public:
    explicit TrackView(QWidget *parent = nullptr);
    void setData(int,QString,QString,QString);
    void setTextColor(QString);
    QCheckBox *t_box;
    QLabel *title;
    QLabel *specs;
    QLabel *duration;

    QHBoxLayout *h1;
    QHBoxLayout *h2;
    QHBoxLayout *h3;

    QVBoxLayout *v1;
    QVBoxLayout *v2;
    QVBoxLayout *v3;

    QGridLayout *g1;

    QString text_color;
    QString back_color;
private:

signals:

public slots:

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};

#endif // TRACKVIEW_H
