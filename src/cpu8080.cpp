#include <cpu8080.hpp>
#include <cstdint>
#include <memory.hpp>
#include <opcodes8080.hpp>

#define SET_FLAG(x, flag) x = x | F
#define HAS_FLAG(x, flag) (x & f > 0)
#define WRITE_L_REG(reg, val) reg |= (val << 8)
#define WRITE_R_REG(reg, val) reg |= val
#define READ_L_REG(reg) (reg & 0xFF00) >> 8
#define READ_R_REG(reg) reg & 0xFF

#define OP_MOV 0b01000000

uint16_t CPU_8080::get_program_counter() const { return r_PC; }

CPU_8080& CPU_8080::instance() {
    static CPU_8080 cpu;
    return cpu;
}

void CPU_8080::mov(ECPU_8080_REGISTERS dest, ECPU_8080_REGISTERS src) {
    uint8_t value;

    switch (src) {
        case ECPU_8080_REGISTERS::REG_A: {
            value = r_A;
            break;
        }
        case ECPU_8080_REGISTERS::REG_B: {
            value = READ_L_REG(r_BC);
            break;
        }
        case ECPU_8080_REGISTERS::REG_C: {
            value = READ_R_REG(r_BC);
            break;
        }
        case ECPU_8080_REGISTERS::REG_D: {
            value = READ_L_REG(r_DE);
            break;
        }
        case ECPU_8080_REGISTERS::REG_E: {
            value = READ_R_REG(r_DE);
            break;
        }
        case ECPU_8080_REGISTERS::REG_H: {
            value = READ_L_REG(r_HL);
            break;
        }
        case ECPU_8080_REGISTERS::REG_L: {
            value = READ_R_REG(r_HL);
            break;
        }
        case ECPU_8080_REGISTERS::REG_M: {
            auto& ram = RAM::instance();
            value = ram.read(r_HL);
            break;
        }
        default: {
            throw -1;
        }
    }
    switch (dest) {
        case ECPU_8080_REGISTERS::REG_A: {
            r_A = value;
            break;
        }
        case ECPU_8080_REGISTERS::REG_B: {
            WRITE_L_REG(r_BC, value);
            break;
        }
        case ECPU_8080_REGISTERS::REG_C: {
            WRITE_R_REG(r_BC, value);
            break;
        }
        case ECPU_8080_REGISTERS::REG_D: {
            WRITE_L_REG(r_DE, value);
            break;
        }
        case ECPU_8080_REGISTERS::REG_E: {
            WRITE_R_REG(r_DE, value);
            break;
        }
        case ECPU_8080_REGISTERS::REG_H: {
            WRITE_L_REG(r_HL, value);
            break;
        }
        case ECPU_8080_REGISTERS::REG_L: {
            WRITE_R_REG(r_HL, value);
            break;
        }
        case ECPU_8080_REGISTERS::REG_M: {
            auto& ram = RAM::instance();
            ram.write(r_HL, value);
            break;
        }
        default: {
            throw -1;
        }
    }
}

int CPU_8080::process_opcode(uint8_t opcode) {
    return i8080::op_info[opcode].tick_required;
}

bool CPU_8080::tick() {
    uint8_t opcode;

    auto& ram = RAM::instance();
    opcode = ram.read(r_PC);

    return 1;
}
