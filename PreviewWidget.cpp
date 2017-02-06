#include "PreviewWidget.h"
#include "Settings.h"
#include <QProcess>
#include <QFile>

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    _model.setColumnCount(2);
    _model.setHeaderData(0, Qt::Horizontal, tr("Property"));
    _model.setHeaderData(1, Qt::Horizontal, tr("Value"));
    ui.tableView->setModel(&_model);
}

void PreviewWidget::setFilePath(const QString& filePath)
{
    QString exiftoolPath = Settings::getInstance()->getExiftoolPath();
    if (exiftoolPath.isEmpty() || !QFile::exists(exiftoolPath))
        return;

    QProcess* process = new QProcess;
    process->start(exiftoolPath, QStringList() << filePath);
    process->waitForFinished();

    QStringList list = QString(process->readAllStandardOutput()).split("\n");
    QMap<QString, QString> entries;
    foreach (QString line, list)
    {
        int indexColon = line.indexOf(':');
        if (indexColon > 0)
        {
            QString property    = line.left(indexColon).simplified();
            QString value       = line.right(line.length() - indexColon - 1).simplified();
            entries.insert(property, value);
        }
    }

    _model.removeRows(0, _model.rowCount());
    for (QMap<QString, QString>::const_iterator it = entries.begin(); it != entries.end(); ++it)
    {
        _model.appendRow(QList<QStandardItem*>()
                         << new QStandardItem(it.key())
                         << new QStandardItem(it.value()));
    }
    ui.tableView->resizeColumnToContents(0);
}
