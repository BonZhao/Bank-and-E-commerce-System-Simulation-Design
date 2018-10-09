#ifndef BANK_BACKEND
#define BANK_BACKEND
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QDateTime>
#include <QLabel>
#include"card.h"

class bank
{
public:
    bank();
    ~bank();
    QString addcardn(QString cardn);
    QString addsum(QString sum);
    QString addB_id(QString bid);


private:
    QString B_id;
    QString cardNum;
    QString money_sum;
};

void regest();
void find_code();
int judge(QString co,QString ad);
int bankset(QString name,QString deposit);
int regeca(card infoca, QString name, QString id, QString call, QString code, QString recode, QString location, QString email, QString message, QString bid,QString cid);
int judgecode(QString cid, QString message);
QString jelecost(QString pay, QString cid, QString code);
#endif // BANK_BACKEND

