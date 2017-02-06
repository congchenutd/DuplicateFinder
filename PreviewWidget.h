#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include "ui_PreviewWidget.h"

#include <QStandardItemModel>

class PreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget* parent = 0);

    void setFilePath(const QString& filePath);

private:
    Ui::PreviewWidget ui;

    QStandardItemModel _model;
};

#endif // PREVIEWWIDGET_H
