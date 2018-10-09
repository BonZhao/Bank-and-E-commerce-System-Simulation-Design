#include "card.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
card::card()
{
    this -> name = "";
    this -> callNumber = "NULL";
    this->IDNum = "IDNum";
    this->location="NULL";
    this->email="NULL";
    this->message="";
    this->code="";
}

card::~card()
{

}

QString card:: getname()
{
    return name;
}


QString card:: getcall()
{
    return callNumber;
}

QString card:: getIDnum()
{
    return IDNum;
}

QString card:: getlocation()
{
    return location;
}

QString card::getemail()
{
    return email;
}

QString card::getcode()
{
    return code;
}

QString card::getmessage()
{
    return message;
}




void card::addName(QString n )    //添加姓名和电话号码
{
        this -> name = n;

}

void card::addcall(QString n)              //添加电话号码
{
    this -> callNumber = n;
}

void card:: addid(QString n)             //添加身份证号
{
    this->IDNum = n;
}

void card:: addcode(QString n)
{
    this->code = n;
}

void card:: addlocation(QString n)
{
    this->location = n;
}

void card:: addmessage(QString n)
{
    this->message = n;
}

void card:: addemail(QString n)
{
    this->email = n;
}

int card::csave(QString bid,QString cid,card c)
{
    QFile file("BANK/"+bid+"/"+cid+".txt" );
    file.open( QIODevice::WriteOnly );
    file.close();

    QFile f1("BANK/"+bid+"/"+cid+".txt" );
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","wrong2",QMessageBox::Cancel);
        return -1;
    }

    QTextStream txtOutput(&f1);
    txtOutput << "name:"<<c.getname()<< endl;
    txtOutput << "id:"<<c.getIDnum() << endl;
    txtOutput << "call:"<<c.getcall()<< endl;
    txtOutput << "code:"<<c.getcode()<< endl;
    txtOutput << "location:"<<c.getlocation()<< endl;
    txtOutput << "sum:0"<< endl;
    txtOutput << "email:"<<c.getcall()<< endl;
    txtOutput << "message:"<<c.getmessage()<< endl;
    f1.close();

    QFile file1("BANK/findc/"+cid+".txt" );
    file1.open( QIODevice::WriteOnly );
    file1.close();
    QFile f2("BANK/findc/"+cid+".txt");
    if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","wrong2",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtOutput1(&f2);
    txtOutput1<<c.getcode()<< endl;
    f2.close();
    return 0;
}





