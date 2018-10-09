#ifndef GOODS
#define GOODS
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QDateTime>
#include <QLabel>

class goods{
private:
       QString description;
       QString cost;
       QString sleft;
       QString name;
       QString gid;
       QString company;
       QString author;
       QString sale;
       QString num;
       QString typenum;
public:
       virtual void getprice(QString disc);
       void getdes(QString descrip);
       void getgid(QString gi);
       void getname(QString na);
       void getsleft(QString sto);
       void getcost(QString co);
        void getcom(QString com);
        void getau(QString au);
        void getsale(QString s);
        void getnum(QString n);
        void gettypenum(QString n);
        QString addnum();
        QString adddes();
        QString addgid();
        QString addsleft();
        QString addcost();
        QString addcom();
        QString addau();
        QString addname();
        QString addsale();
        QString addtypenum();


};

#endif // GOODS

class book: public goods{
private:
         QString discount;
public:
         virtual void getprice(QString disc);
         class book *next;
};

class clothes: public goods{
private:
         QString discount;
public:
         virtual void getprice(QString disc);
         class clothes *next;
};

class food: public goods{

private:
         QString discount;
public:
         virtual void getprice(QString disc);
         class food *next;
};

class acgn: public goods{
private:
         QString discount;
public:
         virtual void getprice(QString disc);
         class acgn *next;
};

void gcons(acgn *al,book *bl,clothes *cl,food *fl);

void calcul(acgn *al,book *bl,clothes *cl,food *fl);
int addor(acgn *al, book *bl, clothes *cl, food *fl, QString uname, int buytype);
int judgetype(QString ju);
