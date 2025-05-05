# Тестовое задание YADRO

## Описание задания

Условия тестового задания можете прочитать [тут](./Тестовое%20задание%20С++.docx)

# 🚀 Начало работы

## 📦 Требования

- C++17 или выше
- CMake 3.10 или выше
- Компилятор с поддержкой C++17 (например, GCC, Clang)

## 🔧 Сборка и запуск

### 1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/ddos-pmv/YADRO_club.git
   cd YADRO_club
   ```
### 2. Создайте директорию сборки и выполните сборку:
   ```bash

   /YADRO_club$ cmake -S . -B buildFiles
   /YADRO_club$ cmake --build buildFiles

   ```
### ▶️ Запуск
   ```bash
   /YADRO_club$ ./buildFiles/YADRO_club ./data/input.txt
   ```

## 🗂️ Структура проекта
- src/ — исходный код программы.
- data/ — входные данные для программы.
- bin/ — директория для исполняемых файлов.
- buildFiles/ — директория для файлов сборки.
- Dockerfile — конфигурация для создания Docker-образа.


## 🐳 Docker-среда
На случай, если сборка проекта в вашей системе вызывает трудности 
(например, из-за версии компилятора, CMake или зависимостей), 
предоставлен Dockerfile, содержащий минимальную среду на базе Ubuntu с двумя компиляторами и CMake.
Это упрощает воспроизводимую сборку проекта в любой среде.

### ⚙️ Что внутри Docker-образа
Базовый образ: ubuntu:latest
Установлены:
- g++ (GCC)
- clang++ (Clang)
- cmake

Все необходимые зависимости для сборки проекта

### 🧪 Как использовать Docker для сборки проекта
1. Убедитесь, что у вас установлен Docker.
2. Соберите Docker-образ:
   ```bash
   docker build -t imageyadro .
   ```
3. Запустите контейнер и войдите в него:
   ```bash
   docker run -it --rm --name containerYadro imageyadro 
   ```
   
4. Внутри контейнера выполните сборку проекта:

GCC:
```bash
    cmake -S . -B buildFiles -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
    cmake --build buildFiles 
```
Clang:
```bash
    cmake -S . -B buildFiles -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
    cmake --build buildFiles
   ```
