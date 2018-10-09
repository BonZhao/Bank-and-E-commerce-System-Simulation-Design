#ifndef CLIENT
#define CLIENT
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QDateTime>
#include <QLabel>


class card
{
private:
 QString name;
 QString callNumber;
 QString IDNum;
 QString email;//
 QString location;
 QString message;
 QString code;
 QString sum;

public:
    card();
    ~card();
    QString deposit();
    QString getname();
    QString getcall();
    QString getIDnum();
    QString getlocation();
    QString getemail();
    QString getcode();
    QString getmessage();

    void addName(QString n);
    void addcall(QString n);
    void addid(QString n);
    void addcode(QString n);
    void addlocation(QString n);
    void addmessage(QString n);
    void addemail(QString n);
    int csave(QString bid, QString cid, card c);
};



#endif // CLIENT

