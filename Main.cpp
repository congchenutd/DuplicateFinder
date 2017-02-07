#include "DuplicateFinderWizard.h"
#include <QApplication>
#include <QDir>

// workaround for a bug on mac > Mavericks
// Finder returns / as the working path of an app bundle
// but if the app is run from terminal, the path is correct
// This method calcluates the path of the bundle from the application's path
QString getCurrentPath()
{
    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    return dir.absolutePath();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

#ifdef Q_OS_OSX
    QDir::setCurrent(getCurrentPath());
#endif

    DuplicateFinderWizard wizard;
    wizard.showMaximized();

    return app.exec();
}
