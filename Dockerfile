FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    ssdeep \
    radare2 \
    python3 \
    python3-pip \
    python3-venv \
    python3-numpy \
    python3-pandas \
    git \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /project

CMD ["/bin/bash"]

