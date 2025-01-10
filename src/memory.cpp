#include "memory.hpp"
#include <memory.h>

RAM &RAM::instance(){
    static RAM ram;
    return ram;
}

RAM::RAM(){
  memset(&mem, 0, MEMORY_SIZE);
}

uint8_t RAM::read(uint16_t adress){
    return mem[adress];
}

void RAM::write(uint16_t adress, uint8_t value){
    mem[adress] = value; 
}

