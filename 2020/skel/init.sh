#!/bin/bash

DAY_DIR="${1}"
mkdir -p "${DAY_DIR}"

# C++ skel
cd "${DAY_DIR}" || exit 1
ln -s ../skel/Makefile .
cp ../skel/skel.cpp skel.cpp
