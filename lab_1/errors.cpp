#include <QMessageBox>
#include "errors.h"

void print_error(error_code_t error)
{
    switch (error)
    {
    case ERROR_ACTION:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка действия");
        break;
    case ERROR_ARGS:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка аргументов функции");
        break;
    case ERROR_INPUT_POINTS:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка чтения точек из файла");
        break;
    case ERROR_AMOUNT_POINTS:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка чтения кол-ва точек из файла");
        break;
    case ERROR_INPUT_EDGES:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка чтения ребёр из файла");
        break;
    case ERROR_AMOUNT_EDGES:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка чтения кол-ва ребёр из файла");
        break;
    case ERROR_FILE_OPEN:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка открытия файла");
        break;
    case ERROR_FILE_WRITE:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка изменения файла");
        break;
    case ERROR_MEMORY:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка выделения памяти");
        break;
    default:
        QMessageBox::critical(NULL, "Ошибка", "Неизвестная ошибка");
    }
}
