COMPILER_NAME := g++
CPPFLAGS := -std=c++20 -Wall -Wextra -Wpedantic

# Говорим компилятору, где искать заголовки
INCLUDES := -I. -Ilist -Iiterator -Iexception

# Папка для объектных файлов
OBJ_DIR := obj

# Объектные файлы
OBJS := $(OBJ_DIR)/main.o $(OBJ_DIR)/exceptions.o

# Все заголовки (для зависимостей)
HEADERS := $(wildcard list/*.h) \
           $(wildcard list/*.hpp) \
           $(wildcard iterator/*.h) \
           $(wildcard iterator/*.hpp) \
           $(wildcard exception/*.h)

# Итоговый файл
TARGET := app.exe

.PHONY: all clean run

all: $(TARGET)

# Сборка (линковка)
$(TARGET): $(OBJS)
	$(COMPILER_NAME) $(CPPFLAGS) -o $@ $^

# Компиляция main.cpp
$(OBJ_DIR)/main.o: main.cpp $(HEADERS) | $(OBJ_DIR)
	$(COMPILER_NAME) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

# Компиляция exceptions.cpp
$(OBJ_DIR)/exceptions.o: exception/exceptions.cpp exception/exceptions.h | $(OBJ_DIR)
	$(COMPILER_NAME) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

# Создание папки obj
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)