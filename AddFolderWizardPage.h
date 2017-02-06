#ifndef ADDFOLDERWIZARDPAGE_H
#define ADDFOLDERWIZARDPAGE_H

#include "ui_AddFolderWizardPage.h"

#include <QStringListModel>

class AddFolderWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit AddFolderWizardPage(QWidget *parent = 0);

protected:
    bool isComplete() const;

private slots:
    void onAdd();
    void onDel();
    void onCurrentRowChanged(const QModelIndex& idx);

private:
    Ui::AddFolderWizardPage ui;

    QStringListModel    _model;
    QModelIndex         _selectedIdx;
};

#endif // ADDFOLDERWIZARDPAGE_H
