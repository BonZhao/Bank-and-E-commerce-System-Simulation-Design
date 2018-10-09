#ifndef RESIGNIN_H
#define RESIGNIN_H

#include <QDialog>

namespace Ui {
class resignin;
}

class resignin : public QDialog
{
    Q_OBJECT

public:
    explicit resignin(QWidget *parent = 0);
    ~resignin();

private:
    Ui::resignin *ui;
};

#endif // RESIGNIN_H
