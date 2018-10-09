#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QMessageBox>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include<QTableWidget>
#include"client.h"
#include<goods.h>
#include <QTableWidgetItem>
#include <QTcpSocket>
#include <QTcpServer>
#include<QtNetwork>
#include<QDir>

book *bl;
food *fl;
clothes *cl;
acgn *al;
int buytype;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    al=(acgn*)new(acgn);
    bl=(book*)new(book);
    cl=(clothes*)new(clothes);
    fl=(food*)new(food);
    ui->setupUi(this);
    ui ->stackedWidget ->setCurrentIndex(0);
    gcons(al,bl,cl,fl);
    calcul(al,bl,cl,fl);
    QString man[10],jian[10];
    int ii=0,jj=0;
    QFile ass("goods/manjian.txt");
            if(!ass.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
            }
     else
            {
                QTextStream txtInput(&ass);
                while(!txtInput.atEnd())
                {
                    man[ii]=txtInput.readLine();
                    jian[jj]=txtInput.readLine();
                    ii++;
                    jj++;
                }
                ui->label_61->setText(man[0]);
                ui->label_63->setText(jian[0]);
                ui->label_62->setText(man[1]);
                ui->label_64->setText(jian[1]);

            }

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_quit_clicked()
{
    QApplication* app;
    app->quit();
}

void MainWindow::on_pushButton_clicked()
{
ui->lineEdit_3->setText("");
ui->lineEdit_4->setText("");
ui->stackedWidget->setCurrentIndex(7);
ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

void MainWindow::on_pushButton_11_clicked()
{
ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_12_clicked()
{
ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    QString cid,message;
    cid=ui->lineEdit_4->text();
    message=ui->lineEdit_3->text();
    int i=judgecode(cid,message);
    if(i==0)
    {
        QFile f1("findc/"+cid+".txt");
        if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui ->stackedWidget ->setCurrentIndex(7);
        }
        else
        {
        QTextStream txtInput1(&f1);
        QString lineStr1;
        lineStr1 = txtInput1.readLine();
        ui->label_42->setText(lineStr1);
        f1.close();
        ui ->stackedWidget ->setCurrentIndex(8);
        }
    }
    else
    {
        ui->lineEdit_3->setText("");
        ui->lineEdit_4->setText("");
        ui ->stackedWidget ->setCurrentIndex(7);
    }
}

void MainWindow::on_pushButton_regester_clicked()
{

    QStringList bankchoice;
    QString innn,clid,clids;
    int tra,tras;
    QFile f1("client/total.txt");



     if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
     {

         QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
         ui ->stackedWidget ->setCurrentIndex(0);
     }
     else
     {
     QTextStream txtInput1(&f1);
     clid=txtInput1.readLine();
     clids=txtInput1.readLine();
     tra=clid.toInt();
     tras=clids.toInt();
     if(tra<99999)
     {
         tra=tras+tra*100000;
         clid=QString::number(tra);
     }
      else
     {
         tra++;
         tras=0;
         tra=tras+tra*100000;
         clid=QString::number(tra);
     }

     ui->lineEdit_address->setText("");
     ui->lineEdit_name->setText("");
     ui->lineEdit_phone->setText("");
     ui->lineEdit_id->setText("");
     ui->lineEdit_code->setText("");
     ui->lineEdit_code->setEchoMode(QLineEdit::Password);
     ui->lineEdit_recode->setText("");
     ui->lineEdit_recode->setEchoMode(QLineEdit::Password);
     ui->lineEdit_uname->setText("");
     ui->lineEdit_message->setText("");
     ui->label_54->setText(clid);
    ui ->stackedWidget ->setCurrentIndex(1);
     }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}

void MainWindow::on_pushButton_7_clicked()
{

    QStringList bankchoice;
    QString innn;
    QFile f("bankname.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        ui ->stackedWidget ->setCurrentIndex(0);
    }
    else
    {
      QTextStream txtInput(&f);
      while(!txtInput.atEnd())
      {

        innn = txtInput.readLine();
         bankchoice.append(innn);
      }
      bankchoice.append("无");
     f.close();
    ui ->stackedWidget ->setCurrentIndex(1);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    int i;
    QString name,uname,code,call,id,cid,message,address;
    name=ui->lineEdit_name->text();
    uname=ui->lineEdit_uname->text();
    code=ui->lineEdit_code->text();
    message=ui->lineEdit_message->text();
    address=ui->lineEdit_address->text();
    call=ui->lineEdit_phone->text();
    id=ui->lineEdit_id->text();
    cid=ui->label_54->text();
    i=client_creat(name,uname,code,call,id,cid,message,address);
    if(i==0)
    {
        buytype=addor(al,bl,cl,fl,uname,0);
    ui ->stackedWidget ->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->label_welcome->setText("欢迎"+uname);
    }
    else
    ui ->stackedWidget ->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{

    QString name,id,call,code,recode,location,cid,message,uname,bank;
    name=ui->lineEdit_name->text();
    id=ui->lineEdit_id->text();
    call=ui->lineEdit_phone->text();
    code=ui->lineEdit_code->text();
    recode=ui->lineEdit_recode->text();
    location=ui->lineEdit_address->text();
    message=ui->lineEdit_message->text();
    uname=ui->lineEdit_uname->text();
    QDir f("client/"+uname);
    int i=0;
    if(name.length()<1||id.length()!=18||call.length()<11||code.length()<6||recode.length()<6||location.length()<0||message.length()<1||uname.length()<1)
    {
        QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
        i= -1;
    }
    if(f.exists())
    {
        QMessageBox::warning(NULL,"warning","user exists",QMessageBox::Cancel);
        i= -1;
        ui->lineEdit_uname->setText("");
    }
    QByteArray ba = call.toLatin1();//QString 转换为 char*
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9')
        s++;
        if (*s)
        { //不是纯数字
            QMessageBox::warning(NULL,"warning","call input wrong",QMessageBox::Cancel);
            i=-1;
        }

    if(QString::compare(code,recode)!=0)
    {
        QMessageBox::warning(NULL,"warning","code input wrong",QMessageBox::Cancel);
        i= -1;
    }


    if(i==0)
    {   ui->label_34->setText(name);
        ui->label_33->setText(id);
        ui->label_31->setText(uname);
        ui->label_35->setText(location);
        ui->label_32->setText(call);
        ui->label_36->setText(message);

        ui ->stackedWidget ->setCurrentIndex(2);
    }
    else
    {
        ui->lineEdit_id->setText("");
        ui->lineEdit_phone->setText("");
        ui->lineEdit_code->setText("");
        ui->lineEdit_recode->setText("");
        ui ->stackedWidget ->setCurrentIndex(1);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(1);
}

void MainWindow::on_pushButton_23_clicked()
{
    acgn *a;
    book *b;
    clothes *c;
    food *f;
    a=al;
    b=bl;
    c=cl;
    f=fl;
    QString uname=ui->lineEdit->text();
    QFile f1("client/"+uname+"/shopcart.txt");
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QTextStream inputtext(&f1);
        while(a->next!=NULL)
        {
        inputtext<<a->addgid()<<":"<<a->addnum()<<endl;
        a=a->next;
        }
        while(b->next!=NULL)
        {
        inputtext<<b->addgid()<<":"<<b->addnum()<<endl;
        b=b->next;
        }
        while(c->next!=NULL)
        {
        inputtext<<c->addgid()<<":"<<c->addnum()<<endl;
        c=c->next;
        }
        while(f->next!=NULL)
        {
        inputtext<<f->addgid()<<":"<<f->addnum()<<endl;
        f=f->next;
        }
        inputtext<<"******"<<endl;
    }
    f1.close();
    QApplication* app;
    app->quit();
}

void MainWindow::on_pushButton_18_clicked()
{
    acgn *a;
    book *b;
    clothes *c;
    food *f;
    a=al;
    b=bl;
    c=cl;
    f=fl;
    QString uname=ui->lineEdit->text();
    QFile f1("client/"+uname+"/shopcart.txt");
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QTextStream inputtext(&f1);
        while(a->next!=NULL)
        {
        inputtext<<a->addgid()<<":"<<a->addnum()<<endl;
        a=a->next;
        }
        while(b->next!=NULL)
        {
        inputtext<<b->addgid()<<":"<<b->addnum()<<endl;
        b=b->next;
        }
        while(c->next!=NULL)
        {
        inputtext<<c->addgid()<<":"<<c->addnum()<<endl;
        c=c->next;
        }
        while(f->next!=NULL)
        {
        inputtext<<f->addgid()<<":"<<f->addnum()<<endl;
        f=f->next;
        }
        inputtext<<"******"<<endl;
    }
    f1.close();
    ui ->stackedWidget ->setCurrentIndex(0);
    ui->label_welcome->setText("");
}

void MainWindow::on_pushButton_21_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_22_clicked()
{
     ui ->stackedWidget ->setCurrentIndex(4);
     ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_login_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui ->stackedWidget ->setCurrentIndex(3);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString uname,code;
    uname=ui->lineEdit->text();
    code=ui->lineEdit_2->text();
    QFile f("client/"+uname+"/"+uname+".txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

    QMessageBox::warning(NULL,"warning","unexist",QMessageBox::Cancel);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui ->stackedWidget ->setCurrentIndex(3);
    }
     else
   {
    QTextStream txtInput(&f);
    QString lineStr;
    for(int i=0;i<4;i++)
    {
        lineStr=txtInput.readLine();
    }
    if(QString::compare(code,lineStr.mid(5))==0)
    {
    buytype=addor(al,bl,cl,fl,uname,0);
    ui->label_welcome->setText("欢迎,"+uname);
    ui ->stackedWidget ->setCurrentIndex(4);
    ui ->stackedWidget_2 ->setCurrentIndex(0);
    }
    else
    {
      QMessageBox::warning(NULL,"warning","wrong code",QMessageBox::Cancel);
      ui ->stackedWidget ->setCurrentIndex(3);

    }
   }
}

void MainWindow::on_pushButton_13_clicked()
{
    book *b;
    b=bl;
    QStringList header;
    ui->tableWidget->setRowCount(10);     //设置行数为10
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,200);
     ui->tableWidget->setColumnWidth(4,200);
     ui->tableWidget->setColumnWidth(5,200);
     ui->tableWidget->setColumnWidth(6,200);
     ui->tableWidget->setColumnWidth(7,200);
     ui->tableWidget->setColumnWidth(8,50);
     ui->tableWidget->setColumnWidth(9,50);
    header<<"NAME"<<"ID"<<"AUTHOR"<<"ORI-COST"<<"PRICE"<<"STORAGE"<<"DESCRIPTION"<<"NUM"<<"ADD"<<"DEC";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(int i=0;b->next!=NULL;i++)
        {
          ui->tableWidget->setItem(i,0,new QTableWidgetItem(b->addname()));
          ui->tableWidget->setItem(i,1,new QTableWidgetItem(b->addgid()));
          ui->tableWidget->setItem(i,2,new QTableWidgetItem(b->addau()));
          ui->tableWidget->setItem(i,3,new QTableWidgetItem(b->addcost()));
          ui->tableWidget->setItem(i,4,new QTableWidgetItem(b->addsale()));
          ui->tableWidget->setItem(i,5,new QTableWidgetItem(b->addsleft()));
          ui->tableWidget->setItem(i,6,new QTableWidgetItem(b->adddes()));
          ui->tableWidget->setItem(i,7,new QTableWidgetItem(b->addnum()));
          ui->tableWidget->setItem(i,8,new QTableWidgetItem("+"));
          ui->tableWidget->setItem(i,9,new QTableWidgetItem("-"));
          b=b->next;
        }
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_16_clicked()
{
    food *f;
    f=fl;
    QStringList header;
    ui->tableWidget->setRowCount(10);     //设置行数为10
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,200);
     ui->tableWidget->setColumnWidth(4,200);
     ui->tableWidget->setColumnWidth(5,200);
     ui->tableWidget->setColumnWidth(6,200);
     ui->tableWidget->setColumnWidth(7,200);
     ui->tableWidget->setColumnWidth(8,50);
     ui->tableWidget->setColumnWidth(9,50);
    header<<"NAME"<<"ID"<<"COMPANY"<<"ORI-COST"<<"PRICE"<<"STORAGE"<<"DESCRIPTION"<<"NUM"<<"ADD"<<"DEC";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(int i=0;f->next!=NULL;i++)
        {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(f->addname()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(f->addgid()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(f->addau()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(f->addcost()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(f->addsale()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(f->addsleft()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(f->adddes()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(f->addnum()));
         ui->tableWidget->setItem(i,8,new QTableWidgetItem("+"));
          ui->tableWidget->setItem(i,9,new QTableWidgetItem("-"));
          f=f->next;
        }
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_17_clicked()
{
    clothes *c;
    c=cl;
    QStringList header;
    ui->tableWidget->setRowCount(10);     //设置行数为10
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,200);
     ui->tableWidget->setColumnWidth(4,200);
     ui->tableWidget->setColumnWidth(5,200);
     ui->tableWidget->setColumnWidth(6,200);
     ui->tableWidget->setColumnWidth(7,200);
     ui->tableWidget->setColumnWidth(8,50);
     ui->tableWidget->setColumnWidth(9,50);
    header<<"NAME"<<"ID"<<"COMPANY"<<"ORI-COST"<<"PRICE"<<"STORAGE"<<"DESCRIPTION"<<"NUM"<<"ADD"<<"DEC";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(int i=0;c->next!=NULL;i++)
        {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(c->addname()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(c->addgid()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(c->addcom()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(c->addcost()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(c->addsale()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(c->addsleft()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(c->adddes()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(c->addnum()));
         ui->tableWidget->setItem(i,8,new QTableWidgetItem("+"));
          ui->tableWidget->setItem(i,9,new QTableWidgetItem("-"));
          c=c->next;
        }
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_14_clicked()
{
    acgn *a;
    a=al;
    QStringList header;
    ui->tableWidget->setRowCount(10);     //设置行数为10
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,200);
     ui->tableWidget->setColumnWidth(4,200);
     ui->tableWidget->setColumnWidth(5,200);
     ui->tableWidget->setColumnWidth(6,200);
     ui->tableWidget->setColumnWidth(7,200);
     ui->tableWidget->setColumnWidth(8,50);
     ui->tableWidget->setColumnWidth(9,50);
    header<<"NAME"<<"ID"<<"COMPANY"<<"ORI-COST"<<"PRICE"<<"STORAGE"<<"DESCRIPTION"<<"NUM"<<"ADD"<<"DEC";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(int i=0;a->next!=NULL;i++)
        {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(a->addname()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(a->addgid()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(a->addcom()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(a->addcost()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(a->addsale()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(a->addsleft()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(a->adddes()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(a->addnum()));
         ui->tableWidget->setItem(i,8,new QTableWidgetItem("+"));
          ui->tableWidget->setItem(i,9,new QTableWidgetItem("-"));
          a=a->next;
        }
    ui->stackedWidget_2->setCurrentIndex(1);
}




void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    acgn *a;
    book *b;
    clothes *c;
    food *f;
    a=al;
    b=bl;
    c=cl;
    f=fl;
    QString ju=ui->tableWidget->item(0,1)->text();
    QString tempp="1";
    int gg=judgetype(ju);
    if(gg==1)
        tempp=al->addtypenum();
    if(gg==2)
        tempp=bl->addtypenum();
    if(gg==3)
        tempp=cl->addtypenum();
    if(gg==4)
        tempp=fl->addtypenum();
    if(column==8&&row<tempp.toInt())
     {

        QString num=ui->tableWidget->item(row,7)->text();
        QString sto=ui->tableWidget->item(row,5)->text();
        QString gidn=ui->tableWidget->item(row,1)->text();
        int a1,b1;
        a1=num.toInt();
        if(a1==0)
            buytype++;
        b1=sto.toInt();
        a1++;
        if(a1<=b1)
        {
        num=QString::number(a1);
        ui->tableWidget->item(row,7)->setText(num);

        int i=0;
        while(a->next!=NULL&&i==0)
        {
            QString temp;
            temp=a->addgid();
            if(!QString::compare(gidn,temp))
            {
                a->getnum(num);
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
                b->getnum(num);
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
                 c->getnum(num);
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
                 f->getnum(num);
                 i=1;
             }
             f=f->next;
         }
        }

    }
    else if(column==9&&row<tempp.toInt())
    {

        QString num=ui->tableWidget->item(row,7)->text();
        QString gidn=ui->tableWidget->item(row,1)->text();
        int a1;
        a1=num.toInt();
        if(a1==1)
        buytype--;
        a1--;
        if(a1>=0)
        {

        num=QString::number(a1);
        ui->tableWidget->item(row,7)->setText(num);
        int i=0;
        while(a->next!=NULL&&i==0)
        {
            QString temp;
            temp=a->addgid();
            if(!QString::compare(gidn,temp))
            {
                a->getnum(num);
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
                b->getnum(num);
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
                 c->getnum(num);
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
                 f->getnum(num);
                 i=1;
             }
             f=f->next;
         }
        }
    }
    else
    {
       if(row<tempp.toInt())
       {
           ui->listWidget->clear();
           if(gg==1)
           {
               QString xx;
               QFile f1("goods/acgn.txt");
               if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                   QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
               }
               else
               {
               QTextStream inputtext1(&f1);
               int i=row+1;
               while(i>0)
               {
                   for(int p=0;p<6;p++)
                   {
                   xx=inputtext1.readLine();
                   if(i==1)
                   {
                   QListWidgetItem* lst = new QListWidgetItem(xx,ui->listWidget);
                   ui->listWidget->insertItem(i, lst);
                   }
                   }
                   xx=inputtext1.readLine();
                   i--;
               }
               }
            f1.close();
           }
           if(gg==2)
           {
               QString xx;
               QFile f1("goods/book.txt");
               if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                   QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
               }
               else
               {
               QTextStream inputtext1(&f1);
               int i=row+1;
               while(i>0)
               {
                   for(int p=0;p<6;p++)
                   {
                   xx=inputtext1.readLine();
                   if(i==1)
                   {
                   QListWidgetItem* lst = new QListWidgetItem(xx,ui->listWidget);
                   ui->listWidget->insertItem(i, lst);
                   }
                   }
                   xx=inputtext1.readLine();
                   i--;
               }
               }
            f1.close();
           }
           if(gg==3)
           {
               QString xx;
               QFile f1("goods/clothes.txt");
               if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                   QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
               }
               else
               {
               QTextStream inputtext1(&f1);
               int i=row+1;
               while(i>0)
               {
                   for(int p=0;p<6;p++)
                   {
                   xx=inputtext1.readLine();
                   if(i==1)
                   {
                   QListWidgetItem* lst = new QListWidgetItem(xx,ui->listWidget);
                   ui->listWidget->insertItem(i, lst);
                   }
                   }
                   xx=inputtext1.readLine();
                   i--;
               }
               }
            f1.close();
           }
           if(gg==4)
           {
               QString xx;
               QFile f1("goods/food.txt");
               if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                   QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
               }
               else
               {
               QTextStream inputtext1(&f1);
               int i=row+1;
               while(i>0)
               {
                   for(int p=0;p<6;p++)
                   {
                   xx=inputtext1.readLine();
                   if(i==1)
                   {
                   QListWidgetItem* lst = new QListWidgetItem(xx,ui->listWidget);
                   ui->listWidget->insertItem(i, lst);
                   }
                   }
                   xx=inputtext1.readLine();
                   i--;
               }
               }
            f1.close();
           }
       }
    }
}



void MainWindow::on_pushButton_19_clicked()
{
    ui->tableWidget_2->clear();
    acgn *a;
    book *b;
    clothes *c;
    food *f;
    a=al;
    b=bl;
    c=cl;
    f=fl;
    int i=0;
    QStringList header;
    ui->tableWidget_2->setRowCount(20);     //设置行数为10
    ui->tableWidget_2->setColumnCount(8);
    header<<"NAME"<<"ID"<<"NUM"<<"PRICE"<<"SUM"<<"STORAGE"<<"ADD"<<"DEC";
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setColumnWidth(0,200);
    ui->tableWidget_2->setColumnWidth(1,200);
    ui->tableWidget_2->setColumnWidth(2,200);
    ui->tableWidget_2->setColumnWidth(3,200);
    ui->tableWidget_2->setColumnWidth(4,200);
    ui->tableWidget_2->setColumnWidth(5,200);
    ui->tableWidget_2->setColumnWidth(6,50);
    ui->tableWidget_2->setColumnWidth(7,50);
    while(a->next!=NULL)
    {
    QString temp;
    temp=a->addnum();
    int u;
    u=temp.toInt();
    if(u>0)
    {
    ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(a->addname()));
    ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(a->addgid()));
    ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(a->addnum()));
    ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(a->addsale()));
    QString ss,sc;
    ss=a->addnum();
    sc=a->addsale();
    double sum;
    sum=ss.toDouble()*sc.toDouble();
    ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(sum)));
    ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(a->addsleft()));
    ui->tableWidget_2->setItem(i,6,new QTableWidgetItem("+"));
    ui->tableWidget_2->setItem(i,7,new QTableWidgetItem("-"));
    i++;
    }
    a=a->next;
    }

    while(b->next!=NULL)
    {
    QString temp;
    temp=b->addnum();
    int u;
    u=temp.toInt();
    if(u>0)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(b->addname()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(b->addgid()));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(b->addnum()));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(b->addsale()));
        QString ss,sc;
        ss=b->addnum();
        sc=b->addsale();
        double sum;
        sum=ss.toDouble()*sc.toDouble();
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(sum)));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(b->addsleft()));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem("+"));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem("-"));
    i++;
    }
    b=b->next;
    }

    while(c->next!=NULL)
    {
    QString temp;
    temp=c->addnum();
    int u;
    u=temp.toInt();
    if(u>0)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(c->addname()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(c->addgid()));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(c->addnum()));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(c->addsale()));
        QString ss,sc;
        ss=c->addnum();
        sc=c->addsale();
        double sum;
        sum=ss.toDouble()*sc.toDouble();
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(sum)));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(c->addsleft()));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem("+"));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem("-"));
    i++;
    }
    c=c->next;
    }

    while(f->next!=NULL)
    {
    QString temp;
    temp=f->addnum();
    int u;
    u=temp.toInt();
    if(u>0)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(f->addname()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(f->addgid()));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(f->addnum()));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(f->addsale()));
        QString ss,sc;
        ss=f->addnum();
        sc=f->addsale();
        double sum;
        sum=ss.toDouble()*sc.toDouble();
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(sum)));
        ui->tableWidget_2->setItem(i,5,new QTableWidgetItem(f->addsleft()));
        ui->tableWidget_2->setItem(i,6,new QTableWidgetItem("+"));
        ui->tableWidget_2->setItem(i,7,new QTableWidgetItem("-"));
    i++;
    }
    f=f->next;
    }
    double he=0;
    for(int u=0;u<i;u++)
    {
        he=he+ui->tableWidget_2->item(u,4)->text().toDouble();
    }
    if(he>=ui->label_61->text().toDouble())
    {
        he=he-ui->label_63->text().toDouble();
    }
    else if(he>=ui->label_62->text().toDouble())
     {
        he=he-ui->label_64->text().toDouble();
    }
    ui->label_sum->setText(QString::number(he));
    QStringList bc;
    QFile f1("client/"+ui->lineEdit->text()+"/bank.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning","BANK FILE OUT",QMessageBox::Cancel);
    }
    else
    {
        QTextStream inp(&f1);
        QString s;
        while(!inp.atEnd())
        {
            s=inp.readLine();
            bc.append(s);
        }
    }
    ui->stackedWidget->setCurrentIndex(5);

}

void MainWindow::on_tableWidget_2_cellClicked(int row, int column)
{
    acgn *a;
    book *b;
    clothes *c;
    food *f;
    a=al;
    b=bl;
    c=cl;
    f=fl;
    if(column==6&&row<buytype)
    {
        QString num=ui->tableWidget_2->item(row,2)->text();
        QString sto=ui->tableWidget_2->item(row,5)->text();
        QString gidn=ui->tableWidget_2->item(row,1)->text();
        QString gsum=ui->tableWidget_2->item(row,4)->text();
        int a1,b1;
        a1=num.toInt();
        b1=sto.toInt();
        a1++;
        if(a1<=b1)
        {
        num=QString::number(a1);
        ui->tableWidget_2->item(row,2)->setText(num);
        double ee=gsum.toDouble();
        ee=ee+ui->tableWidget_2->item(row,3)->text().toDouble();
        ui->tableWidget_2->item(row,4)->setText(QString::number(ee));
        int i=0;
        while(a->next!=NULL&&i==0)
        {
            QString temp;
            temp=a->addgid();
            if(!QString::compare(gidn,temp))
            {
                a->getnum(num);
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
                b->getnum(num);
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
                 c->getnum(num);
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
                 f->getnum(num);
                 i=1;
             }
             f=f->next;
         }

         QString fo=ui->label_sum->text();
         double he=fo.toDouble()+ui->tableWidget_2->item(row,3)->text().toDouble();
         if(he>=ui->label_61->text().toDouble()&&fo.toDouble()<ui->label_61->text().toDouble())
         {
             he=he-ui->label_63->text().toDouble();
         }
         else if(he>=ui->label_62->text().toDouble()&&fo.toDouble()<ui->label_62->text().toDouble())
          {
             he=he-ui->label_64->text().toDouble();
         }

         ui->label_sum->setText(QString::number(he));
        }
    }
    else if(column==7&&row<buytype)
    {
        QString num=ui->tableWidget_2->item(row,2)->text();
        QString gidn=ui->tableWidget_2->item(row,1)->text();
        QString gsum=ui->tableWidget_2->item(row,4)->text();
        int a1;
        a1=num.toInt();
        if(a1==1)
        buytype--;
        a1--;
        if(a1>=0)
        {
        num=QString::number(a1);
        ui->tableWidget_2->item(row,2)->setText(num);
        double ee=gsum.toDouble();
        ee=ee-ui->tableWidget_2->item(row,3)->text().toDouble();
        ui->tableWidget_2->item(row,4)->setText(QString::number(ee));

        int i=0;
        while(a->next!=NULL&&i==0)
        {
            QString temp;
            temp=a->addgid();
            if(!QString::compare(gidn,temp))
            {
                a->getnum(num);
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
                b->getnum(num);
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
                 c->getnum(num);
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
                 f->getnum(num);
                 i=1;
             }
             f=f->next;
         }

         QString fo=ui->label_sum->text();

         double he=fo.toDouble();
         if(he>=(ui->label_61->text().toDouble()-ui->label_63->text().toDouble()))
         {
             he=he+ui->label_63->text().toDouble();
         }
         else if(he>=(ui->label_62->text().toDouble()-ui->label_64->text().toDouble()))
          {
             he=he+ui->label_64->text().toDouble();
         }

          he=he-ui->tableWidget_2->item(row,3)->text().toDouble();
         if(he>=ui->label_61->text().toDouble())
         {
             he=he-ui->label_63->text().toDouble();
         }
         else if(he>=ui->label_62->text().toDouble())
          {
             he=he-ui->label_64->text().toDouble();
         }

         ui->label_sum->setText(QString::number(he));
        }
        if(a1==0)
        {
            ui->tableWidget_2->removeRow(row);
        }
    }

}

void MainWindow::on_pushButton_8_clicked()
{

 on_pushButton_19_clicked();
}

void MainWindow::on_pushButton_9_clicked()
{
   QString uname,uid;
   uname=ui->lineEdit->text();
   QFile f("client/"+uname+"/"+uname+".txt");
   if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
   }
   else
   {
       QTextStream inputtext(&f);
       for(int i=0;i<6;i++)
           uid=inputtext.readLine();
       uid=uid.mid(4);
   }
   f.close();
   QString xx;
   QFile f1("client/"+uname+"/"+uid+".txt");
   if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
   }
   else
   {
   QTextStream inputtext1(&f1);
   int i=1;
   while(!inputtext1.atEnd())
   {
       xx=inputtext1.readLine();
       QListWidgetItem* lst = new QListWidgetItem(xx,ui->listWidget_2);
       ui->listWidget_2->insertItem(i, lst);
       i++;
   }
   }
f1.close();
ui->stackedWidget->setCurrentIndex(9);

}

void MainWindow::on_pushButton_15_clicked()
{
    on_pushButton_13_clicked();
}

void MainWindow::on_pushButton_24_clicked()
{
    on_pushButton_17_clicked();
}

void MainWindow::on_pushButton_25_clicked()
{
    on_pushButton_16_clicked();
}

void MainWindow::on_pushButton_26_clicked()
{
    on_pushButton_14_clicked();
}

void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_20_clicked()
{
    acgn *a;
     book *b;
     clothes *c;
     food *f;
     a=al;
     b=bl;
     c=cl;
     f=fl;
     QString uname=ui->lineEdit->text();
      QString uid;

       QFile fi("client/"+uname+"/"+uname+".txt");
       if(!fi.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QMessageBox::warning(NULL,"warning","SHOPCART FILE OUT",QMessageBox::Cancel);
       }
       else
       {
           QTextStream inputtext(&fi);
           for(int i=0;i<6;i++)
               uid=inputtext.readLine();
           uid=uid.mid(4);
       }
       fi.close();

     QFile f1("client/"+uname+"/shopcart.txt");
     if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
     }
     else
     {
         QTextStream inputtext(&f1);
         while(a->next!=NULL)
         {
         inputtext<<a->addgid()<<":0"<<endl;
         a=a->next;
         }
         while(b->next!=NULL)
         {
         inputtext<<b->addgid()<<":0"<<endl;
         b=b->next;
         }
         while(c->next!=NULL)
         {
         inputtext<<c->addgid()<<":0"<<endl;
         c=c->next;
         }
         while(f->next!=NULL)
         {
         inputtext<<f->addgid()<<":0"<<endl;
         f=f->next;
         }
         inputtext<<"******"<<endl;
     }
     f1.close();

      a=al;
      b=bl;
      c=cl;
      f=fl;

          QFile fs("client/"+uname+"/"+uid+".txt");
          if(!fs.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
          {
           QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
          }
          else
          {
              QTextStream inputtext1(&fs);
              for(int oo=0;oo<buytype;oo++)
              {

            inputtext1<<"name:"<<ui->tableWidget_2->item(oo,0)->text()<<endl;
            inputtext1<<"price:"<<ui->tableWidget_2->item(oo,3)->text()<<endl;
            inputtext1<<"num:"<<ui->tableWidget_2->item(oo,2)->text()<<endl;
            inputtext1<<"sum:"<<ui->tableWidget_2->item(oo,4)->text()<<endl;
            inputtext1<<endl;
          }
              inputtext1<<"***********"<<endl;
         }
           fs.close();


      while(a->next!=NULL)
      {
      int sto,se;
      se=a->addnum().toInt();
      sto=a->addsleft().toInt();
      sto=sto-se;
      a->getnum("0");
      a->getsleft(QString::number(sto));
      a=a->next;
      }
      while(b->next!=NULL)
      {
          int sto,se;
          se=b->addnum().toInt();
          sto=b->addsleft().toInt();
          sto=sto-se;
          b->getnum("0");
          b->getsleft(QString::number(sto));
      b=b->next;
      }
      while(c->next!=NULL)
      {
          int sto,se;
          se=c->addnum().toInt();
          sto=c->addsleft().toInt();
          sto=sto-se;
          c->getnum("0");
          c->getsleft(QString::number(sto));
      c=c->next;
      }
      while(f->next!=NULL)
      {
          int sto,se;
          se=f->addnum().toInt();
          sto=f->addsleft().toInt();
          sto=sto-se;
          f->getnum("0");
          f->getsleft(QString::number(sto));
      f=f->next;
      }

       a=al;
       b=bl;
       c=cl;
       f=fl;

      QFile f2("goods/acgn.txt");
      if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
      {
          QMessageBox::warning(NULL,"warning","ACGN FILE OUT",QMessageBox::Cancel);
      }
      else
      {
          QTextStream inputtext(&f2);
          while(a->next!=NULL)
          {
          inputtext<<"name:"<<a->addname()<<endl;
          inputtext<<"gid:"<<a->addgid()<<endl;
          inputtext<<"company:"<<a->addcom()<<endl;
          inputtext<<"pri-price:"<<a->addcost()<<endl;
          inputtext<<"storage:"<<a->addsleft()<<endl;
          inputtext<<"description:"<<a->adddes()<<endl;
          inputtext<<"******************************"<<endl;
          a=a->next;
          }
      }
      f2.close();

       QFile f3("goods/book.txt");
       if(!f3.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QMessageBox::warning(NULL,"warning","BOOK FILE OUT",QMessageBox::Cancel);
       }
       else
       {
           QTextStream inputtext(&f3);
           while(b->next!=NULL)
           {
           inputtext<<"name:"<<b->addname()<<endl;
           inputtext<<"gid:"<<b->addgid()<<endl;
           inputtext<<"author:"<<b->addau()<<endl;
           inputtext<<"pri-price:"<<b->addcost()<<endl;
           inputtext<<"storage:"<<b->addsleft()<<endl;
           inputtext<<"description:"<<b->adddes()<<endl;
           inputtext<<"******************************"<<endl;
           b=b->next;
           }
       }
       f3.close();

        QFile f4("goods/clothes.txt");
        if(!f4.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(NULL,"warning","BOOK FILE OUT",QMessageBox::Cancel);
        }
        else
        {
            QTextStream inputtext(&f4);
            while(c->next!=NULL)
            {
            inputtext<<"name:"<<c->addname()<<endl;
            inputtext<<"gid:"<<c->addgid()<<endl;
            inputtext<<"company:"<<c->addcom()<<endl;
            inputtext<<"pri-price:"<<c->addcost()<<endl;
            inputtext<<"storage:"<<c->addsleft()<<endl;
            inputtext<<"description:"<<c->adddes()<<endl;
            inputtext<<"******************************"<<endl;
            c=c->next;
            }
        }
        f4.close();

         QFile f5("goods/food.txt");
         if(!f5.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             QMessageBox::warning(NULL,"warning","BOOK FILE OUT",QMessageBox::Cancel);
         }
         else
         {
             QTextStream inputtext(&f5);
             while(f->next!=NULL)
             {
             inputtext<<"name:"<<f->addname()<<endl;
             inputtext<<"gid:"<<f->addgid()<<endl;
             inputtext<<"company:"<<f->addau()<<endl;
             inputtext<<"pri-price:"<<f->addcost()<<endl;
             inputtext<<"storage:"<<f->addsleft()<<endl;
             inputtext<<"description:"<<f->adddes()<<endl;
             inputtext<<"******************************"<<endl;
             f=f->next;
             }
         }
         f5.close();

          ui->stackedWidget->setCurrentIndex(6);
}
















void MainWindow::on_pushButton_31_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
}
