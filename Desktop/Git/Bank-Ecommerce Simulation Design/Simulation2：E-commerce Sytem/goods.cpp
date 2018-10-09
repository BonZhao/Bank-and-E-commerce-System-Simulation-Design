#include"goods.h"
#include<QMessageBox>

void gcons(acgn *al,book *bl,clothes *cl,food *fl)
{
    QString temp;
    acgn *a;
    book *b;
    clothes *c;
    food *f;
    a=(acgn*)new(acgn);
    b=(book*)new(book);
    c=(clothes*)new(clothes);
    f=(food*)new(food);
    int ia=0,ib=0,ic=0,ifo=0;

    QFile f1("goods/acgn.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
    }
    else
    {
    QTextStream txtInput(&f1);
    if(!txtInput.atEnd())
    {
    temp=txtInput.readLine();
    al->getname(temp.mid(5));
    temp=txtInput.readLine();
    al->getgid(temp.mid(4));
    temp=txtInput.readLine();
    al->getcom(temp.mid(8));
    temp=txtInput.readLine();
    al->getcost(temp.mid(10));
    temp=txtInput.readLine();
    al->getsleft(temp.mid(8));
    temp=txtInput.readLine();
    al->getdes(temp.mid(12));
    al->next=a;
    temp=txtInput.readLine();
    temp=txtInput.readLine();
    }
    while(!txtInput.atEnd())
    {
        a->getname(temp.mid(5));
        temp=txtInput.readLine();
        a->getgid(temp.mid(4));
        temp=txtInput.readLine();
        a->getcom(temp.mid(8));
        temp=txtInput.readLine();
        a->getcost(temp.mid(10));
        temp=txtInput.readLine();
        a->getsleft(temp.mid(8));
        temp=txtInput.readLine();
        a->getdes(temp.mid(12));
        acgn *copy;
        copy=(acgn*)new(acgn);
        a->next=copy;
        copy->next=NULL;
        a=copy;
        temp=txtInput.readLine();
        temp=txtInput.readLine();
        ia++;
    }
    if(ia!=0)
        ia++;
    al->gettypenum(QString::number(ia));
    }
    f1.close();

    QFile fb("goods/book.txt");
    if(!fb.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","BOOK FILE OUT",QMessageBox::Cancel);
    }
    else
    {
    QTextStream txtInput(&fb);
    if(!txtInput.atEnd())
    {
    temp=txtInput.readLine();
    bl->getname(temp.mid(5));
    temp=txtInput.readLine();
    bl->getgid(temp.mid(4));
    temp=txtInput.readLine();
    bl->getau(temp.mid(7));
    temp=txtInput.readLine();
    bl->getcost(temp.mid(10));
    temp=txtInput.readLine();
    bl->getsleft(temp.mid(8));
    temp=txtInput.readLine();
    bl->getdes(temp.mid(12));
    bl->next=b;
    temp=txtInput.readLine();
    temp=txtInput.readLine();
    }
    while(!txtInput.atEnd())
    {
        b->getname(temp.mid(5));
        temp=txtInput.readLine();
        b->getgid(temp.mid(4));
        temp=txtInput.readLine();
        b->getau(temp.mid(7));
        temp=txtInput.readLine();
        b->getcost(temp.mid(10));
        temp=txtInput.readLine();
        b->getsleft(temp.mid(8));
        temp=txtInput.readLine();
        b->getdes(temp.mid(12));
        book *copy;
        copy=(book*)new(book);
        b->next=copy;
        copy->next=NULL;
        b=copy;
        temp=txtInput.readLine();
        temp=txtInput.readLine();
        ib++;
    }
    if(ib!=0)
        ib++;
    bl->gettypenum(QString::number(ib));

    }
    fb.close();

    QFile f2("goods/clothes.txt");
    if(!f2.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
    }
    else
    {
    QTextStream txtInput(&f2);
    if(!txtInput.atEnd())
    {
    temp=txtInput.readLine();
    cl->getname(temp.mid(5));
    temp=txtInput.readLine();
    cl->getgid(temp.mid(4));
    temp=txtInput.readLine();
    cl->getcom(temp.mid(8));
    temp=txtInput.readLine();
    cl->getcost(temp.mid(10));
    temp=txtInput.readLine();
    cl->getsleft(temp.mid(8));
    temp=txtInput.readLine();
    cl->getdes(temp.mid(12));
    cl->next=c;
    temp=txtInput.readLine();
    temp=txtInput.readLine();
    }
    while(!txtInput.atEnd())
    {
        c->getname(temp.mid(5));
        temp=txtInput.readLine();
        c->getgid(temp.mid(4));
        temp=txtInput.readLine();
        c->getcom(temp.mid(8));
        temp=txtInput.readLine();
        c->getcost(temp.mid(10));
        temp=txtInput.readLine();
        c->getsleft(temp.mid(8));
        temp=txtInput.readLine();
        c->getdes(temp.mid(12));
        clothes *copy;
        copy=(clothes*)new(clothes);
        c->next=copy;
        copy->next=NULL;
        c=copy;
        temp=txtInput.readLine();
        temp=txtInput.readLine();
        ic++;
    }
    if(ic!=0)
        ic++;
    cl->gettypenum(QString::number(ic));
    }
    f2.close();

    QFile f3("goods/food.txt");
    if(!f3.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
    }
    else
    {

    QTextStream txtInput(&f3);
    if(!txtInput.atEnd())
    {
    temp=txtInput.readLine();
    fl->getname(temp.mid(5));
    temp=txtInput.readLine();
    fl->getgid(temp.mid(4));
    temp=txtInput.readLine();
    fl->getcom(temp.mid(8));
    temp=txtInput.readLine();
    fl->getcost(temp.mid(10));
    temp=txtInput.readLine();
    fl->getsleft(temp.mid(8));
    temp=txtInput.readLine();
    fl->getdes(temp.mid(12));
    fl->next=f;
    temp=txtInput.readLine();
    temp=txtInput.readLine();
    }
    while(!txtInput.atEnd())
    {

        f->getname(temp.mid(5));
        temp=txtInput.readLine();
        f->getgid(temp.mid(4));
        temp=txtInput.readLine();
        f->getcom(temp.mid(8));
        temp=txtInput.readLine();
        f->getcost(temp.mid(10));
        temp=txtInput.readLine();
        f->getsleft(temp.mid(8));
        temp=txtInput.readLine();
        f->getdes(temp.mid(12));
        food *copy;
        copy=(food*)new(food);
        f->next=copy;
        copy->next=NULL;
        f=copy;
        temp=txtInput.readLine();
        temp=txtInput.readLine();
        ifo++;
    }
    if(ifo!=0)
        ifo++;
    fl->gettypenum(QString::number(ifo));
    }
    f3.close();
}

void goods:: getname(QString na)             //添加会员类型
{
    this->name = na;
}

void goods::getcost(QString co)
{
    this->cost=co;
}

void goods::getdes(QString descrip)
{
    this->description=descrip;
}

void goods::getgid(QString gi)
{
    this->gid=gi;
}

void goods::getnum(QString n)
{
    this->num=n;
}

void goods::gettypenum(QString n)
{
    this->typenum=n;
}

void goods::getsleft(QString sto)
{
    this->sleft=sto;
}

void goods::getcom(QString com)
{
    this->company=com;
}

void goods::getau(QString au)
{
    this->author=au;
}



QString goods::addau()
{
    return author;
}

QString goods::addname()
{
    return name;
}

QString goods::addgid()
{
    return gid;
}

QString goods::adddes()
{
    return description;
}

QString goods::addcost()
{
    return cost;
}

QString goods::addsleft()
{
    return sleft;
}

QString goods::addcom()
{
    return company;
}

void goods::getsale(QString s)
{
    this->sale=s;
}

QString goods::addsale()
{
    return sale;
}

QString goods::addnum()
{
    return num;
}
QString goods::addtypenum()
{
    return typenum;
}


void book::getprice(QString disc)
{
   double a,b,c;
   QString co,s;
   co=addcost();
   a=co.toDouble();
   b=disc.toDouble();
   c=a*b;
   s=QString::number(c);
   getsale(s);
}

void food::getprice(QString disc)
{
   double a,b,c;
   QString co,s;
   co=addcost();
   a=co.toDouble();
   b=disc.toDouble();
   c=a*b;
   s=QString::number(c);
    getsale(s);
}

void acgn::getprice(QString disc)
{
   double a,b,c;
   QString co,s;
   co=addcost();
   a=co.toDouble();
   b=disc.toDouble();
   c=a*b;
   s=QString::number(c);
    getsale(s);
}

void clothes::getprice(QString disc)
{
   double a,b,c;
   QString co,s;
   co=addcost();
   a=co.toDouble();
   b=disc.toDouble();
   c=a*b;
   s=QString::number(c);
    getsale(s);
}

void goods::getprice(QString disc)
{
    double a,b,c;
    QString co,s;
    co=addcost();
    a=co.toDouble();
    b=disc.toDouble();
    c=a*b;
    s=QString::number(c);
     getsale(s);
}

void calcul(acgn *al,book *bl,clothes *cl,food *fl)
{
    QFile f1("goods/discount.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QString a,b,c,f;
        acgn *ac=al;
        book *bc=bl;
        clothes *cc=cl;
        food *fc=fl;
        QTextStream txtInput(&f1);
        a=txtInput.readLine().mid(2);
        b=txtInput.readLine().mid(2);
        c=txtInput.readLine().mid(2);
        f=txtInput.readLine().mid(2);
        while (ac->next!=NULL) {
            ac->getprice(a);
            ac=ac->next;
        }
        while (bc->next!=NULL) {
            bc->getprice(b);
            bc=bc->next;
        }
        while (cc->next!=NULL) {
           cc->getprice(c);
            cc=cc->next;
        }
        while (fc->next!=NULL) {
            fc->getprice(c);
            fc=fc->next;
        }
    }
    f1.close();
}

int addor(acgn *al,book *bl,clothes *cl,food *fl,QString uname,int buytype)
{
    QString gidn,n;
    acgn *a=al;
    book *b=bl;
    clothes *c=cl;
    food *f=fl;
    QFile f1("client/"+uname+"/shopcart.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QTextStream txtInput(&f1);
        QString sam=txtInput.readLine();
        while(!txtInput.atEnd())
        {
            int i=0;
            gidn=sam.mid(0,6);
            n=sam.mid(7);
            if(n.toInt()>0)
                buytype++;
            while(a->next!=NULL&&i==0)
            {
                QString temp;
                temp=a->addgid();
                if(!QString::compare(gidn,temp))
                {
                    a->getnum(n);
                    i=1;
                }
                a=a->next;
            }

            while(b->next!=NULL&&i==0)
            {
                QString temp;
                temp=b->addgid();
                if(!QString::compare(gidn,temp))
                {
                    b->getnum(n);
                    i=1;
                }
                b=b->next;
            }

             while(c->next!=NULL&&i==0)
             {
                 QString temp;
                 temp=c->addgid();
                 if(!QString::compare(gidn,temp))
                 {
                     c->getnum(n);
                     i=1;
                 }
                 c=c->next;
             }

             while(f->next!=NULL&&i==0)
             {
                 QString temp;
                 temp=f->addgid();
                 if(!QString::compare(gidn,temp))
                 {
                     f->getnum(n);
                     i=1;
                 }
                 f=f->next;
             }

            a=al;
            b=bl;
            c=cl;
            f=fl;
            sam=txtInput.readLine();
        }
    }
    f1.close();
    return buytype;
}

int judgetype(QString ju)
{
    QFile f1("goods/acgn.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QString sam,ci;
        QTextStream txtInput(&f1);
        while(!txtInput.atEnd())
        {
            ci=txtInput.readLine();
            sam=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
        int i=QString::compare(ju,sam.mid(4));
        if(i==0)
        return 1;

        }

    }

        f1.close();
    QFile f2("goods/book.txt");
    if(!f2.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QString sam,ci;
        QTextStream txtInput(&f2);
        while(!txtInput.atEnd())
        {
            ci=txtInput.readLine();
            sam=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
        int i=QString::compare(ju,sam.mid(4));
        if(i==0)
        return 2;

        }
    }

        f2.close();
    QFile f3("goods/clothes.txt");
    if(!f3.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QString sam,ci;
        QTextStream txtInput(&f3);

            while(!txtInput.atEnd())
            {
                ci=txtInput.readLine();
                sam=txtInput.readLine();
                ci=txtInput.readLine();
                ci=txtInput.readLine();
                ci=txtInput.readLine();
                ci=txtInput.readLine();
                ci=txtInput.readLine();
            int i=QString::compare(ju,sam.mid(4));
            if(i==0)
            return 3;

            }
    }

        f3.close();
    QFile f4("goods/food.txt");
    if(!f4.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QString sam,ci;
        QTextStream txtInput(&f4);
        while(!txtInput.atEnd())
        {
            ci=txtInput.readLine();
            sam=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
            ci=txtInput.readLine();
        int i=QString::compare(ju,sam.mid(4));
        if(i==0)
        return 4;

        }
    }

        f4.close();
        return 5;
}
