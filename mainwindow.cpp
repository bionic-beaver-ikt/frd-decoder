#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "header.h"
#include <QFileDialog>
#include <QDebug>
#include <QDateTime>
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete Graph;
}

void MainWindow::on_header_clicked()
{
    Header *header = new Header();
        header->show();
}

void MainWindow::on_graph10_clicked()
{
    Graph *graph = new Graph();
        graph->show();
}
