#pragma once

#include <stdint.h>

#include <iostream>

// emulator defaults
#define MEMORY_SIZE 65536
#define FREQUENCY_HZ 2000
#define DEFAULT_PROGRAM_PATH "program.bin"

// macrosses
#define DEBUG_ERROR(err_msg) std::cerr << "ERROR:" << __FILE__ << " (" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "):\t\t" err_msg << std::endl

union byte_pair_t {
    uint16_t DBYTE;
    struct {
        uint8_t LBYTE;
        uint8_t HBYTE;
    };
};
