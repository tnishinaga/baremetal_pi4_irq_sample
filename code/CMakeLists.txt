cmake_minimum_required(VERSION 3.10)
project(kernel.elf)

enable_language(ASM C)

set(TARGET_MACHINE "RASPI_3" CACHE STRING "Select RASPI_3 or RASPI_4")
# target_compile_definitions(kernel.elf PRIVATE "TARGET_${TARGET_MACHINE}")
configure_file("${PROJECT_SOURCE_DIR}/target_config.h.in"
   "${PROJECT_SOURCE_DIR}/target_config.h"
   @ONLY
   NEWLINE_STYLE LF
)

set(C_SOURCES
   bcm2835_interrupt.c
   bcm2836_interrupt.c
   interrupt_handler.c
   main.c
   gpio.c
   raspi3_peripheral.c
   raspi4_peripheral.c
   pl011_serial.c
   my_stdio.c
   my_string.c
)

set(C_HEADERS
   bcm2835_interrupt.h
   bcm2836_interrupt.h
   interrupt_handler.h
   gpio.h
   raspi_peripheral.h
   raspi3_peripheral.h
   raspi4_peripheral.h
   pl011_serial.h
   my_stdio.h
   my_string.h
   armv8_misc.h
   target_config.h
)

add_executable(kernel.elf start.S vector_table.S ${C_SOURCES} ${C_HEADERS})

# add linkerscript
set(LINKER_SCRIPT "ldscript.ld")
set_target_properties(kernel.elf PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})
target_link_options(kernel.elf PRIVATE "-T${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT}")
# static link
target_link_options(kernel.elf PRIVATE "-static")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O2")
set(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS} -O2 -DNDEBUG")
set(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -O2 -DDEBUG")

# copy to binary
add_custom_command(
   TARGET kernel.elf
   POST_BUILD
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
   COMMAND ${CMAKE_OBJCOPY} -O binary kernel.elf kernel.bin
)
