#include "SummaryWizardPage.h"

SummaryWizardPage::SummaryWizardPage(QWidget *parent) :
    QWizardPage(parent)
{
    ui.setupUi(this);
    setTitle(tr("All done!"));
}
