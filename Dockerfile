FROM debian:10-slim

WORKDIR /usr/src/app

RUN apt update && \
    apt upgrade --yes && \
    apt install locales --yes && \
    dpkg-reconfigure tzdata

RUN apt-get install --yes \
    build-essential \
    git \
    make \
    cmake

RUN rm -rf /var/lib/apt/lists/*

COPY . .

RUN make install
