#ifndef RESULTWIZARDPAGE_H
#define RESULTWIZARDPAGE_H

#include "ui_ResultWizardPage.h"

class DuplicateFinderWizard;
class ResultModel;
class Selector;

class ResultWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ResultWizardPage(DuplicateFinderWizard* wizard = 0);

protected:
    void initializePage();

private slots:
    void onSelectionChanged (const QModelIndex& idx);
    void onFileDoubleClicked(const QModelIndex& idx);
    void onDeleteOld();
    void onDeleteNew();
    void onDeletePattern();
    void onKeepPattern();
    void onDeleteFolder();
    void onFolderSelected();
    void onPatternChanged();

private:
    void select(Selector* selector);

private:
    Ui::ResultWizardPage ui;

    DuplicateFinderWizard*  _wizard;
    ResultModel*            _model;
};

class Selector
{
public:
    virtual ~Selector() {}
    virtual void select(ResultModel* model, QModelIndex& groupIdx) const = 0;
};

class OldSelector: public Selector
{
public:
    void select(ResultModel* model, QModelIndex& groupIdx) const;
};

class NewSelector: public Selector
{
public:
    void select(ResultModel* model, QModelIndex& groupIdx) const;
};

class PatternSelector: public Selector
{
public:
    PatternSelector(const QString& pattern, bool inclusive);
    void select(ResultModel* model, QModelIndex& groupIdx) const;

private:
    QRegularExpression  _pattern;
    bool                _inclusive;
};

class FolderSelector: public Selector
{
public:
    FolderSelector(const QString& folderPath);
    void select(ResultModel* model, QModelIndex& groupIdx) const;

private:
    QString _folderPath;
};

#endif // RESULTWIZARDPAGE_H
