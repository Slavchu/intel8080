#pragma once

#include <stdint.h>

#define NUM_INSTRUCTIONS 256

namespace i8080 {
struct opcode_info_t {
    uint8_t arg = 0;
    uint8_t tick_required = 0;
    uint8_t tick_required_alt = 0; // some instruction can take different amount
                                   // of cpu cycles depended on conditions
};
const opcode_info_t op_info[NUM_INSTRUCTIONS] = {
    {0, 4},  // 0x00 NOP
    {2, 10}, // 0x01 LXI B, d16
    {0, 7},  // 0x02 STAX B
    {0, 5},  // 0x03 INX B
    {0, 5},  // 0x04 INR B
    {0, 5},  // 0x05 DCR B
    {1, 7},  // 0x06 MVI B, d8
    {0, 4},  // 0x07 RLC
    {0, 4},  // 0x08 NOP
    {0, 10}, // 0x09 DAD B
    {0, 7},  // 0x0A LDAX B
    {0, 5},  // 0x0B DCX B
    {0, 5},  // 0x0C INR C
    {0, 5},  // 0x0D DCR C
    {1, 7},  // 0x0E MVI C, d8
    {0, 4},  // 0x0F RRC

    {0, 4},  // 0x10 NOP
    {2, 10}, // 0x11 LXI D, d16
    {0, 7},  // 0x12 STAX D
    {0, 5},  // 0x13 INX D
    {0, 5},  // 0x14 INR D
    {0, 5},  // 0x15 DCR D
    {1, 7},  // 0x16 MVI D, d8
    {0, 4},  // 0x17 RAL
    {0, 4},  // 0x18 NOP
    {0, 10}, // 0x19 DAD D
    {0, 7},  // 0x1A LDAX D
    {0, 5},  // 0x1B DCX D
    {0, 5},  // 0x1C INR E
    {0, 5},  // 0x1D DCR E
    {1, 7},  // 0x1E MVI E, d8
    {0, 4},  // 0x1F RAR

    {0, 4},  // 0x20 NOP
    {2, 10}, // 0x21 LXI H, d16
    {2, 16}, // 0x22 SHLD adr
    {0, 5},  // 0x23 INX H
    {0, 5},  // 0x24 INR H
    {0, 5},  // 0x25 DCR H
    {1, 7},  // 0x26 MVI H, d8
    {0, 4},  // 0x27 DAA
    {0, 4},  // 0x28 NOP
    {0, 10}, // 0x29 DAD H
    {2, 16}, // 0x2A LHLD adr
    {0, 5},  // 0x2B DCX H
    {0, 5},  // 0x2C INR L
    {0, 5},  // 0x2D DCR L
    {1, 7},  // 0x2E MVI L, d8
    {0, 4},  // 0x2F CMA

    {0, 4},  // 0x30 NOP
    {2, 10}, // 0x31 LXI SP, d16
    {2, 13}, // 0x32 STA adr
    {0, 5},  // 0x33 INX SP
    {0, 10}, // 0x34 INR M
    {0, 10}, // 0x35 DCR M
    {1, 7},  // 0x36 MVI M, d8
    {0, 4},  // 0x37 STC
    {0, 4},  // 0x38 NOP
    {0, 10}, // 0x39 DAD SP
    {0, 13}, // 0x3A LDA adr
    {0, 5},  // 0x3B DCX SP
    {0, 5},  // 0x3C INR A
    {0, 5},  // 0x3D DCR A
    {1, 7},  // 0x3E MVI A, d8
    {0, 4},  // 0x3F CMC

    {0, 5}, // 0x40 MOV B, B
    {0, 5}, // 0x41 MOV B, C
    {0, 5}, // 0x42 MOV B, D
    {0, 5}, // 0x43 MOV B, E
    {0, 5}, // 0x44 MOV B, H
    {0, 5}, // 0x45 MOV B, L
    {0, 5}, // 0x46 MOV B, M
    {0, 5}, // 0x47 MOV B, A
    {0, 5}, // 0x48 MOV C, B
    {0, 5}, // 0x49 MOV C, C
    {0, 5}, // 0x4A MOV C, D
    {0, 5}, // 0x4B MOV C, E
    {0, 5}, // 0x4C MOV C, H
    {0, 5}, // 0x4D MOV C, L
    {0, 7}, // 0x4E MOV C, M
    {0, 5}, // 0x4F MOV C, A

    {0, 5}, // 0x50 MOV D, B
    {0, 5}, // 0x51 MOV D, C
    {0, 5}, // 0x52 MOV D, D
    {0, 5}, // 0x53 MOV D, E
    {0, 5}, // 0x54 MOV D, H
    {0, 5}, // 0x55 MOV D, L
    {0, 5}, // 0x56 MOV D, M
    {0, 5}, // 0x57 MOV D, A
    {0, 5}, // 0x58 MOV E, B
    {0, 5}, // 0x59 MOV E, C
    {0, 5}, // 0x5A MOV E, D
    {0, 5}, // 0x5B MOV E, E
    {0, 5}, // 0x5C MOV E, H
    {0, 5}, // 0x5D MOV E, L
    {0, 7}, // 0x5E MOV E, M
    {0, 5}, // 0x5F MOV E, A

    {0, 5}, // 0x60 MOV H, B
    {0, 5}, // 0x61 MOV H, C
    {0, 5}, // 0x62 MOV H, D
    {0, 5}, // 0x63 MOV H, E
    {0, 5}, // 0x64 MOV H, H
    {0, 5}, // 0x65 MOV H, L
    {0, 7}, // 0x66 MOV H, M
    {0, 5}, // 0x67 MOV H, A
    {0, 5}, // 0x68 MOV L, B
    {0, 5}, // 0x69 MOV L, C
    {0, 5}, // 0x6A MOV L, D
    {0, 5}, // 0x6B MOV L, E
    {0, 5}, // 0x6C MOV L, H
    {0, 5}, // 0x6D MOV L, L
    {0, 7}, // 0x6E MOV L, M
    {0, 5}, // 0x6F MOV L, A

    {0, 7}, // 0x70 MOV M, B
    {0, 7}, // 0x71 MOV M, C
    {0, 7}, // 0x72 MOV M, D
    {0, 7}, // 0x73 MOV M, E
    {0, 7}, // 0x74 MOV M, H
    {0, 7}, // 0x75 MOV M, L
    {0, 7}, // 0x76 HLT
    {0, 7}, // 0x77 MOV M, A
    {0, 5}, // 0x78 MOV A, B
    {0, 5}, // 0x79 MOV A, C
    {0, 5}, // 0x7A MOV A, D
    {0, 5}, // 0x7B MOV A, E
    {0, 5}, // 0x7C MOV A, H
    {0, 5}, // 0x7D MOV A, L
    {0, 7}, // 0x7E MOV A, M
    {0, 5}, // 0x7F MOV A, A

    {0, 4}, // 0x80 ADD B
    {0, 4}, // 0x81 ADD C
    {0, 4}, // 0x82 ADD D
    {0, 4}, // 0x83 ADD E
    {0, 4}, // 0x84 ADD H
    {0, 4}, // 0x85 ADD L
    {0, 4}, // 0x86 ADD M
    {0, 4}, // 0x87 ADD A
    {0, 4}, // 0x88 ADC B
    {0, 4}, // 0x89 ADC C
    {0, 4}, // 0x8A ADC D
    {0, 4}, // 0x8B ADC E
    {0, 4}, // 0x8C ADC H
    {0, 4}, // 0x8D ADC L
    {0, 7}, // 0x8E ADC M
    {0, 4}, // 0x8F ADC A

    {0, 4}, // 0x90 SUB B
    {0, 4}, // 0x91 SUB C
    {0, 4}, // 0x92 SUB D
    {0, 4}, // 0x93 SUB E
    {0, 4}, // 0x94 SUB H
    {0, 4}, // 0x95 SUB L
    {0, 4}, // 0x96 SUB M
    {0, 4}, // 0x97 SUB A
    {0, 4}, // 0x98 SBB B
    {0, 4}, // 0x99 SBB C
    {0, 4}, // 0x9A SBB D
    {0, 4}, // 0x9B SBB E
    {0, 4}, // 0x9C SBB H
    {0, 4}, // 0x9D SBB L
    {0, 7}, // 0x9E SBB M
    {0, 4}, // 0x9F SBB A

    {0, 4}, // 0xA0 ANA B
    {0, 4}, // 0xA1 ANA C
    {0, 4}, // 0xA2 ANA D
    {0, 4}, // 0xA3 ANA E
    {0, 4}, // 0xA4 ANA H
    {0, 4}, // 0xA5 ANA L
    {0, 7}, // 0xA6 ANA M
    {0, 4}, // 0xA7 ANA A
    {0, 4}, // 0xA8 XRA B
    {0, 4}, // 0xA9 XRA C
    {0, 4}, // 0xAA XRA D
    {0, 4}, // 0xAB XRA E
    {0, 4}, // 0xAC XRA H
    {0, 4}, // 0xAD XRA L
    {0, 7}, // 0xAE XRA M
    {0, 4}, // 0xAF XRA A

    {0, 4}, // 0xB0 ORA B
    {0, 4}, // 0xB1 ORA C
    {0, 4}, // 0xB2 ORA D
    {0, 4}, // 0xB3 ORA E
    {0, 4}, // 0xB4 ORA H
    {0, 4}, // 0xB5 ORA L
    {0, 7}, // 0xB6 ORA M
    {0, 4}, // 0xB7 ORA A
    {0, 4}, // 0xB8 CMP B
    {0, 4}, // 0xB9 CMP C
    {0, 4}, // 0xBA CMP D
    {0, 4}, // 0xBB CMP E
    {0, 4}, // 0xBC CMP H
    {0, 4}, // 0xBD CMP L
    {0, 7}, // 0xBE CMP M
    {0, 4}, // 0xBF CMP A

    {0, 11, 5},  // 0xC0 RNZ
    {0, 10},     // 0xC1 POP B
    {2, 10},     // 0xC2 JNZ adr
    {2, 10},     // 0xC3 JMP adr
    {2, 17, 11}, // 0xC4 CNZ adr
    {0, 11},     // 0xC5 PUSH B
    {1, 7},      // 0xC6 ADI d8
    {0, 4},      // 0xC7 RST 0
    {0, 11, 5},  // 0xC8 RZ
    {0, 10},     // 0xC9 RET
    {2, 10},     // 0xCA JZ adr
    {2, 10},     // 0xCB JAM adr
    {2, 17, 11}, // 0xCC CZ adr
    {2, 17},     // 0xCD CALL adr
    {1, 7},      // 0xCE ACI d8
    {0, 11},     // 0xCF RST 1

    {0, 11, 5},  // 0xD0 RNC
    {0, 10},     // 0xD1 POP D
    {2, 10},     // 0xD2 JNC adr
    {2, 10},     // 0xD3 OUT d8
    {2, 17, 11}, // 0xD4 CNZ adr
    {0, 11},     // 0xD5 PUSH D
    {1, 7},      // 0xD6 SUI d8
    {0, 11},     // 0xD7 RST 2
    {0, 11, 5},  // 0xD8 RC
    {0, 10},     // 0xD9 RET
    {2, 10},     // 0xDA JZ adr
    {1, 10},     // 0xDB IN d8
    {2, 17, 11}, // 0xDC CC adr
    {2, 17},     // 0xDD CALL adr
    {1, 7},      // 0xDE SBI d8
    {0, 11},     // 0xDF RST 3

    {0, 11, 5},  // 0xE0 RPO
    {0, 10},     // 0xE1 POP H
    {2, 10},     // 0xE2 JPO adr
    {0, 18},     // 0xE3 XTHL
    {2, 17, 11}, // 0xE4 CPO adr
    {0, 11},     // 0xE5 PUSH H
    {1, 7},      // 0xE6 ANI d8
    {0, 11},     // 0xE7 RST 4
    {0, 4},      // 0xE8 RPE
    {0, 5},      // 0xE9 PCHL
    {2, 10},     // 0xEA JPE adr
    {0, 5},      // 0xEB XCHG d8
    {2, 17, 11}, // 0xEC CPE adr
    {2, 17},     // 0xED CALL adr
    {1, 7},      // 0xEE CPI d8
    {0, 11},     // 0xEF RST 5

    {0, 11, 5},  // 0xF0 RP
    {0, 10},     // 0xF1 POP PSW
    {2, 10},     // 0xF2 JP adr
    {0, 4},      // 0xF3 DI
    {2, 17, 11}, // 0xF4 CP adr
    {0, 11},     // 0xF5 PUSH PSW
    {1, 7},      // 0xF6 ORI d8
    {0, 11},     // 0xF7 RST 6
    {0, 4},      // 0xF8 RM
    {0, 5},      // 0xF9 SPHL
    {2, 10},     // 0xFA JM adr
    {0, 4},      // 0xFB EI
    {2, 17, 11}, // 0xFC CM adr
    {2, 17},     // 0xFD CALL adr
    {1, 7},      // 0xFE CPI d8
    {0, 11},     // 0xFF RST 7
};

}; // namespace i8080
