#pragma once

#include <common.hpp>

#define FLAG_SIGN 0b10000000
#define FLAG_ZERO 0b01000000
#define FLAG_AC 0b00010000
#define FLAG_PAIRITY 0b00000100
#define FLAG_CARRY 0b00000001

/*
 * Singletone class that represents INTEL 8080
 */
enum ECPU_8080_REGISTERS {
    REG_A = 0b111,
    REG_B = 0b000,
    REG_C = 0b001,
    REG_D = 0b010,
    REG_E = 0b011,
    REG_H = 0b100,
    REG_L = 0b101,
    REG_M = 0b110
};

enum ECPU_8080_REGISTER_PAIRS {
    REG_BC = 0b00,
    REG_DE = 0b01,
    REG_HL = 0b10,
    REG_SP = 0b11
};

class CPU_8080 {
    CPU_8080(CPU_8080 const&) = delete;
    CPU_8080& operator=(CPU_8080 const&) = delete;
    CPU_8080() {};
    ~CPU_8080() {};

    // register section
    uint8_t r_A;
    uint16_t r_BC;
    uint16_t r_DE;
    uint16_t r_HL;
    uint16_t r_PC = 0x00;
    uint16_t r_SP = 0x00;       // after all starts from 0xFFFE
    uint8_t flag = 0b00000010;  // layout 0bSZ0A0P1C
    // end of register section

    /*
     * processes opcode
     * [IN] opcode: opcode, lol, what else could you expect?
     * return value: ticks required for opcode
     * 
     * Note: it is shitcode I didn't test well, it can throw exceptions. PLEASE, HANDLE THEM!!!
     */
    int process_opcode(uint8_t opcode);

    // instuctions
    void mov(ECPU_8080_REGISTERS dest, ECPU_8080_REGISTERS src);
    void mvi(ECPU_8080_REGISTERS dest, uint8_t value);
    void lxi(ECPU_8080_REGISTER_PAIRS dest, uint16_t value);

   public:
    static CPU_8080& instance();
    bool tick();
    uint16_t get_program_counter() const;
};
