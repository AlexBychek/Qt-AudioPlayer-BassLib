#ifndef METADATAFACADE_H
#define METADATAFACADE_H

#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/audioproperties.h>
#include <taglib/flacfile.h>
#include <taglib/apefile.h>
#include <taglib/mpegfile.h>

#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

#include <QString>
#include <QObject>
#include <QDebug>
#include <taglib/flacpicture.h>
#include <taglib/tlist.h>
#include <taglib/flacproperties.h>
#include <taglib/tpropertymap.h>
#include <QPixmap>
#include <QBuffer>
#include <QDir>

class StategyAnother
{
public:
    static QPixmap getPic(QString file_dir)
    {
         QFileInfo fi(file_dir);
         QDir dir(fi.absoluteDir());
         QPixmap pic;

         QStringList filterList;
         filterList << "*.jpg" << "*.png";
         dir.setNameFilters(filterList);
         QStringList resultList = dir.entryList();
         if(resultList.size() > 0)
         {
             QString format = resultList[0].right(resultList[0].size()-resultList[0].lastIndexOf(".")-1);
             QByteArray ba = format.toLocal8Bit();
             const char *formt = ba.data();
             pic.load(dir.path() + "/" + resultList[0], formt);
         }
         return pic;
    }
};

class StategyFlac
{
public:
    static QPixmap getPic(QString path_file)
    {
        QPixmap pic;

        TagLib::FLAC::File fil(reinterpret_cast<const wchar_t*>(path_file.constData()));
        TagLib::List<TagLib::FLAC::Picture*> ls;
        ls = fil.pictureList();
        if(ls.size() > 0)
        {
            pic.loadFromData((const uchar*)ls[0]->data().data(),ls[0]->data().size());
            return pic;
        }else
        {
            return StategyAnother::getPic(path_file);
        }
    }
};

class StategyMP3
{
public:
    static QPixmap getPic(QString path_file)
    {
        QPixmap pic;
        TagLib::MPEG::File file(reinterpret_cast<const wchar_t*>(path_file.constData()));
               TagLib::ID3v2::Tag *id3v2tag = file.ID3v2Tag();
               TagLib::ID3v2::FrameList Frame ;
               TagLib::ID3v2::AttachedPictureFrame *PicFrame ;
               void *RetImage = NULL, *SrcImage ;
               unsigned long Size ;
               if(id3v2tag)
               {
                   Frame = id3v2tag->frameListMap()["APIC"];
                    if (!Frame.isEmpty() )
                    {
                        for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it)
                              {
                                PicFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it) ;
                                {
                                  Size = PicFrame->picture().size() ;
                                  SrcImage = malloc ( Size ) ;
                                  if ( SrcImage )
                                  {
                                    pic.loadFromData( (const uchar*)PicFrame->picture().data(), PicFrame->picture().size() ) ;

                                    free( SrcImage ) ;
                                    return pic;
                                  }
                               }
                            }
                         }
                    else
                    {
                        return StategyAnother::getPic(path_file);
                    }
            }
    }
};

class MetaDataFacade
{
public:
    MetaDataFacade(){};

    static QStringList get_meta_data(QString, QString);
    static QPixmap getPic(QString, QString);
};

#endif // METADATAFACADE_H
