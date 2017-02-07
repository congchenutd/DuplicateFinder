#include "DuplicateFinderWizard.h"
#include "ResultWizardPage.h"
#include "ResultModel.h"
#include "Settings.h"
#include <QDateTime>
#include <QDebug>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QMultiMap>

ResultWizardPage::ResultWizardPage(DuplicateFinderWizard* wizard) :
    QWizardPage(wizard), _wizard(wizard)
{
    ui.setupUi(this);
    ui.splitter->setSizes(QList<int>() << 300 << 200);
    connect(ui.radioDeleteOld,      SIGNAL(clicked(bool)), SLOT(onDeleteOld()));
    connect(ui.radioDeleteNew,      SIGNAL(clicked(bool)), SLOT(onDeleteNew()));
    connect(ui.radioDeletePattern,  SIGNAL(clicked(bool)), SLOT(onDeletePattern()));
    connect(ui.radioKeepPattern,    SIGNAL(clicked(bool)), SLOT(onKeepPattern()));
    connect(ui.radioDeleteFolder,   SIGNAL(clicked(bool)), SLOT(onDeleteFolder()));
    connect(ui.lePattern,           SIGNAL(textEdited(QString)),        SLOT(onPatternChanged()));
    connect(ui.tvDuplicates, SIGNAL(doubleClicked(QModelIndex)), SLOT(onFileDoubleClicked(QModelIndex)));
}

void ResultWizardPage::initializePage()
{
    _model = _wizard->getResultModel();
    ui.tvDuplicates->setModel(_model);
    ui.tvDuplicates->expandAll();
    connect(ui.tvDuplicates->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            SLOT(onSelectionChanged(QModelIndex)));

    disconnect(ui.comboFolders);
    foreach (const QString& folderPath, Settings::getInstance()->getFolderList())
        ui.comboFolders->addItem(folderPath);
    connect(ui.comboFolders, SIGNAL(currentIndexChanged(int)), SLOT(onFolderSelected()));
}

void ResultWizardPage::onSelectionChanged(const QModelIndex& idx)
{
    if (idx.parent().isValid()) // only file item
        ui.previewWidget->setFilePath(_model->data(idx).toString());
}

void ResultWizardPage::onFileDoubleClicked(const QModelIndex& idx)
{
    if (idx.parent().isValid()) // only file item
        QDesktopServices::openUrl(QUrl::fromLocalFile(_model->itemFromIndex(idx)->text()));
}

void ResultWizardPage::onDeleteOld() {
    select(new OldSelector);
}

void ResultWizardPage::onDeleteNew() {
    select(new NewSelector);
}

void ResultWizardPage::onDeletePattern() {
    select(new PatternSelector(ui.lePattern->text(), true));
}

void ResultWizardPage::onKeepPattern() {
    select(new PatternSelector(ui.lePattern->text(), false));
}

void ResultWizardPage::onDeleteFolder() {
    select(new FolderSelector(ui.comboFolders->currentText()));
}

void ResultWizardPage::onFolderSelected()
{
    ui.radioDeleteFolder->setChecked(true);
    onDeleteFolder();
}

void ResultWizardPage::onPatternChanged()
{
    ui.radioKeepPattern->setChecked(true);
    onKeepPattern();
}

void ResultWizardPage::select(Selector* selector)
{
    for (int row = 0; row < _model->rowCount(); ++row)
    {
        QModelIndex groupIdx = _model->index(row, 0);
        for (int fileRow = 0; fileRow < _model->rowCount(groupIdx); ++fileRow)
        {
            QModelIndex idx = _model->index(fileRow, 0, groupIdx);
            _model->itemFromIndex(idx)->setCheckState(Qt::Unchecked);
        }
        selector->select(_model, groupIdx);
    }
}

void OldSelector::select(ResultModel* model, QModelIndex& groupIdx) const
{
    // Sort and group the files by time
    QMultiMap<QDateTime, QModelIndex> time2Indexes;
    for (int row = 0; row < model->rowCount(groupIdx); ++row)
    {
        QModelIndex idx = model->index(row, 0, groupIdx);
        QString filePath = model->data(idx).toString();
        time2Indexes.insert(QFileInfo(filePath).lastModified(), idx);
    }

    // if there are more than 1 groups
    if (time2Indexes.keys().toSet().count() > 1)
    {
        // select the files in the 1st group
        QList<QModelIndex> indexes = time2Indexes.values(time2Indexes.keys().first());
        foreach (const QModelIndex& idx, indexes)
            model->itemFromIndex(idx)->setCheckState(Qt::Checked);
    }
}

void NewSelector::select(ResultModel* model, QModelIndex& groupIdx) const
{
    // Sort and group the files by time
    QMultiMap<QDateTime, QModelIndex> time2Indexes;
    for (int row = 0; row < model->rowCount(groupIdx); ++row)
    {
        QModelIndex idx = model->index(row, 0, groupIdx);
        QString filePath = model->data(idx).toString();
        time2Indexes.insert(QFileInfo(filePath).lastModified(), idx);
    }

    // if there are more than 1 groups
    if (time2Indexes.keys().toSet().count() > 1)
    {
        // select the files in the last group
        QList<QModelIndex> indexes = time2Indexes.values(time2Indexes.keys().last());
        foreach (const QModelIndex& idx, indexes)
            model->itemFromIndex(idx)->setCheckState(Qt::Checked);
    }
}


PatternSelector::PatternSelector(const QString& pattern, bool inclusive)
    : _pattern(QRegularExpression(pattern)), _inclusive(inclusive) {}

void PatternSelector::select(ResultModel* model, QModelIndex& groupIdx) const
{
    QModelIndexList selected;
    for (int row = 0; row < model->rowCount(groupIdx); ++row)
    {
        QModelIndex idx = model->index(row, 0, groupIdx);
        QString filePath = model->data(idx).toString();
        if (_inclusive && QFileInfo(filePath).fileName().contains(_pattern))
            selected << idx;
        else if (!_inclusive && !QFileInfo(filePath).fileName().contains(_pattern))
            selected << idx;
    }

    // avoid selecting the whole group
    if (selected.count() < model->rowCount(groupIdx))
        foreach (const QModelIndex& idx, selected)
            model->itemFromIndex(idx)->setCheckState(Qt::Checked);
}


FolderSelector::FolderSelector(const QString& folderPath)
    : _folderPath(folderPath) {}

void FolderSelector::select(ResultModel* model, QModelIndex& groupIdx) const
{
    QModelIndexList selected;
    for (int row = 0; row < model->rowCount(groupIdx); ++row)
    {
        QModelIndex idx = model->index(row, 0, groupIdx);
        QString filePath = model->data(idx).toString();
        if (filePath.startsWith(_folderPath))
            selected << idx;
    }

    // avoid selecting the whole group
    if (selected.count() < model->rowCount(groupIdx))
        foreach (const QModelIndex& idx, selected)
            model->itemFromIndex(idx)->setCheckState(Qt::Checked);
}
