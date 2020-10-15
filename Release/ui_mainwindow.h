/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddTrack;
    QWidget *centralwidget;
    QPushButton *Play_button;
    QPushButton *Stop_button;
    QPushButton *Pause_button;
    QPushButton *Next_file;
    QPushButton *Previous_file;
    QSlider *play_slider;
    QSlider *Volume;
    QTabWidget *PlayLists;
    QWidget *tab;
    QLabel *Album_image;
    QLabel *Name;
    QLabel *Album;
    QLabel *Specs;
    QLabel *StPos;
    QLabel *EnPos;
    QCheckBox *Loop;
    QCheckBox *cling;
    QPushButton *Add_Track;
    QLabel *all_cpec;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(398, 589);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setContextMenuPolicy(Qt::DefaultContextMenu);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 85);"));
        actionAddTrack = new QAction(MainWindow);
        actionAddTrack->setObjectName(QString::fromUtf8("actionAddTrack"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Play_button = new QPushButton(centralwidget);
        Play_button->setObjectName(QString::fromUtf8("Play_button"));
        Play_button->setGeometry(QRect(180, 150, 50, 50));
        Play_button->setStyleSheet(QString::fromUtf8("QPushButton{border-image:url(:/IP1/Favorites/Icon_Pack1/Play_white.png);}\n"
"QPushButton:pressed{ border-image:url(:/IP1/Favorites/Icon_Pack1/Play_click.png); }"));
        Stop_button = new QPushButton(centralwidget);
        Stop_button->setObjectName(QString::fromUtf8("Stop_button"));
        Stop_button->setGeometry(QRect(120, 150, 50, 50));
        Stop_button->setStyleSheet(QString::fromUtf8("QPushButton{border-image:url(:/IP1/Favorites/Icon_Pack1/Stop_white.png);}\n"
"QPushButton:pressed{ border-image:url(:/IP1/Favorites/Icon_Pack1/Stop_click.png); }"));
        Pause_button = new QPushButton(centralwidget);
        Pause_button->setObjectName(QString::fromUtf8("Pause_button"));
        Pause_button->setGeometry(QRect(240, 150, 50, 50));
        Pause_button->setStyleSheet(QString::fromUtf8("QPushButton{border-image:url(:/IP1/Favorites/Icon_Pack1/Pause_white.png);}\n"
"QPushButton:pressed{ border-image:url(:/IP1/Favorites/Icon_Pack1/Pause_click.png); }"));
        Next_file = new QPushButton(centralwidget);
        Next_file->setObjectName(QString::fromUtf8("Next_file"));
        Next_file->setGeometry(QRect(300, 150, 50, 50));
        Next_file->setStyleSheet(QString::fromUtf8("QPushButton{border-image:url(:/IP1/Favorites/Icon_Pack1/Next_white.png);}\n"
"QPushButton:pressed{ border-image:url(:/IP1/Favorites/Icon_Pack1/Next_click.png); }"));
        Previous_file = new QPushButton(centralwidget);
        Previous_file->setObjectName(QString::fromUtf8("Previous_file"));
        Previous_file->setGeometry(QRect(60, 150, 50, 50));
        Previous_file->setStyleSheet(QString::fromUtf8("QPushButton{border-image:url(:/IP1/Favorites/Icon_Pack1/Back_white.png);}\n"
"QPushButton:pressed{ border-image:url(:/IP1/Favorites/Icon_Pack1/Back_click.png); }"));
        play_slider = new QSlider(centralwidget);
        play_slider->setObjectName(QString::fromUtf8("play_slider"));
        play_slider->setGeometry(QRect(15, 230, 370, 20));
        play_slider->setMinimum(1);
        play_slider->setMaximum(100);
        play_slider->setPageStep(10);
        play_slider->setOrientation(Qt::Horizontal);
        Volume = new QSlider(centralwidget);
        Volume->setObjectName(QString::fromUtf8("Volume"));
        Volume->setGeometry(QRect(10, 140, 21, 51));
        Volume->setMinimum(0);
        Volume->setMaximum(100);
        Volume->setPageStep(1);
        Volume->setValue(50);
        Volume->setSliderPosition(50);
        Volume->setOrientation(Qt::Vertical);
        PlayLists = new QTabWidget(centralwidget);
        PlayLists->setObjectName(QString::fromUtf8("PlayLists"));
        PlayLists->setGeometry(QRect(0, 260, 400, 271));
        PlayLists->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"    border: 1px solid black;\n"
"    background: white;\n"
"}\n"
"\n"
"QTabWidget::tab-bar:top {\n"
"    top: 1px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar:bottom {\n"
"    bottom: 1px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar:left {\n"
"    right: 1px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar:right {\n"
"    left: 1px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    border: 1px solid black;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: white;\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    background: silver;\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover {\n"
"    background: #999;\n"
"}\n"
"\n"
"QTabBar::tab:top:!selected {\n"
"    margin-top: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:bottom:!selected {\n"
"    margin-bottom: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:top, QTabBar::tab:bottom {\n"
"    min-width: 8ex;\n"
"    margin-right: -1px;\n"
"    padding: 5px 10px 5px 10px;\n"
"}\n"
"\n"
"QTabBar::tab:top:selected {\n"
"    border-bottom-color: none;\n"
"}\n"
"\n"
"QTabBar::tab:bottom:selected {\n"
"    border-top"
                        "-color: none;\n"
"}\n"
"\n"
"QTabBar::tab:top:last, QTabBar::tab:bottom:last,\n"
"QTabBar::tab:top:only-one, QTabBar::tab:bottom:only-one {\n"
"    margin-right: 0;\n"
"}\n"
"\n"
"QTabBar::tab:left:!selected {\n"
"    margin-right: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:right:!selected {\n"
"    margin-left: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:left, QTabBar::tab:right {\n"
"    min-height: 8ex;\n"
"    margin-bottom: -1px;\n"
"    padding: 10px 5px 10px 5px;\n"
"}\n"
"\n"
"QTabBar::tab:left:selected {\n"
"    border-left-color: none;\n"
"}\n"
"\n"
"QTabBar::tab:right:selected {\n"
"    border-right-color: none;\n"
"}\n"
"\n"
"QTabBar::tab:left:last, QTabBar::tab:right:last,\n"
"QTabBar::tab:left:only-one, QTabBar::tab:right:only-one {\n"
"    margin-bottom: 0;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        PlayLists->addTab(tab, QString());
        Album_image = new QLabel(centralwidget);
        Album_image->setObjectName(QString::fromUtf8("Album_image"));
        Album_image->setGeometry(QRect(10, 10, 120, 120));
        Album_image->setStyleSheet(QString::fromUtf8("border-image: url(:/Logo/icon_my_player.png);"));
        Album_image->setAlignment(Qt::AlignCenter);
        Name = new QLabel(centralwidget);
        Name->setObjectName(QString::fromUtf8("Name"));
        Name->setGeometry(QRect(140, 10, 251, 41));
        Name->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        Name->setAlignment(Qt::AlignCenter);
        Album = new QLabel(centralwidget);
        Album->setObjectName(QString::fromUtf8("Album"));
        Album->setGeometry(QRect(140, 50, 251, 41));
        Album->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        Album->setAlignment(Qt::AlignCenter);
        Specs = new QLabel(centralwidget);
        Specs->setObjectName(QString::fromUtf8("Specs"));
        Specs->setGeometry(QRect(140, 90, 251, 41));
        Specs->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        Specs->setAlignment(Qt::AlignCenter);
        StPos = new QLabel(centralwidget);
        StPos->setObjectName(QString::fromUtf8("StPos"));
        StPos->setGeometry(QRect(15, 210, 50, 16));
        StPos->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        StPos->setAlignment(Qt::AlignCenter);
        EnPos = new QLabel(centralwidget);
        EnPos->setObjectName(QString::fromUtf8("EnPos"));
        EnPos->setGeometry(QRect(335, 210, 50, 16));
        EnPos->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        EnPos->setAlignment(Qt::AlignCenter);
        Loop = new QCheckBox(centralwidget);
        Loop->setObjectName(QString::fromUtf8("Loop"));
        Loop->setGeometry(QRect(360, 150, 31, 21));
        Loop->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"    image: url(:/IP1/Favorites/Icon_Pack1/Loop_white.png);\n"
"    width: 30px;\n"
"	height: 30px;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"    image :url(:/IP1/Favorites/Icon_Pack1/Loop_click.png);\n"
"    width: 30px;\n"
"	height: 30px;\n"
"}"));
        cling = new QCheckBox(centralwidget);
        cling->setObjectName(QString::fromUtf8("cling"));
        cling->setGeometry(QRect(360, 180, 31, 21));
        cling->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"    image: url(:/IP1/Favorites/Icon_Pack1/Shuff_white.png);\n"
"    width: 30px;\n"
"	height: 30px;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"    image: url(:/IP1/Favorites/Icon_Pack1/Shuff_click.png);\n"
"    width: 30px;\n"
"	height: 30px;\n"
"}"));
        Add_Track = new QPushButton(centralwidget);
        Add_Track->setObjectName(QString::fromUtf8("Add_Track"));
        Add_Track->setGeometry(QRect(10, 540, 21, 21));
        Add_Track->setStyleSheet(QString::fromUtf8("QPushButton{border-image:url(:/IP1/Favorites/Icon_Pack1/plus_white.png);}\n"
"QPushButton:pressed{ border-image:url(:/IP1/Favorites/Icon_Pack1/plus_click.png); }"));
        all_cpec = new QLabel(centralwidget);
        all_cpec->setObjectName(QString::fromUtf8("all_cpec"));
        all_cpec->setGeometry(QRect(50, 540, 300, 20));
        all_cpec->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        all_cpec->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 398, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        PlayLists->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FPlayer", nullptr));
        actionAddTrack->setText(QCoreApplication::translate("MainWindow", "AddTrack", nullptr));
        Play_button->setText(QString());
        Stop_button->setText(QString());
        Pause_button->setText(QString());
        Next_file->setText(QString());
        Previous_file->setText(QString());
        PlayLists->setTabText(PlayLists->indexOf(tab), QCoreApplication::translate("MainWindow", "Default", nullptr));
        Album_image->setText(QString());
        Name->setText(QString());
        Album->setText(QString());
        Specs->setText(QString());
        StPos->setText(QString());
        EnPos->setText(QString());
        Loop->setText(QString());
        cling->setText(QString());
        Add_Track->setText(QString());
        all_cpec->setText(QCoreApplication::translate("MainWindow", "0 / 00:00:00 / 0.00 MB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
