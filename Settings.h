#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
public:
    static Settings* getInstance();

    QStringList getFolderList() const;
    void setFolderList(const QStringList& folderList);

    QStringList getFileTypes() const;
    QString     getExiftoolPath() const;

private:
    Settings(const QString& fileName);

private:
    static Settings* _instance;
};

#endif // SETTINGS_H
