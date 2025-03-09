# docker build -t intersect_image .
# docker run -it -v .:/app intersect_image /bin/bash

FROM ubuntu:24.04

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
    g++ \
    cmake \
    libeigen3-dev\
    libgtest-dev 

WORKDIR /app