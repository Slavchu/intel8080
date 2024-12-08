#pragma once

#include <common.hpp>

#define FLAG_SIGN     0b10000000
#define FLAG_ZERO     0b01000000
#define FLAG_AC       0b00010000
#define FLAG_PAIRITY  0b00000100
#define FLAG_CARRY    0b00000001

/*
 * Singletone class that represents INTEL 8080 
*/
class CPU_8080{
  
  CPU_8080(CPU_8080 const &) = delete;
  CPU_8080& operator=(CPU_8080 const &) = delete;
  CPU_8080()  {};
  ~CPU_8080() {};
  uint16_t program_counter = 0x00;
  uint16_t stack_pointer = 0x00;    //after all starts from 0xFFFE 
  uint8_t flag = 0b00000010;        //layout 0bSZ0A0P1C
public:
  static CPU_8080& instance();
  bool tick();
  uint16_t get_program_counter() const; 
};

