#include <stdint.h>
#include <stddef.h>

#include "my_stdio.h"
#include "my_string.h"

#include "raspi_peripheral.h"

int my_puts(const char *s)
{
    size_t size = my_strlen(s);
    pl011_write(UART0, (uint8_t *)s, size);
    pl011_write(UART0, (uint8_t *)"\n", 1);
    return (int)size;
}