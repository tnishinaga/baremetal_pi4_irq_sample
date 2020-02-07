#!/bin/bash -x

TFTP_ROOT="../netboot/tftpboot/"

cp -f config.txt ${TFTP_ROOT}
cp -f build/kernel.bin ${TFTP_ROOT}
