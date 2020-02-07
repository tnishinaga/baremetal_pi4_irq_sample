#include "gpio.h"

#include <stdlib.h>
#include <stdbool.h>

static inline bool in_port_range(uint32_t port)
{
    if (port <= 53) {
        return true;
    }
    return false;
}

static inline int gpio_error_check(GPIO_Type *gpio, uint32_t port)
{
    if (gpio == NULL) {
        return -1;
    }
    if (!in_port_range(port)) {
        return -1;
    }
    return 0;
}

int gpio_mode(GPIO_Type *gpio, uint32_t port, GPIO_FUNC func)
{
    if (gpio_error_check(gpio, port) < 0) {
        return -1;
    }

    uint32_t fselnum = port / 10;
    uint32_t fselrest = port % 10;

    uint32_t gpfsel = gpio->GPFSEL[fselnum];
    gpfsel &= ~((uint32_t)(0x07 << (fselrest * 3)));
    gpfsel |= (uint32_t)(func << (fselrest * 3));
    gpio->GPFSEL[fselnum] = gpfsel;

    return 0;
}

int gpio_output(GPIO_Type *gpio, uint32_t port, bool out)
{
    if (gpio_error_check(gpio, port) < 0) {
        return -1;
    }

    volatile uint32_t *reg = NULL;
    if (out == true) {
        reg = gpio->GPSET;
    } else {
        reg = gpio->GPCLR;
    }

    uint32_t num = port / 32;
    reg[num] = 1 << (port % 32);

    return 0;
}
