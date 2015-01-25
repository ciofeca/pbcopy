#ifndef PBCOPY_H
#define PBCOPY_H

#include <QGuiApplication>
#include <QClipboard>
#include <QQuickView>
#include <QTimer>
#include <QFile>
#include <QDebug>

#include <sailfishapp.h>

#include <signal.h>
#include <unistd.h>

static void signalarm(int sig)
{
    if(sig==SIGALRM) exit(0);
}


class Clippami: public QObject
{
    Q_OBJECT
public:
    explicit Clippami(QObject* parent, QClipboard* clip): QObject(parent), c(clip) { }

public slots:
    void run()
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);
        QTextStream cerr(stderr);
        cerr << "!--" << APP_NAME << " " << APP_VERSION << endl;
        if(c->text().size() > 0)
        {
            cerr << "!--currently " << c->text().size() << " bytes in clipboard:" << endl;
            cout << c->text() << endl;
        }
        cerr << "!--reading from stdin:" << endl;
        QString txt(cin.readAll());
        c->clear();
        c->setText(txt);
        c->selectionChanged();
        cerr << "!--clipboard now " << c->text().size() << " bytes:" << endl << c->text() << endl;

        signal(SIGALRM,::signalarm);
        alarm(1);
    }

private:
    QClipboard* c;
};

#endif // PBCOPY_H
