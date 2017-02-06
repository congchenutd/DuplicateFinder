#ifndef SUMMARYWIZARDPAGE_H
#define SUMMARYWIZARDPAGE_H

#include "ui_SummaryWizardPage.h"

class SummaryWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit SummaryWizardPage(QWidget *parent = 0);

private:
    Ui::SummaryWizardPage ui;
};

#endif // SUMMARYWIZARDPAGE_H
