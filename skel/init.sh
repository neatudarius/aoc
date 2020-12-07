#!/bin/bash

DAY_DIR="${1}"
mkdir -p "${DAY_DIR}"

# C++ skel
cd "${DAY_DIR}" || exit 1
ln -fs ../../skel/Makefile .
cp ../../skel/skel.cpp aoc.cpp

# Python skel
cp ../../skel/skel.py aoc.py

# in/out files
touch in out
