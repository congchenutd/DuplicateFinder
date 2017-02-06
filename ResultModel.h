#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include <QStandardItemModel>

class ResultModel : public QStandardItemModel
{
public:
    ResultModel(QObject* parent = Q_NULLPTR);

    void addGroup(const QStringList& fileList);
};

#endif // RESULTMODEL_H
