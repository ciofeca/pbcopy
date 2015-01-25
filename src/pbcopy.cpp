// pbcopy -- alfonso martone

#include "pbcopy.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Clippami task(&app, QGuiApplication::clipboard());
    QObject::connect(&task, SIGNAL(finished()), &app, SLOT(quit()));
    QTimer::singleShot(0, &task, SLOT(run()));
    return app.exec();
}
