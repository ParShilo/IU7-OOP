#include <QMessageBox>
#include "errors.h"

void print_error(error_code_t error)
{
    switch (error)
    {
    case ERROR_ACTION:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка действия");
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
    case ERROR_SCENE:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка обработки сцены");
        break;
    case ERROR_POINTS:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка обработки точек");
        break;
    case ERROR_EDGE_INDEX:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка использования ребра: некорректные индексы");
        break;
    case ERROR_EDGES:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка обработки рёбер");
        break;
    case ERROR_FILE:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка работы с файлом");
        break;
    case ERROR_FILENAME:
        QMessageBox::critical(NULL, "Ошибка", "Ошибка с именем файла");
        break;
    default:
        QMessageBox::critical(NULL, "Ошибка", "Неизвестная ошибка");
    }
}
