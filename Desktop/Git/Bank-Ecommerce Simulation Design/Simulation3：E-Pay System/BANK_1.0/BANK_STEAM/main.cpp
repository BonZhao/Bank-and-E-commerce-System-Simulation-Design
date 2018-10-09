#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include"bank_backend.h"
#include"card.h"


bank *bankname[8];
card *head;

int main(int argc, char *argv[])
{
    QFileInfo t("BANK");
    QApplication a(argc, argv);
    MainWindow w;


    w.show();
    return a.exec();
}





