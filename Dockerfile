# Используем официальный образ Ubuntu LTS
FROM ubuntu:22.04

# Устанавливаем необходимые пакеты
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    clang \
    lldb \
    cmake \
    vim \
    && rm -rf /var/lib/apt/lists/*



RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt install -y \
    libgtest-dev \
    && cd /usr/src/gtest \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && cp lib/*.a /usr/lib \
    && rm -rf /var/lib/apt/lists/*


COPY ./ /app
# Создаем рабочую директорию
WORKDIR /app