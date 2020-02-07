#pragma once

#include "target_config.h"

#ifdef TARGET_RASPI_3 
    #include "raspi3_peripheral.h"
#elif defined(TARGET_RASPI_4)
    #include "raspi4_peripheral.h"
#else
    #error "select TARGET_RASPI_3 or TARGET_RASPI_4"
#endif