#include"client.h"
#include<QMessageBox>
#include<QDir>


int judgecode(QString cid, QString message)
{
    QFile f("client/"+cid+"/"+cid+".txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    for(int i=0;i<7;i++)
    lineStr = txtInput.readLine();
    if(QString::compare(lineStr.mid(8),message)!=0)
     {
        QMessageBox::warning(NULL,"warning","wrong input",QMessageBox::Cancel);
        return -1;
    }
    f.close();

    return 0;
}

int client_creat(QString name,QString uname,QString code,QString call, QString id, QString cid, QString message, QString address)
{
    QDir *temp = new QDir;
    bool exist = temp->exists("client/"+uname);
    if(exist)
    {
    QMessageBox::warning(NULL,"warning","error2",QMessageBox::Cancel);
    return -1;
    }
    else
    {
      bool ok1 = temp->mkdir("client/"+uname);
      if( !ok1 )
      QMessageBox::warning(NULL,"warning","error3",QMessageBox::Cancel);
    }

    QFile file("client/"+uname+"/"+uname+".txt" );
    file.open( QIODevice::WriteOnly );
    file.close();

    QFile f1("client/"+uname+"/"+uname+".txt");
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","error4",QMessageBox::Cancel);
        return -1;
    }

    QTextStream txtOutput(&f1);
    txtOutput << "name:"<<name<< endl;
    txtOutput << "username:"<<uname << endl;
    txtOutput << "call:"<<call<< endl;
    txtOutput << "code:"<<code<< endl;
    txtOutput << "id:"<<id<< endl;
    txtOutput << "cid:"<<cid<< endl;
    txtOutput << "message:"<<message<< endl;
    txtOutput << "address:"<<address<< endl;
    f1.close();

    QFile file2("client/"+uname+"/"+cid+".txt" );
    file2.open( QIODevice::WriteOnly );
    file2.close();

    QFile file3("findc/"+uname+".txt" );
    file3.open( QIODevice::WriteOnly );
    file3.close();

    QFile f2("findc/"+uname+".txt");
    if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","error5",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtOutput1(&f2);
    txtOutput1 <<code<< endl;
    f2.close();

    QFile file5("findcid/"+uname+".txt" );
    file5.open( QIODevice::WriteOnly );
    file5.close();

    QFile f3("findcid/"+uname+".txt");
    if(!f3.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","error6",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtOutput3(&f3);
    txtOutput3 <<cid<< endl;
    f3.close();

    QString tra,copy;
    int t;
    tra=cid;
    t=tra.toInt();
    t=t%100000+1;
    if(t!=100000)
    {
    tra=QString::number(t,10);
    copy=QString::number(cid.toInt()/100000);
    }
    else
    {
       copy=QString::number(cid.toInt()/100000+1);
       tra='0';
    }
    QFile f5("client/total.txt");
    if(!f5.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","error7",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtOutput5(&f5);
    txtOutput5 <<copy<< endl;
    txtOutput5 <<tra<< endl;
    f5.close();


    QFile file6("client/"+uname+"/shopcart.txt" );
    file6.open( QIODevice::WriteOnly );
    file6.close();


    QFile fs("client/"+uname+"/shopcart.txt");
    QFile fa("goods/total.txt");
    if(!fs.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","error6",QMessageBox::Cancel);
        return -1;
    }
    if(!fa.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","error6",QMessageBox::Cancel);
        return -1;
    }
    QTextStream txtOutputs(&fs);
    QTextStream txtOutputa(&fa);
    QString u1,u2,u3;
    int x,x2;
    u3=txtOutputa.readLine();
    u1=txtOutputa.readLine();
    x=u1.toInt();
    for(int i=1;i<=x;i++)
    {
        x2=100000*u3.toInt()+i;
        u2=QString::number(x2);
        txtOutputs<<u2<<":0"<<endl;
    }
    txtOutputs<<"******"<<endl;
    fs.close();

    QFile file9("client/"+uname+"/bank.txt" );
    file9.open( QIODevice::WriteOnly );
    file9.close();

    return 0;
}
