#!/bin/bash


binaries=(
    "LICENCE.broadcom"
    "bootcode.bin"
    "fixup.dat"
    "fixup4.dat"
    "fixup4cd.dat"
    "fixup4db.dat"
    "fixup4x.dat"
    "fixup_cd.dat"
    "fixup_db.dat"
    "fixup_x.dat"
    "start.elf"
    "start4.elf"
    "start4cd.elf"
    "start4db.elf"
    "start4x.elf"
    "start_cd.elf"
    "start_db.elf"
    "start_x.elf"
    "bcm2711-rpi-4-b.dtb"
)

url="https://github.com/Hexxeh/rpi-firmware/raw/0dfefdceed89582e9ddda856a9056739d0cf9059/"

mkdir -p tftpboot/
cd tftpboot/

for binary in "${binaries[@]}"; do
    echo "download ${url}${binary}"
    curl -s -L -O ${url}${binary}
done

# enable uart
if [[ "$OSTYPE" == "darwin"* ]]; then
    gsed -i -e "s/BOOT_UART=0/BOOT_UART=1/" bootcode.bin
else
    sed -i -e "s/BOOT_UART=0/BOOT_UART=1/" bootcode.bin
fi