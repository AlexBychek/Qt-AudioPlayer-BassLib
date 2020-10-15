#include "metadatafacade.h"

QStringList MetaDataFacade::get_meta_data(QString path_file, QString format_file)
    {
        QStringList list;
        list.push_back(path_file);
        list.push_back(QFileInfo(path_file).fileName());
        list.push_back(format_file);
        list.push_back(QFileInfo(path_file).absolutePath());

        if(format_file == "flac")
        {
            TagLib::FLAC::File fil(reinterpret_cast<const wchar_t*>(path_file.constData()));
            list.push_back(fil.tag()->artist().toCString(true));
            list.push_back(fil.tag()->title().toCString(true));
            list.push_back(fil.tag()->album().toCString(true));
            list.push_back(QString::number(fil.audioProperties()->bitrate()));
            if(fil.audioProperties()->channels() == 2)
            list.push_back("Stereo");
            else if(fil.audioProperties()->channels() == 1)
            list.push_back("Mono");
            list.push_back(list[2] + " :: " + list[7] + " kbps, " + QString::number((float)((float)fil.length() / 1024)/1024, 'f', 2)  + " MB, " + list[8]);
            list.push_back(QString::number((float)((float)fil.length() / 1024)/1024));
            list.push_back(QString::number(fil.audioProperties()->length()));


        }else if(format_file == "mp3")
        {
            static const char *IdPicture = "APIC";
            TagLib::MPEG::File file(reinterpret_cast<const wchar_t*>(path_file.constData()));
            list.push_back(file.tag()->artist().toCString(true));
            list.push_back(file.tag()->title().toCString(true));
            list.push_back(file.tag()->album().toCString(true));
            list.push_back(QString::number(file.audioProperties()->bitrate()));
            if(file.audioProperties()->channels() == 2)
            list.push_back("Stereo");
            else if(file.audioProperties()->channels() == 1)
            list.push_back("Mono");
            list.push_back(list[2] + " :: " + list[7] + " kbps, " + QString::number((float)((float)file.length() / 1024)/1024, 'f', 2)  + " MB, " + list[8]);
            list.push_back(QString::number((float)((float)file.length() / 1024)/1024));
            list.push_back(QString::number(file.audioProperties()->length()));

            }
        else
        {
            TagLib::FileRef file(reinterpret_cast<const wchar_t*>(path_file.constData()));
            list.push_back(file.tag()->artist().toCString(true));
            list.push_back(file.tag()->title().toCString(true));
            list.push_back(file.tag()->album().toCString(true));
            list.push_back(QString::number(file.audioProperties()->bitrate()));
            if(file.audioProperties()->channels() == 2)
            list.push_back("Stereo");
            else if(file.audioProperties()->channels() == 1)
            list.push_back("Mono");

            list.push_back(list[2] + " :: " + list[7] + " kbps, " + QString::number((float)((float)file.file()->length() / 1024)/1024, 'f', 2)  + " MB, " + list[8]);

            list.push_back(QString::number((float)((float)file.file()->length() / 1024)/1024));
            list.push_back(QString::number(file.audioProperties()->length()));

        }

        return list;
}

QPixmap MetaDataFacade::getPic(QString path_file, QString format_file)
{
    if(format_file == "flac" || format_file == "FLAC")
        return StategyFlac::getPic(path_file);
    else if(format_file == "mp3")
        return StategyMP3::getPic(path_file);
    else
        return StategyAnother::getPic(path_file);
}
