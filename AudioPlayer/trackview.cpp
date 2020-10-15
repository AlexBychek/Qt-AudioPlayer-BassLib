#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
     t_box = new QCheckBox("");
     title = new QLabel("");
     specs = new QLabel("");
     duration = new QLabel("");

     h1 = new QHBoxLayout;
     h2 = new QHBoxLayout;
     h3 = new QHBoxLayout;
     v1 = new QVBoxLayout;
     v2 = new QVBoxLayout;
     v3 = new QVBoxLayout;
     g1 = new QGridLayout;
    duration->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

     h1->addWidget(t_box);
     h1->addWidget(title,QBoxLayout::RightToLeft);
     h1->addWidget(duration,QBoxLayout::RightToLeft);
     v3->addLayout(h1);

     v1->addLayout(h1,0);
     h2->addWidget(specs);
     v2->addLayout(h2,0);
     g1->addLayout(v3,0,0);
     g1->addLayout(v2,1,0);
     setLayout(g1);
     t_box->setChecked(true);
}

void TrackView::setData(int num, QString title, QString specs, QString dur)
{
    int n = num;
    QString str1 = QString::number(n) + ".";
    t_box->setText(str1);
    QString str = title;
    str.resize(47);
    str+="...";

    if(title.size() > 50)
        this->title->setText(str);
    else
        this->title->setText(title);

    this->specs->setText(specs);
    this->duration->setText(dur);
}

void TrackView::setTextColor(QString text_color)
{
  this->text_color = "color: "+text_color+";";
  this->setStyleSheet(this->text_color + this->back_color);
}

void TrackView::focusInEvent(QFocusEvent *event)
{
    back_color = "background-color: Orange;";
    this->setStyleSheet(this->text_color + "background-color: Orange;");
}

void TrackView::focusOutEvent(QFocusEvent *event)
{
    back_color = "background-color: transparent;";
    this->setStyleSheet(this->text_color +"background-color: transparent;");
}
