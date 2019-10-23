#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//class Graph;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_open_file_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    double sec_of_day[256];
    double time_of_flight[256];
    int str10;
};
#endif // MAINWINDOW_H
