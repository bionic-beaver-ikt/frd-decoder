#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {class Graph;}

//class QIntValidator;

QT_END_NAMESPACE

class Graph : public QMainWindow
{
    Q_OBJECT

protected:
void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;
void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph() override;
    Graph graph() const;
    double sec_of_day[65535];
    double time_of_flight[65535];
    int str10;
    double min;
    double max;
    double min2;
    double max2;

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
