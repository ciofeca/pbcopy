#ifndef PBCOPY_H
#define PBCOPY_H

#include <QGuiApplication>
#include <QClipboard>
#include <QTimer>
#include <QFile>
#include <QDebug>

class Clippami: public QObject
{
    Q_OBJECT
public:
    explicit Clippami(QObject* parent, QClipboard* clip): QObject(parent) { c = clip; }

public slots:
    void run()
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);
        QTextStream cerr(stderr);
        cerr << "!--pbcopy (" << c->text().size() << " bytes):" << endl;
        if(c->text().size() > 0) cout << c->text() << endl;
        cerr << "!--reading from stdin:" << endl;
        txt = cin.readAll();
        c->clear();
        c->setText(txt);
        cerr << "!--clipboard now " << c->text().size() << " bytes:" << endl << c->text() << endl;
        sleep(1);
        emit finished();
    }

signals:
    void finished();

private:
    QClipboard* c;
    QString txt;
    QFile file;
};

#endif // PBCOPY_H
