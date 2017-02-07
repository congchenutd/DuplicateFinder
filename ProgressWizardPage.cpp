#include "DuplicateFinderWizard.h"
#include "ProgressWizardPage.h"
#include "Settings.h"
#include "ResultModel.h"

#include <QDirIterator>
#include <QDebug>
#include <QCryptographicHash>
#include <QTimer>
#include <QDateTime>

ProgressWizardPage::ProgressWizardPage(DuplicateFinderWizard* wizard) :
    QWizardPage(wizard), _wizard(wizard)
{
    ui.setupUi(this);
    setTitle(tr("Scanning for duplicate files"));
}

void ProgressWizardPage::initializePage()
{
    _wizard->clearResult();
    preScan();
    ui.progressBar->setMinimum(0);
    ui.progressBar->setMaximum(_candidates.count());
    ui.progressBar->setValue(0);
    QTimer::singleShot(500, this, SLOT(doScan()));  // Delay scan until the page is loaded
}

bool ProgressWizardPage::isComplete() const {
    return ui.progressBar->value() == _candidates.count();
}

void ProgressWizardPage::preScan()
{
    QStringList folderList = Settings::getInstance()->getFolderList();
    QStringList fileTypes  = Settings::getInstance()->getFileTypes();

    QMultiHash<qint64, QString> size2Path;
    foreach (const QString& folder, folderList)
    {
        QDirIterator it(folder, fileTypes, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            QString filePath = it.next();
            size2Path.insert(QFileInfo(filePath).size(), filePath);
        }
    }

    foreach (qint64 size, size2Path.keys().toSet())
    {
        QStringList paths = size2Path.values(size);
        if (paths.count() > 1)
            _candidates << paths;
    }
}

void ProgressWizardPage::doScan()
{
    QMultiHash<QByteArray, QString> signature2Path;
    foreach (const QString& filePath, _candidates)
    {
        QFile file(filePath);
        file.open(QFile::ReadOnly);
        QByteArray md4 = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md4).toHex();
        signature2Path.insert(md4, filePath);
        ui.progressBar->setValue(ui.progressBar->value() + 1);
        qApp->processEvents();
        emit completeChanged();
    }

    foreach (const QByteArray& md4, signature2Path.keys().toSet())
    {
        QStringList paths = signature2Path.values(md4);
        if (paths.count() > 1)
            _wizard->addResult(paths);
    }
}
