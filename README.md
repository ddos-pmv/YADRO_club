# Тестовое задание YADRO

## Описание задания

Условия тестового задания можете прочитать [тут](./Тестовое%20задание%20С++.docx)

## Требования

- CMake 3.2 или выше
- Компилятор C++ с поддержкой стандарта C++20

## Сборка и запуск

1. Клонируйте репозиторий:
   ```sh
   git clone https://github.com/ddos-pmv/YADRO_club.git
   cd YADRO_club
   ```
2. Создайте директорию сборки и выполните сборку:

   ```bash

   /YADRO$ mkdir buildFiles
   /YADRO$ cd buildFiles
   YADRO/build$ cmake ..
   YADRO/build$ cmake --build .
   ```

3. Перейдите к исполняемому файлу и запустите:

```bash
    YADRO/buildFiles$ cd ../bin
    YADRO/bin$ ./YADRO input.txt
```

## Важно

- **Все файлы со входными данными должны лежать в папке data/**
