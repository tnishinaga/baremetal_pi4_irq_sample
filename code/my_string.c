#include "my_string.h"

size_t my_strlen(const char *s)
{
    size_t count = 0;
    while (*s != '\0') {
        count++;
        s++;
    }
    return count;
}