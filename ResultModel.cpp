#include "ResultModel.h"

#include <QFileInfo>

ResultModel::ResultModel(QObject* parent)
    : QStandardItemModel(parent)
{
    setColumnCount(1);
    setHeaderData(0, Qt::Horizontal, tr("Duplicated files"));
}

/**
 * GroupItem 1
 *    |--- File path 1
 *    |--- File path 2
 * GroupItem 2
 *    |--- File path 1
 *    |--- File path 2
 */
void ResultModel::addGroup(const QStringList& fileList)
{
    QStandardItem* parentItem = invisibleRootItem();
    QStandardItem* groupItem = new QStandardItem(QFileInfo(fileList.front()).fileName());
    parentItem->appendRow(groupItem);
    foreach (const QString& filePath, fileList)
    {
        QStandardItem* fileItem = new QStandardItem(filePath);
        fileItem->setCheckable(true);
        groupItem->appendRow(fileItem);
    }
}
