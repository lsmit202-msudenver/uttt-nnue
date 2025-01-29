# Versions
FROM mcr.microsoft.com/devcontainers/base:1-bookworm

ARG CONAN_VERSION=2.12.1
ARG CMAKE_VERSION=3.31.5

# Install packages
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        # Needed base packages
		build-essential \
        # compiler tooling
        llvm lldb clang ninja-build \ 
        # dev tooling
        cppcheck valgrind clang-format ccache \        
    && apt-get autoremove -y \
    && apt-get clean autoclean \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/* /var/tmp/*

# Install Conan
RUN \
    curl -fsSL https://github.com/conan-io/conan/releases/download/${CONAN_VERSION}/conan-${CONAN_VERSION}-amd64.deb -o /tmp/conan.deb && \
    dpkg -i /tmp/conan.deb

# Install CMake
RUN \
    curl -fsSL https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz -o /tmp/cmake.tar.gz && \
    mkdir -p /opt/cmake && \
    tar -xzf /tmp/cmake.tar.gz -C /opt/cmake/ --strip-components=1 && \
    chmod +x /opt/cmake/bin/* && \
    ln -sf /opt/cmake/bin/cmake /usr/bin/cmake && \
    ln -sf /opt/cmake/bin/ctest /usr/bin/ctest && \
    ln -sf /opt/cmake/bin/cpack /usr/bin/cpack && \
    ln -sf /opt/cmake/bin/ccmake /usr/bin/ccmake && \
    rm -rf /tmp/*


# # update alternatives
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100

# update compiler environment vars
ENV CC=/usr/bin/clang \
    CXX=/usr/bin/clang++
