#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bank_backend.h"
#include"card.h"
#include <QComboBox>
#include <QMessageBox>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QTcpSocket>
#include <QTcpServer>
#include<QtNetwork>

QTcpServer *Bserver;
QTcpSocket *clientend;
card cardfo;
bank bankfo;
QString tempsave;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui ->stackedWidget ->setCurrentIndex(0);
    ui->lineEdit_10->setEchoMode(QLineEdit::Password);
    ui->lineEdit_11->setEchoMode(QLineEdit::Password);
    ui->lineEdit_16->setEchoMode(QLineEdit::Password);
    ui->lineEdit_20->setEchoMode(QLineEdit::Password);
    Bserver=new QTcpServer;
    Bserver->listen(QHostAddress::Any,6666);
    connect(Bserver,SIGNAL(newConnection()),this,SLOT(newConnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnect()
{
     clientend = Bserver->nextPendingConnection();
     connect(clientend,SIGNAL(readyRead()),this,SLOT(received()));

}
void MainWindow::received()
{
    QString buffer,ret;
    buffer=clientend->readLine();
    QString cid,code,pay;
    QString pre,prem1,prem2;
    pre=buffer.mid(0,1);
    prem1='#';
    prem2='*';
    if(!QString::compare(pre,prem1))
    {
      cid=buffer.mid(1,9);
      code=buffer.mid(10);
      QFile f("BANK/findc/"+cid+".txt");
      if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
      {
          ret="#c";
      }
      else
      {
          QTextStream inp(&f);
          QString che=inp.readLine();

          if(!QString::compare(che,code))
           ret="#s";
          else
           ret="#p";
      }
    }
    else if(!QString::compare(pre,prem2))
    {
        cid=buffer.mid(1,9);
        code=buffer.mid(10,6);
        pay=buffer.mid(16);
        ret=jelecost(pay,cid,code);
    }
    clientend->write(ret.toLatin1());

}


void MainWindow::on_code_master_clicked()
{
    ui->lineEdit_9->setText("");
    ui->lineEdit_9->setEchoMode(QLineEdit::Password);
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui->lineEdit_23->setText("");
ui ->stackedWidget ->setCurrentIndex(5);
}

void MainWindow::on_deposit_clicked()
{
    ui->lineEdit_12->setText("");
    ui->lineEdit_14->setText("");
    ui->lineEdit_13->setText("");
ui ->stackedWidget ->setCurrentIndex(8);
}

void MainWindow::on_takemoney_clicked()
{
  ui->lineEdit_15->setText("");
   ui->lineEdit_16->setText("");
    ui->lineEdit_17->setText("");
     ui->lineEdit_18->setText("");
ui ->stackedWidget ->setCurrentIndex(10);
}

void MainWindow::on_leave_sys_clicked()
{
    QApplication* app;
    app->quit();
}

void MainWindow::on_regesister_clicked()
{
    ui->comboBox->clear();
    QStringList bankchoice;
    QString innn;
    QFile f("BANK/bankname.txt");
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
      ui->comboBox->addItems(bankchoice);
     f.close();
     ui ->stackedWidget ->setCurrentIndex(1);
   }
}

void MainWindow::on_find_code_clicked()
{

ui->lineEdit_21->setText("");
ui->lineEdit_22->setText("");
ui ->stackedWidget ->setCurrentIndex(15);
}

void MainWindow::on_ifo_check_clicked()
{
ui->lineEdit_19->setText("");
ui->lineEdit_20->setText("");
 ui ->stackedWidget ->setCurrentIndex(13);
}


void MainWindow::on_return_tof1_clicked()
{
    ui->comboBox->clear();
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof2_clicked()
{
    ui->comboBox->clear();
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof3_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof4_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof5_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof6_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof7_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof8_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tof9_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tofA_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tofB_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tofC_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tofD_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
void MainWindow::on_return_tofE_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}







void MainWindow::on_rege_con_clicked()
{
    QString name,id,call,code,recode,location,email,message;
    name=ui->lineEdit_name->text();
    id=ui->lineEdit_id->text();
    call=ui->lineEdit_call->text();
    code=ui->lineEdit_code->text();
    recode=ui->lineEdit_recode->text();
    location=ui->lineEdit_location->text();
    email=ui->lineEdit_email->text();
    message=ui->lineEdit_message->text();
    int i=0;
    if(name.length()<1||id.length()!=18||call.length()<11||code.length()<6||recode.length()<6||location.length()<0||email.length()<0||message.length()<0)
    {
        QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
        i= -1;
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
    {   ui->label_22->setText(name);
        ui->label_21->setText(id);
        ui->label_23->setText(ui->label_3->text());
        ui->label_24->setText(email);
        ui->label_25->setText(location);
        ui->label_28->setText(call);
        ui->label_29->setText(message);

        ui ->stackedWidget ->setCurrentIndex(3);
    }
    else
    {
        ui->lineEdit_name->setText("");
        ui->lineEdit_id->setText("");
        ui->lineEdit_call->setText("");
        ui->lineEdit_code->setText("");
        ui->lineEdit_recode->setText("");
        ui->lineEdit_location->setText("");
        ui->lineEdit_email->setText("");
        ui->lineEdit_message->setText("");
        ui ->stackedWidget ->setCurrentIndex(2);
    }
}

void MainWindow::on_returntof_fi_clicked()
{
     ui ->stackedWidget ->setCurrentIndex(0);
}

void MainWindow::on_returntof_lt_clicked()
{
     ui ->stackedWidget ->setCurrentIndex(0);
}

void MainWindow::on_bankrege_clicked()
{

QString nameb,odepo;
nameb=ui->getbankname->text();
odepo=ui->getodepo->text();
int i;
i=bankset(nameb,odepo);
if(i==0)
{
ui ->stackedWidget ->setCurrentIndex(19);
ui->getbankname->setText("");
ui->getodepo->setText("");
ui->label_72->setText(nameb);
ui->label_73->setText(odepo);
}
else
{
 ui ->stackedWidget ->setCurrentIndex(18);
 ui->getbankname->setText("");
 ui->getodepo->setText("");

}
}



void MainWindow::on_bank_add_clicked()
{
ui->admin->setText("");
ui->codea->setText("");
ui->getbankname->setText("");
ui->getodepo->setText("");
ui->codea->setEchoMode(QLineEdit::Password);
ui ->stackedWidget ->setCurrentIndex(17);
}

void MainWindow::on_returntofex_clicked()
{
   ui ->stackedWidget ->setCurrentIndex(0);

}

void MainWindow::on_confirm_clicked()
{
    QString co,ad;
    co=ui->codea->text();
    ad=ui->admin->text();
    int i=judge(co,ad);
    if(i==0)
    {
        ui ->stackedWidget ->setCurrentIndex(18);
    }
    else
    {
        ui->admin->setText("");
        ui->codea->setText("");
      ui ->stackedWidget ->setCurrentIndex(17);
    }

}

void MainWindow::on_reconfirm_clicked()
{
   QString bankchoice,bid,cid,cnum;
   int ta,ti;
   bool ok;
   bankchoice=ui->comboBox->currentText();
   if(bankchoice=="无")
     {
       QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
       ui ->stackedWidget ->setCurrentIndex(1);
   }
   else
       {
   bid=bankchoice.mid(0,1);
   ta=bid.toInt(&ok,10);
   ta=ta*100000000;

   QFile f("BANK/"+bid+"/total.txt");
   if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
       ui ->stackedWidget ->setCurrentIndex(0);
   }
   QTextStream txtInput(&f);
   QString lineStr;
   lineStr = txtInput.readLine();
   lineStr =txtInput.readLine();
   cnum=lineStr.mid(8,3);
   f.close();

   ti=cnum.toInt(&ok,10);
   ti=ti+1;
   ta=ta+ti;
   cid=QString::number(ta,10);
   ui->lineEdit_name->setText("");
   ui->lineEdit_id->setText("");
   ui->lineEdit_call->setText("");
   ui->lineEdit_code->setText("");
   ui->lineEdit_recode->setText("");
   ui->lineEdit_location->setText("");
   ui->lineEdit_email->setText("");
   ui->lineEdit_message->setText("");
   ui->lineEdit_code->setEchoMode(QLineEdit::Password);
   ui->lineEdit_recode->setEchoMode(QLineEdit::Password);
   ui->label_3->setText(cid);
   ui ->stackedWidget ->setCurrentIndex(2);
   }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString name,id,call,code,recode,location,email,message,bid,cid;
    name=ui->lineEdit_name->text();
    id=ui->lineEdit_id->text();
    call=ui->lineEdit_call->text();
    code=ui->lineEdit_code->text();
    recode=ui->lineEdit_recode->text();
    location=ui->lineEdit_location->text();
    email=ui->lineEdit_email->text();
    message=ui->lineEdit_message->text();
    cid=ui->label_3->text();
    bid=cid.mid(0,1);
     int i;
     i=regeca(cardfo,name,id,call, code,recode,location,email,message,cid,bid);
     if(i==0)
     ui ->stackedWidget ->setCurrentIndex(4);
     else
     {
     ui->lineEdit_name->setText("");
     ui->lineEdit_id->setText("");
     ui->lineEdit_call->setText("");
     ui->lineEdit_code->setText("");
     ui->lineEdit_recode->setText("");
     ui->lineEdit_location->setText("");
     ui->lineEdit_email->setText("");
     ui->lineEdit_message->setText("");
     ui->comboBox->clear();
     ui ->stackedWidget ->setCurrentIndex(3);
     }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(2);
}

void MainWindow::on_pushButton_31_clicked()
{
    QString cid,message;
    cid=ui->lineEdit_21->text();
    message=ui->lineEdit_22->text();
    int i=judgecode(cid,message);
    if(i==0)
    {
        QFile f1("BANK/findc/"+cid+".txt");
        if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
            ui->lineEdit_21->setText("");
            ui->lineEdit_22->setText("");
            ui ->stackedWidget ->setCurrentIndex(15);
        }
        else
        {
        QTextStream txtInput1(&f1);
        QString lineStr1;
        lineStr1 = txtInput1.readLine();
        ui->label_69->setText(lineStr1);
        f1.close();
        ui ->stackedWidget ->setCurrentIndex(16);
        }
    }
    else
    {
        ui->lineEdit_21->setText("");
        ui->lineEdit_22->setText("");
        ui ->stackedWidget ->setCurrentIndex(15);
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    QString cid,code;
    cid=ui->lineEdit_19->text();
    code= ui->lineEdit_20->text();
    QFile f1("BANK/findc/"+cid+".txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        ui->lineEdit_19->setText("");
        ui->lineEdit_20->setText("");
        ui ->stackedWidget ->setCurrentIndex(13);
    }
    QTextStream txtInput1(&f1);
    QString lineStr1;
    lineStr1 = txtInput1.readLine();
    if(QString::compare(code,lineStr1)!=0)
    {
        QMessageBox::warning(NULL,"warning","code wrong",QMessageBox::Cancel);
        ui->lineEdit_19->setText("");
        ui->lineEdit_20->setText("");
        ui ->stackedWidget ->setCurrentIndex(13);
    }
    else
       {
        QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
            ui->lineEdit_19->setText("");
            ui->lineEdit_20->setText("");
            ui ->stackedWidget ->setCurrentIndex(13);
        }
        else
        {
        QTextStream txtInput(&f);
        QString lineStr,linestr2;
        lineStr = txtInput.readLine();
        ui->label_60->setText(lineStr.mid(5));
        lineStr = txtInput.readLine();
        lineStr = txtInput.readLine();
        ui->label_61->setText(lineStr.mid(5));
        lineStr = txtInput.readLine();
        lineStr = txtInput.readLine();
        lineStr = txtInput.readLine();
        ui->label_62->setText(lineStr.mid(4));
        lineStr = txtInput.readLine();
        lineStr = txtInput.readLine();
        ui->label_63->setText(lineStr.mid(8));
        QFile f2("BANK/bankname.txt");
        f2.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream txtInput1(&f2);
        linestr2 = txtInput1.readLine();
        while(linestr2.mid(0,1)!=cid.mid(0,1))
            linestr2 = txtInput1.readLine();
        ui->label_59->setText(linestr2.mid(2));

        }
        f.close();
         ui ->stackedWidget ->setCurrentIndex(14);
    }
    f1.close();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString cid,code,info;
    cid=ui->lineEdit_23->text();
    code=ui->lineEdit_9->text();
    QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        ui->lineEdit_9->setText("");
        ui->lineEdit_23->setText("");
        ui ->stackedWidget ->setCurrentIndex(5);
    }
    else
    {
        QTextStream txtInput(&f);
        QString lineStr;
        for(int i=1;i<=4;i++)
        {
             lineStr = txtInput.readLine();
             info=lineStr.mid(5);
        }
        if(QString::compare(code,info)!=0)
        {
            ui->lineEdit_9->setText("");
            ui->lineEdit_23->setText("");
            QMessageBox::warning(NULL,"warning","code wrong",QMessageBox::Cancel);
            ui ->stackedWidget ->setCurrentIndex(5);
        }
        else
        {

                ui ->stackedWidget ->setCurrentIndex(6);
        }
    }
    f.close();
}


void MainWindow::on_return_tof4_2_clicked()
{
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui ->stackedWidget ->setCurrentIndex(0);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString cid,ncode,code,rencode,info[9];
    code=ui->lineEdit_9->text();
    cid=ui->lineEdit_23->text();
    ncode=ui->lineEdit_10->text();
    rencode=ui->lineEdit_11->text();
    if(QString::compare(ncode,rencode)!=0||ncode.length()<6)
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        ui->lineEdit_10->setText("");
        ui->lineEdit_11->setText("");
        ui ->stackedWidget ->setCurrentIndex(6);
    }
    else
    {
    QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        ui->lineEdit_10->setText("");
        ui->lineEdit_11->setText("");
        ui ->stackedWidget ->setCurrentIndex(6);
    }
    else
    {
        QTextStream txtInput(&f);
        QString lineStr;
        for(int i=1;i<=8;i++)
        {
             lineStr = txtInput.readLine();
             info[i]=lineStr;
        }
    }
    f.close();

    info[4]="code:"+ncode;
    QFile f1("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","file out",QMessageBox::Cancel);
        ui->lineEdit_10->setText("");
        ui->lineEdit_11->setText("");
        ui ->stackedWidget ->setCurrentIndex(6);
    }
    else
    {
    QTextStream txtOutput(&f1);
    for(int i=1;i<=8;i++)
    txtOutput << info[i]<< endl;
    }


    QFile f2("BANK/findc/"+cid+".txt");
    if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,"warning2","file out",QMessageBox::Cancel);
        ui->lineEdit_10->setText("");
        ui->lineEdit_11->setText("");
        ui ->stackedWidget ->setCurrentIndex(6);
    }
    else
    {
    QTextStream txtOutput(&f2);
    txtOutput << info[4].mid(5)<< endl;
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
    ui ->stackedWidget ->setCurrentIndex(7);
    }


    }


}

void MainWindow::on_pushButton_19_clicked()
{
    QString cid,zheng,xiao,info[9],binfo[4];
    double x,y;
    cid=ui->lineEdit_14->text();
    zheng=ui->lineEdit_12->text();
    xiao=ui->lineEdit_13->text();
    if(xiao=="")
        xiao="0";
    if(xiao.length()>2||zheng.length()<1)
    {
        QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
        ui->lineEdit_14->setText("");
        ui->lineEdit_13->setText("");
        ui->lineEdit_12->setText("");
        ui ->stackedWidget ->setCurrentIndex(8);
    }
    else
     {
        QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
            ui->lineEdit_14->setText("");
            ui->lineEdit_13->setText("");
            ui->lineEdit_12->setText("");
            ui ->stackedWidget ->setCurrentIndex(8);
        }
        else
        {
            QTextStream txtInput(&f);
            QString lineStr;
            for(int i=1;i<=8;i++)
            {
                 lineStr = txtInput.readLine();
                 info[i]=lineStr;
            }
        }
        f.close();
        x=info[6].mid(4).toDouble();
        x=x+zheng.toDouble()+xiao.toDouble()/100;
        info[6]="sum:"+QString::number(x,'f',2);
        x=info[6].mid(4).toDouble();
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(NULL,"warning2","file out",QMessageBox::Cancel);
            ui->lineEdit_14->setText("");
            ui->lineEdit_13->setText("");
            ui->lineEdit_12->setText("");
            ui ->stackedWidget ->setCurrentIndex(8);
        }
        else
        {
        QTextStream txtOutput(&f);
        for(int i=1;i<=8;i++)
        txtOutput <<info[i] << endl;
        }


        QFile f1("BANK/"+cid.mid(0,1)+"/total.txt");
        if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QMessageBox::warning(NULL,"warning","BFILE OUT",QMessageBox::Cancel);
            ui->lineEdit_14->setText("");
            ui->lineEdit_13->setText("");
            ui->lineEdit_12->setText("");
            ui ->stackedWidget ->setCurrentIndex(8);
        }
        else
        {
            QTextStream txtInput(&f1);
            QString lineStr;
            for(int i=1;i<=3;i++)
            {
                 lineStr = txtInput.readLine();
                 binfo[i]=lineStr;
            }
        }
        f1.close();
        y=binfo[3].mid(4).toDouble();
         y=y+x;
        binfo[3]="sum:"+QString::number(y,'f',2);
        if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(NULL,"warning2","file out",QMessageBox::Cancel);
            ui->lineEdit_14->setText("");
            ui->lineEdit_13->setText("");
            ui->lineEdit_12->setText("");
            ui ->stackedWidget ->setCurrentIndex(8);
        }
        else
        {
        QTextStream txtOutput(&f1);
        for(int i=1;i<=3;i++)
        txtOutput <<binfo[i] << endl;
        ui->label_42->setText(zheng+"."+xiao);
        ui ->stackedWidget ->setCurrentIndex(9);
        }


    }
}

void MainWindow::on_pushButton_23_clicked()
{
    QString cid,code;
    cid=ui->lineEdit_15->text();
    code=ui->lineEdit_16->text();
    QFile f("BANK/findc/"+cid+".txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
        ui->lineEdit_15->setText("");
        ui->lineEdit_16->setText("");
        ui ->stackedWidget ->setCurrentIndex(10);
    }
    else
    {
        QTextStream txtInput(&f);
        QString lineStr;
        lineStr = txtInput.readLine();
        if(code==lineStr)
        {
            ui ->stackedWidget ->setCurrentIndex(11);
            ui->lineEdit_17->setText("");
            ui->lineEdit_18->setText("");
        }
        else
         {
            QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
            ui->lineEdit_15->setText("");
            ui->lineEdit_16->setText("");
            ui ->stackedWidget ->setCurrentIndex(10);
        }

    }
    f.close();
}

void MainWindow::on_pushButton_25_clicked()
{
    QString cid,zheng,xiao,info[9],binfo[4];
    double x,y,z;
    zheng=ui->lineEdit_17->text();
    xiao=ui->lineEdit_18->text();
    cid=ui->lineEdit_15->text();
            if(xiao=="")
                xiao="0";
            if(xiao.length()>2||zheng.length()<1)
            {
                QMessageBox::warning(NULL,"warning","input wrong",QMessageBox::Cancel);
                ui->lineEdit_14->setText("");
                ui->lineEdit_13->setText("");
                ui->lineEdit_12->setText("");
                ui ->stackedWidget ->setCurrentIndex(8);
            }
            else
             {
                QFile f("BANK/"+cid.mid(0,1)+"/"+cid+".txt");
                if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
                {

                    QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
                    ui->lineEdit_17->setText("");
                    ui->lineEdit_18->setText("");
                    ui ->stackedWidget ->setCurrentIndex(11);
                }
                else
                {
                    QTextStream txtInput(&f);
                    QString lineStr;
                    for(int i=1;i<=8;i++)
                    {
                         lineStr = txtInput.readLine();
                         info[i]=lineStr;
                    }
                }
                f.close();
                x=info[6].mid(4).toDouble();
                z=zheng.toDouble()+xiao.toDouble()/100;
                if(z>x)
                {
                    QMessageBox::warning(NULL,"warning","小鬼，你没存那么多",QMessageBox::Cancel);
                    ui->lineEdit_17->setText("");
                    ui->lineEdit_18->setText("");
                    ui ->stackedWidget ->setCurrentIndex(11);
                }
                else
                {
                x=x-z;
                info[6]="sum:"+QString::number(x,'f',2);
                x=info[6].mid(4).toDouble();
                if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QMessageBox::warning(NULL,"warning","FILE OUT",QMessageBox::Cancel);
                    ui->lineEdit_17->setText("");
                    ui->lineEdit_18->setText("");
                    ui ->stackedWidget ->setCurrentIndex(11);
                }
                else
                {
                QTextStream txtOutput(&f);
                for(int i=1;i<=8;i++)
                txtOutput <<info[i] << endl;
                }


                QFile f1("BANK/"+cid.mid(0,1)+"/total.txt");
                if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QMessageBox::warning(NULL,"warning","BFILE OUT",QMessageBox::Cancel);
                    ui->lineEdit_17->setText("");
                    ui->lineEdit_18->setText("");
                    ui ->stackedWidget ->setCurrentIndex(11);
                }
                else
                {
                    QTextStream txtInput(&f1);
                    QString lineStr;
                    for(int i=1;i<=3;i++)
                    {
                         lineStr = txtInput.readLine();
                         binfo[i]=lineStr;
                    }
                }
                f1.close();
                y=binfo[3].mid(4).toDouble();
                 y=y-z;
                binfo[3]="sum:"+QString::number(y,'f',2);
                if(!f1.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QMessageBox::warning(NULL,"warning","BFILE OUT2",QMessageBox::Cancel);
                    ui->lineEdit_17->setText("");
                    ui->lineEdit_18->setText("");
                    ui ->stackedWidget ->setCurrentIndex(11);
                }
                else
                {
                QTextStream txtOutput(&f1);
                for(int i=1;i<=3;i++)
                txtOutput <<binfo[i] << endl;
                ui->label_50->setText(zheng+"."+xiao);
                ui ->stackedWidget ->setCurrentIndex(12);
                }


            }
                }
}

void MainWindow::on_return_tofA_2_clicked()
{
    ui ->stackedWidget ->setCurrentIndex(0);
}
