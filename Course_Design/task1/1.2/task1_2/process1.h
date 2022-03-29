#ifndef PROCESS1_H
#define PROCESS1_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class process1;
}

class process1 : public QWidget
{
    Q_OBJECT

public:
    explicit process1(QWidget *parent = nullptr);
    ~process1();
public slots:
    void print();

private:
    Ui::process1 *ui;
    int num;
};

#endif // PROCESS1_H
