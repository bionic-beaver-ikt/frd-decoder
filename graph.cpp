#include "graph.h"
#include "ui_graph.h"
#include "mainwindow.h"
#include "mainwindow.cpp"
#include <QPainter>
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>

QT_USE_NAMESPACE

Graph::Graph(QWidget *parent) : QMainWindow(parent), ui(new Ui::Graph)
{
    ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open FRD File"), "", tr(".FRD files (*.frd)"));
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

            min = time_of_flight[0];
            for (int i = 0; i<str10; i++)
            {
qDebug() << QString::number(time_of_flight[i], 'g', 16);
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
            ui->textBrowser->setText("Minimum time of flight: " + (QString::number(min, 'g', 14)) + "\r\nMaximum time of flight: "+ (QString::number(max, 'g', 14)) + "\r\nTotal seconds: "+ (QString::number(max2-min2, 'g', 12))+ "\r\nData records: "+ (QString::number(str10)));
        }
        else
        {
            QMessageBox::warning(this, "Alarm! Алярм!", "Can't open file!", QMessageBox::Ok);
            /*QMessageBox msgBox;
            msgBox.setText("Alarm! Алярм!");
            msgBox.setInformativeText("Can't open file!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();*/
        }
    //repaint();
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
    painter.translate(75, side-25);
    painter.scale(side/1100, side/1100);
    painter.setPen(Qt::NoPen);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(-100, 0, 2040, 0); //OX
    painter.drawLine(0, 100, 0, -1060); //OY

    QFont font;
    font.setPointSize(font.pointSize()+1);
    font.setBold(true);
    //QRectF temp_num = QRectF (10, -10, 200, -30);
    painter.setFont(font);

    for (int i=1;i<11;i++) {
        painter.drawLine(-5, i*-100, 5, i*-100);
        painter.drawLine(i*200, 5, i*200, -5);
        painter.drawText(QRectF (i*200-100, 5, 200, 20),Qt::AlignCenter, QString::number((max2-min2)/10*i, 'g', 8));
        painter.drawText(QRectF (-80, -i*100-10, 75, 20),Qt::AlignCenter, QString::number(min+((max-min)/10*i), 'g', 8));
    }
    painter.drawLine(-10, -1040, 0, -1060);
    painter.drawLine(10, -1040, 0, -1060);
    painter.drawLine(2020, -10, 2040, 0);
    painter.drawLine(2020, 10, 2040, 0);

        double delta = 1000/(max-min);
        double delta2 = 2000/(max2-min2);

        QPointF point1(0,0);
        for (int i = 0; i<str10; i++)
        {
            QPointF point2((sec_of_day[i]-min2)*delta2,(time_of_flight[i]-min)*-delta);
            painter.drawLine(point1,point2);
            //qDebug() << point1;
            //qDebug() << point2;
            point1=point2;
        }
            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
}

Graph::~Graph()
{
    delete ui;
}
