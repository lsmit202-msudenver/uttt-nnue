#!/bin/bash

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
BASE_DIR="$(dirname -- "$SCRIPT_DIR")"
BUILD_DIR="$BASE_DIR"/build

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

conan install .. --output-folder=. --build=missing
cmake -DBUILD_TESTING=TRUE -DBUILD_SHARED_LIBS=TRUE -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

if command -v clang-format &> /dev/null; then
    cmake --build . --target format
fi