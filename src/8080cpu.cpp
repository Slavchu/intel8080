#include <8080cpu.hpp>
#include <memory.hpp>

uint16_t CPU_8080::get_program_counter() const{
    return program_counter;
}

CPU_8080& CPU_8080::instance(){
    static CPU_8080 cpu;
    return cpu;
}

bool CPU_8080::tick(){
    return 1;
}

