#include "DuplicateFinderWizard.h"
#include "AddFolderWizardPage.h"
#include "ResultWizardPage.h"
#include "ProgressWizardPage.h"
#include "ResultModel.h"
#include "SummaryWizardPage.h"

DuplicateFinderWizard::DuplicateFinderWizard(QWidget* parent)
    : QWizard(parent)
{
    setWindowTitle("Duplicate Finder");
    setWindowIcon(QIcon(":/Images/Duplicate.png"));
    setWizardStyle(QWizard::ClassicStyle);
    addPage(new AddFolderWizardPage);
    addPage(new ProgressWizardPage(this));
    addPage(new ResultWizardPage(this));
    addPage(new SummaryWizardPage(this));

    _resultModel = new ResultModel;
}

void DuplicateFinderWizard::addResult(const QStringList& fileList) {
    _resultModel->addGroup(fileList);
}

void DuplicateFinderWizard::clearResult()
{
    _resultModel->removeRows(0, _resultModel->rowCount());
}

ResultModel* DuplicateFinderWizard::getResultModel() const {
    return _resultModel;
}
