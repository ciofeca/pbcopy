#ifndef PBCOPY_H
#define PBCOPY_H

#include <QGuiApplication>
#include <QStringList>
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
    if(sig==SIGALRM) QCoreApplication::quit();
}


class Clippami: public QObject
{
    Q_OBJECT
public:
    explicit Clippami(QObject* parent, QClipboard* clip, QString str): QObject(parent), c(clip), arg(str) { }

public slots:
    void run()
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);
        QTextStream cerr(stderr);
        cerr << "!--" << APP_NAME << " " << APP_VERSION << endl;
        if(c->text().size() > 0)
        {
            cerr << "!--currently " << c->text().size() << " characters in clipboard:" << endl;
            cout << c->text() << endl;
        }
        cerr << "!--reading from stdin:" << endl;
        QString txt(arg);
        txt += cin.readAll();
        c->clear();
        c->setText(txt);
        c->selectionChanged();
        cerr << "!--clipboard now " << c->text().size() << " characters:" << endl << c->text() << endl;

        signal(SIGALRM,::signalarm);
        alarm(1);
    }

private:
    QClipboard* c;
    QString arg;
};

#endif // PBCOPY_H
