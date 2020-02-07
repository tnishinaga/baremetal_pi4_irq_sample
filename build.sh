#!/bin/bash

docker run --rm \
    -v ${PWD}:/home/work:rw \
    tnishinaga/aarch64-elf_toolchain \
    bash -c " \
        cd /home/work/code
        cmake -H. \
            -Bbuild \
            -GNinja \
            -DCMAKE_TOOLCHAIN_FILE=./aarch64-elf-gcc.cmake \
            -DCMAKE_BUILD_TYPE=Release \
            -DTARGET_MACHINE=RASPI_4
        cmake --build build
        ./install.sh
    "