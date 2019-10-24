#include "header.h"
#include "ui_header.h"
#include "graph.h"
#include <QFileDialog>
#include <QDebug>
#include <QDateTime>
#include "QTimer"
#include <QMessageBox>

Header::Header(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Header)
{
    ui->setupUi(this);

}

Header::~Header()
{
    delete ui;
    //delete Graph;
}

void Header::on_open_file_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open FRD File"), "", tr(".FRD files (*.frd)"));
    ui->file_label->setText(fileName);
    QFile file(fileName);
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            int h1 = 0;
            int h2 = 0;
            int h3 = 0;
            int h4 = 0;
            int h8 = 0;
            int h9 = 0;
            int c0 = 0;
            str10 = 0;
            while(!file.atEnd())
            {
                //читаем строку
                QString str = file.readLine();
                //Делим строку на слова разделенные пробелом
                QString str1 = str.mid(0,2);
                if ((str1 == "H1") or (str1 == "h1"))
                {
                    h1++;
                    if (str.mid(3,3) == "CRD") ui->H1_1->setChecked(true);
                    ui->H1_2->setText(str.mid(7,2));
                    ui->H1_3->setText(str.mid(10,4));
                    ui->H1_4->setText(str.mid(15,2));
                    ui->H1_5->setText(str.mid(18,2));
                    ui->H1_6->setText(str.mid(21,2));
                }
                if ((str1 == "H2") or (str1 == "h2"))
                {
                    h2++;
                    ui->H2_1->setText(str.mid(3,10));
                    ui->H2_2->setText(str.mid(14,4));
                    ui->H2_3->setText(str.mid(19,2));
                    ui->H2_4->setText(str.mid(22,2));
                    ui->H2_5->setText(str.mid(25,2));
                    switch (str.mid(25,2).toInt())
                    {
                    case 3:
                        ui->H2_5_3->setChecked(true);
                        break;
                    case 4:
                        ui->H2_5_4->setChecked(true);
                        break;
                    case 7:
                        ui->H2_5_7->setChecked(true);
                        break;
                    case 1:
                        case 2:
                        case 5:
                        case 6:
                        case 8:
                        case 9:
                        ui->H2_5_0->setChecked(true);
                        break;
                    default:
                        ui->H2_5_10->setChecked(true);
                        break;
                    }
                }
                if ((str1 == "H3") or (str1 == "h3"))
                {
                    h3++;
                    ui->H3_1->setText(str.mid(3,10));
                    ui->H3_2->setText(str.mid(14,8));
                    ui->H3_3->setText(str.mid(23,4));
                    ui->H3_4->setText(str.mid(28,8));
                    ui->H3_5->setText(str.mid(37,1));
                    ui->H3_6->setText(str.mid(39,1));
                    switch (str.mid(37,1).toInt())
                    {
                    case 1:
                        ui->H3_5_1->setChecked(true);
                        break;
                    case 2:
                        ui->H3_5_2->setChecked(true);
                        break;
                    case 0:
                        ui->H3_5_0->setChecked(true);
                        break;
                    }
                    switch (str.mid(39,1).toInt())
                    {
                    case 1:
                        ui->H3_6_1->setChecked(true);
                        break;
                    case 2:
                        ui->H3_6_2->setChecked(true);
                        break;
                    case 3:
                        ui->H3_6_3->setChecked(true);
                        break;
                    case 4:
                        ui->H3_6_4->setChecked(true);
                        break;
                    }
                }
                if ((str1 == "H4") or (str1 == "h4"))
                {
                    h4++;
                    ui->H4_1->setText(str.mid(3,2));
                    ui->H4_2->setText(str.mid(6,4));
                    ui->H4_3->setText(str.mid(11,2));
                    ui->H4_4->setText(str.mid(14,2));
                    ui->H4_5->setText(str.mid(17,2));
                    ui->H4_6->setText(str.mid(20,2));
                    ui->H4_7->setText(str.mid(23,2));
                    ui->H4_8->setText(str.mid(26,4));
                    ui->H4_9->setText(str.mid(31,2));
                    ui->H4_10->setText(str.mid(34,2));
                    ui->H4_11->setText(str.mid(37,2));
                    ui->H4_12->setText(str.mid(40,2));
                    ui->H4_13->setText(str.mid(43,2));
                    ui->H4_20->setText(str.mid(59,1));
                    ui->H4_21->setText(str.mid(61,1));
                    switch (str.mid(3,2).toInt())
                    {
                    case 1:
                        ui->H4_1_1->setChecked(true);
                        break;
                    case 2:
                        ui->H4_1_2->setChecked(true);
                        break;
                    case 0:
                        ui->H4_1_0->setChecked(true);
                        break;
                    }
                    switch (str.mid(46,2).toInt())
                    {
                    case 1:
                        ui->H4_14_1->setChecked(true);
                        break;
                    case 2:
                        ui->H4_14_2->setChecked(true);
                        break;
                    case 0:
                        ui->H4_14_0->setChecked(true);
                        break;
                    }
                    if (str.mid(49,1).toInt() == 1) ui->H4_15->setChecked(true);
                    if (str.mid(51,1).toInt() == 1) ui->H4_16->setChecked(true);
                    if (str.mid(53,1).toInt() == 1) ui->H4_17->setChecked(true);
                    if (str.mid(55,1).toInt() == 1) ui->H4_18->setChecked(true);
                    if (str.mid(57,1).toInt() == 1) ui->H4_19->setChecked(true);
                    switch (str.mid(59,1).toInt())
                    {
                    case 0:
                        ui->H4_20_0->setChecked(true);
                        break;
                    case 1:
                        ui->H4_20_1->setChecked(true);
                        break;
                    case 2:
                        ui->H4_20_2->setChecked(true);
                        break;
                    case 3:
                        ui->H4_20_3->setChecked(true);
                        break;
                    case 4:
                        ui->H4_20_4->setChecked(true);
                        break;
                    }
                    switch (str.mid(61,1).toInt())
                    {
                    case 1:
                        ui->H4_21_1->setChecked(true);
                        break;
                    case 2:
                        ui->H4_21_2->setChecked(true);
                        break;
                    case 0:
                        ui->H4_21_0->setChecked(true);
                        break;
                    }
                }
                if ((str1 == "H8") or (str1 == "h8")) h8++;
                if ((str1 == "H9") or (str1 == "h9")) h9++;
                if ((str1 == "C0") or (str1 == "c0"))
                {
                    c0++;
                    ui->C0_1->setText(str.mid(3,1));
                    ui->C0_2->setText(str.mid(5,10));
                    ui->C0_3->setText(str.mid(16,4));
                    ui->C0_4->setText(str.mid(21,4));
                    ui->C0_5->setText(str.mid(26,4));
                    ui->C0_6->setText(str.mid(31,4));
                    ui->C0_7->setText(str.mid(36,4));
                }
            }
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
}

void Header::on_pushButton_clicked()
{
    Graph *graph = new Graph();
        graph->show();
}
