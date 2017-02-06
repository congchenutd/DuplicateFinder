#include "AddFolderWizardPage.h"
#include "ResultWizardPage.h"
#include "MainWindow.h"
#include "ProgressWizardPage.h"
#include "DuplicateFinderWizard.h"
#include <QApplication>
#include <QWizard>
#include <QMediaPlayer>
#include <QVideoWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DuplicateFinderWizard wizard;
    wizard.show();

//    MainWindow wnd;
//    wnd.showMaximized();

//    QMediaPlayer* player = new QMediaPlayer;
//    player->setMedia(QUrl::fromLocalFile("/Users/Cong/OneDrive/Pictures/Camera Roll/20170204_025345000_iOS.MOV"));

//    QVideoWidget* videoWidget = new QVideoWidget;
//    player->setVideoOutput(videoWidget);
//    videoWidget->showMaximized();
//    player->play();

    return app.exec();
}
