#ifndef PROGRESSWIZARDPAGE_H
#define PROGRESSWIZARDPAGE_H

#include "ui_ProgressWizardPage.h"

class DuplicateFinderWizard;

class ProgressWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ProgressWizardPage(DuplicateFinderWizard* wizard = 0);

protected:
    void initializePage();
    bool isComplete() const;

private:
    void preScan();

private slots:
    void doScan();

private:
    Ui::ProgressWizardPage ui;

    QStringList _candidates;
    DuplicateFinderWizard* _wizard;
};


#endif // PROGRESSWIZARDPAGE_H
