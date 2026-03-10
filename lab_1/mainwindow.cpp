#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_move_clicked()
{

}

void MainWindow::on_button_rotate_clicked()
{

}

void MainWindow::on_button_scale_clicked()
{

}

