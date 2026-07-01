#!/usr/bin/env bash

set -xe

gcc  main.c gl.c -o main -I../inc ../lib/libglfw3.a -lGL -lm

