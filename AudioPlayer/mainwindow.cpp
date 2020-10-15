#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new AudioThread(this);
    timer = new QTimer();
    step_timer = new QTimer();

    if(!QDir(QDir::currentPath() + "/Playlist/").exists())
        QDir().mkdir(QDir::currentPath() + "/Playlist/");

    if(!QDir(QDir::currentPath() + "/MainWindow/").exists())
        QDir().mkdir(QDir::currentPath() + "/MainWindow/");

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    timer->setInterval(1000);
    step_timer->setInterval(50);

    index_track = -1;
    current_pl = -1;
    pl = -1;

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->play_slider->setStyle(new MyStyle(ui->play_slider->style()));
    ui->Volume->setStyle(new MyStyle(ui->Volume->style()));

    connect(player, &AudioThread::curPos, [this](double a, double b){ updateTimer(a,b); });
    connect(ui->play_slider, &QSlider::sliderReleased, [this]{ setTrackPos(); });
    connect(ui->play_slider, &QSlider::sliderMoved, [this](int i){ showTimePos(i); });
    connect(ui->Volume, &QSlider::sliderMoved, player, &AudioThread::SetVolume);
    connect(ui->Volume, &QSlider::valueChanged, player, &AudioThread::SetVolume);
    connect(ui->Volume, &QSlider::sliderMoved, [this](int i){showVolumeLevel(i);});
    connect(ui->Volume, &QSlider::valueChanged, [this](int i){showVolumeLevel(i);}) ;
    connect(timer, &QTimer::timeout,[this]{ showTitle();});
    connect(step_timer, &QTimer::timeout,[this]{ updateStepTimer();});
    connect(this, &MainWindow::trackPos, [this](int i){ player->changePosition(i); });

    connect(ui->Stop_button, &QPushButton::clicked, player, &AudioThread::stop);
    connect(ui->Play_button, &QPushButton::clicked, player, &AudioThread::resume);
    connect(ui->Pause_button, &QPushButton::clicked, player, &AudioThread::pause);
    connect(player, &AudioThread::GetNextTrack,[this](bool i){ toNextTrack(i);});
    connect(ui->Add_Track, SIGNAL(clicked()), this, SLOT(on_actionAddTrack_triggered()));

    //////////
    PlayList* p_list = new PlayList(this);
    ui->PlayLists->removeTab(0);
    ui->PlayLists->addTab(p_list, "Default");
    pl_list.push_back(p_list);

    connect(ui->PlayLists, &QTabWidget::currentChanged, [this]{
            this->getallspec(pl_list[ui->PlayLists->currentIndex()]->length_all_track, pl_list[ui->PlayLists->currentIndex()]->size_all_track);
    });

    connect(pl_list[0], &PlayList::cellDoubleClicked, [this]{ setcurpl(); });
    connect(pl_list[0], &PlayList::cellDoubleClicked, [this]{ plau_audio(); });
    connect(pl_list[0], &PlayList::set_all_spec, [this](quint32 a, double b){ getallspec(a, b); });
    connect(this,SIGNAL(push_listFile(QStringList)),pl_list[0],SLOT(add_file(QStringList)));


    ui->PlayLists->tabBar()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->PlayLists->tabBar(), &QTabBar::customContextMenuRequested,[this](QPoint i){ slotCustomMenuRequested(i);});

    p_list->setName("Default");
    getdata();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    qDeleteAll(pl_list);
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    menu->setStyleSheet("background-color: rgb(85, 85, 85);");
    QAction * addDevice = new QAction(QString::fromUtf8("Добавить"), this);
    QAction * deleteDevice = new QAction(QString::fromUtf8("Удалить"), this);
    QAction * cleanDevice = new QAction(QString::fromUtf8("Очистить"), this);
    QAction * closeDevice = new QAction(QString::fromUtf8("Закрыть"), this);

    connect(addDevice, &QAction::triggered,[this]() { slotAddPlist(); });
    connect(closeDevice, &QAction::triggered,[this]() { slotRemovePlist(1); });
    connect(deleteDevice, &QAction::triggered,[this]() { slotRemovePlist(2); });
    connect(cleanDevice, &QAction::triggered,[this]() {slotCleanPlist();});

    menu->addAction(addDevice);
    menu->addAction(closeDevice);
    menu->addAction(deleteDevice);
    menu->addAction(cleanDevice);
    menu->popup(ui->PlayLists->tabBar()->mapToGlobal(pos));
}

void MainWindow::slotRemovePlist(int flag)
{
        if (QMessageBox::warning(this, "Закрыть/Удалить список", "Вы уверены?" ,QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            {
                int i = ui->PlayLists->currentIndex();

                if(i == 0)
                {
                    pl_list[0]->AllClear();
                    pl_list[0]->deletelist();
                }

                else
                {
                    if(i == this->current_pl)
                    {
                        this->current_pl = -1;
                        this->index_track = -1;
                    }
                    else if(i < this->current_pl)
                    {
                        this->current_pl--;
                    }
                    ui->PlayLists->widget(i)->deleteLater();
                    ui->PlayLists->removeTab(i);
                    if(flag == 2)
                        pl_list[i]->deletelist();
                    pl_list.removeAt(i);
                }
         }
}

void MainWindow::slotAddPlist()
{
    bool ok;
    QString text = QInputDialog::getText(0, "Input dialog",
                                         "Введите название плейлиста:", QLineEdit::Normal,
                                         "", &ok);

    if (ok && !text.isEmpty()) {
            this->createPList(text);
    }
}

void MainWindow::createPList(QString name)
{
    int i = ui->PlayLists->count();
    PlayList* p_list = new PlayList(this);
    ui->PlayLists->addTab(p_list, name);
    this->pl_list.push_back(p_list);

    connect(pl_list[i], &PlayList::cellDoubleClicked, [this]{ setcurpl(); });
    connect(pl_list[i], &PlayList::cellDoubleClicked, [this]{ plau_audio(); });
    connect(pl_list[i], &PlayList::set_all_spec, [this](quint32 a, double b){ getallspec(a, b); });
    pl_list[i]->setName(name);
}

void MainWindow::slotCleanPlist()
{
    if (QMessageBox::warning(this,QString::fromUtf8("Очистить список"),QString::fromUtf8("Вы уверены, что хотите очистить список?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            int i = ui->PlayLists->currentIndex();
                pl_list[i]->AllClear();
        }
}

int MainWindow::generator(int max, int cur)
{
    int gen = qrand() % ((max) - 0) + 0;
    while(gen == cur)
    {
        gen = qrand() % ((max) - 0) + 0;
    }
    return gen;
}

void MainWindow::updateStepTimer()
{
    emit showTimePos(ui->play_slider->value());
    emit trackPos(ui->play_slider->value());
    this->player->resume();
    this->step_timer->stop();
    this->ui->play_slider->setEnabled(true);
}

void MainWindow::setTrackPos()
{
    this->player->pause();
    this->ui->play_slider->setEnabled(false);
    step_timer->start();
}

void MainWindow::showVolumeLevel(int vol)
{
    ui->Name->setText("Громкость " + QString::number(vol) + "%");
    timer->start();
}

void MainWindow::showTitle()
{
    ui->Name->setText(label_name);
    timer->stop();
}

void MainWindow::showTimePos(int time)
{
    if(ui->play_slider->maximum() <= 60)
    ui->Name->setText(QDateTime::fromTime_t(time).toUTC().toString("ss") + "(" + QDateTime::fromTime_t(ui->play_slider->maximum() - time).toUTC().toString("ss") + ")" + "/" + QDateTime::fromTime_t(ui->play_slider->maximum()).toUTC().toString("ss"));
    else if(ui->play_slider->maximum() <= 3600)
    ui->Name->setText(QDateTime::fromTime_t(time).toUTC().toString("mm:ss") + "(" + QDateTime::fromTime_t(ui->play_slider->maximum() - time).toUTC().toString("mm:ss") + ")" + "/" + QDateTime::fromTime_t(ui->play_slider->maximum()).toUTC().toString("mm:ss"));
    else
    ui->Name->setText(QDateTime::fromTime_t(time).toUTC().toString("hh:mm:ss") + "(" + QDateTime::fromTime_t(ui->play_slider->maximum() - time).toUTC().toString("hh:mm:ss") + ")" + "/" + QDateTime::fromTime_t(ui->play_slider->maximum()).toUTC().toString("hh:mm:ss"));
    timer->start();
}

void MainWindow::on_Play_button_clicked()
{
        if(pl == -1)
        {
        ui->Specs->setText(spec);
        if(title != "")
        {
            ui->Name->setText(title);
            ui->Album->setText(artist + " - " + album);
        }else
        {
            ui->Name->setText(name_file);
            ui->Album->setText(artist + " - " + album);
        }
        ui->Album_image->setPixmap(this->pic.scaled(120,120));
        }

        pl = 0;
}
void MainWindow::plau_audio()
{
    if( (pl_list[current_pl]->rowCount() != 0) && (pl_list[current_pl]->currentRow() != -1))
    {
            if(index_track != -1)
            {
                if(index_track < pl_list[current_pl]->popsize())
                  pl_list[current_pl]->setcolor("black",index_track);
            }

        this->index_track = pl_list[current_pl]->currentRow();
        pl_list[current_pl]->setcolor("white",index_track);
        player->play(pl_list[current_pl]->getFileName());

        QStringList ls = pl_list[current_pl]->get_file_data(index_track);
        get_file_data(ls, pl_list[current_pl]->get_file_cover(index_track));
        ui->play_slider->setMaximum(player->GetTimeOfStream());
        ui->play_slider->setValue(player->GetPosOfStream());

        artist = ls[2];
        title = ls[1];
        album = ls[3];
        spec = ls[4];
        name_file = ls[0];

        pl = 0;
    }
}

void MainWindow::toNextTrack(bool check)
{
    if((this->countcheck() < 2 || index_track == pl_list[current_pl]->popsize()-1) && !ui->Loop->isChecked())
        this->on_Stop_button_clicked();
    else if(!ui->Loop->isChecked())
        this->on_Next_file_clicked();
    else
       this->plau_audio();
}

void MainWindow::on_Stop_button_clicked()
{
       ui->play_slider->setValue(0);
       ui->StPos->setText("");
       ui->EnPos->setText("");
       ui->Name->setText("");
       ui->Album->setText("");
       ui->Album_image->clear();
       ui->Specs->setText("");
       ui->Album_image->clear();
       pl = -1;
}

void MainWindow::on_Pause_button_clicked()
{
    pl = 1;
}

void MainWindow::updateTimer(double Position, double Total)
{
    if(Total <= 60)
    {
        ui->StPos->setText(QDateTime::fromTime_t(Position).toUTC().toString("ss"));
        ui->EnPos->setText(QDateTime::fromTime_t(Total).toUTC().toString("ss"));
    }
    else if(Total <= 3600){
        ui->StPos->setText(QDateTime::fromTime_t(Position).toUTC().toString("mm:ss"));
        ui->EnPos->setText(QDateTime::fromTime_t(Total).toUTC().toString("mm:ss"));
    }else
    {
        ui->StPos->setText(QDateTime::fromTime_t(Position).toUTC().toString("hh:mm:ss"));
        ui->EnPos->setText(QDateTime::fromTime_t(Total).toUTC().toString("hh:mm:ss"));
    }

    if(!(ui->play_slider->isSliderDown()))
    ui->play_slider->setValue(Position);
}

void MainWindow::get_file_data(QStringList ls, QPixmap pic)
{
    this->pic = pic;
    ui->Album_image->clear();
    ui->Album_image->setPixmap(this->pic.scaled(120,120));

   if(ls[1] != "")
   { 
       QString str = ls[1];
       if(str.size() > 40)
       {
           str.resize(37);
           str+="...";

           ui->Name->setText(str);
       }
          ui->Name->setText(str);
          label_name = ls[1];
   }
   else
   {
       QString str = ls[0];
       if(str.size() > 40)
       {
           str.resize(37);
           str+="...";

           ui->Name->setText(str);
       }
        ui->Name->setText(str);
        label_name = ls[0];
   }
   QString str = ls[2] + " - " + ls[3];
   if(str.size() > 50)
   {
       str.resize(47);
       str+="...";
        ui->Album->setText(str);
   }
   else
        ui->Album->setText(str);
   ui->Specs->setText(ls[4]);
}

void MainWindow::on_Next_file_clicked()
{
    if(pl_list[current_pl]->popsize() != 0)
    {
        if(this->countcheck() == 1 && pl_list[current_pl]->trackckek(index_track))
        {

        }
        else if(this->countcheck() > 0)
        {

        if(ui->cling->isChecked() && this->countcheck() > 1)
        {

            int gen = this->generator(pl_list[current_pl]->popsize(), index_track);
            bool ch = pl_list[current_pl]->trackckek(gen);

            do
            {
                gen = this->generator(pl_list[current_pl]->popsize(), index_track);
                ch = pl_list[current_pl]->trackckek(gen);
                if(ch)
                {
                    pl_list[current_pl]->selectRow(gen);
                    this->plau_audio();
                    break;
                }
            }while(!ch);
        }else{

            //если конец - пойти сначала
            if(index_track == pl_list[current_pl]->popsize()-1)
            {
              for(int i = 0; i < pl_list[current_pl]->popsize(); i++)
              {
                 if(pl_list[current_pl]->trackckek(i))
                 {
                      pl_list[current_pl]->selectRow(i);
                      this->plau_audio();
                      break;
                 }
              }
            }else
            {
                //От текущего до конца
                for(int i = index_track+1; i < pl_list[current_pl]->popsize();i++)
                {
                   if(pl_list[current_pl]->trackckek(i))
                   {
                       pl_list[current_pl]->selectRow(i);
                       this->plau_audio();
                       break;
                   }
                   //Если конец сначала
                   if(i == pl_list[current_pl]->popsize() -1 )
                   {
                       for(int i = 0; i < pl_list[current_pl]->popsize(); i++)
                       {
                           if(pl_list[current_pl]->trackckek(i))
                           {
                               pl_list[current_pl]->selectRow(i);
                               this->plau_audio();
                               break;
                           }
                       }
                   }
                }
            }
        }
    }
    }
}

void MainWindow::on_Previous_file_clicked()
{
   if(pl_list[current_pl]->popsize() != 0)
   {
       if(this->countcheck() < 2 && pl_list[current_pl]->trackckek(index_track))
       {

       }
       else if(this->countcheck() > 0 )
       {
       if(ui->cling->isChecked() && this->countcheck() > 1)
       {
           int gen = this->generator(pl_list[current_pl]->popsize(), index_track);
           bool ch = pl_list[current_pl]->trackckek(gen);

           do
           {
               gen = this->generator(pl_list[current_pl]->popsize(), index_track);
               ch = pl_list[current_pl]->trackckek(gen);
               if(ch)
               {
                   pl_list[current_pl]->selectRow(gen);
                   this->plau_audio();
                   break;
               }
           }while(!ch);
       }else
       {
           if(index_track == 0)
           {
               for(int i = pl_list[current_pl]->popsize()-1; i >= 0; i--)
                   if(pl_list[current_pl]->trackckek(i))
                   {
                        pl_list[current_pl]->selectRow(i);
                        this->plau_audio();
                         break;
                   }
           }else
           {
               for(int i = index_track-1; i >= 0; i--)
               {
                   if(pl_list[current_pl]->trackckek(i))
                   {
                        pl_list[current_pl]->selectRow(i);
                        this->plau_audio();
                        break;
                    }
                    if(i == 0 )
                    {
                        for(int i = pl_list[current_pl]->popsize()-1; i >= 0; i--)
                        {
                            if(pl_list[current_pl]->trackckek(i))
                            {
                                pl_list[current_pl]->selectRow(i);
                                this->plau_audio();
                                break;
                            }
                        }
                     }
                  }
              }
          }
      }
   }
}


int MainWindow::countcheck()
{
    int k = 0;
    for(int i = 0; i < pl_list[current_pl]->popsize(); i++)
    {
        if(pl_list[current_pl]->trackckek(i))
            k++;
    }
    return k;
}

void MainWindow::getallspec(quint32 length_all_track, double size_all_track)
{
    QString days = QString::number(QDateTime::fromTime_t(length_all_track).toUTC().toString("dd").toInt() - 1) + ":";
    if(length_all_track <= 86400 && size_all_track < 1024)
        ui->all_cpec->setText(QString::number(pl_list[ui->PlayLists->currentIndex()]->popsize()) +" / " +  QDateTime::fromTime_t(length_all_track).toUTC().toString("hh:mm:ss") + " / " + QString::number(size_all_track, 'f', 2) + " MB");
    if(length_all_track <= 86400 && size_all_track > 1024)
        ui->all_cpec->setText(QString::number(pl_list[ui->PlayLists->currentIndex()]->popsize()) +" / " +  QDateTime::fromTime_t(length_all_track).toUTC().toString("hh:mm:ss") + " / " + QString::number(size_all_track/1024, 'f', 2) + " GB");
    else if(length_all_track > 86400 && size_all_track < 1024)
        ui->all_cpec->setText(QString::number(pl_list[ui->PlayLists->currentIndex()]->popsize()) +" / " + days +  QDateTime::fromTime_t(length_all_track).toUTC().toString("hh:mm:ss") + " / " + QString::number(size_all_track, 'f', 2) + " MB");
    else if(length_all_track > 86400 && size_all_track > 1024)
        ui->all_cpec->setText(QString::number(pl_list[ui->PlayLists->currentIndex()]->popsize()) +" / " + days +  QDateTime::fromTime_t(length_all_track).toUTC().toString("hh:mm:ss") + " / " + QString::number(size_all_track/1024, 'f', 2) + " GB");

}

void MainWindow::setcurpl()
{
    if(current_pl == -1)
        current_pl = ui->PlayLists->currentIndex();
    else if(current_pl != ui->PlayLists->currentIndex())
        this->current_pl = ui->PlayLists->currentIndex();
}

void MainWindow::savestate()
{
        QFile globaldata( QDir::currentPath() + "/MainWindow/MainWindowData.xml");
        qDebug() << QDir::currentPath();
        globaldata.open(QIODevice::WriteOnly);
        QTextStream out(&globaldata);
        XMLBuilder builder;

        builder.begin("MainWindowData");

        builder.begin("Volume");
        builder.attr("level", QString::number(ui->Volume->value()));
        builder.end();

        builder.begin("PlayList");
        builder.attr("index", QString::number(current_pl));
        builder.end();

        builder.begin("track");
        builder.attr("index", QString::number(index_track));
        builder.end();

        if(this->pl >= 0)
        {
            builder.begin("PlayState");
            builder.attr("State", QString::number(pl));
            builder.attr("Position", QString::number(ui->play_slider->value()));
            builder.end();
        }

        if(pl_list.size()>1)
        {
            for(int i = 1; i < pl_list.size();i++)
            {
                builder.begin("OtherList");
                builder.attr("name", pl_list[i]->name);
                builder.end();
            }
        }

        builder.end();
        out << builder.getXML();
        globaldata.close();
}

void MainWindow::getdata()
{
    QFile globaldata( QDir::currentPath() + "/MainWindow/MainWindowData.xml");

    bool tre = false;

    int pos = 0;
    if (!globaldata.open(QFile::ReadOnly | QFile::Text))
     {
        globaldata.close();
     } else {

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&globaldata);

        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                    foreach (const QXmlStreamAttribute &attr, xmlReader.attributes()) {
                        if(xmlReader.name() == "Volume")
                        {
                            if(attr.name().toString() == "level")                           
                                ui->Volume->setValue(attr.value().toInt()); 
                        }
                        if(xmlReader.name() == "PlayList")
                        {
                            if(attr.name().toString() == "index")
                            {
                                tre = true;
                                this->current_pl = attr.value().toInt();
                            }
                        }
                        if(xmlReader.name() == "track")
                        {
                            if(attr.name().toString() == "index")
                                this->index_track = attr.value().toInt();
                        }
                        if(xmlReader.name() == "PlayState")
                        {
                            if(attr.name().toString() == "State")
                                this->pl = attr.value().toInt();
                            if(attr.name().toString() == "Position")
                                pos = attr.value().toInt();
                        }
                        if(xmlReader.name() == "OtherList")
                        {
                            if(attr.name().toString() == "name")
                                this->createPList(attr.value().toString());

                        }

                       }

                   }
        xmlReader.readNext();
                    }

        if(current_pl != -1 && tre)
            ui->PlayLists->setCurrentIndex(current_pl);
        if(pl == 0 && current_pl != -1 && index_track != -1)
        {
            pl_list[current_pl]->selectRow(index_track);
            this->plau_audio();
            ui->play_slider->setValue(pos);
            this->setTrackPos();

        }else if(pl == 1 && current_pl != -1 && index_track != -1)
        {
            pl_list[current_pl]->selectRow(index_track);
            this->plau_audio();
            player->pause();
            this->on_Pause_button_clicked();
            ui->play_slider->setValue(pos);
            this->setTrackPos();
        }
     globaldata.close();
                }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->savestate();
}

void MainWindow::on_Add_Track_clicked()
{
    QStringList f_path = QFileDialog::getOpenFileNames(this, "Open a file", "./", tr("Все форматы (*.mp3 *.flac *.aac *.ac3 *.adx *.aix *.ape *.mpc *.spx *.tta *.alac *.opus *.m4a *.mp4 *.ogg *.wv *.wma *.mpc *.wav);;"
                                                                                     "MPEG Audio Lauyer III (*.mp3) ;;"
                                                                                     "Free Lossless Audio Codec (*.flac);;"
                                                                                     "Advanced Audio Coding (*.aac);;"
                                                                                     "Dolby Digital (*.ac3);;"
                                                                                     "CRI ADX (*.adx);;"
                                                                                     "AIX (*.aix);;"
                                                                                     "Monkey’s Audio (*.ape);;"
                                                                                     "Media Player Classic (*.mpc);;"
                                                                                     "Speex  (*.spx);;"
                                                                                     "True Audio (*.tta);;"
                                                                                     "Apple Lossless (*.alac);;"
                                                                                     "Opus (*.opus);;"
                                                                                     "Advanced Audio Coding (*.m4a *.mp4);;"
                                                                                     "OGG Vorbis Audio (*.ogg);;"
                                                                                     "WavPack (*.wv);;"
                                                                                     "Windows Media Audio (*.wma);;"
                                                                                     "MusePack (*.mpc);;"
                                                                                     "Waveform Audio (*.wav);;"));
    emit push_listFile(f_path);
}
