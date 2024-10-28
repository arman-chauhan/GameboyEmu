#include "instruction.h"
#include "cpu.h"
#include "memory.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define IM_U8 8
#define IM_I8 9
#define IM_U16 16

//==================================================================================================================
//
// LOAD FAMILY
//
//==================================================================================================================

//------------------------------------------------------------------------------
//      Load an immediate 8-bit value into a register
//------------------------------------------------------------------------------
void LD_R8_u8(uint8_t* reg) { *reg = IM_U8; }

/*      Load immediate 8-bit values into registers      */
void LD_A_8IM(regs_t* regs) { LD_R8_u8(&regs->A); } // 0x3E
void LD_B_8IM(regs_t* regs) { LD_R8_u8(&regs->B); } // 0x06
void LD_C_8IM(regs_t* regs) { LD_R8_u8(&regs->C); } // 0x0E
void LD_D_8IM(regs_t* regs) { LD_R8_u8(&regs->D); } // 0x16
void LD_E_8IM(regs_t* regs) { LD_R8_u8(&regs->E); } // 0x1E
void LD_H_8IM(regs_t* regs) { LD_R8_u8(&regs->H); } // 0x26
void LD_L_8IM(regs_t* regs) { LD_R8_u8(&regs->L); } // 0x2E

//------------------------------------------------------------------------------
//      Load data between registers (8-bit)
//------------------------------------------------------------------------------
void LD_R8_R8(uint8_t* a, const uint8_t b) { *a = b; }

/*      Load from other registers to regsiter A     */
void LD_A_A(regs_t* regs) { LD_R8_R8(&regs->A, regs->A); } // 0x7F
void LD_A_B(regs_t* regs) { LD_R8_R8(&regs->A, regs->B); } // 0x78
void LD_A_C(regs_t* regs) { LD_R8_R8(&regs->A, regs->C); } // 0x79
void LD_A_D(regs_t* regs) { LD_R8_R8(&regs->A, regs->D); } // 0x7A
void LD_A_E(regs_t* regs) { LD_R8_R8(&regs->A, regs->E); } // 0x7B
void LD_A_H(regs_t* regs) { LD_R8_R8(&regs->A, regs->H); } // 0x7C
void LD_A_L(regs_t* regs) { LD_R8_R8(&regs->A, regs->L); } // 0x7D

/*      Load from other registers to regsiter B     */
void LD_B_A(regs_t* regs) { LD_R8_R8(&regs->B, regs->A); } // 0x47
void LD_B_B(regs_t* regs) { LD_R8_R8(&regs->B, regs->B); } // 0x40
void LD_B_C(regs_t* regs) { LD_R8_R8(&regs->B, regs->C); } // 0x41
void LD_B_D(regs_t* regs) { LD_R8_R8(&regs->B, regs->D); } // 0x42
void LD_B_E(regs_t* regs) { LD_R8_R8(&regs->B, regs->E); } // 0x43
void LD_B_H(regs_t* regs) { LD_R8_R8(&regs->B, regs->H); } // 0x44
void LD_B_L(regs_t* regs) { LD_R8_R8(&regs->B, regs->L); } // 0x45

/*      Load from other registers to regsiter C     */
void LD_C_A(regs_t* regs) { LD_R8_R8(&regs->C, regs->A); } // 0x4F
void LD_C_B(regs_t* regs) { LD_R8_R8(&regs->C, regs->B); } // 0x48
void LD_C_C(regs_t* regs) { LD_R8_R8(&regs->C, regs->C); } // 0x49
void LD_C_D(regs_t* regs) { LD_R8_R8(&regs->C, regs->D); } // 0x4A
void LD_C_E(regs_t* regs) { LD_R8_R8(&regs->C, regs->E); } // 0x4B
void LD_C_H(regs_t* regs) { LD_R8_R8(&regs->C, regs->H); } // 0x4C
void LD_C_L(regs_t* regs) { LD_R8_R8(&regs->C, regs->L); } // 0x4D

/*      Load from other registers to regsiter D     */
void LD_D_A(regs_t* regs) { LD_R8_R8(&regs->D, regs->A); } // 0x57
void LD_D_B(regs_t* regs) { LD_R8_R8(&regs->D, regs->B); } // 0x50
void LD_D_C(regs_t* regs) { LD_R8_R8(&regs->D, regs->C); } // 0x51
void LD_D_D(regs_t* regs) { LD_R8_R8(&regs->D, regs->D); } // 0x52
void LD_D_E(regs_t* regs) { LD_R8_R8(&regs->D, regs->E); } // 0x53
void LD_D_H(regs_t* regs) { LD_R8_R8(&regs->D, regs->H); } // 0x54
void LD_D_L(regs_t* regs) { LD_R8_R8(&regs->D, regs->L); } // 0x55

/*      Load from other registers to regsiter E      */
void LD_E_A(regs_t* regs) { LD_R8_R8(&regs->E, regs->A); } // 0x5F
void LD_E_B(regs_t* regs) { LD_R8_R8(&regs->E, regs->B); } // 0x58
void LD_E_C(regs_t* regs) { LD_R8_R8(&regs->E, regs->C); } // 0x59
void LD_E_D(regs_t* regs) { LD_R8_R8(&regs->E, regs->D); } // 0x5A
void LD_E_E(regs_t* regs) { LD_R8_R8(&regs->E, regs->E); } // 0x5B
void LD_E_H(regs_t* regs) { LD_R8_R8(&regs->E, regs->H); } // 0x5C
void LD_E_L(regs_t* regs) { LD_R8_R8(&regs->E, regs->L); } // 0x5D

/*      Load from other registers to regsiter H      */
void LD_H_A(regs_t* regs) { LD_R8_R8(&regs->H, regs->A); } // 0x67
void LD_H_B(regs_t* regs) { LD_R8_R8(&regs->H, regs->B); } // 0x60
void LD_H_C(regs_t* regs) { LD_R8_R8(&regs->H, regs->C); } // 0x61
void LD_H_D(regs_t* regs) { LD_R8_R8(&regs->H, regs->D); } // 0x62
void LD_H_E(regs_t* regs) { LD_R8_R8(&regs->H, regs->E); } // 0x63
void LD_H_H(regs_t* regs) { LD_R8_R8(&regs->H, regs->H); } // 0x64
void LD_H_L(regs_t* regs) { LD_R8_R8(&regs->H, regs->L); } // 0x65

/*      Load from other registers to regsiter L      */
void LD_L_A(regs_t* regs) { LD_R8_R8(&regs->L, regs->A); } // 0x6F
void LD_L_B(regs_t* regs) { LD_R8_R8(&regs->L, regs->B); } // 0x68
void LD_L_C(regs_t* regs) { LD_R8_R8(&regs->L, regs->C); } // 0x69
void LD_L_D(regs_t* regs) { LD_R8_R8(&regs->L, regs->D); } // 0x6A
void LD_L_E(regs_t* regs) { LD_R8_R8(&regs->L, regs->E); } // 0x6B
void LD_L_H(regs_t* regs) { LD_R8_R8(&regs->L, regs->H); } // 0x6C
void LD_L_L(regs_t* regs) { LD_R8_R8(&regs->L, regs->L); } // 0x6D

/*      Load value in register HL to SP      */
void LD_SP_HL(regs_t* regs) { regs->SP = regs->HL; } // Fx09

//------------------------------------------------------------------------------
//      Load an immediate 16-bit value into a register
//------------------------------------------------------------------------------
void LD_R16_u16(uint16_t* a) { *a = IM_U16; }

/*      Load immediate 16-bit values into registers     */
void LD_BC_16IM(regs_t* regs) { LD_R16_u16(&regs->BC); } // 0x01
void LD_DE_16IM(regs_t* regs) { LD_R16_u16(&regs->DE); } // 1x01
void LD_HL_16IM(regs_t* regs) { LD_R16_u16(&regs->HL); } // 2x01
void LD_SP_16IM(regs_t* regs) { LD_R16_u16(&regs->SP); } // 3x01

//------------------------------------------------------------------------------
//      Load 8 bit data from memory address into a register
//------------------------------------------------------------------------------
void LD_R8_mu8(const uint16_t addr, uint8_t* reg) {
    const uint16_t value = read_u8(addr);
    *reg = value;
}

/*      Load data from memory address pointed by HL into registers      */
void LD_B_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->B); } // 0x46
void LD_C_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->C); } // 0x4E
void LD_D_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->D); } // 0x56
void LD_E_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->E); } // 0x5E
void LD_H_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->H); } // 0x66
void LD_L_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->L); } // 0x6E

/*      Load data from memory into register A       */
void LD_A_mHL(regs_t* regs) { LD_R8_mu8(regs->HL, &regs->A); } // 0x7E
void LD_A_mBC(regs_t* regs) { LD_R8_mu8(regs->BC, &regs->A); } // 0x0A
void LD_A_mDE(regs_t* regs) { LD_R8_mu8(regs->DE, &regs->A); } // 1x0A
void LD_A_m16(regs_t* regs) { LD_R8_mu8(IM_U16, &regs->A); }   // Fx0A

/*      NOTE: maybe you mask the result of increment and decrement       */
void LD_A_HLD(regs_t* regs) {
    LD_R8_mu8(regs->HL, &regs->A);
    regs->HL++;
} // 3x0A
void LD_A_HLI(regs_t* regs) {
    LD_R8_mu8(regs->HL, &regs->A);
    regs->HL--;
} // 2x0A

//------------------------------------------------------------------------------
//       Load 8 bit data from the register into memory
//------------------------------------------------------------------------------
void LD_m_u8(const uint16_t addr, const uint8_t value) { write_u8(addr, value); }

/*      Store data from a register into memory address (pointed by HL)      */
void LD_mHL_A(regs_t* regs) { LD_m_u8(regs->HL, regs->A); } // 0x77
void LD_mHL_B(regs_t* regs) { LD_m_u8(regs->HL, regs->B); } // 0x70
void LD_mHL_C(regs_t* regs) { LD_m_u8(regs->HL, regs->C); } // 0x71
void LD_mHL_D(regs_t* regs) { LD_m_u8(regs->HL, regs->D); } // 0x72
void LD_mHL_E(regs_t* regs) { LD_m_u8(regs->HL, regs->E); } // 0x73
void LD_mHL_H(regs_t* regs) { LD_m_u8(regs->HL, regs->H); } // 0x74
void LD_mHL_L(regs_t* regs) { LD_m_u8(regs->HL, regs->L); } // 0x75
void LD_mHL_8IM(regs_t* regs) { LD_m_u8(regs->HL, IM_U8); } // 3x06

void LD_mBC_A(regs_t* regs) { LD_m_u8(regs->BC, regs->A); } // 0x02
void LD_mDE_A(regs_t* regs) { LD_m_u8(regs->DE, regs->A); } // 1x02

void LD_m16_A(regs_t* regs) { LD_m_u8(IM_U16, regs->A); } // Ex0A

// TODO correct
void LD_m16_SP(regs_t* regs) { LD_m_u8(IM_U16, regs->SP); } // 0x08

/*      NOTE maybe you mask the result of increment and decrement       */
void LD_HLI_A(regs_t* regs) {
    LD_m_u8(regs->HL, regs->A);
    regs->HL++;
} // 2x02
void LD_HLD_A(regs_t* regs) {
    LD_m_u8(regs->HL, regs->A);
    regs->HL--;
} // 3x02

void LD_HL_SP8IM(regs_t* regs) { regs->HL = regs->SP + IM_I8; } // Fx08

void LD_FF00_C_A(regs_t* regs) { write_io(regs->C, regs->A); } // Ex02
void LD_A_FFOO_C(regs_t* regs) { regs->A = read_io(regs->C); } // Fx02
void LD_A_FF00_8IM(regs_t* regs) { regs->A = read_io(IM_U8); } // Fx00
void LD_FF00_8IM_A(regs_t* regs) { write_io(IM_U8, regs->A); } // Ex00

//==================================================================================================================
//
// ARTHEMETIC FAMILY
//
//==================================================================================================================

void set_flag(uint8_t* flag_reg, const uint8_t flag, const uint8_t value) {
    assert(value == 1 | value == 0 && flag <= 7 && flag >= 4);
    const uint8_t mask = flag;
    switch (value) {
    case 1: *flag_reg |= mask; break;
    case 0: *flag_reg &= ~mask; break;
    default: exit(69);
    }
}

// NOTE: the result of addition is masked, might be wrong
void ADD_R8(uint8_t* a_reg, uint8_t n, uint8_t* flag_reg) {
    const uint8_t a_value = *a_reg;
    const uint16_t res = a_value + n;
    *a_reg = res;

    const uint8_t bit3overflow = (a_value & 0x0f) + (n & 0x0f) > 0x0f;
    const uint8_t bit7overflow = res > 0xff;
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_Z, (res & 0xff) == 0 ? 1 : 0);
    set_flag(flag_reg, FLAG_H, bit3overflow ? 1 : 0);
    set_flag(flag_reg, FLAG_C, bit7overflow ? 1 : 0);
}

void ADD_A_A(regs_t* regs) { ADD_R8(&regs->A, regs->A, &regs->F); }             // 8x07
void ADD_A_B(regs_t* regs) { ADD_R8(&regs->A, regs->B, &regs->F); }             // 8x00
void ADD_A_C(regs_t* regs) { ADD_R8(&regs->A, regs->C, &regs->F); }             // 8x01
void ADD_A_D(regs_t* regs) { ADD_R8(&regs->A, regs->D, &regs->F); }             // 8x02
void ADD_A_E(regs_t* regs) { ADD_R8(&regs->A, regs->E, &regs->F); }             // 8x03
void ADD_A_H(regs_t* regs) { ADD_R8(&regs->A, regs->H, &regs->F); }             // 8x04
void ADD_A_L(regs_t* regs) { ADD_R8(&regs->A, regs->L, &regs->F); }             // 8x05
void ADD_A_8IM(regs_t* regs) { ADD_R8(&regs->A, IM_U8, &regs->F); }             // Cx06
void ADD_A_mHL(regs_t* regs) { ADD_R8(&regs->A, read_u8(regs->HL), &regs->F); } // 8x06

// NOTE: the result of addition is masked, might be wrong
void ADD_R16(uint16_t* hl_reg, uint16_t nn, uint8_t* flag_reg) {
    const uint16_t hl_value = *hl_reg;
    const uint32_t res = hl_value + nn;
    *hl_reg = res;

    const uint8_t bit11overflow = (hl_value & 0x0fff) + (nn & 0x0fff) > 0x0fff;
    const uint8_t bit15overflow = res > 0xffff;
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, (bit11overflow ? 1 : 0));
    set_flag(flag_reg, FLAG_C, (bit15overflow ? 1 : 0));
}

void ADD_HL_BC(regs_t* regs) { ADD_R16(&regs->HL, regs->BC, &regs->F); } // 0x09
void ADD_HL_DE(regs_t* regs) { ADD_R16(&regs->HL, regs->DE, &regs->F); } // 1x09
void ADD_HL_HL(regs_t* regs) { ADD_R16(&regs->HL, regs->HL, &regs->F); } // 2x09
void ADD_HL_SP(regs_t* regs) { ADD_R16(&regs->HL, regs->SP, &regs->F); } // 3x08

// NOTE: the result of addition is masked, might be wrong
void ADD_SP_e8(regs_t* regs) {
    const uint16_t SP = regs->SP;
    const uint32_t res = (regs->SP + IM_I8);
    regs->SP = res;

    const uint8_t bit3overflow = (SP & 0x000f) + (IM_I8 & 0x0f) > 0x0f;
    const uint8_t bit7overflow = (SP & 0x00ff) + (IM_I8 & 0xff) > 0xff;
    set_flag(&regs->F, FLAG_N, 0);
    set_flag(&regs->F, FLAG_Z, 0);
    set_flag(&regs->F, FLAG_H, (bit3overflow ? 1 : 0));
    set_flag(&regs->F, FLAG_C, (bit7overflow ? 1 : 0));
} // Ex08

void ADC_R8(uint8_t* a_reg, const uint8_t n, uint8_t* flag_reg) {
    const uint8_t a_value = *a_reg;
    const uint8_t carry = (*flag_reg & FLAG_C);
    const uint16_t res = a_value + n + carry;
    *a_reg = res;

    const uint8_t bit3overflow = (a_value & 0x0f) + (n & 0x0f + carry) > 0xff;
    const uint8_t bit7overflow = res > 0xff;
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_Z, (res & 0xff) == 0 ? 1 : 0);
    set_flag(flag_reg, FLAG_H, bit3overflow);
    set_flag(flag_reg, FLAG_C, bit7overflow);
}

void ADC_A_A(regs_t* regs) { ADC_R8(&regs->A, regs->A, &regs->F); } // 8x0F
void ADC_A_B(regs_t* regs) { ADC_R8(&regs->A, regs->B, &regs->F); } // 8x08
void ADC_A_C(regs_t* regs) { ADC_R8(&regs->A, regs->C, &regs->F); } // 8x09
void ADC_A_D(regs_t* regs) { ADC_R8(&regs->A, regs->D, &regs->F); } // 8x0A
void ADC_A_E(regs_t* regs) { ADC_R8(&regs->A, regs->E, &regs->F); } // 8x0B
void ADC_A_H(regs_t* regs) { ADC_R8(&regs->A, regs->H, &regs->F); } // 8x0C
void ADC_A_L(regs_t* regs) { ADC_R8(&regs->A, regs->L, &regs->F); } // 8x0D

void ADC_A_mHL(regs_t* regs) { ADC_R8(&regs->A, read_u8(regs->HL), &regs->F); } // 8x0E
void ADC_A_8IM(regs_t* regs) { ADC_R8(&regs->A, IM_U8, &regs->F); }             // Cx0E

void SUB_R8(uint8_t* a_reg, uint8_t n, uint8_t* flag_reg) {
    const uint8_t a_value = *a_reg;
    const uint16_t res = a_value - n;
    *a_reg = res;

    const uint8_t bit4borrow = (a_value & 0x0f) < (n & 0x0f);
    set_flag(flag_reg, FLAG_N, 1);
    set_flag(flag_reg, FLAG_Z, ((res & 0xff) == 0) ? 1 : 0);
    set_flag(flag_reg, FLAG_H, bit4borrow);
    set_flag(flag_reg, FLAG_C, (n > a_value ? 1 : 0));
}

void SUB_A_A(regs_t* regs) { SUB_R8(&regs->A, regs->A, &regs->F); } // 9x07
void SUB_A_B(regs_t* regs) { SUB_R8(&regs->A, regs->B, &regs->F); } // 9x00
void SUB_A_C(regs_t* regs) { SUB_R8(&regs->A, regs->C, &regs->F); } // 9x01
void SUB_A_D(regs_t* regs) { SUB_R8(&regs->A, regs->D, &regs->F); } // 9x02
void SUB_A_E(regs_t* regs) { SUB_R8(&regs->A, regs->E, &regs->F); } // 9x03
void SUB_A_H(regs_t* regs) { SUB_R8(&regs->A, regs->H, &regs->F); } // 9x04
void SUB_A_L(regs_t* regs) { SUB_R8(&regs->A, regs->L, &regs->F); } // 9x05

void SUB_A_mHL(regs_t* regs) { SUB_R8(&regs->A, read_u8(regs->HL), &regs->F); } // 9x06
void SUB_A_8IM(regs_t* regs) { SUB_R8(&regs->A, IM_U8, &regs->F); }             // Dx06

void SBC_R8(uint8_t* a_reg, const uint8_t n, uint8_t* flag_reg) {
    const uint8_t a_value = *a_reg;
    const uint8_t carry = (*flag_reg & FLAG_C);
    const uint16_t res = a_value - n - carry;
    *a_reg = res;

    const uint8_t bit4borrow = (a_value & 0x0f) < (n & 0x0f + carry);
    set_flag(flag_reg, FLAG_N, 1);
    set_flag(flag_reg, FLAG_Z, ((res & 0xff) == 0 ? 1 : 0));
    set_flag(flag_reg, FLAG_H, bit4borrow);
    set_flag(flag_reg, FLAG_C, (n + carry > a_value ? 1 : 0));
}

void SBC_A_A(regs_t* regs) { SBC_R8(&regs->A, regs->A, &regs->F); } // 9x0F
void SBC_A_B(regs_t* regs) { SBC_R8(&regs->A, regs->B, &regs->F); } // 9x08
void SBC_A_C(regs_t* regs) { SBC_R8(&regs->A, regs->C, &regs->F); } // 9x09
void SBC_A_D(regs_t* regs) { SBC_R8(&regs->A, regs->D, &regs->F); } // 9x0A
void SBC_A_E(regs_t* regs) { SBC_R8(&regs->A, regs->E, &regs->F); } // 9x0B
void SBC_A_H(regs_t* regs) { SBC_R8(&regs->A, regs->H, &regs->F); } // 9x0C
void SBC_A_L(regs_t* regs) { SBC_R8(&regs->A, regs->L, &regs->F); } // 9x0D

void SBC_A_mHL(regs_t* regs) { SBC_R8(&regs->A, read_u8(regs->HL), &regs->F); } // 9x0E
void SBC_A_8IM(regs_t* regs) { SBC_R8(&regs->A, IM_U8, &regs->F); }             // Dx0E

void CP_R8(const uint8_t a_value, const uint8_t n, uint8_t* flag_reg) {
    const uint16_t res = a_value - n;

    const uint8_t bit4borrow = (a_value & 0x0f) < (n & 0x0f);
    set_flag(flag_reg, FLAG_N, 1);
    set_flag(flag_reg, FLAG_Z, ((res & 0xff) == 0 ? 1 : 0));
    set_flag(flag_reg, FLAG_H, bit4borrow);
    set_flag(flag_reg, FLAG_C, (n > a_value ? 1 : 0));
}

void CP_A_A(regs_t* regs) { CP_R8(regs->A, regs->A, &regs->F); } // Bx0F
void CP_A_B(regs_t* regs) { CP_R8(regs->A, regs->B, &regs->F); } // Bx08
void CP_A_C(regs_t* regs) { CP_R8(regs->A, regs->C, &regs->F); } // Bx09
void CP_A_D(regs_t* regs) { CP_R8(regs->A, regs->D, &regs->F); } // Bx0A
void CP_A_E(regs_t* regs) { CP_R8(regs->A, regs->E, &regs->F); } // Bx0B
void CP_A_H(regs_t* regs) { CP_R8(regs->A, regs->H, &regs->F); } // Bx0C
void CP_A_L(regs_t* regs) { CP_R8(regs->A, regs->L, &regs->F); } // Bx0D

void CP_A_mHL(regs_t* regs) { SBC_R8(&regs->A, read_u8(regs->HL), &regs->F); } // Bx0E
void CP_A_8IM(regs_t* regs) { SBC_R8(&regs->A, IM_U8, &regs->F); }             // Fx0E

void AND_R8(uint8_t* a_reg, const uint8_t n, uint8_t* flag_reg) {
    const uint8_t res = *a_reg & n;
    *a_reg = res;

    set_flag(flag_reg, FLAG_Z, ((res & 0xff) == 0) ? 1 : 0);
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 1);
    set_flag(flag_reg, FLAG_C, 0);
}

void AND_A_A(regs_t* regs) { AND_R8(&regs->A, regs->A, &regs->F); } // Ax07
void AND_A_B(regs_t* regs) { AND_R8(&regs->A, regs->B, &regs->F); } // Ax00
void AND_A_C(regs_t* regs) { AND_R8(&regs->A, regs->C, &regs->F); } // Ax01
void AND_A_D(regs_t* regs) { AND_R8(&regs->A, regs->D, &regs->F); } // Ax02
void AND_A_E(regs_t* regs) { AND_R8(&regs->A, regs->E, &regs->F); } // Ax03
void AND_A_H(regs_t* regs) { AND_R8(&regs->A, regs->H, &regs->F); } // Ax04
void AND_A_L(regs_t* regs) { AND_R8(&regs->A, regs->L, &regs->F); } // Ax05

void AND_A_mHL(regs_t* regs) { SBC_R8(&regs->A, read_u8(regs->HL), &regs->F); } // Ax06
void AND_A_8IM(regs_t* regs) { SBC_R8(&regs->A, IM_U8, &regs->F); }             // Ex06

void XOR_R8(uint8_t* a_reg, const uint8_t n, uint8_t* flag_reg) {
    const uint8_t res = *a_reg ^ n;
    *a_reg = res;

    set_flag(flag_reg, FLAG_Z, ((res & 0xff) == 0) ? 1 : 0);
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, 0);
}

void XOR_A_A(regs_t* regs) { XOR_R8(&regs->A, regs->A, &regs->F); } // Ax0F
void XOR_A_B(regs_t* regs) { XOR_R8(&regs->A, regs->B, &regs->F); } // Ax08
void XOR_A_C(regs_t* regs) { XOR_R8(&regs->A, regs->C, &regs->F); } // Ax09
void XOR_A_D(regs_t* regs) { XOR_R8(&regs->A, regs->D, &regs->F); } // Ax0A
void XOR_A_E(regs_t* regs) { XOR_R8(&regs->A, regs->E, &regs->F); } // Ax0B
void XOR_A_H(regs_t* regs) { XOR_R8(&regs->A, regs->H, &regs->F); } // Ax0C
void XOR_A_L(regs_t* regs) { XOR_R8(&regs->A, regs->L, &regs->F); } // Ax0D

void XOR_A_mHL(regs_t* regs) { XOR_R8(&regs->A, read_u8(regs->HL), &regs->F); } // Ax0E
void XOR_A_8IM(regs_t* regs) { XOR_R8(&regs->A, IM_U8, &regs->F); }             // Ex0E

void OR_R8(uint8_t* a_reg, const uint8_t n, uint8_t* flag_reg) {
    const uint8_t res = *a_reg | n;
    *a_reg = res;

    set_flag(flag_reg, FLAG_Z, ((res & 0xff) == 0) ? 1 : 0);
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, 0);
}

void OR_A_A(regs_t* regs) { OR_R8(&regs->A, regs->A, &regs->F); } // Bx07
void OR_A_B(regs_t* regs) { OR_R8(&regs->A, regs->B, &regs->F); } // Bx00
void OR_A_C(regs_t* regs) { OR_R8(&regs->A, regs->C, &regs->F); } // Bx01
void OR_A_D(regs_t* regs) { OR_R8(&regs->A, regs->D, &regs->F); } // Bx02
void OR_A_E(regs_t* regs) { OR_R8(&regs->A, regs->E, &regs->F); } // Bx03
void OR_A_H(regs_t* regs) { OR_R8(&regs->A, regs->H, &regs->F); } // Bx04
void OR_A_L(regs_t* regs) { OR_R8(&regs->A, regs->L, &regs->F); } // Bx05

void OR_A_mHL(regs_t* regs) { OR_R8(&regs->A, read_u8(regs->HL), &regs->F); } // Bx06
void OR_A_8IM(regs_t* regs) { OR_R8(&regs->A, IM_U8, &regs->F); }             // Fx06

void INC_R8(uint8_t* reg, uint8_t* flag_reg) {
    const uint8_t value = *reg;
    *reg = value + 1;

    const uint8_t bit3overflow = (value & 0x0f) + 1 > 0x0f;
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_Z, ((*reg & 0xff) == 0) ? 1 : 0);
    set_flag(flag_reg, FLAG_N, bit3overflow);
}

void INC_A(regs_t* regs) { INC_R8(&regs->A, &regs->F); } // 3x0C
void INC_B(regs_t* regs) { INC_R8(&regs->B, &regs->F); } // 0x04
void INC_C(regs_t* regs) { INC_R8(&regs->C, &regs->F); } // 0x0C
void INC_D(regs_t* regs) { INC_R8(&regs->D, &regs->F); } // 1x04
void INC_E(regs_t* regs) { INC_R8(&regs->E, &regs->F); } // 1x0C
void INC_H(regs_t* regs) { INC_R8(&regs->H, &regs->F); } // 2x04
void INC_L(regs_t* regs) { INC_R8(&regs->L, &regs->F); } // 2x0C
void INC_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    INC_R8(&value, &regs->F);
    write_u8(regs->HL, value);
} // 3x04

void INC_R16(uint16_t* reg) { *reg = *reg + 1; }

void INC_BC(regs_t* regs) { INC_R16(&regs->BC); } // 0x03
void INC_DE(regs_t* regs) { INC_R16(&regs->DE); } // 1x03
void INC_HL(regs_t* regs) { INC_R16(&regs->HL); } // 2x03
void INC_SP(regs_t* regs) { INC_R16(&regs->SP); } // 3x02

void DEC_R8(uint8_t* reg, uint8_t* flag_reg) {
    const uint8_t value = *reg;
    *reg = value - 1;

    const uint8_t bit4borrow = (value & 0x0f - 1) > 0x0f;
    set_flag(flag_reg, FLAG_N, 1);
    set_flag(flag_reg, FLAG_Z, ((*reg & 0xff) == 0) ? 1 : 0);
    set_flag(flag_reg, FLAG_H, bit4borrow);
}

void DEC_A(regs_t* regs) { DEC_R8(&regs->A, &regs->F); } // 3x0D
void DEC_B(regs_t* regs) { DEC_R8(&regs->B, &regs->F); } // 0x05
void DEC_C(regs_t* regs) { DEC_R8(&regs->C, &regs->F); } // 0x0D
void DEC_D(regs_t* regs) { DEC_R8(&regs->D, &regs->F); } // 1x05
void DEC_E(regs_t* regs) { DEC_R8(&regs->E, &regs->F); } // 1x0D
void DEC_H(regs_t* regs) { DEC_R8(&regs->H, &regs->F); } // 2x05
void DEC_L(regs_t* regs) { DEC_R8(&regs->L, &regs->F); } // 2x0D

void DEC_R16(uint16_t* reg) { *reg = *reg - 1 & 0xffff; }

void DEC_BC(regs_t* regs) { DEC_R16(&regs->BC); } // 0x0B
void DEC_DE(regs_t* regs) { DEC_R16(&regs->DE); } // 1x0B
void DEC_HL(regs_t* regs) { DEC_R16(&regs->HL); } // 2x0B
void DEC_SP(regs_t* regs) { DEC_R16(&regs->SP); } // 3x0B

void DEC_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    DEC_R8(&value, &regs->F);
    write_u8(regs->HL, value);
} // 3x05

//==================================================================================================================
//
// STACK OPERATIONS  FAMILY
//
//==================================================================================================================
void POP_R16(uint16_t* reg, uint16_t* sp) {
    *reg = read_u16(*sp);
    *sp += 2;
}

void POP_BC(regs_t* regs) { POP_R16(&regs->BC, &regs->SP); } // Cx01
void POP_DE(regs_t* regs) { POP_R16(&regs->DE, &regs->SP); } // Dx01
void POP_HL(regs_t* regs) { POP_R16(&regs->HL, &regs->SP); } // Ex01
void POP_AF(regs_t* regs) {
    POP_R16(&regs->AF, &regs->SP);
    regs->F &= 0xf0; // Lower nibble of F register is always zero
} // Fx01

void PUSH_R16(const uint16_t reg, uint16_t* sp) {
    *sp -= 2;
    write_u16(*sp, reg);
}

void PUSH_BC(regs_t* regs) { PUSH_R16(regs->BC, &regs->SP); } // Cx05
void PUSH_DE(regs_t* regs) { PUSH_R16(regs->DE, &regs->SP); } // Dx05
void PUSH_HL(regs_t* regs) { PUSH_R16(regs->HL, &regs->SP); } // Ex05
void PUSH_AF(regs_t* regs) { PUSH_R16(regs->AF, &regs->SP); } // Fx05

//==================================================================================================================
//
// BIT OPERATIONS  FAMILY
//
//==================================================================================================================

// TODO IMPLEMENT THESE
void RLCA(regs_t* regs) { regs->A = 0; } // 0x07
void RRCA(regs_t* regs) { regs->A = 0; } // 0x0F
void RLA(regs_t* regs) { regs->A = 0; }  // 1x07
void RRA(regs_t* regs) { regs->A = 0; }  // 1x0F

void RLC_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t carry = *value >> 7;
    const uint8_t rotated = *value << 1 | carry;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void RLC_A(regs_t* regs) { RLC_n(&regs->A, &regs->F); } // Cx07
void RLC_B(regs_t* regs) { RLC_n(&regs->B, &regs->F); } // Cx00
void RLC_C(regs_t* regs) { RLC_n(&regs->C, &regs->F); } // Cx01
void RLC_D(regs_t* regs) { RLC_n(&regs->D, &regs->F); } // Cx02
void RLC_E(regs_t* regs) { RLC_n(&regs->E, &regs->F); } // Cx03
void RLC_H(regs_t* regs) { RLC_n(&regs->H, &regs->F); } // Cx04
void RLC_L(regs_t* regs) { RLC_n(&regs->L, &regs->F); } // Cx05
void RLC_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    RLC_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // Cx06

void RL_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t rotated = *value << 1 | (*flag_reg & FLAG_C);
    const uint8_t carry = *value >> 7;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void RL_A(regs_t* regs) { RL_n(&regs->A, &regs->F); } // Cx17
void RL_B(regs_t* regs) { RL_n(&regs->B, &regs->F); } // Cx10
void RL_C(regs_t* regs) { RL_n(&regs->C, &regs->F); } // Cx11
void RL_D(regs_t* regs) { RL_n(&regs->D, &regs->F); } // Cx12
void RL_E(regs_t* regs) { RL_n(&regs->E, &regs->F); } // Cx13
void RL_H(regs_t* regs) { RL_n(&regs->H, &regs->F); } // Cx14
void RL_L(regs_t* regs) { RL_n(&regs->L, &regs->F); } // Cx15
void RL_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    RL_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // Cx16

void RRC_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t carry = *value & 0x01;
    const uint8_t rotated = carry << 7 | *value >> 1;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void RRC_A(regs_t* regs) { RRC_n(&regs->A, &regs->F); } // Cx0F
void RRC_B(regs_t* regs) { RRC_n(&regs->B, &regs->F); } // CX08
void RRC_C(regs_t* regs) { RRC_n(&regs->C, &regs->F); } // CX09
void RRC_D(regs_t* regs) { RRC_n(&regs->D, &regs->F); } // CX0A
void RRC_E(regs_t* regs) { RRC_n(&regs->E, &regs->F); } // CX0B
void RRC_H(regs_t* regs) { RRC_n(&regs->H, &regs->F); } // CX0C
void RRC_L(regs_t* regs) { RRC_n(&regs->L, &regs->F); } // CX0D
void RRC_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    RRC_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // CX0E

void RR_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t rotated = (*flag_reg & FLAG_C) << 7 | *value >> 1;
    const uint8_t carry = *value & 0x01;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void RR_A(regs_t* regs) { RR_n(&regs->A, &regs->F); } // Cx1F
void RR_B(regs_t* regs) { RR_n(&regs->B, &regs->F); } // CX18
void RR_C(regs_t* regs) { RR_n(&regs->C, &regs->F); } // CX19
void RR_D(regs_t* regs) { RR_n(&regs->D, &regs->F); } // CX1A
void RR_E(regs_t* regs) { RR_n(&regs->E, &regs->F); } // CX1B
void RR_H(regs_t* regs) { RR_n(&regs->H, &regs->F); } // CX1C
void RR_L(regs_t* regs) { RR_n(&regs->L, &regs->F); } // CX1D
void RR_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    RR_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // CX1E

void SLA_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t rotated = *value << 1;
    const uint8_t carry = *value >> 7;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void SLA_A(regs_t* regs) { SLA_n(&regs->A, &regs->F); } // Cx27
void SLA_B(regs_t* regs) { SLA_n(&regs->B, &regs->F); } // Cx20
void SLA_C(regs_t* regs) { SLA_n(&regs->C, &regs->F); } // Cx21
void SLA_D(regs_t* regs) { SLA_n(&regs->D, &regs->F); } // Cx22
void SLA_E(regs_t* regs) { SLA_n(&regs->E, &regs->F); } // Cx23
void SLA_H(regs_t* regs) { SLA_n(&regs->H, &regs->F); } // Cx24
void SLA_L(regs_t* regs) { SLA_n(&regs->L, &regs->F); } // Cx25
void SLA_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    SLA_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // Cx26

void SRA_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t rotated = *value >> 1 | (*value & 0x80);
    const uint8_t carry = *value & 0x01;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void SRA_A(regs_t* regs) { SRA_n(&regs->A, &regs->F); } // Cx2F
void SRA_B(regs_t* regs) { SRA_n(&regs->B, &regs->F); } // CX28
void SRA_C(regs_t* regs) { SRA_n(&regs->C, &regs->F); } // CX29
void SRA_D(regs_t* regs) { SRA_n(&regs->D, &regs->F); } // CX2A
void SRA_E(regs_t* regs) { SRA_n(&regs->E, &regs->F); } // CX2B
void SRA_H(regs_t* regs) { SRA_n(&regs->H, &regs->F); } // CX2C
void SRA_L(regs_t* regs) { SRA_n(&regs->L, &regs->F); } // CX2D
void SRA_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    SRA_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // CX2E

void SRL_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t rotated = *value >> 1;
    const uint8_t carry = *value & 0x01;
    *value = rotated;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, carry);
    set_flag(flag_reg, FLAG_Z, rotated == 0);
}

void SRL_A(regs_t* regs) { SRL_n(&regs->A, &regs->F); } // Cx3F
void SRL_B(regs_t* regs) { SRL_n(&regs->B, &regs->F); } // CX38
void SRL_C(regs_t* regs) { SRL_n(&regs->C, &regs->F); } // CX39
void SRL_D(regs_t* regs) { SRL_n(&regs->D, &regs->F); } // CX3A
void SRL_E(regs_t* regs) { SRL_n(&regs->E, &regs->F); } // CX3B
void SRL_H(regs_t* regs) { SRL_n(&regs->H, &regs->F); } // CX3C
void SRL_L(regs_t* regs) { SRL_n(&regs->L, &regs->F); } // CX3D
void SRL_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    SRL_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // CX3E

void SWAP_n(uint8_t* value, uint8_t* flag_reg) {
    const uint8_t swaped = *value << 4 | *value >> 4;
    *value = swaped;

    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 0);
    set_flag(flag_reg, FLAG_C, 0);
    set_flag(flag_reg, FLAG_Z, swaped == 0);
}

void SWAP_A(regs_t* regs) { SWAP_n(&regs->A, &regs->F); } // Cx37
void SWAP_B(regs_t* regs) { SWAP_n(&regs->B, &regs->F); } // Cx30
void SWAP_C(regs_t* regs) { SWAP_n(&regs->C, &regs->F); } // Cx31
void SWAP_D(regs_t* regs) { SWAP_n(&regs->D, &regs->F); } // Cx32
void SWAP_E(regs_t* regs) { SWAP_n(&regs->E, &regs->F); } // Cx33
void SWAP_H(regs_t* regs) { SWAP_n(&regs->H, &regs->F); } // Cx34
void SWAP_L(regs_t* regs) { SWAP_n(&regs->L, &regs->F); } // Cx35
void SWAP_mHL(regs_t* regs) {
    uint8_t value = read_u8(regs->HL);
    SWAP_n(&value, &regs->F);

    write_u8(regs->HL, value);
} // Cx36

void BIT_b_n(const uint8_t value, const uint8_t position, uint8_t* flag_reg) {
    const uint8_t selected = value & (1 << position);

    set_flag(flag_reg, FLAG_Z, selected == 0);
    set_flag(flag_reg, FLAG_N, 0);
    set_flag(flag_reg, FLAG_H, 1);
}

void BIT_0_A(regs_t* regs) { BIT_b_n(regs->A, 0, &regs->F); } // Cx47
void BIT_0_B(regs_t* regs) { BIT_b_n(regs->B, 0, &regs->F); } // Cx40
void BIT_0_C(regs_t* regs) { BIT_b_n(regs->C, 0, &regs->F); } // Cx41
void BIT_0_D(regs_t* regs) { BIT_b_n(regs->D, 0, &regs->F); } // Cx42
void BIT_0_E(regs_t* regs) { BIT_b_n(regs->E, 0, &regs->F); } // Cx43
void BIT_0_H(regs_t* regs) { BIT_b_n(regs->H, 0, &regs->F); } // Cx44
void BIT_0_L(regs_t* regs) { BIT_b_n(regs->L, 0, &regs->F); } // Cx45

void BIT_1_A(regs_t* regs) { BIT_b_n(regs->A, 1, &regs->F); } // Cx4F
void BIT_1_B(regs_t* regs) { BIT_b_n(regs->B, 1, &regs->F); } // CX48
void BIT_1_C(regs_t* regs) { BIT_b_n(regs->C, 1, &regs->F); } // CX49
void BIT_1_D(regs_t* regs) { BIT_b_n(regs->D, 1, &regs->F); } // CX4A
void BIT_1_E(regs_t* regs) { BIT_b_n(regs->E, 1, &regs->F); } // CX4B
void BIT_1_H(regs_t* regs) { BIT_b_n(regs->H, 1, &regs->F); } // CX4C
void BIT_1_L(regs_t* regs) { BIT_b_n(regs->L, 1, &regs->F); } // CX4D

void BIT_2_A(regs_t* regs) { BIT_b_n(regs->A, 2, &regs->F); } // Cx57
void BIT_2_B(regs_t* regs) { BIT_b_n(regs->B, 2, &regs->F); } // Cx50
void BIT_2_C(regs_t* regs) { BIT_b_n(regs->C, 2, &regs->F); } // Cx51
void BIT_2_D(regs_t* regs) { BIT_b_n(regs->D, 2, &regs->F); } // Cx52
void BIT_2_E(regs_t* regs) { BIT_b_n(regs->E, 2, &regs->F); } // Cx53
void BIT_2_H(regs_t* regs) { BIT_b_n(regs->H, 2, &regs->F); } // Cx54
void BIT_2_L(regs_t* regs) { BIT_b_n(regs->L, 2, &regs->F); } // Cx55

void BIT_3_A(regs_t* regs) { BIT_b_n(regs->A, 3, &regs->F); } // Cx5F
void BIT_3_B(regs_t* regs) { BIT_b_n(regs->B, 3, &regs->F); } // CX58
void BIT_3_C(regs_t* regs) { BIT_b_n(regs->C, 3, &regs->F); } // CX59
void BIT_3_D(regs_t* regs) { BIT_b_n(regs->D, 3, &regs->F); } // CX5A
void BIT_3_E(regs_t* regs) { BIT_b_n(regs->E, 3, &regs->F); } // CX5B
void BIT_3_H(regs_t* regs) { BIT_b_n(regs->H, 3, &regs->F); } // CX5C
void BIT_3_L(regs_t* regs) { BIT_b_n(regs->L, 3, &regs->F); } // CX5D

void BIT_4_A(regs_t* regs) { BIT_b_n(regs->A, 4, &regs->F); } // Cx67
void BIT_4_B(regs_t* regs) { BIT_b_n(regs->B, 4, &regs->F); } // Cx60
void BIT_4_C(regs_t* regs) { BIT_b_n(regs->C, 4, &regs->F); } // Cx61
void BIT_4_D(regs_t* regs) { BIT_b_n(regs->D, 4, &regs->F); } // Cx62
void BIT_4_E(regs_t* regs) { BIT_b_n(regs->E, 4, &regs->F); } // Cx63
void BIT_4_H(regs_t* regs) { BIT_b_n(regs->H, 4, &regs->F); } // Cx64
void BIT_4_L(regs_t* regs) { BIT_b_n(regs->L, 4, &regs->F); } // Cx65

void BIT_5_A(regs_t* regs) { BIT_b_n(regs->A, 5, &regs->F); } // Cx6F
void BIT_5_B(regs_t* regs) { BIT_b_n(regs->B, 5, &regs->F); } // CX68
void BIT_5_C(regs_t* regs) { BIT_b_n(regs->C, 5, &regs->F); } // CX69
void BIT_5_D(regs_t* regs) { BIT_b_n(regs->D, 5, &regs->F); } // CX6A
void BIT_5_E(regs_t* regs) { BIT_b_n(regs->E, 5, &regs->F); } // CX6B
void BIT_5_H(regs_t* regs) { BIT_b_n(regs->H, 5, &regs->F); } // CX6C
void BIT_5_L(regs_t* regs) { BIT_b_n(regs->L, 5, &regs->F); } // CX6D

void BIT_6_A(regs_t* regs) { BIT_b_n(regs->A, 6, &regs->F); } // Cx77
void BIT_6_B(regs_t* regs) { BIT_b_n(regs->B, 6, &regs->F); } // Cx70
void BIT_6_C(regs_t* regs) { BIT_b_n(regs->C, 6, &regs->F); } // Cx71
void BIT_6_D(regs_t* regs) { BIT_b_n(regs->D, 6, &regs->F); } // Cx72
void BIT_6_E(regs_t* regs) { BIT_b_n(regs->E, 6, &regs->F); } // Cx73
void BIT_6_H(regs_t* regs) { BIT_b_n(regs->H, 6, &regs->F); } // Cx74
void BIT_6_L(regs_t* regs) { BIT_b_n(regs->L, 6, &regs->F); } // Cx75

void BIT_7_A(regs_t* regs) { BIT_b_n(regs->A, 7, &regs->F); } // Cx7F
void BIT_7_B(regs_t* regs) { BIT_b_n(regs->B, 7, &regs->F); } // CX78
void BIT_7_C(regs_t* regs) { BIT_b_n(regs->C, 7, &regs->F); } // CX79
void BIT_7_D(regs_t* regs) { BIT_b_n(regs->D, 7, &regs->F); } // CX7A
void BIT_7_E(regs_t* regs) { BIT_b_n(regs->E, 7, &regs->F); } // CX7B
void BIT_7_H(regs_t* regs) { BIT_b_n(regs->H, 7, &regs->F); } // CX7C
void BIT_7_L(regs_t* regs) { BIT_b_n(regs->L, 7, &regs->F); } // CX7D

void BIT_0_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 0, &regs->F); } // Cx46
void BIT_1_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 1, &regs->F); } // CX4E
void BIT_2_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 2, &regs->F); } // Cx56
void BIT_3_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 3, &regs->F); } // CX5E
void BIT_4_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 4, &regs->F); } // Cx66
void BIT_5_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 5, &regs->F); } // CX6E
void BIT_6_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 6, &regs->F); } // Cx76
void BIT_7_mHL(regs_t* regs) { BIT_b_n(read_u8(regs->HL), 7, &regs->F); } // CX7E

void RES_b_n(uint8_t* value, const uint8_t position) {
    *value = *value & ~(1 << position);
}

void RES_b_mem(const uint16_t addr, const uint8_t position) {
    uint8_t value = read_u8(addr);
    RES_b_n(&value, position);
    write_u8(addr, value);
}

void RES_0_A(regs_t* regs) { RES_b_n(&regs->A, 0); } // Cx87
void RES_0_B(regs_t* regs) { RES_b_n(&regs->B, 0); } // Cx80
void RES_0_C(regs_t* regs) { RES_b_n(&regs->C, 0); } // Cx81
void RES_0_D(regs_t* regs) { RES_b_n(&regs->D, 0); } // Cx82
void RES_0_E(regs_t* regs) { RES_b_n(&regs->E, 0); } // Cx83
void RES_0_H(regs_t* regs) { RES_b_n(&regs->H, 0); } // Cx84
void RES_0_L(regs_t* regs) { RES_b_n(&regs->L, 0); } // Cx85

void RES_1_A(regs_t* regs) { RES_b_n(&regs->A, 1); } // Cx8F
void RES_1_B(regs_t* regs) { RES_b_n(&regs->B, 1); } // CX88
void RES_1_C(regs_t* regs) { RES_b_n(&regs->C, 1); } // CX89
void RES_1_D(regs_t* regs) { RES_b_n(&regs->D, 1); } // CX8A
void RES_1_E(regs_t* regs) { RES_b_n(&regs->E, 1); } // CX8B
void RES_1_H(regs_t* regs) { RES_b_n(&regs->H, 1); } // CX8C
void RES_1_L(regs_t* regs) { RES_b_n(&regs->L, 1); } // CX8D

void RES_2_A(regs_t* regs) { RES_b_n(&regs->A, 2); } // Cx97
void RES_2_B(regs_t* regs) { RES_b_n(&regs->B, 2); } // Cx90
void RES_2_C(regs_t* regs) { RES_b_n(&regs->C, 2); } // Cx91
void RES_2_D(regs_t* regs) { RES_b_n(&regs->D, 2); } // Cx92
void RES_2_E(regs_t* regs) { RES_b_n(&regs->E, 2); } // Cx93
void RES_2_H(regs_t* regs) { RES_b_n(&regs->H, 2); } // Cx94
void RES_2_L(regs_t* regs) { RES_b_n(&regs->L, 2); } // Cx95

void RES_3_A(regs_t* regs) { RES_b_n(&regs->A, 3); } // Cx9F
void RES_3_B(regs_t* regs) { RES_b_n(&regs->B, 3); } // CX98
void RES_3_C(regs_t* regs) { RES_b_n(&regs->C, 3); } // CX99
void RES_3_D(regs_t* regs) { RES_b_n(&regs->D, 3); } // CX9A
void RES_3_E(regs_t* regs) { RES_b_n(&regs->E, 3); } // CX9B
void RES_3_H(regs_t* regs) { RES_b_n(&regs->H, 3); } // CX9C
void RES_3_L(regs_t* regs) { RES_b_n(&regs->L, 3); } // CX9D

void RES_4_A(regs_t* regs) { RES_b_n(&regs->A, 4); } // CxA7
void RES_4_B(regs_t* regs) { RES_b_n(&regs->B, 4); } // CxA0
void RES_4_C(regs_t* regs) { RES_b_n(&regs->C, 4); } // CxA1
void RES_4_D(regs_t* regs) { RES_b_n(&regs->D, 4); } // CxA2
void RES_4_E(regs_t* regs) { RES_b_n(&regs->E, 4); } // CxA3
void RES_4_H(regs_t* regs) { RES_b_n(&regs->H, 4); } // CxA4
void RES_4_L(regs_t* regs) { RES_b_n(&regs->L, 4); } // CxA5

void RES_5_A(regs_t* regs) { RES_b_n(&regs->A, 5); } // CxAF
void RES_5_B(regs_t* regs) { RES_b_n(&regs->B, 5); } // CXA8
void RES_5_C(regs_t* regs) { RES_b_n(&regs->C, 5); } // CXA9
void RES_5_D(regs_t* regs) { RES_b_n(&regs->D, 5); } // CXAA
void RES_5_E(regs_t* regs) { RES_b_n(&regs->E, 5); } // CXAB
void RES_5_H(regs_t* regs) { RES_b_n(&regs->H, 5); } // CXAC
void RES_5_L(regs_t* regs) { RES_b_n(&regs->L, 5); } // CXAD

void RES_6_A(regs_t* regs) { RES_b_n(&regs->A, 6); } // CxB7
void RES_6_B(regs_t* regs) { RES_b_n(&regs->B, 6); } // CxB0
void RES_6_C(regs_t* regs) { RES_b_n(&regs->C, 6); } // CxB1
void RES_6_D(regs_t* regs) { RES_b_n(&regs->D, 6); } // CxB2
void RES_6_E(regs_t* regs) { RES_b_n(&regs->E, 6); } // CxB3
void RES_6_H(regs_t* regs) { RES_b_n(&regs->H, 6); } // CxB4
void RES_6_L(regs_t* regs) { RES_b_n(&regs->L, 6); } // CxB5

void RES_7_A(regs_t* regs) { RES_b_n(&regs->A, 7); } // CxBF
void RES_7_B(regs_t* regs) { RES_b_n(&regs->B, 7); } // CXB8
void RES_7_C(regs_t* regs) { RES_b_n(&regs->C, 7); } // CXB9
void RES_7_D(regs_t* regs) { RES_b_n(&regs->D, 7); } // CXBA
void RES_7_E(regs_t* regs) { RES_b_n(&regs->E, 7); } // CXBB
void RES_7_H(regs_t* regs) { RES_b_n(&regs->H, 7); } // CXBC
void RES_7_L(regs_t* regs) { RES_b_n(&regs->L, 7); } // CXBD

void RES_0_mHL(regs_t* regs) { RES_b_mem(regs->HL, 0); } // Cx86
void RES_1_mHL(regs_t* regs) { RES_b_mem(regs->HL, 1); } // CX8E
void RES_2_mHL(regs_t* regs) { RES_b_mem(regs->HL, 2); } // Cx96
void RES_3_mHL(regs_t* regs) { RES_b_mem(regs->HL, 3); } // CX9E
void RES_4_mHL(regs_t* regs) { RES_b_mem(regs->HL, 4); } // CxA6
void RES_5_mHL(regs_t* regs) { RES_b_mem(regs->HL, 5); } // CXAE
void RES_6_mHL(regs_t* regs) { RES_b_mem(regs->HL, 6); } // CxB6
void RES_7_mHL(regs_t* regs) { RES_b_mem(regs->HL, 7); } // CXBE

void SET_b_n(uint8_t* value, const uint8_t position) {
    *value = *value | (1 << position);
}

void SET_b_mem(const uint16_t addr, const uint8_t position) {
    uint8_t value = read_u8(addr);
    RES_b_n(&value, position);
    write_u8(addr, value);
}

void SET_0_A(regs_t* regs) { SET_b_n(&regs->A, 0); } // CxC7
void SET_0_B(regs_t* regs) { SET_b_n(&regs->B, 0); } // CxC0
void SET_0_C(regs_t* regs) { SET_b_n(&regs->C, 0); } // CxC1
void SET_0_D(regs_t* regs) { SET_b_n(&regs->D, 0); } // CxC2
void SET_0_E(regs_t* regs) { SET_b_n(&regs->E, 0); } // CxC3
void SET_0_H(regs_t* regs) { SET_b_n(&regs->H, 0); } // CxC4
void SET_0_L(regs_t* regs) { SET_b_n(&regs->L, 0); } // CxC5

void SET_1_A(regs_t* regs) { SET_b_n(&regs->A, 1); } // CxCF
void SET_1_B(regs_t* regs) { SET_b_n(&regs->B, 1); } // CXC8
void SET_1_C(regs_t* regs) { SET_b_n(&regs->C, 1); } // CXC9
void SET_1_D(regs_t* regs) { SET_b_n(&regs->D, 1); } // CXCA
void SET_1_E(regs_t* regs) { SET_b_n(&regs->E, 1); } // CXCB
void SET_1_H(regs_t* regs) { SET_b_n(&regs->H, 1); } // CXCC
void SET_1_L(regs_t* regs) { SET_b_n(&regs->L, 1); } // CXCD

void SET_2_A(regs_t* regs) { SET_b_n(&regs->A, 2); } // CxD7
void SET_2_B(regs_t* regs) { SET_b_n(&regs->B, 2); } // CxD0
void SET_2_C(regs_t* regs) { SET_b_n(&regs->C, 2); } // CxD1
void SET_2_D(regs_t* regs) { SET_b_n(&regs->D, 2); } // CxD2
void SET_2_E(regs_t* regs) { SET_b_n(&regs->E, 2); } // CxD3
void SET_2_H(regs_t* regs) { SET_b_n(&regs->H, 2); } // CxD4
void SET_2_L(regs_t* regs) { SET_b_n(&regs->L, 2); } // CxD5

void SET_3_A(regs_t* regs) { SET_b_n(&regs->A, 3); } // CxDF
void SET_3_B(regs_t* regs) { SET_b_n(&regs->B, 3); } // CXD8
void SET_3_C(regs_t* regs) { SET_b_n(&regs->C, 3); } // CXD9
void SET_3_D(regs_t* regs) { SET_b_n(&regs->D, 3); } // CXDA
void SET_3_E(regs_t* regs) { SET_b_n(&regs->E, 3); } // CXDB
void SET_3_H(regs_t* regs) { SET_b_n(&regs->H, 3); } // CXDC
void SET_3_L(regs_t* regs) { SET_b_n(&regs->L, 3); } // CXDD

void SET_4_A(regs_t* regs) { SET_b_n(&regs->A, 4); } // CxE7
void SET_4_B(regs_t* regs) { SET_b_n(&regs->B, 4); } // CxE0
void SET_4_C(regs_t* regs) { SET_b_n(&regs->C, 4); } // CxE1
void SET_4_D(regs_t* regs) { SET_b_n(&regs->D, 4); } // CxE2
void SET_4_E(regs_t* regs) { SET_b_n(&regs->E, 4); } // CxE3
void SET_4_H(regs_t* regs) { SET_b_n(&regs->H, 4); } // CxE4
void SET_4_L(regs_t* regs) { SET_b_n(&regs->L, 4); } // CxE5

void SET_5_A(regs_t* regs) { SET_b_n(&regs->A, 5); } // CxEF
void SET_5_B(regs_t* regs) { SET_b_n(&regs->B, 5); } // CXE8
void SET_5_C(regs_t* regs) { SET_b_n(&regs->C, 5); } // CXE9
void SET_5_D(regs_t* regs) { SET_b_n(&regs->D, 5); } // CXEA
void SET_5_E(regs_t* regs) { SET_b_n(&regs->E, 5); } // CXEB
void SET_5_H(regs_t* regs) { SET_b_n(&regs->H, 5); } // CXEC
void SET_5_L(regs_t* regs) { SET_b_n(&regs->L, 5); } // CXED

void SET_6_A(regs_t* regs) { SET_b_n(&regs->A, 6); } // CxF7
void SET_6_B(regs_t* regs) { SET_b_n(&regs->B, 6); } // CxF0
void SET_6_C(regs_t* regs) { SET_b_n(&regs->C, 6); } // CxF1
void SET_6_D(regs_t* regs) { SET_b_n(&regs->D, 6); } // CxF2
void SET_6_E(regs_t* regs) { SET_b_n(&regs->E, 6); } // CxF3
void SET_6_H(regs_t* regs) { SET_b_n(&regs->H, 6); } // CxF4
void SET_6_L(regs_t* regs) { SET_b_n(&regs->L, 6); } // CxF5

void SET_7_A(regs_t* regs) { SET_b_n(&regs->A, 7); } // CxFF
void SET_7_B(regs_t* regs) { SET_b_n(&regs->B, 7); } // CXF8
void SET_7_C(regs_t* regs) { SET_b_n(&regs->C, 7); } // CXF9
void SET_7_D(regs_t* regs) { SET_b_n(&regs->D, 7); } // CXFA
void SET_7_E(regs_t* regs) { SET_b_n(&regs->E, 7); } // CXFB
void SET_7_H(regs_t* regs) { SET_b_n(&regs->H, 7); } // CXFC
void SET_7_L(regs_t* regs) { SET_b_n(&regs->L, 7); } // CXFD

void SET_0_mHL(regs_t* regs) { SET_b_mem(regs->HL, 0); } // CxC6
void SET_1_mHL(regs_t* regs) { SET_b_mem(regs->HL, 1); } // CXCE
void SET_2_mHL(regs_t* regs) { SET_b_mem(regs->HL, 2); } // CxD6
void SET_3_mHL(regs_t* regs) { SET_b_mem(regs->HL, 3); } // CXDE
void SET_4_mHL(regs_t* regs) { SET_b_mem(regs->HL, 4); } // CxE6
void SET_5_mHL(regs_t* regs) { SET_b_mem(regs->HL, 5); } // CXEE
void SET_6_mHL(regs_t* regs) { SET_b_mem(regs->HL, 6); } // CxF6
void SET_7_mHL(regs_t* regs) { SET_b_mem(regs->HL, 7); } // CXFE

//==================================================================================================================
//
// CONTROL FLOW FAMILY
//
//==================================================================================================================

void JR_n(uint16_t* PC) { *PC += IM_I8; }

void JR_8IM(regs_t* regs) { JR_n(&regs->PC); } // 1x08
void JR_Z_8IM(regs_t* regs) {
    if (regs->F & FLAG_Z) JR_n(&regs->PC);
} // 2x08
void JR_C_8IM(regs_t* regs) {
    if (regs->F & FLAG_C) JR_n(&regs->PC);
} // 3x08
void JR_NZ_8IM(regs_t* regs) {
    if (!(regs->F & FLAG_Z)) JR_n(&regs->PC);
} // 2x00
void JR_NC_8IM(regs_t* regs) {
    if (!(regs->F & FLAG_C)) JR_n(&regs->PC);
} // 3x00

void JP_nn(uint16_t* PC) { *PC = IM_U16; }

void JP_16IM(regs_t* regs) { JP_nn(&regs->PC); }  // Cx03
void JP_HL(regs_t* regs) { regs->PC = regs->HL; } // Ex09
void JP_Z_16IM(regs_t* regs) {
    if (regs->F & FLAG_Z) JP_nn(&regs->PC);
} // Cx0A
void JP_C_16IM(regs_t* regs) {
    if (regs->F & FLAG_C) JP_nn(&regs->PC);
} // Dx0A
void JP_NZ_16IM(regs_t* regs) {
    if (!(regs->F & FLAG_Z)) JP_nn(&regs->PC);
} // Cx02
void JP_NC_16IM(regs_t* regs) {
    if (!(regs->F & FLAG_C)) JP_nn(&regs->PC);
} // Dx02

void CALL(uint16_t* PC, uint16_t* SP) {
    PUSH_R16(*PC, SP);
    *PC = IM_U8;
}

void CALL_16IM(regs_t* regs) { CALL(&regs->PC, &regs->SP); } // Cx0D
void CALL_C_16IM(regs_t* regs) {
    if (regs->F & FLAG_C) { CALL_16IM(regs); }
} // Dx0C
void CALL_Z_16IM(regs_t* regs) {
    if (!(regs->F & FLAG_Z)) { CALL_16IM(regs); }
} // Cx0C
void CALL_NZ_16IM(regs_t* regs) {
    if (!(regs->F & FLAG_Z)) { CALL_16IM(regs); }
} // Cx04
void CALL_NC_16IM(regs_t* regs) {
    if (!(regs->F & FLAG_C)) { CALL_16IM(regs); }
} // Dx04

void RET(regs_t* regs) { POP_R16(&regs->PC, &regs->SP); } // Cx09

void RET_C(regs_t* regs) {
    if (regs->F & FLAG_C) { RET(regs); }
} // Dx08
void RET_Z(regs_t* regs) {
    if (regs->F & FLAG_Z) { RET(regs); }
} // Cx08
void RET_NC(regs_t* regs) {
    if (!(regs->F & FLAG_C)) { RET(regs); }
} // Dx00
void RET_NZ(regs_t* regs) {
    if (!(regs->F & FLAG_Z)) { RET(regs); }
} // Cx00

void restart(const uint8_t addr, uint16_t* PC, uint16_t* SP) {
    PUSH_R16(*PC, SP);
    *PC = addr;
}

void RST_00h(regs_t* regs) { restart(0x00, &regs->PC, &regs->SP); } // Cx07
void RST_08h(regs_t* regs) { restart(0x08, &regs->PC, &regs->SP); } // Cx0F
void RST_10h(regs_t* regs) { restart(0x10, &regs->PC, &regs->SP); } // Dx07
void RST_18h(regs_t* regs) { restart(0x18, &regs->PC, &regs->SP); } // Dx0F
void RST_20h(regs_t* regs) { restart(0x20, &regs->PC, &regs->SP); } // Ex07
void RST_28h(regs_t* regs) { restart(0x28, &regs->PC, &regs->SP); } // Ex0F
void RST_30h(regs_t* regs) { restart(0x30, &regs->PC, &regs->SP); } // Fx07
void RST_38h(regs_t* regs) { restart(0x38, &regs->PC, &regs->SP); } // Fx0F

void NOP(cpu_t* cpu) { cpu->regs.A = 0; } // 0x00

void DI(cpu_t* cpu) { cpu->IME = 0; }        // Fx03
void HALT(cpu_t* cpu) { cpu->halted = 1; }   // 7x06
void STOP(cpu_t* cpu) { cpu->stopped = 1; }  // 1x00
void EI(cpu_t* cpu) { cpu->IME_enable = 1; } // Fx0B
void RETI(cpu_t* cpu) {
    RET(&cpu->regs);
    EI(cpu);
} // Dx09

void DAA(regs_t* regs) {
    if (regs->F & FLAG_N) {
        if (regs->F & FLAG_C) { regs->A -= 0x60; }
        if (regs->F & FLAG_H) { regs->A -= 0x06; }
    } else {
        if ((regs->F & FLAG_C) || regs->A > 0x99) { regs->A += 0x60; }
        if ((regs->F & FLAG_H) || (regs->A & 0x0F) > 0x09) { regs->A += 0x06; }
    }
    set_flag(&regs->F, FLAG_H, 0);
    set_flag(&regs->C, FLAG_C, regs->A > 0x99);
    set_flag(&regs->F, FLAG_Z, regs->A == 0);
} // 2x07

void CPL(regs_t* regs) {
    regs->A = ~regs->A;
    set_flag(&regs->F, FLAG_N, 1);
    set_flag(&regs->F, FLAG_H, 1);
} // 2x0F

void SCF(regs_t* regs) {
    set_flag(&regs->F, FLAG_C, 1);
    set_flag(&regs->F, FLAG_N, 0);
    set_flag(&regs->F, FLAG_H, 0);
} // 3x07

void CCF(regs_t* regs) {
    set_flag(&regs->F, FLAG_C, ~(regs->F & FLAG_C));
    set_flag(&regs->F, FLAG_N, 0);
    set_flag(&regs->F, FLAG_H, 0);
} // 3x0F

void PREFIX(cpu_t* cpu) { printf("%u", cpu->halted); } // Cx0B
void UNKNOWN(regs_t* regs) {
    printf("Unknown opcode %u", regs->A);
    exit(69);
}

// void UNKONWN(void); // Dx03
// void UNKNOWN(void); // Dx0B
// void UNKNOWN(void); // Dx0D
// void UNKNOWN(void); // Ex03
// void UNKNOWN(void); // Ex04
// void UNKNOWN(void); // Ex0B
// void UNKNOWN(void); // Ex0C
// void UNKNOWN(void); // Ex0D
// void UNKNOWN(void); // Fx04
// void UNKNOWN(void); // Fx0C
// void UNKNOWN(void); // Fx0D

// static regs_t* regs;
// static cpu_t* cpu;

#define SET_OP(inst_ptr, opcode, handler, type, label, len, cycle1, cycle2)              \
    do {                                                                                 \
        inst_ptr[opcode].execute = (context){.ctx_##type = &handler};                    \
        inst_ptr[opcode].mnemonic = label;                                               \
        inst_ptr[opcode].length = len;                                                   \
        inst_ptr[opcode].cycle[0] = cycle1;                                              \
        inst_ptr[opcode].cycle[1] = cycle2;                                              \
    } while (0)

void InitOptable(inst_t* table) {
    SET_OP(table, 0x00, NOP, cpu, "NOP", 1, 4, 0);
    SET_OP(table, 0x01, LD_BC_16IM, regs, "LD BC %i", 3, 12, 0);
    SET_OP(table, 0x02, LD_mBC_A, regs, "LD  A", 1, 8, 0);
    SET_OP(table, 0x03, INC_BC, regs, "INC BC", 1, 8, 0);
    SET_OP(table, 0x04, INC_B, regs, "INC B", 1, 4, 0);
    SET_OP(table, 0x05, DEC_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x06, LD_B_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0x07, RLCA, regs, "", 1, 4, 0);
    SET_OP(table, 0x08, LD_m16_SP, regs, "", 3, 20, 0);
    SET_OP(table, 0x09, ADD_HL_BC, regs, "", 1, 8, 0);
    SET_OP(table, 0x0A, LD_A_mBC, regs, "", 1, 8, 0);
    SET_OP(table, 0x0B, DEC_BC, regs, "", 1, 8, 0);
    SET_OP(table, 0x0C, INC_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x0D, DEC_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x0E, LD_C_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0x0F, RRCA, regs, "", 1, 4, 0);

    SET_OP(table, 0x10, STOP, cpu, "STOP", 1, 4, 0);
    SET_OP(table, 0x11, LD_DE_16IM, regs, "", 3, 12, 0);
    SET_OP(table, 0x12, LD_mDE_A, regs, "", 1, 8, 0);
    SET_OP(table, 0x13, INC_DE, regs, "", 1, 8, 0);
    SET_OP(table, 0x14, INC_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x15, DEC_D, regs, "DEC D", 1, 4, 0);
    SET_OP(table, 0x16, LD_D_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0x17, RLA, regs, "", 1, 4, 0);
    SET_OP(table, 0x18, JR_8IM, regs, "", 2, 12, 0);
    SET_OP(table, 0x19, ADD_HL_DE, regs, "", 1, 8, 0);
    SET_OP(table, 0x1A, LD_A_mDE, regs, "", 1, 8, 0);
    SET_OP(table, 0x1B, DEC_DE, regs, "", 1, 8, 0);
    SET_OP(table, 0x1C, INC_E, regs, "", 1, 8, 0);
    SET_OP(table, 0x1D, DEC_E, regs, "", 1, 8, 0);
    SET_OP(table, 0x1E, LD_E_8IM, regs, "", 2, 8, 1);
    SET_OP(table, 0x1F, RRA, regs, "", 1, 4, 0);

    SET_OP(table, 0x20, JR_NZ_8IM, regs, "", 2, 8, 12);
    SET_OP(table, 0x21, LD_HL_16IM, regs, "", 3, 12, 0);
    SET_OP(table, 0x22, LD_HLI_A, regs, "", 1, 8, 0);
    SET_OP(table, 0x23, INC_HL, regs, "", 1, 8, 0);
    SET_OP(table, 0x24, INC_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x25, DEC_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x26, LD_H_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0x27, DAA, regs, "", 1, 4, 0);
    SET_OP(table, 0x28, JR_Z_8IM, regs, "", 2, 8, 12);
    SET_OP(table, 0x29, ADD_HL_HL, regs, "", 1, 8, 0);
    SET_OP(table, 0x2A, LD_A_HLI, regs, "", 1, 8, 0);
    SET_OP(table, 0x2B, DEC_HL, regs, "", 1, 8, 0);
    SET_OP(table, 0x2C, INC_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x2D, DEC_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x2E, LD_L_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0x2F, CPL, regs, "", 1, 4, 0);

    SET_OP(table, 0x30, JR_NC_8IM, regs, "", 2, 8, 12);
    SET_OP(table, 0x31, LD_SP_16IM, regs, "", 3, 12, 0);
    SET_OP(table, 0x32, LD_HLD_A, regs, "", 1, 8, 0);
    SET_OP(table, 0x33, INC_SP, regs, "", 1, 8, 0);
    SET_OP(table, 0x34, INC_mHL, regs, "", 1, 12, 0);
    SET_OP(table, 0x35, DEC_mHL, regs, "", 1, 12, 0);
    SET_OP(table, 0x36, LD_mHL_8IM, regs, "", 2, 12, 0);
    SET_OP(table, 0x37, SCF, regs, "", 1, 4, 0);
    SET_OP(table, 0x38, JR_C_8IM, regs, "", 2, 8, 12);
    SET_OP(table, 0x39, ADD_HL_SP, regs, "", 1, 8, 0);
    SET_OP(table, 0x3A, LD_A_HLD, regs, "", 1, 8, 0);
    SET_OP(table, 0x3B, DEC_SP, regs, "", 1, 8, 0);
    SET_OP(table, 0x3C, INC_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x3D, DEC_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x3E, LD_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0x3F, CCF, regs, "", 1, 4, 0);

    SET_OP(table, 0x40, LD_B_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x41, LD_B_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x42, LD_B_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x43, LD_B_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x44, LD_B_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x45, LD_B_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x46, LD_B_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x47, LD_B_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x48, LD_C_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x49, LD_C_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x4A, LD_C_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x4B, LD_C_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x4C, LD_C_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x4D, LD_C_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x4E, LD_C_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x4F, LD_C_A, regs, "", 1, 4, 0);

    SET_OP(table, 0x50, LD_D_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x51, LD_D_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x52, LD_D_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x53, LD_D_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x54, LD_D_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x55, LD_D_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x56, LD_D_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x57, LD_D_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x58, LD_E_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x59, LD_E_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x5A, LD_E_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x5B, LD_E_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x5C, LD_E_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x5D, LD_E_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x5E, LD_E_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x5F, LD_E_A, regs, "", 1, 4, 0);

    SET_OP(table, 0x60, LD_H_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x61, LD_H_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x62, LD_H_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x63, LD_H_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x64, LD_H_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x65, LD_H_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x66, LD_H_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x67, LD_H_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x68, LD_L_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x69, LD_L_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x6A, LD_L_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x6B, LD_L_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x6C, LD_L_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x6D, LD_L_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x6E, LD_L_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x6F, LD_L_A, regs, "", 1, 4, 0);

    SET_OP(table, 0x70, LD_mHL_B, regs, "", 1, 8, 0);
    SET_OP(table, 0x71, LD_mHL_C, regs, "", 1, 8, 0);
    SET_OP(table, 0x72, LD_mHL_D, regs, "", 1, 8, 0);
    SET_OP(table, 0x73, LD_mHL_E, regs, "", 1, 8, 0);
    SET_OP(table, 0x74, LD_mHL_H, regs, "", 1, 8, 0);
    SET_OP(table, 0x75, LD_mHL_L, regs, "", 1, 8, 0);
    SET_OP(table, 0x76, HALT, cpu, "HALT", 1, 4, 0);
    SET_OP(table, 0x77, LD_mHL_A, regs, "", 1, 8, 0);
    SET_OP(table, 0x78, LD_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x79, LD_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x7A, LD_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x7B, LD_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x7C, LD_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x7D, LD_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x7E, LD_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x7F, LD_A_A, regs, "", 1, 4, 0);

    SET_OP(table, 0x80, ADD_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x81, ADD_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x82, ADD_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x83, ADD_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x84, ADD_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x85, ADD_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x86, ADD_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x87, ADD_A_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x88, ADC_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x89, ADC_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x8A, ADC_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x8B, ADC_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x8C, ADC_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x8D, ADC_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x8E, ADC_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x8F, ADC_A_A, regs, "", 1, 4, 0);

    SET_OP(table, 0x90, SUB_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x91, SUB_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x92, SUB_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x93, SUB_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x94, SUB_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x95, SUB_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x96, SUB_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x97, SUB_A_A, regs, "", 1, 4, 0);
    SET_OP(table, 0x98, SBC_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0x99, SBC_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0x9A, SBC_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0x9B, SBC_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0x9C, SBC_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0x9D, SBC_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0x9E, SBC_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0x9F, SBC_A_A, regs, "", 1, 4, 0);

    SET_OP(table, 0xA0, AND_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0xA1, AND_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0xA2, AND_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0xA3, AND_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0xA4, AND_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0xA5, AND_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0xA6, AND_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0xA7, AND_A_A, regs, "", 1, 4, 0);
    SET_OP(table, 0xA8, XOR_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0xA9, XOR_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0xAA, XOR_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0xAB, XOR_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0xAC, XOR_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0xAD, XOR_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0xAE, XOR_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0xAF, XOR_A_A, regs, "", 1, 4, 0);

    SET_OP(table, 0xB0, OR_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0xB1, OR_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0xB2, OR_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0xB3, OR_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0xB4, OR_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0xB5, OR_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0xB6, OR_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0xB7, OR_A_A, regs, "", 1, 4, 0);
    SET_OP(table, 0xB8, CP_A_B, regs, "", 1, 4, 0);
    SET_OP(table, 0xB9, CP_A_C, regs, "", 1, 4, 0);
    SET_OP(table, 0xBA, CP_A_D, regs, "", 1, 4, 0);
    SET_OP(table, 0xBB, CP_A_E, regs, "", 1, 4, 0);
    SET_OP(table, 0xBC, CP_A_H, regs, "", 1, 4, 0);
    SET_OP(table, 0xBD, CP_A_L, regs, "", 1, 4, 0);
    SET_OP(table, 0xBE, CP_A_mHL, regs, "", 1, 8, 0);
    SET_OP(table, 0xBF, CP_A_A, regs, "", 1, 4, 0);

    SET_OP(table, 0xC0, RET_NZ, regs, "", 1, 8, 20);
    SET_OP(table, 0xC1, POP_BC, regs, "", 1, 12, 0);
    SET_OP(table, 0xC2, JP_NZ_16IM, regs, "", 3, 12, 16);
    SET_OP(table, 0xC3, JP_16IM, regs, "", 3, 16, 0);
    SET_OP(table, 0xC4, CALL_NZ_16IM, regs, "", 3, 12, 24);
    SET_OP(table, 0xC5, PUSH_BC, regs, "", 1, 16, 0);
    SET_OP(table, 0xC6, ADD_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xC7, RST_00h, regs, "", 1, 16, 0);
    SET_OP(table, 0xC8, RET_Z, regs, "", 1, 8, 20);
    SET_OP(table, 0xC9, RET, regs, "", 1, 16, 0);
    SET_OP(table, 0xCA, JP_Z_16IM, regs, "", 3, 12, 16);
    SET_OP(table, 0xCB, PREFIX, cpu, "", 1, 4, 0);
    SET_OP(table, 0xCC, CALL_Z_16IM, regs, "", 3, 12, 24);
    SET_OP(table, 0xCD, CALL_16IM, regs, "", 3, 24, 0);
    SET_OP(table, 0xCE, ADC_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xCF, RST_08h, regs, "", 1, 16, 0);

    SET_OP(table, 0xD0, RET_NC, regs, "", 1, 8, 20);
    SET_OP(table, 0xD1, POP_DE, regs, "", 1, 12, 0);
    SET_OP(table, 0xD2, JP_NC_16IM, regs, "", 3, 12, 16);
    SET_OP(table, 0xD3, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xD4, CALL_NC_16IM, regs, "", 3, 12, 24);
    SET_OP(table, 0xD5, PUSH_DE, regs, "", 1, 16, 0);
    SET_OP(table, 0xD6, SUB_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xD7, RST_10h, regs, "", 1, 16, 0);
    SET_OP(table, 0xD8, RET_C, regs, "", 1, 8, 0);
    SET_OP(table, 0xD9, RETI, cpu, "", 1, 16, 0);
    SET_OP(table, 0xDA, JP_C_16IM, regs, "", 3, 12, 16);
    SET_OP(table, 0xDB, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xDC, CALL_C_16IM, regs, "", 3, 12, 24);
    SET_OP(table, 0xDD, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xDE, SBC_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xDF, RST_18h, regs, "", 1, 16, 0);

    SET_OP(table, 0xE0, LD_FF00_8IM_A, regs, "", 2, 12, 0);
    SET_OP(table, 0xE1, POP_HL, regs, "", 1, 12, 0);
    SET_OP(table, 0xE2, LD_FF00_C_A, regs, "", 1, 8, 0);
    SET_OP(table, 0xE3, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xE4, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xE5, PUSH_HL, regs, "", 1, 16, 0);
    SET_OP(table, 0xE6, AND_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xE7, RST_20h, regs, "", 1, 16, 0);
    SET_OP(table, 0xE8, ADD_SP_e8, regs, "", 2, 16, 0);
    SET_OP(table, 0xE9, JP_HL, regs, "", 1, 4, 0);
    SET_OP(table, 0xEA, LD_m16_A, regs, "", 3, 16, 0);
    SET_OP(table, 0xEB, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xEC, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xED, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xEE, XOR_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xEF, RST_28h, regs, "", 1, 16, 0);

    SET_OP(table, 0xF0, LD_A_FF00_8IM, regs, "", 2, 12, 0);
    SET_OP(table, 0xF1, POP_AF, regs, "", 1, 12, 0);
    SET_OP(table, 0xF2, LD_A_FFOO_C, regs, "", 1, 8, 0);
    SET_OP(table, 0xF3, DI, cpu, "", 1, 4, 0);
    SET_OP(table, 0xF4, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xF5, PUSH_AF, regs, "", 1, 16, 0);
    SET_OP(table, 0xF6, OR_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xF7, RST_30h, regs, "", 1, 16, 0);
    SET_OP(table, 0xF8, LD_HL_SP8IM, regs, "", 1, 8, 0);
    SET_OP(table, 0xF9, LD_SP_HL, regs, "", 1, 8, 0);
    SET_OP(table, 0xFA, LD_A_m16, regs, "", 3, 16, 0);
    SET_OP(table, 0xFB, EI, cpu, "", 1, 4, 0);
    SET_OP(table, 0xFC, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xFD, UNKNOWN, regs, "", 0, 0, 0);
    SET_OP(table, 0xFE, CP_A_8IM, regs, "", 2, 8, 0);
    SET_OP(table, 0xFF, RST_38h, regs, "", 1, 16, 0);
}

void InitPrefixedOptable(inst_t* table) {
    SET_OP(table, 0x00, RLC_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x01, RLC_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x02, RLC_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x03, RLC_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x04, RLC_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x05, RLC_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x06, RLC_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x07, RLC_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x08, RRC_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x09, RRC_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x0A, RRC_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x0B, RRC_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x0C, RRC_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x0D, RRC_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x0E, RRC_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x0F, RRC_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x10, RL_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x11, RL_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x12, RL_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x13, RL_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x14, RL_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x15, RL_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x16, RL_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x17, RL_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x18, RR_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x19, RR_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x1A, RR_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x1B, RR_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x1C, RR_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x1D, RR_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x1E, RR_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x1F, RR_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x20, SLA_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x21, SLA_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x22, SLA_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x23, SLA_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x24, SLA_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x25, SLA_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x26, SLA_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x27, SLA_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x28, SRA_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x29, SRA_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x2A, SRA_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x2B, SRA_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x2C, SRA_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x2D, SRA_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x2E, SRA_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x2F, SRA_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x30, SWAP_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x31, SWAP_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x32, SWAP_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x33, SWAP_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x34, SWAP_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x35, SWAP_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x36, SWAP_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x37, SWAP_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x38, SRL_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x39, SRL_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x3A, SRL_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x3B, SRL_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x3C, SRL_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x3D, SRL_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x3E, SRL_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x3F, SRL_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x40, BIT_0_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x41, BIT_0_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x42, BIT_0_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x43, BIT_0_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x44, BIT_0_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x45, BIT_0_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x46, BIT_0_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x47, BIT_0_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x48, BIT_1_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x49, BIT_1_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x4A, BIT_1_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x4B, BIT_1_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x4C, BIT_1_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x4D, BIT_1_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x4E, BIT_1_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x4F, BIT_1_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x50, BIT_2_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x51, BIT_2_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x52, BIT_2_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x53, BIT_2_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x54, BIT_2_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x55, BIT_2_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x56, BIT_2_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x57, BIT_2_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x58, BIT_3_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x59, BIT_3_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x5A, BIT_3_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x5B, BIT_3_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x5C, BIT_3_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x5D, BIT_3_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x5E, BIT_3_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x5F, BIT_3_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x60, BIT_4_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x61, BIT_4_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x62, BIT_4_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x63, BIT_4_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x64, BIT_4_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x65, BIT_4_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x66, BIT_4_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x67, BIT_4_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x68, BIT_5_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x69, BIT_5_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x6A, BIT_5_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x6B, BIT_5_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x6C, BIT_5_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x6D, BIT_5_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x6E, BIT_5_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x6F, BIT_5_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x70, BIT_6_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x71, BIT_6_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x72, BIT_6_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x73, BIT_6_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x74, BIT_6_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x75, BIT_6_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x76, BIT_6_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x77, BIT_6_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x78, BIT_7_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x79, BIT_7_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x7A, BIT_7_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x7B, BIT_7_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x7C, BIT_7_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x7D, BIT_7_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x7E, BIT_7_mHL, regs, "", 2, 12, 0);
    SET_OP(table, 0x7F, BIT_7_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x80, RES_0_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x81, RES_0_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x82, RES_0_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x83, RES_0_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x84, RES_0_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x85, RES_0_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x86, RES_0_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x87, RES_0_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x88, RES_1_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x89, RES_1_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x8A, RES_1_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x8B, RES_1_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x8C, RES_1_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x8D, RES_1_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x8E, RES_1_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x8F, RES_1_A, regs, "", 2, 8, 0);

    SET_OP(table, 0x90, RES_2_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x91, RES_2_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x92, RES_2_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x93, RES_2_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x94, RES_2_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x95, RES_2_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x96, RES_2_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x97, RES_2_A, regs, "", 2, 8, 0);
    SET_OP(table, 0x98, RES_3_B, regs, "", 2, 8, 0);
    SET_OP(table, 0x99, RES_3_C, regs, "", 2, 8, 0);
    SET_OP(table, 0x9A, RES_3_D, regs, "", 2, 8, 0);
    SET_OP(table, 0x9B, RES_3_E, regs, "", 2, 8, 0);
    SET_OP(table, 0x9C, RES_3_H, regs, "", 2, 8, 0);
    SET_OP(table, 0x9D, RES_3_L, regs, "", 2, 8, 0);
    SET_OP(table, 0x9E, RES_3_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0x9F, RES_3_A, regs, "", 2, 8, 0);

    SET_OP(table, 0xA0, RES_4_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xA1, RES_4_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xA2, RES_4_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xA3, RES_4_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xA4, RES_4_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xA5, RES_4_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xA6, RES_4_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xA7, RES_4_A, regs, "", 2, 8, 0);
    SET_OP(table, 0xA8, RES_5_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xA9, RES_5_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xAA, RES_5_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xAB, RES_5_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xAC, RES_5_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xAD, RES_5_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xAE, RES_5_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xAF, RES_5_A, regs, "", 2, 8, 0);

    SET_OP(table, 0xB0, RES_6_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xB1, RES_6_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xB2, RES_6_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xB3, RES_6_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xB4, RES_6_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xB5, RES_6_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xB6, RES_6_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xB7, RES_6_A, regs, "", 2, 8, 0);
    SET_OP(table, 0xB8, RES_7_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xB9, RES_7_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xBA, RES_7_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xBB, RES_7_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xBC, RES_7_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xBD, RES_7_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xBE, RES_7_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xBF, RES_7_A, regs, "", 2, 8, 0);

    SET_OP(table, 0xC0, SET_0_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xC1, SET_0_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xC2, SET_0_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xC3, SET_0_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xC4, SET_0_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xC5, SET_0_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xC6, SET_0_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xC7, SET_0_A, regs, "", 2, 8, 0);
    SET_OP(table, 0xC8, SET_1_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xC9, SET_1_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xCA, SET_1_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xCB, SET_1_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xCC, SET_1_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xCD, SET_1_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xCE, SET_1_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xCF, SET_1_A, regs, "", 2, 8, 0);

    SET_OP(table, 0xD0, SET_2_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xD1, SET_2_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xD2, SET_2_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xD3, SET_2_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xD4, SET_2_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xD5, SET_2_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xD6, SET_2_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xD7, SET_2_A, regs, "", 2, 8, 0);
    SET_OP(table, 0xD8, SET_3_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xD9, SET_3_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xDA, SET_3_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xDB, SET_3_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xDC, SET_3_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xDD, SET_3_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xDE, SET_3_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xDF, SET_3_A, regs, "", 2, 8, 0);

    SET_OP(table, 0xE0, SET_4_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xE1, SET_4_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xE2, SET_4_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xE3, SET_4_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xE4, SET_4_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xE5, SET_4_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xE6, SET_4_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xE7, SET_4_A, regs, "", 2, 8, 0);
    SET_OP(table, 0xE8, SET_5_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xE9, SET_5_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xEA, SET_5_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xEB, SET_5_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xEC, SET_5_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xED, SET_5_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xEE, SET_5_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xEF, SET_5_A, regs, "", 2, 8, 0);

    SET_OP(table, 0xF0, SET_6_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xF1, SET_6_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xF2, SET_6_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xF3, SET_6_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xF4, SET_6_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xF5, SET_6_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xF6, SET_6_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xF7, SET_6_A, regs, "", 2, 8, 0);
    SET_OP(table, 0xF8, SET_7_B, regs, "", 2, 8, 0);
    SET_OP(table, 0xF9, SET_7_C, regs, "", 2, 8, 0);
    SET_OP(table, 0xFA, SET_7_D, regs, "", 2, 8, 0);
    SET_OP(table, 0xFB, SET_7_E, regs, "", 2, 8, 0);
    SET_OP(table, 0xFC, SET_7_H, regs, "", 2, 8, 0);
    SET_OP(table, 0xFD, SET_7_L, regs, "", 2, 8, 0);
    SET_OP(table, 0xFE, SET_7_mHL, regs, "", 2, 16, 0);
    SET_OP(table, 0xFF, SET_7_A, regs, "", 2, 8, 0);
}

// void ExecuteOpcode(cpu_t* cpu, uint8_t opcode) {
//     if (cpu->IME_enable) {
//         cpu->IME = 1;
//         cpu->IME_enable = 0;
//     }
//     inst_t table[256];
//     InitOptable(table);
