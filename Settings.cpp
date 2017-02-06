#include "Settings.h"

#include <QDir>
#include <QResource>
#include <QSize>

Settings *Settings::getInstance()
{
    if (_instance == 0)
        _instance = new Settings("DuplicateFinder.ini");
    return _instance;
}

QStringList Settings::getFolderList() const {
    return value("FolderList").toStringList();
}

void Settings::setFolderList(const QStringList& folderList) {
    setValue("FolderList", folderList);
}

QStringList Settings::getFileTypes() const {
    return QStringList()
            << "*.mpg" << "*.mpeg" << "*.mp4" << "*.mov"
            << "*.jpg" << "*.jpeg" << "*.png";
}

QString Settings::getExiftoolPath() const {
    return "/usr/local/bin/exiftool";
}

Settings::Settings(const QString& fileName)
    : QSettings(fileName, QSettings::IniFormat) {}

Settings* Settings::_instance = 0;
