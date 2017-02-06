#include "DuplicateFinderWizard.h"
#include "ResultWizardPage.h"
#include "ResultModel.h"
#include <QDebug>

ResultWizardPage::ResultWizardPage(DuplicateFinderWizard* wizard) :
    QWizardPage(wizard), _wizard(wizard)
{
    ui.setupUi(this);
    ui.splitter->setSizes(QList<int>() << 300 << 200);
}

void ResultWizardPage::initializePage()
{
    _model = _wizard->getResultModel();
    ui.tvDuplicates->setModel(_model);
    ui.tvDuplicates->expandAll();
    connect(ui.tvDuplicates->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            SLOT(selectionChanged(QModelIndex)));
}

void ResultWizardPage::selectionChanged(const QModelIndex& idx)
{
    if (idx.parent().isValid()) // only file item
        ui.previewWidget->setFilePath(_model->data(idx).toString());
}
