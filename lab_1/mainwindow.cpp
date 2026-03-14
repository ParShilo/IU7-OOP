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
    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    connect(ui->action_open, &QAction::triggered, this, &MainWindow::on_action_open_clicked);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::on_action_save_clicked);
    connect(ui->button_scale, &QPushButton::clicked, this, &MainWindow::on_button_scale_clicked);
    connect(ui->button_move, &QPushButton::clicked, this, &MainWindow::on_button_move_clicked);
    connect(ui->button_rotate, &QPushButton::clicked, this, &MainWindow::on_button_rotate_clicked);
}

MainWindow::~MainWindow()
{
    request_t request;
    request.action = EXIT;
    choose_action(request);
    delete ui;
}

static double radian(const double angle)
{
    return angle * (M_PI / 180);
}

// Рисовать
error_code_t MainWindow::draw()
{
    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    request_t request;
    request.action = DRAW;
    request.scene = {
        .scene = ui->graphicsView->scene(),
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height()
    };

    return choose_action(request);
}

// Перенести
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

// Повернуть
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

// Масштабировать
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

// Открыть файл
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

// Сохранить файл
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
