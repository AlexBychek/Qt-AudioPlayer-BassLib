#include "playlist.h"

PlayList::PlayList(QWidget *parent) : QTableWidget(parent) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setDragDropMode(QAbstractItemView::DropOnly);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(false);
    setWordWrap(false);
    setAcceptDrops(true);

    setStyleSheet("background-color: rgb(152, 152, 152);");

    insertColumn(0);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    horizontalHeader()->hide();
    verticalHeader()->hide();


    connect(this, &PlayList::dropped, [this](const QMimeData * p){ add_file(p); });
    connect(this, &PlayList::customContextMenuRequested, [this](QPoint i){ slotCustomMenuRequested(i); });

    length_all_track = 0;
    size_all_track = 0;
}

void PlayList::dragEnterEvent(QDragEnterEvent *event) {

    event->acceptProposedAction();
}

void PlayList::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void PlayList::dropEvent(QDropEvent *event)
{
    emit dropped(event->mimeData());
}

void PlayList::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}
void PlayList::add_file(const QMimeData* data)
{
    QList<QUrl> tem = data->urls();

    for(int i = 0; i < tem.size(); i++)
    {
        if(QFile::exists(QUrl::fromLocalFile(tem[i].path()).toLocalFile()))
        {
            QString file_path = QUrl::fromLocalFile(tem[i].path()).toLocalFile();
            QString f_format = file_path.right((file_path.size()-file_path.lastIndexOf(".")-1));

            if(validformat(f_format))
            {
                if(f_format == "fpl")
                    this->getdata(file_path);
                else
                {
                    this->insertRow(this->rowCount());
                    Track* track = new Track(MetaDataFacade::get_meta_data(file_path, f_format), this->rowCount());
                    track_list.push_back(track);

                    this->setCellWidget(this->rowCount()-1,0, track->track_view);
                    this->resizeRowToContents(this->rowCount()-1);
                }
            }
        }
    }
    savestate();
    this->all_cpec();
    emit set_all_spec(length_all_track, size_all_track);
}

bool PlayList::validformat(QString format)
{
    const QStringList formats = { "fpl", "mp3", "flac", "FLAC", "aac", "ac3", "adx", "aix", "ape", "mpc", "spx", "tta", "alac", "opus", "m4a", "mp4", "ogg", "wv", "wma", "mpc", "wav" };

    for(int i = 0; i < formats.size(); ++i)
    {
        if(format == formats[i])
            return true;
    }
        return false;

}

void PlayList::add_file(QStringList f_path)
{
    QStringList f_name = f_path;
    QStringList f_format = f_path;

   for(int i = 0; i < f_path.size();i++)
   {
       if(QFile::exists(f_path[i]))
       {
           f_format[i] = f_path[i].right(f_path[i].size()-f_path[i].lastIndexOf(".")-1);

           this->insertRow(this->rowCount());
           Track *track = new Track(MetaDataFacade::get_meta_data(f_path[i], f_format[i]), this->rowCount());

           track_list.push_back(track);
           this->setCellWidget(this->rowCount()-1,0, track->track_view);
           this->resizeRowToContents(this->rowCount()-1);
       }
   }

    savestate();
    this->all_cpec();
    emit set_all_spec(length_all_track, size_all_track);
}

void PlayList::clear() {
    emit changed();
}

PlayList::~PlayList()
{
    qDeleteAll(track_list);
}

void PlayList::slotCustomMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    menu->setStyleSheet("background-color: rgb(85, 85, 85);");
    QAction * deleteDevice = new QAction(QString::fromUtf8("Удалить"), this);
    connect(deleteDevice, &QAction::triggered, this, &PlayList::slotRemoveRecord);
    menu->addAction(deleteDevice);
    menu->popup(this->viewport()->mapToGlobal(pos));
}

void PlayList::slotRemoveRecord()
{
    int row = this->selectionModel()->currentIndex().row();
    if(row >= 0){
        if (QMessageBox::warning(this,QString::fromUtf8("Удаление записи"),QString::fromUtf8("Вы уверены, что хотите удалить эту запись?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            {
                int i = this->currentRow();
                Track * t = track_list[i];
                delete t;
                track_list.removeAt(i);
                this->removeRow(this->currentRow());
                savestate();
                this->all_cpec();
                emit set_all_spec(length_all_track, size_all_track);
            }
        }
}

QString PlayList::getFileName()
{
    return track_list[currentRow()]->file_path;
}

QStringList PlayList::get_file_data(int i)
{
    QStringList ls;
    ls.push_back(track_list[i]->file_name);
    ls.push_back(track_list[i]->title);
    ls.push_back(track_list[i]->artist);
    ls.push_back(track_list[i]->album);
    ls.push_back(track_list[i]->spec);
    ls.push_back(track_list[i]->file_format);
    return ls;
}

QPixmap PlayList::get_file_cover(int i)
{
    return  MetaDataFacade::getPic(track_list[i]->file_path, track_list[i]->file_format);
}

void PlayList::setcolor(QString color, int i)
{
    track_list[i]->track_view->setTextColor(color);
}

int PlayList::popsize()
{
    return track_list.size();
}

bool PlayList::trackckek(int i)
{
    return track_list[i]->track_view->t_box->isChecked();
}

void PlayList::all_cpec()
{
    this->length_all_track = 0;
    this->size_all_track = 0;

    int k = track_list.size();
    for(int i = 0; i < k; i++)
    {
       this->length_all_track += track_list[i]->length;
       this->size_all_track += track_list[i]->file_size;
    }
}

void PlayList::AllClear()
{
    while(track_list.size() != 0)
    {
        this->removeCellWidget(0,0);
        Track * t = track_list[0];
        delete t;
        track_list.removeAt(0);
        this->removeRow(0);
    }
    this->all_cpec();
    emit set_all_spec(length_all_track, size_all_track);
}

void PlayList::setName(QString str)
{
    this->name = str;
    getdata(QDir::currentPath() + "/Playlist/" + name + ".fpl");
}

void PlayList::savestate()
{
        QFile globaldata( QDir::currentPath() + "/Playlist/"+ name+".fpl");
        globaldata.open(QIODevice::WriteOnly);
        QTextStream out(&globaldata);
        out.setCodec("UTF-8");
        XMLBuilder builder;
        builder.begin("List");        

        for(int i = 0; i < track_list.size();i++)
        {
           builder.begin("track");
           builder.attr("path", track_list[i]->file_path);
           builder.end();

        }
        builder.end();
        out << builder.getXML();
        globaldata.close();

}
void PlayList::getdata(QString path)
{
    QFile globaldata(path);
    QString file_path;
    QString f_format;
    Track* track;

    if (!globaldata.open(QFile::ReadOnly | QFile::Text))
        globaldata.close();
    else {

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&globaldata);
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                    foreach (const QXmlStreamAttribute &attr, xmlReader.attributes()) {
                        if(xmlReader.name() == "track")
                        {
                            if(attr.name().toString() == "path")
                            {
                                if(QFile::exists(attr.value().toString()))
                                {
                                    file_path = attr.value().toString();
                                    f_format = file_path.right((file_path.size()-file_path.lastIndexOf(".")-1));

                                    this->insertRow(this->rowCount());
                                    track = new Track(MetaDataFacade::get_meta_data(file_path, f_format), this->rowCount());

                                    track_list.push_back(track);

                                    this->setCellWidget(this->rowCount()-1,0,track->track_view);
                                    this->resizeRowToContents(this->rowCount()-1);
                                }
                            }
                        }
                    }
                }
                        xmlReader.readNext();
            }
        }

        this->all_cpec();
        emit set_all_spec(length_all_track, size_all_track);
        globaldata.close();
}

void PlayList::deletelist()
{
    QFile( QDir::currentPath() + "/Playlist/"+ name+".fpl").remove();
}
