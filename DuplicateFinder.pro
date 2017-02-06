#-------------------------------------------------
#
# Project created by QtCreator 2017-02-02T10:50:35
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuplicateFinder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
        MainWindow.cpp \
    Main.cpp \
    AddFolderWizardPage.cpp \
    ResultWizardPage.cpp \
    ProgressWizardPage.cpp \
    Settings.cpp \
    DuplicateFinderWizard.cpp \
    ResultModel.cpp \
    SummaryWizardPage.cpp \
    PreviewWidget.cpp

HEADERS  += MainWindow.h \
    AddFolderWizardPage.h \
    ResultWizardPage.h \
    ProgressWizardPage.h \
    Settings.h \
    DuplicateFinderWizard.h \
    ResultModel.h \
    SummaryWizardPage.h \
    PreviewWidget.h

FORMS    += MainWindow.ui \
    AddFolderWizardPage.ui \
    ResultWizardPage.ui \
    ProgressWizardPage.ui \
    SummaryWizardPage.ui \
    PreviewWidget.ui
