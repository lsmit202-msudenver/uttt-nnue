# Versions
FROM mcr.microsoft.com/devcontainers/base:1-bookworm


# Install Packages
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
		gnupg ca-certificates software-properties-common \
        llvm lldb clang cppcheck valgrind ccache cmake wget git \
        # required by vscode
        gdb make ninja-build rsync zip \
    && apt-get autoremove -y \
    && apt-get clean autoclean \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/* /var/tmp/*

# update alternatives
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100

# update compiler environment vars
ENV CC=/usr/bin/clang \
    CXX=/usr/bin/clang++ \
    LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8 LANGUAGE=en_US.UTF-8
