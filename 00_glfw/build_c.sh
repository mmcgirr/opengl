#!/usr/bin/env bash

set -xe

gcc -I../ext/glfw/include -o main main.c  ../ext/glfw/build/src/libglfw3.a -lGL -lm
