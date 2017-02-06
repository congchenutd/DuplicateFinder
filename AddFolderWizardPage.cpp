#include "AddFolderWizardPage.h"
#include "Settings.h"
#include <QFileDialog>

AddFolderWizardPage::AddFolderWizardPage(QWidget *parent) :
    QWizardPage(parent)
{
    ui.setupUi(this);
    setTitle("Add folders for scan");
    ui.listView->setModel(&_model);
    ui.btDel->setEnabled(false);

    connect(ui.btAdd, SIGNAL(clicked(bool)), SLOT(onAdd()));
    connect(ui.btDel, SIGNAL(clicked(bool)), SLOT(onDel()));
    connect(ui.listView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(onCurrentRowChanged(QModelIndex)));
}

// Enables next button
bool AddFolderWizardPage::isComplete() const {
    return _model.rowCount() > 0;
}

void AddFolderWizardPage::onAdd()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Folder"),
                                                    ".",
                                                    QFileDialog::ShowDirsOnly |
                                                    QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty() || _model.stringList().contains(dir, Qt::CaseInsensitive))
        return;

    int lastRow = _model.rowCount();
    _model.insertRow(lastRow);
    _model.setData(_model.index(lastRow), dir);

    emit completeChanged();     // re-validate isComplete()
    Settings::getInstance()->setFolderList(_model.stringList());
}

void AddFolderWizardPage::onDel()
{
    if (_selectedIdx.isValid())
    {
        _model.removeRow(_selectedIdx.row());
        emit completeChanged();     // re-validate isComplete()
    }
}

void AddFolderWizardPage::onCurrentRowChanged(const QModelIndex& idx)
{
    _selectedIdx = idx;
    ui.btDel->setEnabled(idx.isValid());
}
