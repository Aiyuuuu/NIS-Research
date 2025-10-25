
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive


RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    lld \
    ssdeep \
    radare2 \
    python3 \
    python3-pip \
    python3-venv \
    python3-numpy \
    python3-pandas \
    git \
    wget \
    ca-certificates \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

COPY binaries/sdhash /usr/local/bin/sdhash
RUN chmod +x /usr/local/bin/sdhash

COPY binaries/usr/lib/x86_64-linux-gnu /usr/local/lib/sdhash_libs

ENV LD_LIBRARY_PATH=/usr/local/lib/sdhash_libs:$LD_LIBRARY_PATH

COPY binaries/tigress_4.0.11-1_all.deb /tmp/tigress.deb
RUN dpkg -i /tmp/tigress.deb || true && \
    apt-get update && apt-get install -y -f && \
    rm -f /tmp/tigress.deb && \
    apt-get clean && rm -rf /var/lib/apt/lists/*
RUN command -v tigress >/dev/null 2>&1 && tigress --version || (echo "tigress install failed" && exit 1)

WORKDIR /project

CMD ["/bin/bash"]

