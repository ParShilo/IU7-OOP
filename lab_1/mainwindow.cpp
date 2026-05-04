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
    task_t task;
    task.action = EXIT;
    choose_action(task);
    delete ui;
}

static double radian(const double angle)
{
    return angle * (M_PI / 180);
}

error_code_t MainWindow::draw()
{
    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    task_t task;
    task.action = DRAW;
    task.scene = {
        .scene = ui->graphicsView->scene(),
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height()
    };

    return choose_action(task);
}

void MainWindow::on_button_move_clicked()
{
    task_t task;
    task.action = MOVE;
    task.move = {.x = ui->move_x->value(),
                 .y = -1 * ui->move_y->value(),
                 .z = ui->move_z->value()};

    error_code_t rc = choose_action(task);
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
    task_t task;
    task.action = ROTATE;
    task.rotate = {.angle_x = radian(ui->rotate_x->value()),
                   .angle_y = radian(ui->rotate_y->value()),
                   .angle_z = radian(ui->rotate_z->value())};

    error_code_t rc = choose_action(task);
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
    task_t task;
    task.action = SCALE;
    task.scale = {.kx = ui->scale_x->value(),
                  .ky = ui->scal_y->value(),
                  .kz = ui->scale_z->value()};

    error_code_t rc = choose_action(task);
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
    task_t task;
    task.action = OPEN;

    QByteArray ba = path.toLocal8Bit();
    task.file_name = ba.data();

    error_code_t rc = choose_action(task);
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
    task_t task;
    task.action = SAVE;
    task.file_name = path.toUtf8().data();

    error_code_t rc = choose_action(task);
    if (rc)
        print_error(rc);
    else
    {
        rc = draw();
        if (rc)
            print_error(rc);
    }
}
