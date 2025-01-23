ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Versions
ARG UBUNTU_VERSION=24.04
ARG LLVM_VERSION=17

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/*

FROM docker.io/library/ubuntu:${UBUNTU_VERSION} AS base

WORKDIR /tmp

ENV LANG en_US.utf8
ENV DEBIAN_FRONTEND=noninteractive

# Install Packages
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        locales gnupg2 ca-certificates software-properties-common \
        cppcheck valgrind ccache cmake wget git \
        # required by Visual Studio
        gdb make ninja-build rsync zip \
        # required by LLVM
        lsb-release zlib1g-dev \
    && apt-get autoremove -y \
    && apt-get clean autoclean \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/*

# Define locale
RUN localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8

# Latest CMake
RUN version="$(curl -s https://api.github.com/repos/Kitware/CMake/releases/latest | jq -r '.tag_name' | cut -c 2-)"; echo "Latest Version: $version" && \
    url="https://github.com/Kitware/CMake/releases/download/v$version/cmake-$version-linux-x86_64.sh"; echo "Download URL: $url" && \
    wget -q $url && \
    mkdir /opt/cmake && \
    sh cmake-$version-linux-x86_64.sh --prefix=/opt/cmake --skip-license && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
    rm -rf cmake-$version-linux-x86_64.sh

# LLVM
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh ${LLVM_VERSION} all && \
    rm ./llvm.sh

# add llvm to path
ENV PATH="/usr/lib/llvm-${LLVM_VERSION}/bin:/usr/lib/llvm-${LLVM_VERSION}/include:${PATH}"
ENV LD_LIBRARY_PATH="/usr/lib/llvm-${LLVM_VERSION}/lib:${LD_LIBRARY_PATH}"

# unversionize the binaries
RUN ln -s /usr/bin/clang-${LLVM_VERSION} /usr/bin/clang && \
    ln -s /usr/bin/clang++-${LLVM_VERSION} /usr/bin/clang++ && \
    ln -s /usr/bin/clang-format-${LLVM_VERSION} /usr/bin/clang-format

# update alternatives
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100

# update compiler environment vars
ENV CC=/usr/bin/clang \
    CXX=/usr/bin/clang++ \
    LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8

USER $USERNAME
