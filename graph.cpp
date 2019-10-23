#include "graph.h"
#include "ui_graph.h"
#include "mainwindow.h"
#include "mainwindow.cpp"
#include <QPainter>
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>

QT_USE_NAMESPACE



Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
   // ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr(".FRD files (*.frd)"));
    //ui->file_label->setText(fileName);
    QFile file(fileName);
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            str10 = 0;
            while(!file.atEnd())
            {
                //читаем строку
                QString str = file.readLine();
                //Делим строку на слова разделенные пробелом
                QString str1 = str.mid(0,2);
                if (str1 == "10")
                {
                    //qDebug() << str10;
                    sec_of_day[str10] = str.mid(3,18).toDouble();
                    //qDebug() << str.mid(3,18);
                    //qDebug() << QString::number(str.mid(3,18).toDouble(), 'g', 12);
                    time_of_flight[str10] =  str.mid(22,18).toDouble();
                    //qDebug() << str.mid(22,18);
                    //qDebug() << QString::number(str.mid(22,18).toDouble(), 'g', 12);
                    str10++;

                }
            }
            qDebug() << QString::number(sec_of_day[str10-1]-sec_of_day[0], 'g', 12);

            min = time_of_flight[0];
            for (int i = 0; i<str10; i++)
            {
                if (time_of_flight[i] < min) min = time_of_flight[i];
            }

            max = time_of_flight[0];
            for (int i = 0; i<str10; i++)
            {
                if (time_of_flight[i] > max) max = time_of_flight[i];
            }

            min2 = sec_of_day[0];
            for (int i = 0; i<str10; i++)
            {
                if (sec_of_day[i] < min2) min2 = sec_of_day[i];
            }

            max2 = sec_of_day[0];
            for (int i = 0; i<str10; i++)
            {
                if (sec_of_day[i] > max2) max2 = sec_of_day[i];
            }

            qDebug() << QString::number(min, 'g', 14);
            qDebug() << QString::number(max, 'g', 14);
            qDebug() << QString::number(min2, 'g', 14);
            qDebug() << QString::number(max2, 'g', 14);
        }
        else
        {
            qDebug()<< "don't open file";
        }
    repaint();
}

void Graph::timerEvent(QTimerEvent *event)
{
   int m_timerId = startTimer(2000);
   if (event->timerId() == m_timerId)
   {
       //readData();
   }
}

void Graph::paintEvent(QPaintEvent *)
{
    //QString str = date2.toString("dd-hhmmss");
    /*QString str2 = date2.toString("dd");
    if (str2!=data2)
    {
        file.close();
        QDateTime date = date.currentDateTime();
        str = date.toString("yyMMdd-hhmmss");
        data2 = date.toString("dd");
        file.setFileName("C:\\1\\" +str+ ".txt");
        if (file.isOpen()) file.close();
        if (file.exists()==false) file.open(QIODevice::WriteOnly);
    }*/

    QPainter painter(this); // определяем объект painter, который обеспечивает рисование
    //painter.drawImage(0,0, img.scaled(this->size())); // рисуем наше изображение от 0,0 и растягиваем по всему виджету

   //Q_UNUSED(event);
    //m_timerId = startTimer(1000);
    painter.setRenderHint(QPainter::Antialiasing);
    double side = qMin(width(), height());
    //painter.translate(side/2, side/2);
    painter.translate(10, side-10);
    painter.scale(side/1050, side/1050);
    painter.setPen(Qt::NoPen);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(-100, 0, 1000, 0); //OX
    painter.drawLine(0, 100, 0, -1000); //OY
    for (int i=1;i<10;i++) {
        painter.drawLine(-10, i*-100, 10, i*-100);
        painter.drawLine(i*100, 10, i*100, -10);
    }
    painter.drawLine(-10, -980, 0, -1000);
    painter.drawLine(10, -980, 0, -1000);
    painter.drawLine(980, -10, 1000, 0);
    painter.drawLine(980, 10, 1000, 0);
        //painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    //painter.setRenderHint(QPainter::Antialiasing);

        //painter.setPen(Qt::NoPen);
        QColor textcolour(0, 0, 0);
        painter.setPen(textcolour);
        QFont font;
        font.setPointSize(font.pointSize());
        font.setBold(true);
        QRectF temp_num = QRectF (10, -10, 200, -30);
        painter.setFont(font);
        painter.drawText(temp_num,Qt::AlignCenter,"Не подключено");

        double delta = max-min/1000;
        double delta2 = max2-min2/1000;

        for (int i = 0; i<str10; i++)
        {

        }
}

Graph::~Graph()
{
    delete ui;
}
