#ifndef MAINWINDOW_H__
#define MAINWINDOW_H__

#include <QMainWindow>

#include "errors.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void on_action_open_clicked();
    void on_action_save_clicked();

private slots:
    error_code_t draw();
    void on_button_move_clicked();
    void on_button_scale_clicked();
    void on_button_rotate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
