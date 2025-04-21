/* Hi, stranger!
 * If you want to understand how this shit works,
 * please, check this guide http://dunfield.classiccmp.org/r/8080.txt
 */
#include <algorithm>
#include <cpu8080.hpp>
#include <cstdint>
#include <memory.hpp>
#include <opcodes8080.hpp>

#include "common.hpp"

// constants
#define OP_MOV 0b01000000
#define OP_MVI 0b00000110
#define OP_LXI 0b00000001
#define OP_LDA 0b00111010
#define OP_STA 0b00110010
#define OP_LHDL 0b00101010
#define OP_SHDL 0b00100010
#define OP_LDAX 0b00001010
#define OP_STAX 0b00000010

// macrosses
#define IS_OPCODE(x, opcode) (x & opcode) == opcode
#define SET_FLAG(x, flag) x = x | F
#define HAS_FLAG(x, flag) (x & f > 0)
#define WRITE_L_REG(reg, val) reg |= (val << 8)
#define WRITE_R_REG(reg, val) reg |= val
#define READ_L_REG(reg) (reg & 0xFF00) >> 8
#define READ_R_REG(reg) reg & 0xFF
#define MOV_GET_DEST(opcode) (opcode & 0b00111000) >> 3
#define MOV_GET_SOURCE(opcode) opcode & 0b00000111
#define MVI_GET_DEST(opcode) (opcode & 0b00111000) >> 3
#define LXI_GET_DEST(opcode) (opcode & 0b00110000) >> 4
#define LDAX_GET_SRC(opcode) (opcode & 00110000) >> 4
#define STAX_GET_DST(opcode) (opcode & 00110000) >> 4

uint16_t CPU_8080::get_program_counter() const { return r_PC; }

CPU_8080& CPU_8080::instance() {
    static CPU_8080 cpu;
    return cpu;
}

int CPU_8080::process_opcode(uint8_t opcode) {
    auto& ram = RAM::instance();

    if (IS_OPCODE(opcode, OP_MOV)) {
        CPU_8080::mov(static_cast<ECPU_8080_REGISTERS>(MOV_GET_DEST(opcode)),
                      static_cast<ECPU_8080_REGISTERS>(MOV_GET_SOURCE(opcode)));
    } else if (IS_OPCODE(opcode, OP_MVI)) {
        uint8_t value = ram.read(++CPU_8080::r_PC);
        CPU_8080::mvi(static_cast<ECPU_8080_REGISTERS>(MVI_GET_DEST(opcode)),
                      value);
    } else if (IS_OPCODE(opcode, OP_LXI)) {
        byte_pair_t reg_pair;
        reg_pair.LBYTE = ram.read(++r_PC);
        reg_pair.HBYTE = ram.read(++r_PC);
        CPU_8080::lxi(static_cast<ECPU_8080_REGISTER_PAIRS>(LXI_GET_DEST(opcode)),
                      reg_pair.DBYTE);
    } else if (IS_OPCODE(opcode, OP_LDA)) {
        byte_pair_t address;
        address.LBYTE = ram.read(++r_PC);
        address.HBYTE = ram.read(++r_PC);
        CPU_8080::lda(address.DBYTE);
    } else if (IS_OPCODE(opcode, OP_STA)) {
        byte_pair_t address;
        address.LBYTE = ram.read(++r_PC);
        address.HBYTE = ram.read(++r_PC);
        CPU_8080::sta(address.DBYTE);
    } else if (IS_OPCODE(opcode, OP_LHDL)) {
        byte_pair_t address;
        address.LBYTE = ram.read(++r_PC);
        address.HBYTE = ram.read(++r_PC);
        CPU_8080::lhdl(address.DBYTE);
    } else if (IS_OPCODE(opcode, OP_SHDL)) {
        byte_pair_t address;
        address.LBYTE = ram.read(++r_PC);
        address.HBYTE = ram.read(++r_PC);
        CPU_8080::shdl(address.DBYTE);
    } else if (IS_OPCODE(opcode, OP_LDAX)) {
        CPU_8080::ldax(static_cast<ECPU_8080_REGISTER_PAIRS>(LDAX_GET_SRC(opcode)));
    } else if (IS_OPCODE(opcode, OP_STAX)) {
        CPU_8080::ldax(static_cast<ECPU_8080_REGISTER_PAIRS>(STAX_GET_DST(opcode)));
    }

    ++r_PC;
    return i8080::op_info[opcode].tick_required;
}

bool CPU_8080::tick() {
    uint8_t opcode;
    static uint8_t ticks = 1;
    auto& ram = RAM::instance();
    opcode = ram.read(r_PC);

    try {
        if (ticks) {
            ticks--;
            return 1;
        }
        ticks = process_opcode(opcode);
    } catch (int ex) {
        return 0;
    }
    return 1;
}

// instruction zone
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

void CPU_8080::mvi(ECPU_8080_REGISTERS dest, uint8_t value) {
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

void CPU_8080::lxi(ECPU_8080_REGISTER_PAIRS dest, uint16_t value) {
    switch (dest) {
        case ECPU_8080_REGISTER_PAIRS::REG_BC: {
            r_BC = value;
            break;
        }
        case ECPU_8080_REGISTER_PAIRS::REG_DE: {
            r_DE = value;
            break;
        }
        case ECPU_8080_REGISTER_PAIRS::REG_HL: {
            r_HL = value;
            break;
        }
        case ECPU_8080_REGISTER_PAIRS::REG_SP: {
            r_SP = value;
            break;
        }
        default: {
            throw -1;
            break;
        }
    }
}

void CPU_8080::lda(uint16_t address) {
    auto& ram = RAM::instance();
    r_A = ram.read(address);
}

void CPU_8080::sta(uint16_t address) {
    auto& ram = RAM::instance();
    ram.write(address, r_A);
}

void CPU_8080::lhdl(uint16_t address) {
    auto& ram = RAM::instance();
    byte_pair_t hl;
    hl.LBYTE = ram.read(address);
    hl.HBYTE = ram.read(address + 1);
    r_HL = hl.DBYTE;
}

void CPU_8080::shdl(uint16_t address) {
    byte_pair_t hl;
    auto& ram = RAM::instance();
    hl.DBYTE = r_HL;
    ram.write(address, hl.LBYTE);
    ram.write(address + 1, hl.HBYTE);
}

void CPU_8080::ldax(ECPU_8080_REGISTER_PAIRS src) {
    auto& ram = RAM::instance();
    uint16_t address;
    switch (src) {
        case ECPU_8080_REGISTER_PAIRS::REG_BC: {
            address = r_BC;
            break;
        }
        case ECPU_8080_REGISTER_PAIRS::REG_DE: {
            address = r_DE;
            break;
        }
        default: {
            DEBUG_ERROR("Only BC and DE register pairs allowed");
            throw -1;
        }
    }
    r_A = ram.read(address);
}

void CPU_8080::stax(ECPU_8080_REGISTER_PAIRS dst) {
    auto& ram = RAM::instance();
    uint16_t address;
    switch (dst) {
        case ECPU_8080_REGISTER_PAIRS::REG_BC: {
            address = r_BC;
            break;
        }
        case ECPU_8080_REGISTER_PAIRS::REG_DE: {
            address = r_DE;
            break;
        }
        default: {
            DEBUG_ERROR("Only BC and DE register pairs allowed");
            throw -1;
        }
    }
    ram.write(address, r_A);
}

void CPU_8080::xchg(void) {
    std::swap(r_DE, r_HL);
}
// end of instruction zone
