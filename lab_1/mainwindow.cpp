#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QMenu>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "errors.h"
#include "actions.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    request_t request;
    request.action = EXIT;
    choose_action(request);
    delete ui;
}

error_code_t MainWindow::draw()
{
    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

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

static double radian(const double angle)
{
    return angle * (M_PI / 180);
}

void MainWindow::on_button_rotate_clicked()
{
    request_t request;
    request.action = ROTATE;
    request.rotate = {.angle_x = radian(ui->rotate_x->value()),
                      .angle_y = radian(ui->rotate_y->value()),
                      .angle_z = radian(ui->rotate_z->value())};

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

void MainWindow::on_button_scale_clicked()
{
    request_t request;
    request.action = SCALE;
    request.scale = {.kx = ui->scale_x->value(),
                     .ky = ui->scal_y->value(),
                     .kz = ui->scale_z->value()};

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

void MainWindow::on_action_open_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    request_t request;
    request.action = OPEN;

    QByteArray ba = path.toLocal8Bit();
    request.file_name = ba.data();

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

void MainWindow::on_action_save_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    request_t request;
    request.action = SAVE;
    request.file_name = path.toUtf8().data();

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
