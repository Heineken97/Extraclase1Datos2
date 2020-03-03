#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * @brief calculates dijkstra and handles showing data
 */
//
void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->setText("House");

}

