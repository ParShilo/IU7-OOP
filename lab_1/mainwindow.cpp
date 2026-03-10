#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "errors.h"
#include "actions.h"

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

error_code_t MainWindow::draw()
{
    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(),
                                            rcontent.height());

    request_t request;
    request.action = DRAW;
    request.view = {
        .scene = ui->graphicsView->scene(),
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
        .line_color = Qt::black
    };

    return choose_action(request);
}

void MainWindow::on_button_move_clicked()
{
    request_t request;
    request.action = MOVE;
    request.move = {.dx = ui->move_x->value(),
                    .dy = ui->move_y->value(),
                    .dz = ui->move_z->value()};

    error_code_t rc = choose_action(request);
    if (rc)
        print_error(rc);
    else
    {
        rc = draw();
        if (rc)
            print_error(rc);
    }
}

void MainWindow::on_button_rotate_clicked()
{

}

void MainWindow::on_button_scale_clicked()
{

}

