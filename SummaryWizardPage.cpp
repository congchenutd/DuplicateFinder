#include "SummaryWizardPage.h"
#include "DuplicateFinderWizard.h"
#include "ResultModel.h"
#include "Settings.h"
#include <QDir>

SummaryWizardPage::SummaryWizardPage(DuplicateFinderWizard* wizard) :
    QWizardPage(wizard), _wizard(wizard)
{
    ui.setupUi(this);
}

void SummaryWizardPage::initializePage()
{
    _model = _wizard->getResultModel();
    int selectedCount = preScan();
    ui.progressBar->setMinimum(0);
    ui.progressBar->setValue(0);
    ui.progressBar->setMaximum(selectedCount);
    setTitle(tr("Deleting selected files"));
    doDelete();
}

bool SummaryWizardPage::isComplete() const {
    return ui.progressBar->value() == ui.progressBar->maximum();
}

int SummaryWizardPage::preScan()
{
    int selectedCount = 0;
    for (int row = 0; row < _model->rowCount(); ++row)
    {
        QModelIndex groupIdx = _model->index(row, 0);
        QStringList filePaths;
        for (int fileRow = 0; fileRow < _model->rowCount(groupIdx); ++fileRow)
        {
            QModelIndex idx = _model->index(fileRow, 0, groupIdx);
            QStandardItem* selectedItem = _model->itemFromIndex(idx);
            if (selectedItem->checkState() == Qt::Checked)
                selectedCount ++;
        }
    }
    return selectedCount;
}

void SummaryWizardPage::doDelete()
{
    for (int row = 0; row < _model->rowCount(); ++row)
    {
        QModelIndex groupIdx = _model->index(row, 0);
        QStringList filePaths;
        for (int fileRow = 0; fileRow < _model->rowCount(groupIdx); ++fileRow)
        {
            QModelIndex idx = _model->index(fileRow, 0, groupIdx);
            QStandardItem* selectedItem = _model->itemFromIndex(idx);
            if (selectedItem->checkState() == Qt::Checked)
            {
                QString oldFilePath = selectedItem->text();
                QString newFilePath = Settings::getInstance()->getTrashLocation()
                        + QDir::separator()
                        + QFileInfo(oldFilePath).fileName();
                QFile(oldFilePath).rename(newFilePath);
                ui.progressBar->setValue(ui.progressBar->value() + 1);
                qApp->processEvents();
                if (isComplete())
                    setTitle(tr("All done!"));
                emit completeChanged();
            }
        }
    }
}
