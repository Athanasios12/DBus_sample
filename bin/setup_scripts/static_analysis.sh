#!/bin/sh
SRC_DIR="../src"
INCLUDE_DIR="../include"
clang-tidy -checks=-*,clang-analyzer-*,cppcoreguidelines- $SRC_DIR/*.cpp -- -std=c++17 -I$INCLUDE_DIR $(pkg-config --cflags dbus-1)

