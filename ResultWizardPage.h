#ifndef RESULTWIZARDPAGE_H
#define RESULTWIZARDPAGE_H

#include "ui_ResultWizardPage.h"

class DuplicateFinderWizard;
class ResultModel;

class ResultWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ResultWizardPage(DuplicateFinderWizard* wizard = 0);

protected:
    void initializePage();

private slots:
    void selectionChanged(const QModelIndex& idx);

private:
    Ui::ResultWizardPage ui;

    DuplicateFinderWizard*  _wizard;
    ResultModel*            _model;
};

#endif // RESULTWIZARDPAGE_H
