#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QWidget>
#include <QtCore>
#include <QDebug>
#include <qpushbutton.h>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

bank::bank()
{
    this -> B_id = "";
    this->money_sum="";
    this->cardNum="";
}

bank::~bank()
{

}

int regeca(card infoca,QString name,QString id,QString call,QString code,QString recode,QString location,QString email,QString message,QString cid,QString bid)
{
infoca.addName(name);
infoca.addcall(call);
infoca.addcode(code);
infoca.addemail(email);
infoca.addid(id);
infoca.addlocation(location);
infoca.addmessage(message);
int i=infoca.csave(bid,cid,infoca);
int u=cid.toDouble();
int x=bid.toDouble();
u=u-x*100000000;
QString newnum=QString::number(u),sum;
while(newnum.length()<3)
{
    newnum="0"+newnum;
}
QFile f("BANK/"+bid+"/total.txt");
if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
{

    QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
    return -1;
}
QTextStream txtInput(&f);
QString lineStr;
lineStr = txtInput.readLine();
lineStr = txtInput.readLine();
lineStr = txtInput.readLine();
    sum=lineStr.mid(4);
f.close();
QFile f1("BANK/"+bid+"/"+"total.txt");
if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
{
    QMessageBox::warning(NULL,"congratulations2","right2",QMessageBox::Cancel);
    return -1;
}
QTextStream txtOutput(&f1);
txtOutput << "bankid:"<<bid<< endl;
txtOutput << "cardnum:"<<newnum << endl;
txtOutput << "sum:"<<sum<< endl;
return i;
}
//////////////////////////
int bankset(QString name,QString deposit)
{
    int p;
    if(name.length()<1)
    {

        QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
        return -1;
    }

    if(deposit.length()<7)
    {

        QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
        return -1;
    }



    QByteArray ba = deposit.toLatin1();//QString 转换为 char*
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9')
        s++;
        if (*s)
        { //不是纯数字
            QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
            return -1;
        }

    QFile f("BANK/bankname.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        return -1;
    }
    QString newid=NULL;
    QTextStream txtInput(&f);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        p=QString::compare(name,lineStr.mid(2));
            if(p==0)
            {
                QMessageBox::warning(NULL,"warning","已存在",QMessageBox::Cancel);
                return -1;
            }
        newid=lineStr.mid(0,1);
    }
    f.close(); //创造新注册的银行的ID
    if (newid==NULL)
        newid="0";
    bool ok;
    int x=newid.toInt(&ok,10);
    x=x+1;
    newid=QString::number(x,10);

    QDir *temp = new QDir;
    bool exist = temp->exists("BANK/"+newid);
    if(exist)
    {
    QMessageBox::warning(NULL,"warning","error2",QMessageBox::Cancel);
    return -1;
    }
    else
    {
      bool ok1 = temp->mkdir("BANK/"+newid);
      if( !ok1 )
      QMessageBox::warning(NULL,"warning","error3",QMessageBox::Cancel);
    }

    QFile file("BANK/"+newid+"/"+"total.txt" );
    file.open( QIODevice::WriteOnly );
    file.close();

    QFile f1("BANK/"+newid+"/"+"total.txt");
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"congratulations2","right2",QMessageBox::Cancel);
        return -1;
    }

    QTextStream txtOutput(&f1);
    txtOutput << "bankid:"<<newid<< endl;
    txtOutput << "cardnum:000" << endl;
    txtOutput << "sum:"<<deposit<< endl;
    f.close();


    QFile mFile("BANK/bankname.txt");
    if(mFile.open(QIODevice::Append))     //方式为追加
    {
        QTextStream out(&mFile);
       out<<newid;
       out<<".";
       out<<name;
       out<<"\r\n";
    }
    mFile.flush();
    mFile.close();
    return 0;
}


int judge(QString co,QString ad)
{
    QFile f("admin/admin.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    lineStr = txtInput.readLine();
    if(QString::compare(lineStr,ad)!=0)
     {
        QMessageBox::warning(NULL,"warning","wrong input1",QMessageBox::Cancel);
        return -1;
    }
    lineStr = txtInput.readLine();
    if(QString::compare(lineStr,co)!=0)
     {
        QMessageBox::warning(NULL,"warning","wrong input2",QMessageBox::Cancel);
        return -1;
    }
    f.close();
    return 0;
}

QString bank::addcardn(QString cardn)
{
    return cardn;
}

QString bank::addsum(QString sum)
{
    return sum;
}

QString bank::addB_id(QString bid)
{
    return bid;
}

int judgecode(QString cid,QString message)
{
    QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    for(int i=0;i<8;i++)
    lineStr = txtInput.readLine();
    if(QString::compare(lineStr.mid(8),message)!=0)
     {
        QMessageBox::warning(NULL,"warning","wrong input",QMessageBox::Cancel);
        return -1;
    }
    f.close();

    return 0;
}

QString jelecost(QString pay,QString cid,QString code)
{
    QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
    QString Buffer[10],B2[5];
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        return "*c";
    }
    else
    {
        QTextStream inp(&f);
        QString x;
        for(int i=0;i<8;i++)
        {
            Buffer[i]=inp.readLine();
        }
        x=Buffer[3].mid(5);
        if(QString::compare(x,code))
         {
            return "*p";
        }
        else
        {
            QString sum;
            sum=Buffer[5].mid(4);
            if(sum.toDouble()<pay.toDouble())
            {
                return "*u";
            }
            else
            {
               double xian=sum.toDouble()-pay.toDouble();
               sum=QString::number(xian,'f',2);
               Buffer[5]="sum:"+sum;
               f.close();
               f.open(QIODevice::WriteOnly | QIODevice::Text);
               QTextStream inp2(&f);
               for(int i=0;i<8;i++)
               {
                  inp2<<Buffer[i]<<endl;
               }
                  f.close();

                QFile f1("BANK/"+cid.mid(0,1)+"/total.txt");
                   f1.open(QIODevice::ReadOnly | QIODevice::Text);
                     QTextStream inp3(&f1);
                   for(int i=0;i<3;i++)
                     B2[i]=inp3.readLine();
                   B2[2]="sum:"+QString::number(B2[2].mid(4).toDouble()-pay.toDouble(),'f',2);
                   f1.close();
                   f1.open(QIODevice::WriteOnly | QIODevice::Text);
                   QTextStream inp5(&f1);
                   for(int i=0;i<3;i++)
                   {
                      inp5<<B2[i]<<endl;
                   }
                   f1.close();

                   return "*s";
            }
    }
}
}
