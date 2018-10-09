#ifndef CLIENT
#define CLIENT
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QDateTime>
#include <QLabel>

int client_creat(QString name,QString uname,QString code,QString call, QString id, QString cid, QString message, QString address);
int judgecode(QString cid, QString message);
#endif // CLIENT

