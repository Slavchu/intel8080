#include "memory.hpp"

RAM &RAM::instance(){
    static RAM ram;
    return ram;
}

uint8_t RAM::read(uint16_t adress){
    return mem[adress];
}
void RAM::write(uint16_t adress, uint8_t value){
    mem[adress] = value; 
}

