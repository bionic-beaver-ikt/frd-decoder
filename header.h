#ifndef HEADER_H
#define HEADER_H

#include <QMainWindow>
#include <QPainter>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Header; }
QT_END_NAMESPACE

//class Graph;

class Header : public QMainWindow
{
    Q_OBJECT

public:
    Header(QWidget *parent = nullptr);
    ~Header() override;

private slots:
    void on_open_file_clicked();
    void on_pushButton_clicked();

private:
    Ui::Header *ui;
    double sec_of_day[1024];
    double time_of_flight[1024];
    int str10;
};
#endif // HEADER_H
