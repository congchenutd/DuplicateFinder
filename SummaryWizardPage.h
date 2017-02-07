#ifndef SUMMARYWIZARDPAGE_H
#define SUMMARYWIZARDPAGE_H

#include "ui_SummaryWizardPage.h"

class DuplicateFinderWizard;
class ResultModel;

class SummaryWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SummaryWizardPage(DuplicateFinderWizard* wizard = 0);

protected:
    void initializePage();
    bool isComplete() const;

private:
    int preScan();
    void doDelete();

private:
    Ui::SummaryWizardPage ui;

    DuplicateFinderWizard*  _wizard;
    ResultModel*            _model;
};

#endif // SUMMARYWIZARDPAGE_H
