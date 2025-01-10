#pragma once
#include "common.hpp"
/*
 * Singletone class that represents RAM
*/
class RAM{  
  uint8_t mem[MEMORY_SIZE];
  RAM();
  ~RAM(){};
public:

  static RAM& instance();
  
  RAM(RAM const&) = delete;
  RAM& operator=(RAM const&) = delete;
  uint8_t read(uint16_t adress);
  void write(uint16_t adress, uint8_t value);
};
