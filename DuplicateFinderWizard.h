#ifndef DUPLICATEFINDERWIZARD_H
#define DUPLICATEFINDERWIZARD_H

#include <QWizard>

class ResultModel;

class DuplicateFinderWizard : public QWizard
{
public:
    DuplicateFinderWizard(QWidget* parent = Q_NULLPTR);
    void addResult(const QStringList& fileList);
    void clearResult();
    ResultModel* getResultModel() const;

private:
    ResultModel* _resultModel;
};

#endif // DUPLICATEFINDERWIZARD_H
