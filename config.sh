#!/bin/sh

cmake -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF  -D glew-cmake_BUILD_SHARED=OFF -S . -B build
