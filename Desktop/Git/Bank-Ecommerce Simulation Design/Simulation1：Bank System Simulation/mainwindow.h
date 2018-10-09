#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bank_backend.h"
#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_code_master_clicked();

    void on_deposit_clicked();

    void on_takemoney_clicked();

    void on_leave_sys_clicked();

    void on_regesister_clicked();

    void on_find_code_clicked();

    void on_ifo_check_clicked();

    void on_return_tof1_clicked();

    void on_return_tofE_clicked();

    void on_return_tofD_clicked();

    void on_return_tofC_clicked();

    void on_return_tofB_clicked();
    void on_return_tofA_clicked();
    void on_return_tof9_clicked();
    void on_return_tof8_clicked();
    void on_return_tof7_clicked();
    void on_return_tof6_clicked();
    void on_return_tof5_clicked();
    void on_return_tof4_clicked();
    void on_return_tof3_clicked();
    void on_return_tof2_clicked();




      void newConnect();
      void received();

    void on_rege_con_clicked();

    void on_returntof_fi_clicked();

    void on_returntof_lt_clicked();

    void on_bankrege_clicked();

    void on_bank_add_clicked();

    void on_returntofex_clicked();

    void on_confirm_clicked();

    void on_reconfirm_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_6_clicked();

    void on_return_tof4_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_25_clicked();

    void on_return_tofA_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
