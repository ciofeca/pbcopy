// pbcopy -- alfonso martone

#include "pbcopy.h"

int main(int argc, char* argv[])
{
    QString name(APP_NAME), vers(APP_VERSION), org(APP_AUTHOR);
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setApplicationName(name);
    app->setApplicationVersion(vers);
    app->setOrganizationName(org);
    QStringList arg;
    for(int n=1; n<argc; n++) arg << argv[n];
    Clippami task(&*app, QGuiApplication::clipboard(), arg.join((QChar)(' ')));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    view->setTitle(name);
    view->show();
    QObject::connect(&task, SIGNAL(finished()), &*app, SLOT(quit()));
    QTimer::singleShot(333, &task, SLOT(run()));
    return app->exec();
}

// ---
