/*
 Copyright 2013 Michael Pavone
 This file is part of BlastEm.
 BlastEm is free software distributed under the terms of the GNU General Public License version 3 or greater. See COPYING for full license text.
*/

#ifndef M68KINST_H_
#define M68KINST_H_

#include <stdint.h>

typedef struct {
	// ctern_node     *labels;
	uint8_t       *visited;
	// deferred_addr *deferred;
	uint32_t      address_mask;
	uint32_t      invalid_inst_addr_mask;
	uint32_t      visit_preshift;
} disasm_context;
typedef int (*format_label_fun)(char * dst, uint32_t address, disasm_context * context);

int format_label(char *dst, uint32_t address, disasm_context *context){
	return 0;
}

#ifdef M68030
#define M68020
#endif
#ifdef M68020
#define M68010
#endif

typedef enum {
	BIT_MOVEP_IMMED = 0,
	MOVE_BYTE,
	MOVE_LONG,
	MOVE_WORD,
	MISC,
	QUICK_ARITH_LOOP,
	BRANCH,
	MOVEQ,
	OR_DIV_SBCD,
	SUB_SUBX,
	A_LINE,
	CMP_XOR,
	AND_MUL_ABCD_EXG,
	ADD_ADDX,
	SHIFT_ROTATE,
	F_LINE
} m68k_optypes;

typedef enum {
	M68K_ABCD,
	M68K_ADD,
	M68K_ADDX,
	M68K_AND,
	M68K_ANDI_CCR,
	M68K_ANDI_SR,
	M68K_ASL,
	M68K_ASR,
	M68K_BCC,
	M68K_BCHG,
	M68K_BCLR,
	M68K_BSET,
	M68K_BSR,
	M68K_BTST,
	M68K_CHK,
	M68K_CLR,
	M68K_CMP,
	M68K_DBCC,
	M68K_DIVS,
	M68K_DIVU,
	M68K_EOR,
	M68K_EORI_CCR,
	M68K_EORI_SR,
	M68K_EXG,
	M68K_EXT,
	M68K_ILLEGAL,
	M68K_JMP,
	M68K_JSR,
	M68K_LEA,
	M68K_LINK,
	M68K_LSL,
	M68K_LSR,
	M68K_MOVE,
	M68K_MOVE_CCR,
	M68K_MOVE_FROM_SR,
	M68K_MOVE_SR,
	M68K_MOVE_USP,
	M68K_MOVEM,
	M68K_MOVEP,
	M68K_MULS,
	M68K_MULU,
	M68K_NBCD,
	M68K_NEG,
	M68K_NEGX,
	M68K_NOP,
	M68K_NOT,
	M68K_OR,
	M68K_ORI_CCR,
	M68K_ORI_SR,
	M68K_PEA,
	M68K_RESET,
	M68K_ROL,
	M68K_ROR,
	M68K_ROXL,
	M68K_ROXR,
	M68K_RTE,
	M68K_RTR,
	M68K_RTS,
	M68K_SBCD,
	M68K_SCC,
	M68K_STOP,
	M68K_SUB,
	M68K_SUBX,
	M68K_SWAP,
	M68K_TAS,
	M68K_TRAP,
	M68K_TRAPV,
	M68K_TST,
	M68K_UNLK,
	M68K_INVALID,
	M68K_A_LINE_TRAP,
	M68K_F_LINE_TRAP,
#ifdef M68010
	M68K_BKPT,
	M68K_MOVE_FROM_CCR,
	M68K_MOVEC,
	M68K_MOVES,
	M68K_RTD,
#endif
#ifdef M68020
	M68K_BFCHG,
	M68K_BFCLR,
	M68K_BFEXTS,
	M68K_BFEXTU,
	M68K_BFFFO,
	M68K_BFINS,
	M68K_BFSET,
	M68K_BFTST,
	M68K_CALLM,
	M68K_CAS,
	M68K_CAS2,
	M68K_CHK2,
	M68K_CMP2,
	M68K_CP_BCC,
	M68K_CP_DBCC,
	M68K_CP_GEN,
	M68K_CP_RESTORE,
	M68K_CP_SAVE,
	M68K_CP_SCC,
	M68K_CP_TRAPCC,
	M68K_DIVSL,
	M68K_DIVUL,
	M68K_EXTB,
	M68K_PACK,
	M68K_RTM,
	M68K_TRAPCC,
	M68K_UNPK,
#endif
} m68K_op;

typedef enum {
	VAR_NORMAL,
	VAR_QUICK,
	VAR_IMMEDIATE,
	VAR_BYTE,
	VAR_WORD,
	VAR_LONG
} m68K_variant;

typedef enum {
	OPSIZE_BYTE=0,
	OPSIZE_WORD,
	OPSIZE_LONG,
	OPSIZE_INVALID,
	OPSIZE_UNSIZED
} m68K_opsizes;

typedef enum {
//actual addressing mode field values
	MODE_REG = 0,
	MODE_AREG,
	MODE_AREG_INDIRECT,
	MODE_AREG_POSTINC,
	MODE_AREG_PREDEC,
	MODE_AREG_DISPLACE,
	MODE_AREG_INDEX_MEM, //bunch of relatively complicated modes
	MODE_PC_INDIRECT_ABS_IMMED, //Modes that use the program counter, an absolute address or immediate value
//expanded values
	MODE_AREG_INDEX_DISP8,
#ifdef M68020
	MODE_AREG_INDEX_BASE_DISP,
	MODE_AREG_PREINDEX,
	MODE_AREG_POSTINDEX,
	MODE_AREG_MEM_INDIRECT,
	MODE_AREG_BASE_DISP,
	MODE_INDEX_BASE_DISP,
	MODE_PREINDEX,
	MODE_POSTINDEX,
	MODE_MEM_INDIRECT,
	MODE_BASE_DISP,
#endif
	MODE_ABSOLUTE_SHORT,
	MODE_ABSOLUTE,
	MODE_PC_DISPLACE,
	MODE_PC_INDEX_DISP8,
#ifdef M68020
	MODE_PC_INDEX_BASE_DISP,
	MODE_PC_PREINDEX,
	MODE_PC_POSTINDEX,
	MODE_PC_MEM_INDIRECT,
	MODE_PC_BASE_DISP,
	MODE_ZPC_INDEX_BASE_DISP,
	MODE_ZPC_PREINDEX,
	MODE_ZPC_POSTINDEX,
	MODE_ZPC_MEM_INDIRECT,
	MODE_ZPC_BASE_DISP,
#endif
	MODE_IMMEDIATE,
	MODE_IMMEDIATE_WORD,//used to indicate an immediate operand that only uses a single extension word even for a long operation
	MODE_UNUSED
} m68k_addr_modes;
#ifdef M68020
#define M68K_FLAG_BITFIELD 0x80
#endif

typedef enum {
	COND_TRUE,
	COND_FALSE,
	COND_HIGH,
	COND_LOW_SAME,
	COND_CARRY_CLR,
	COND_CARRY_SET,
	COND_NOT_EQ,
	COND_EQ,
	COND_OVERF_CLR,
	COND_OVERF_SET,
	COND_PLUS,
	COND_MINUS,
	COND_GREATER_EQ,
	COND_LESS,
	COND_GREATER,
	COND_LESS_EQ
} m68K_condition;

#ifdef M68010
typedef enum {
	CR_SFC,
	CR_DFC,
#ifdef M68020
	CR_CACR,
#endif
	CR_USP,
	CR_VBR,
#ifdef M68020
	CR_CAAR,
	CR_MSP,
	CR_ISP
#endif
} m68k_control_reg;

#ifdef M68020
#define MAX_HIGH_CR 0x804
#define MAX_LOW_CR 0x002
#else
#define MAX_HIGH_CR 0x801
#define MAX_LOW_CR 0x001
#endif

#endif

typedef struct {
#ifdef M68020
	uint16_t bitfield;
#endif
	uint8_t  addr_mode;
	union {
		struct {
			uint8_t pri;
			uint8_t sec;
#ifdef M68020
			uint8_t scale;
			uint8_t disp_sizes;
#endif
			int32_t displacement;
#ifdef M68020
			int32_t outer_disp;
#endif
		} regs;
		uint32_t immed;
	} params;
} m68k_op_info;

typedef struct m68kinst {
	uint8_t op;
	uint8_t variant;
	union {
		uint8_t size;
		uint8_t cond;
	} extra;
	uint8_t bytes;
	uint32_t address;
	m68k_op_info src;
	m68k_op_info dst;
} m68kinst;

typedef enum {
	VECTOR_RESET_STACK,
	VECTOR_RESET_PC,
	VECTOR_ACCESS_FAULT,
	VECTOR_ADDRESS_ERROR,
	VECTOR_ILLEGAL_INST,
	VECTOR_INT_DIV_ZERO,
	VECTOR_CHK,
	VECTOR_TRAPV,
	VECTOR_PRIV_VIOLATION,
	VECTOR_TRACE,
	VECTOR_LINE_1010,
	VECTOR_LINE_1111,
	VECTOR_COPROC_VIOLATION=13,
	VECTOR_FORMAT_ERROR,
	VECTOR_UNINIT_INTERRUPT,
	VECTOR_SPURIOUS_INTERRUPT=24,
	VECTOR_INT_1,
	VECTOR_INT_2,
	VECTOR_INT_3,
	VECTOR_INT_4,
	VECTOR_INT_5,
	VECTOR_INT_6,
	VECTOR_INT_7,
	VECTOR_TRAP_0,
	VECTOR_TRAP_1,
	VECTOR_TRAP_2,
	VECTOR_TRAP_3,
	VECTOR_TRAP_4,
	VECTOR_TRAP_5,
	VECTOR_TRAP_6,
	VECTOR_TRAP_7,
	VECTOR_TRAP_8,
	VECTOR_TRAP_9,
	VECTOR_TRAP_10,
	VECTOR_TRAP_11,
	VECTOR_TRAP_12,
	VECTOR_TRAP_13,
	VECTOR_TRAP_14,
	VECTOR_TRAP_15,
	VECTOR_USER0 = 64
} m68k_vector;

typedef uint16_t (*m68k_fetch_fun)(uint32_t address, void *data);

uint32_t m68k_decode(m68k_fetch_fun fetch, void *data, m68kinst * dst, uint32_t address);
uint32_t m68k_branch_target(m68kinst * inst, uint32_t *dregs, uint32_t *aregs);
uint8_t m68k_is_branch(m68kinst * inst);
uint8_t m68k_is_noncall_branch(m68kinst * inst);
int m68k_disasm(m68kinst * decoded, char * dst);

#endif


/*
 Copyright 2013 Michael Pavone
 This file is part of BlastEm.
 BlastEm is free software distributed under the terms of the GNU General Public License version 3 or greater. See COPYING for full license text.
*/
// #include "68kinst.h"
// #include "disasm.h"
#include <string.h>
#include <stdio.h>

uint32_t sign_extend16(uint32_t val)
{
	return (val & 0x8000) ? val | 0xFFFF0000 : val;
}

uint32_t sign_extend8(uint32_t val)
{
	return (val & 0x80) ? val | 0xFFFFFF00 : val;
}

#define INVALID_ADDRESS 0xFFFFFFFF

uint32_t m68k_decode_op_ex(uint16_t opcode, uint32_t address, m68k_fetch_fun fetch, void *data, uint8_t mode, uint8_t reg, uint8_t size, m68k_op_info *dst)
{
	uint16_t ext, tmp;
	dst->addr_mode = mode;
	switch(mode)
	{
	case MODE_REG:
	case MODE_AREG:
	case MODE_AREG_INDIRECT:
	case MODE_AREG_POSTINC:
	case MODE_AREG_PREDEC:
		dst->params.regs.pri = reg;
		break;
	case MODE_AREG_DISPLACE:
		ext = fetch(address, data);
		address += 2;
		dst->params.regs.pri = reg;
		dst->params.regs.displacement = sign_extend16(ext);
		break;
	case MODE_AREG_INDEX_MEM:
		dst->params.regs.pri = reg;
		ext = fetch(address, data);
		address += 2;
		dst->params.regs.sec = ext >> 11;//includes areg/dreg bit, reg num and word/long bit
#ifdef M68020
		dst->params.regs.scale = ext >> 9 & 3;
		if (ext & 0x100)
		{
			dst->params.regs.disp_sizes = ext >> 4 & 3;
			switch (dst->params.regs.disp_sizes)
			{
			case 0:
				//reserved
				return INVALID_ADDRESS;
			case 1:
				dst->params.regs.displacement = 0;
				break;
			case 2:
				dst->params.regs.displacement = sign_extend16(fetch(address, data));
				address += 2;
				break;
			case 3:
				tmp = fetch(address, data);
				address += 2;
				dst->params.regs.displacement = tmp << 16 | fetch(address, data);
				address += 2;
				break;
			}
			if (ext & 0x3)
			{
				//memory indirect
				switch (ext & 0xC4)
				{
				case 0x00:
					dst->addr_mode = MODE_AREG_PREINDEX;
					break;
				case 0x04:
					dst->addr_mode = MODE_AREG_POSTINDEX;
					break;
				case 0x40:
					dst->addr_mode = MODE_AREG_MEM_INDIRECT;
					break;
				case 0x80:
					dst->addr_mode = MODE_PREINDEX;
					break;
				case 0x84:
					dst->addr_mode = MODE_POSTINDEX;
					break;
				case 0xC0:
					dst->addr_mode = MODE_MEM_INDIRECT;
					break;
				}
				dst->params.regs.disp_sizes |= ext << 4 & 0x30;
				switch (ext & 0x3)
				{
				case 0:
					//reserved
					return INVALID_ADDRESS;
				case 1:
					dst->params.regs.outer_disp = 0;
					break;
				case 2:
					dst->params.regs.outer_disp = sign_extend16(fetch(address, data));
					address += 2;
					break;
				case 3:
					tmp = fetch(address, data);
					address += 2;
					dst->params.regs.outer_disp = tmp << 16 | fetch(address, data);
					address += 2;
					break;
				}
			} else {
				switch (ext >> 6 & 3)
				{
				case 0:
					dst->addr_mode = MODE_AREG_INDEX_BASE_DISP;
					break;
				case 1:
					dst->addr_mode = MODE_AREG_BASE_DISP;
					break;
				case 2:
					dst->addr_mode = MODE_INDEX_BASE_DISP;
					break;
				case 3:
					dst->addr_mode = MODE_BASE_DISP;
					break;
				}
			}
		} else {
#endif
			dst->addr_mode = MODE_AREG_INDEX_DISP8;
			dst->params.regs.displacement = sign_extend8(ext&0xFF);
#ifdef M68020
		}
#endif
		break;
	case MODE_PC_INDIRECT_ABS_IMMED:
		switch(reg)
		{
		case 0:
			dst->addr_mode = MODE_ABSOLUTE_SHORT;
			ext = fetch(address, data);
			address += 2;
			dst->params.immed = sign_extend16(ext);
			break;
		case 1:
			dst->addr_mode = MODE_ABSOLUTE;
			ext = fetch(address, data);
			address += 2;
			dst->params.immed = ext << 16 | fetch(address, data);
			address += 2;
			break;
		case 3:
			ext = fetch(address, data);
			address += 2;
			dst->params.regs.sec = ext >> 11;//includes areg/dreg bit, reg num and word/long bit
#ifdef M68020
			dst->params.regs.scale = ext >> 9 & 3;
			if (ext & 0x100)
			{
				dst->params.regs.disp_sizes = ext >> 4 & 3;
				switch (dst->params.regs.disp_sizes)
				{
				case 0:
					//reserved
					return INVALID_ADDRESS;
				case 1:
					dst->params.regs.displacement = 0;
					break;
				case 2:
					dst->params.regs.displacement = sign_extend16(fetch(address, data));
					address += 2;
					break;
				case 3:
					tmp = *(cur++);
					dst->params.regs.displacement = tmp << 16 | fetch(address, data);
					address += 2;
					break;
				}
				if (ext & 0x3)
				{
					//memory indirect
					switch (ext & 0xC4)
					{
					case 0x00:
						dst->addr_mode = MODE_PC_PREINDEX;
						break;
					case 0x04:
						dst->addr_mode = MODE_PC_POSTINDEX;
						break;
					case 0x40:
						dst->addr_mode = MODE_PC_MEM_INDIRECT;
						break;
					case 0x80:
						dst->addr_mode = MODE_ZPC_PREINDEX;
						break;
					case 0x84:
						dst->addr_mode = MODE_ZPC_POSTINDEX;
						break;
					case 0xC0:
						dst->addr_mode = MODE_ZPC_MEM_INDIRECT;
						break;
					}
					dst->params.regs.disp_sizes |= ext << 4 & 0x30;
					switch (ext & 0x3)
					{
					case 0:
						//reserved
						return INVALID_ADDRESS;
					case 1:
						dst->params.regs.outer_disp = 0;
						break;
					case 2:
						dst->params.regs.outer_disp = sign_extend16(fetch(address, data));
						address += 2;
						break;
					case 3:
						tmp = fetch(address, data);
						address += 2;
						dst->params.regs.outer_disp = tmp << 16 | fetch(address, data);
						address += 2;
						break;
					}
				} else {
					switch (ext >> 6 & 3)
					{
					case 0:
						dst->addr_mode = MODE_PC_INDEX_BASE_DISP;
						break;
					case 1:
						dst->addr_mode = MODE_PC_BASE_DISP;
						break;
					case 2:
						dst->addr_mode = MODE_ZPC_INDEX_BASE_DISP;
						break;
					case 3:
						dst->addr_mode = MODE_ZPC_BASE_DISP;
						break;
					}
				}
			} else {
#endif
				dst->addr_mode = MODE_PC_INDEX_DISP8;
				dst->params.regs.displacement = sign_extend8(ext&0xFF);
#ifdef M68020
			}
#endif
			break;
		case 2:
			dst->addr_mode = MODE_PC_DISPLACE;
			ext = fetch(address, data);
			address += 2;
			dst->params.regs.displacement = sign_extend16(ext);
			break;
		case 4:
			dst->addr_mode = MODE_IMMEDIATE;
			ext = fetch(address, data);
			address += 2;
			switch (size)
			{
			case OPSIZE_BYTE:
				dst->params.immed = ext & 0xFF;
				break;
			case OPSIZE_WORD:
				dst->params.immed = ext;
				break;
			case OPSIZE_LONG:
				dst->params.immed = ext << 16 | fetch(address, data);
				address += 2;
				break;
			}
			break;
		default:
			return INVALID_ADDRESS;
		}
		break;
	}
	return address;
}

uint8_t m68k_valid_immed_dst(m68k_op_info *dst)
{
	if (dst->addr_mode == MODE_AREG || dst->addr_mode == MODE_IMMEDIATE) {
		return 0;
	}
	return 1;
}

uint8_t m68k_valid_immed_limited_dst(m68k_op_info *dst)
{
	if (dst->addr_mode == MODE_AREG || dst->addr_mode > MODE_ABSOLUTE) {
		return 0;
	}
	return 1;
}

uint8_t m68k_valid_full_arith_dst(m68k_op_info *dst)
{
	if (dst->addr_mode < MODE_AREG_INDIRECT || dst->addr_mode > MODE_ABSOLUTE) {
		return 0;
	}
	return 1;
}

uint8_t m68k_valid_movem_dst(m68k_op_info *dst)
{
	if (dst->addr_mode == MODE_REG || dst->addr_mode == MODE_AREG_POSTINC) {
		return 0;
	}
	return m68k_valid_immed_limited_dst(dst);
}

uint32_t m68k_decode_op(uint16_t opcode, uint32_t address, m68k_fetch_fun fetch, void *data, uint8_t size, m68k_op_info *dst)
{
	uint8_t mode = (opcode >> 3) & 0x7;
	uint8_t reg = opcode & 0x7;
	return m68k_decode_op_ex(opcode, address, fetch, data, mode, reg, size, dst);
}

void m68k_decode_cond(uint16_t op, m68kinst * decoded)
{
	decoded->extra.cond = (op >> 0x8) & 0xF;
}

uint8_t m68k_reg_quick_field(uint16_t op)
{
	return (op >> 9) & 0x7;
}

uint32_t m68k_decode(m68k_fetch_fun fetch, void *data, m68kinst * decoded, uint32_t address)
{
	uint32_t start_address = address;
	uint16_t opcode = fetch(address, data);
	address += 2;
	uint8_t optype = opcode >> 12;
	uint8_t size;
	uint8_t reg;
	uint8_t opmode;
	uint32_t immed;
	decoded->op = M68K_INVALID;
	decoded->src.addr_mode = decoded->dst.addr_mode = MODE_UNUSED;
	decoded->variant = VAR_NORMAL;
	decoded->address = start_address;
	switch(optype)
	{
	case BIT_MOVEP_IMMED:
		if ((opcode & 0x138) == 0x108) {
			//MOVEP
			decoded->op = M68K_MOVEP;
			decoded->extra.size = opcode & 0x40 ? OPSIZE_LONG : OPSIZE_WORD;
			if (opcode & 0x80) {
				//memory dest
				decoded->src.addr_mode = MODE_REG;
				decoded->src.params.regs.pri = m68k_reg_quick_field(opcode);
				decoded->dst.addr_mode = MODE_AREG_DISPLACE;
				decoded->dst.params.regs.pri = opcode & 0x7;
				decoded->dst.params.regs.displacement = fetch(address, data);
				address += 2;
			} else {
				//memory source
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				decoded->src.addr_mode = MODE_AREG_DISPLACE;
				decoded->src.params.regs.pri = opcode & 0x7;
				decoded->src.params.regs.displacement = fetch(address, data);
				address += 2;
			}
		} else if (opcode & 0x100) {
			//BTST, BCHG, BCLR, BSET
			switch ((opcode >> 6) & 0x3)
			{
			case 0:
				decoded->op = M68K_BTST;
				break;
			case 1:
				decoded->op = M68K_BCHG;
				break;
			case 2:
				decoded->op = M68K_BCLR;
				break;
			case 3:
				decoded->op = M68K_BSET;
				break;
			}
			decoded->src.addr_mode = MODE_REG;
			decoded->src.params.regs.pri = m68k_reg_quick_field(opcode);
			decoded->extra.size = OPSIZE_BYTE;
			address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->dst));
			if (
				address == INVALID_ADDRESS || decoded->dst.addr_mode == MODE_AREG
				|| (decoded->op != M68K_BTST && !m68k_valid_immed_limited_dst(&decoded->dst))
			) {
				decoded->op = M68K_INVALID;
				break;
			}
			if (decoded->dst.addr_mode == MODE_REG) {
				decoded->extra.size = OPSIZE_LONG;
			}
		} else if ((opcode & 0xF00) == 0x800) {
			//BTST, BCHG, BCLR, BSET
			switch ((opcode >> 6) & 0x3)
			{
			case 0:
				decoded->op = M68K_BTST;
				break;
			case 1:
				decoded->op = M68K_BCHG;
				break;
			case 2:
				decoded->op = M68K_BCLR;
				break;
			case 3:
				decoded->op = M68K_BSET;
				break;
			}
			opmode = (opcode >> 3) & 0x7;
			reg = opcode & 0x7;
			decoded->src.addr_mode = MODE_IMMEDIATE_WORD;
			decoded->src.params.immed = fetch(address, data) & 0xFF;
			address += 2;
			decoded->extra.size = OPSIZE_BYTE;
			address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, decoded->extra.size, &(decoded->dst));
			if (
				address == INVALID_ADDRESS || !m68k_valid_immed_dst(&decoded->dst)
				|| (decoded->op != M68K_BTST && !m68k_valid_immed_limited_dst(&decoded->dst))
			) {
				decoded->op = M68K_INVALID;
				break;
			}
			if (decoded->dst.addr_mode == MODE_REG) {
				decoded->extra.size = OPSIZE_LONG;
			}
		} else if ((opcode & 0xC0) == 0xC0) {
#ifdef M68020
			//CMP2, CHK2, CAS, CAS2, RTM, CALLM
#endif
		} else {
			switch ((opcode >> 9) & 0x7)
			{
			case 0:
				if ((opcode & 0xFF) == 0x3C) {
					decoded->op = M68K_ORI_CCR;
					decoded->extra.size = OPSIZE_BYTE;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->src.params.immed = fetch(address, data) & 0xFF;
					address += 2;
				} else if((opcode & 0xFF) == 0x7C) {
					decoded->op = M68K_ORI_SR;
					decoded->extra.size = OPSIZE_WORD;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->src.params.immed = fetch(address, data);
					address += 2;
				} else {
					decoded->op = M68K_OR;
					decoded->variant = VAR_IMMEDIATE;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->extra.size = size = (opcode >> 6) & 3;
					reg = opcode & 0x7;
					opmode = (opcode >> 3) & 0x7;
					switch (size)
					{
					case OPSIZE_BYTE:
						decoded->src.params.immed = fetch(address, data) & 0xFF;
						address += 2;
						break;
					case OPSIZE_WORD:
						decoded->src.params.immed = fetch(address, data);
						address += 2;
						break;
					case OPSIZE_LONG:
						immed = fetch(address, data);
						address += 2;
						decoded->src.params.immed = immed << 16 | fetch(address, data);
						address += 2;
						break;
					}
					address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, size, &(decoded->dst));
					if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&(decoded->dst))) {
						decoded->op = M68K_INVALID;
						break;
					}
				}
				break;
			case 1:
				//ANDI, ANDI to CCR, ANDI to SR
				if ((opcode & 0xFF) == 0x3C) {
					decoded->op = M68K_ANDI_CCR;
					decoded->extra.size = OPSIZE_BYTE;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->src.params.immed = fetch(address, data) & 0xFF;
					address += 2;
				} else if((opcode & 0xFF) == 0x7C) {
					decoded->op = M68K_ANDI_SR;
					decoded->extra.size = OPSIZE_WORD;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->src.params.immed = fetch(address, data);
					address += 2;
				} else {
					decoded->op = M68K_AND;
					decoded->variant = VAR_IMMEDIATE;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->extra.size = size = (opcode >> 6) & 3;
					reg = opcode & 0x7;
					opmode = (opcode >> 3) & 0x7;
					switch (size)
					{
					case OPSIZE_BYTE:
						decoded->src.params.immed = fetch(address, data) & 0xFF;
						address += 2;
						break;
					case OPSIZE_WORD:
						decoded->src.params.immed = fetch(address, data);
						address += 2;
						break;
					case OPSIZE_LONG:
						immed = fetch(address, data);
						address += 2;
						decoded->src.params.immed = immed << 16 | fetch(address, data);
						address += 2;
						break;
					}
					address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, size, &(decoded->dst));
					if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&(decoded->dst))) {
						decoded->op = M68K_INVALID;
						break;
					}
				}
				break;
			case 2:
				decoded->op = M68K_SUB;
				decoded->variant = VAR_IMMEDIATE;
				decoded->src.addr_mode = MODE_IMMEDIATE;
				decoded->extra.size = size = (opcode >> 6) & 3;
				reg = opcode & 0x7;
				opmode = (opcode >> 3) & 0x7;
				switch (size)
				{
				case OPSIZE_BYTE:
					decoded->src.params.immed = fetch(address, data) & 0xFF;
					address += 2;
					break;
				case OPSIZE_WORD:
					decoded->src.params.immed = fetch(address, data);
					address += 2;
					break;
				case OPSIZE_LONG:
					immed = fetch(address, data);
					address += 2;
					decoded->src.params.immed = immed << 16 | fetch(address, data);
					address += 2;
					break;
				}
				address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, size, &(decoded->dst));
				if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&(decoded->dst))) {
					decoded->op = M68K_INVALID;
					break;
				}
				break;
			case 3:
				decoded->op = M68K_ADD;
				decoded->variant = VAR_IMMEDIATE;
				decoded->src.addr_mode = MODE_IMMEDIATE;
				decoded->extra.size = size = (opcode >> 6) & 3;
				reg = opcode & 0x7;
				opmode = (opcode >> 3) & 0x7;
				switch (size)
				{
				case OPSIZE_BYTE:
					decoded->src.params.immed = fetch(address, data) & 0xFF;
					address += 2;
					break;
				case OPSIZE_WORD:
					decoded->src.params.immed = fetch(address, data);
					address += 2;
					break;
				case OPSIZE_LONG:
					immed = fetch(address, data);
					address += 2;
					decoded->src.params.immed = immed << 16 | fetch(address, data);
					address += 2;
					break;
				}
				address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, size, &(decoded->dst));
				if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&(decoded->dst))) {
					decoded->op = M68K_INVALID;
					break;
				}
				break;
			case 4:
				//BTST, BCHG, BCLR, BSET
				//Seems like this should be unnecessary since bit instructions are explicitly handled above
				//Possible this is redundant or the case above is overly restrictive
				//TODO: Investigate whether this can be removed
				switch ((opcode >> 6) & 0x3)
				{
				case 0:
					decoded->op = M68K_BTST;
					break;
				case 1:
					decoded->op = M68K_BCHG;
					break;
				case 2:
					decoded->op = M68K_BCLR;
					break;
				case 3:
					decoded->op = M68K_BSET;
					break;
				}
				decoded->src.addr_mode = MODE_IMMEDIATE_WORD;
				decoded->src.params.immed = fetch(address, data) & 0xFF;
				address += 2;
				address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_BYTE, &(decoded->dst));
				if (
					address == INVALID_ADDRESS || !m68k_valid_immed_dst(&decoded->dst)
					|| (decoded->op != M68K_BTST && !m68k_valid_immed_limited_dst(&decoded->dst))
				) {
					decoded->op = M68K_INVALID;
					break;
				}
				break;
			case 5:
				//EORI, EORI to CCR, EORI to SR
				if ((opcode & 0xFF) == 0x3C) {
					decoded->op = M68K_EORI_CCR;
					decoded->extra.size = OPSIZE_BYTE;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->src.params.immed = fetch(address, data) & 0xFF;
					address += 2;
				} else if((opcode & 0xFF) == 0x7C) {
					decoded->op = M68K_EORI_SR;
					decoded->extra.size = OPSIZE_WORD;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->src.params.immed = fetch(address, data);
					address += 2;
				} else {
					decoded->op = M68K_EOR;
					decoded->variant = VAR_IMMEDIATE;
					decoded->src.addr_mode = MODE_IMMEDIATE;
					decoded->extra.size = size = (opcode >> 6) & 3;
					reg = opcode & 0x7;
					opmode = (opcode >> 3) & 0x7;
					switch (size)
					{
					case OPSIZE_BYTE:
						decoded->src.params.immed = fetch(address, data) & 0xFF;
						address += 2;
						break;
					case OPSIZE_WORD:
						decoded->src.params.immed = fetch(address, data);
						address += 2;
						break;
					case OPSIZE_LONG:
						immed = fetch(address, data);
						address += 2;
						decoded->src.params.immed = immed << 16 | fetch(address, data);
						address += 2;
						break;
					}
					address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, size, &(decoded->dst));
					if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&(decoded->dst))) {
						decoded->op = M68K_INVALID;
						break;
					}
				}
				break;
			case 6:
				decoded->op = M68K_CMP;
				decoded->variant = VAR_IMMEDIATE;
				decoded->extra.size = (opcode >> 6) & 0x3;
				decoded->src.addr_mode = MODE_IMMEDIATE;
				reg = opcode & 0x7;
				opmode = (opcode >> 3) & 0x7;
				switch (decoded->extra.size)
				{
				case OPSIZE_BYTE:
					decoded->src.params.immed = fetch(address, data) & 0xFF;
					address += 2;
					break;
				case OPSIZE_WORD:
					decoded->src.params.immed = fetch(address, data);
					address += 2;
					break;
				case OPSIZE_LONG:
					immed = fetch(address, data);
					address += 2;
					decoded->src.params.immed = (immed << 16) | fetch(address, data);
					address += 2;
					break;
				}
				address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, decoded->extra.size, &(decoded->dst));
				if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&(decoded->dst))) {
					decoded->op = M68K_INVALID;
					break;
				}
				break;
			case 7:
#ifdef M68010
				decoded->op = M68K_MOVES;
				decoded->extra.size = opcode >> 6 & 0x3;
				immed = fetch(address, data);
				address += 2;
				reg = immed  >> 12 & 0x7;
				opmode = immed & 0x8000 ? MODE_AREG : MODE_REG;
				if (immed & 0x800) {
					decoded->src.addr_mode = opmode;
					decoded->src.params.regs.pri = reg;
					address = m68k_decode_op_ex(opcode, address, fetch, data, *start >> 3 & 0x7, *start & 0x7, decoded->extra.size, &(decoded->dst));
				} else {
					address = m68k_decode_op_ex(opcode, address, fetch, data, *start >> 3 & 0x7, *start & 0x7, decoded->extra.size, &(decoded->src));
					decoded->dst.addr_mode = opmode;
					decoded->dst.params.regs.pri = reg;
				}
#endif
				break;
			}
		}
		break;
	case MOVE_BYTE:
	case MOVE_LONG:
	case MOVE_WORD:
		decoded->op = M68K_MOVE;
		decoded->extra.size = optype == MOVE_BYTE ? OPSIZE_BYTE : (optype == MOVE_WORD ? OPSIZE_WORD : OPSIZE_LONG);
		opmode = (opcode >> 6) & 0x7;
		reg = m68k_reg_quick_field(opcode);
		address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
		if (address == INVALID_ADDRESS || (decoded->src.addr_mode == MODE_AREG && optype == MOVE_BYTE)) {
			decoded->op = M68K_INVALID;
			break;
		}
		address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, decoded->extra.size, &(decoded->dst));
		if (address == INVALID_ADDRESS || decoded->dst.addr_mode > MODE_ABSOLUTE || (decoded->dst.addr_mode == MODE_AREG && optype == MOVE_BYTE)) {
			decoded->op = M68K_INVALID;
			break;
		}
		break;
	case MISC:

		if ((opcode & 0x1C0) == 0x1C0) {
			decoded->op = M68K_LEA;
			decoded->extra.size = OPSIZE_LONG;
			decoded->dst.addr_mode = MODE_AREG;
			decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
			address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
			if (
				address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_REG || decoded->src.addr_mode == MODE_AREG
				|| decoded->src.addr_mode == MODE_AREG_POSTINC || decoded->src.addr_mode == MODE_AREG_PREDEC
				|| decoded->src.addr_mode == MODE_IMMEDIATE
			) {
				decoded->op = M68K_INVALID;
				break;
			}
		} else {
			if (opcode & 0x100) {
				decoded->op = M68K_CHK;
				if ((opcode & 0x180) == 0x180) {
					decoded->extra.size = OPSIZE_WORD;
				} else {
					//only on M68020+
#ifdef M68020
					decoded->extra.size = OPSIZE_LONG;
#else
					decoded->op = M68K_INVALID;
					break;
#endif
				}
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
			} else {
				opmode = (opcode >> 3) & 0x7;
				if ((opcode & 0xB80) == 0x880 && opmode != MODE_REG && opmode != MODE_AREG) {
					//TODO: Check for invalid modes that are dependent on direction
					decoded->op = M68K_MOVEM;
					decoded->extra.size = opcode & 0x40 ? OPSIZE_LONG : OPSIZE_WORD;
					reg = opcode & 0x7;
					if(opcode & 0x400) {
						decoded->dst.addr_mode = MODE_REG;
						decoded->dst.params.immed = fetch(address, data);
						address += 2;
						address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, decoded->extra.size, &(decoded->src));
						if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG_PREDEC || decoded->src.addr_mode == MODE_IMMEDIATE) {
							decoded->op = M68K_INVALID;
							break;
						}
						if (decoded->src.addr_mode == MODE_PC_DISPLACE || decoded->src.addr_mode == MODE_PC_INDEX_DISP8) {
							//adjust displacement to account for extra instruction word
							decoded->src.params.regs.displacement += 2;
						}
					} else {
						decoded->src.addr_mode = MODE_REG;
						decoded->src.params.immed = fetch(address, data);
						address += 2;
						address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, decoded->extra.size, &(decoded->dst));
						if (address == INVALID_ADDRESS || !m68k_valid_movem_dst(&decoded->dst)) {
							decoded->op = M68K_INVALID;
							break;
						}
					}
				} else {
					optype = (opcode >> 9) & 0x7;
					size = (opcode >> 6) & 0x3;
					switch(optype)
					{
					case 0:
						//Move from SR or NEGX
						if (size == OPSIZE_INVALID) {
							decoded->op = M68K_MOVE_FROM_SR;
							size = OPSIZE_WORD;
						} else {
							decoded->op = M68K_NEGX;
						}
						decoded->extra.size = size;
						address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
						if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
							decoded->op = M68K_INVALID;
							break;
						}
						break;
					case 1:
						//MOVE from CCR or CLR
						if (size == OPSIZE_INVALID) {
#ifdef M68010
							decoded->op = M68K_MOVE_FROM_CCR;
							size = OPSIZE_WORD;
#else
							break;
#endif
						} else {
							decoded->op = M68K_CLR;
						}
						decoded->extra.size = size;
						address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
						if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
							decoded->op = M68K_INVALID;
							break;
						}
						break;
					case 2:
						//MOVE to CCR or NEG
						if (size == OPSIZE_INVALID) {
							decoded->op = M68K_MOVE_CCR;
							size = OPSIZE_WORD;
							address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->src));
							if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
								decoded->op = M68K_INVALID;
								break;
							}
						} else {
							decoded->op = M68K_NEG;
							address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
							if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
								decoded->op = M68K_INVALID;
								break;
							}
						}
						decoded->extra.size = size;
						break;
					case 3:
						//MOVE to SR or NOT
						if (size == OPSIZE_INVALID) {
							decoded->op = M68K_MOVE_SR;
							size = OPSIZE_WORD;
							address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->src));
							if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
								decoded->op = M68K_INVALID;
								break;
							}
						} else {
							decoded->op = M68K_NOT;
							address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
							if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
								decoded->op = M68K_INVALID;
								break;
							}
						}
						decoded->extra.size = size;
						break;
					case 4:
						//EXT, EXTB, LINK.l, NBCD, SWAP, BKPT, PEA
						switch((opcode >> 3) & 0x3F)
						{
						case 1:
#ifdef M68020
							decoded->op = M68K_LINK;
							decoded->extra.size = OPSIZE_LONG;
							reg = opcode & 0x7;
							immed = fetch(address, data) << 16;
							address += 2;
							immed |= fetch(address, data);
							address += 2;
#endif
							break;
						case 8:
							decoded->op = M68K_SWAP;
							decoded->src.addr_mode = MODE_REG;
							decoded->src.params.regs.pri = opcode & 0x7;
							decoded->extra.size = OPSIZE_WORD;
							break;
						case 9:
#ifdef M68010
							decoded->op = M68K_BKPT;
							decoded->src.addr_mode = MODE_IMMEDIATE;
							decoded->extra.size = OPSIZE_UNSIZED;
							decoded->src.params.immed = opcode & 0x7;
#endif
							break;
						case 0x10:
							decoded->op = M68K_EXT;
							decoded->dst.addr_mode = MODE_REG;
							decoded->dst.params.regs.pri = opcode & 0x7;
							decoded->extra.size = OPSIZE_WORD;
							break;
						case 0x18:
							decoded->op = M68K_EXT;
							decoded->dst.addr_mode = MODE_REG;
							decoded->dst.params.regs.pri = opcode & 0x7;
							decoded->extra.size = OPSIZE_LONG;
							break;
						case 0x38:
#ifdef M68020
#endif
							break;
						default:
							if (!(opcode & 0x1C0)) {
								decoded->op = M68K_NBCD;
								decoded->extra.size = OPSIZE_BYTE;
								address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_BYTE, &(decoded->dst));
								if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
									decoded->op = M68K_INVALID;
									break;
								}
							} else if((opcode & 0x1C0) == 0x40) {
								decoded->op = M68K_PEA;
								decoded->extra.size = OPSIZE_LONG;
								address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_LONG, &(decoded->src));
								if (
									address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_REG || decoded->src.addr_mode == MODE_AREG
									|| decoded->src.addr_mode == MODE_AREG_POSTINC || decoded->src.addr_mode == MODE_AREG_PREDEC
									|| decoded->src.addr_mode == MODE_IMMEDIATE
								) {
									decoded->op = M68K_INVALID;
									break;
								}
							}
						}
						break;
					case 5:
						//BGND, ILLEGAL, TAS, TST
						optype = opcode & 0xFF;
						if (optype == 0xFA) {
							//BGND - CPU32 only
						} else if (optype == 0xFC) {
							decoded->op = M68K_ILLEGAL;
							decoded->extra.size = OPSIZE_UNSIZED;
						} else {
							if (size == OPSIZE_INVALID) {
								decoded->op = M68K_TAS;
								decoded->extra.size = OPSIZE_BYTE;
								address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->dst));
								if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
									decoded->op = M68K_INVALID;
									break;
								}
							} else {
								decoded->op = M68K_TST;
								decoded->extra.size = size;
								address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
								if (address == INVALID_ADDRESS) {
									decoded->op = M68K_INVALID;
									break;
								}
#ifndef M68020
								if (!m68k_valid_immed_limited_dst(&decoded->src)) {
									decoded->op = M68K_INVALID;
									break;
								}
#endif
							}
						}
						break;
					case 6:
						//MULU, MULS, DIVU, DIVUL, DIVS, DIVSL
#ifdef M68020
						//TODO: Implement these for 68020+ support
#endif
						break;
					case 7:
						//TRAP, LINK.w, UNLNK, MOVE USP, RESET, NOP, STOP, RTE, RTD, RTS, TRAPV, RTR, MOVEC, JSR, JMP
						if (opcode & 0x80) {
							//JSR, JMP
							if (opcode & 0x40) {
								decoded->op = M68K_JMP;
							} else {
								decoded->op = M68K_JSR;
							}
							decoded->extra.size = OPSIZE_UNSIZED;
							address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_UNSIZED, &(decoded->src));
							if (
								address == INVALID_ADDRESS
								|| (decoded->src.addr_mode < MODE_AREG_DISPLACE && decoded->src.addr_mode != MODE_AREG_INDIRECT)
								|| decoded->src.addr_mode == MODE_IMMEDIATE
							) {
								decoded->op = M68K_INVALID;
								break;
							}
						} else {
							//it would appear bit 6 needs to be set for it to be a valid instruction here
							if (!(opcode & 0x40)) {
								decoded->op = M68K_INVALID;
								break;
							}
							switch((opcode >> 3) & 0x7)
							{
							case 0:
							case 1:
								//TRAP
								decoded->op = M68K_TRAP;
								decoded->extra.size = OPSIZE_UNSIZED;
								decoded->src.addr_mode = MODE_IMMEDIATE;
								decoded->src.params.immed = opcode & 0xF;
								break;
							case 2:
								//LINK.w
								decoded->op = M68K_LINK;
								decoded->extra.size = OPSIZE_WORD;
								decoded->src.addr_mode = MODE_AREG;
								decoded->src.params.regs.pri = opcode & 0x7;
								decoded->dst.addr_mode = MODE_IMMEDIATE;
								decoded->dst.params.immed = sign_extend16(fetch(address, data));
								address += 2;
								break;
							case 3:
								//UNLK
								decoded->op = M68K_UNLK;
								decoded->extra.size = OPSIZE_UNSIZED;
								decoded->dst.addr_mode = MODE_AREG;
								decoded->dst.params.regs.pri = opcode & 0x7;
								break;
							case 4:
							case 5:
								//MOVE USP
								decoded->op = M68K_MOVE_USP;
								if (opcode & 0x8) {
									decoded->dst.addr_mode = MODE_AREG;
									decoded->dst.params.regs.pri = opcode & 0x7;
								} else {
									decoded->src.addr_mode = MODE_AREG;
									decoded->src.params.regs.pri = opcode & 0x7;
								}
								break;
							case 6:
								decoded->extra.size = OPSIZE_UNSIZED;
								switch(opcode & 0x7)
								{
								case 0:
									decoded->op = M68K_RESET;
									break;
								case 1:
									decoded->op = M68K_NOP;
									break;
								case 2:
									decoded->op = M68K_STOP;
									decoded->src.addr_mode = MODE_IMMEDIATE;
									decoded->src.params.immed =fetch(address, data);
									address += 2;
									break;
								case 3:
									decoded->op = M68K_RTE;
									break;
								case 4:
#ifdef M68010
									decoded->op = M68K_RTD;
									decoded->src.addr_mode = MODE_IMMEDIATE;
									decoded->src.params.immed =fetch(address, data);
									address += 2;
#endif
									break;
								case 5:
									decoded->op = M68K_RTS;
									break;
								case 6:
									decoded->op = M68K_TRAPV;
									break;
								case 7:
									decoded->op = M68K_RTR;
									break;
								}
								break;
							case 7:
								//MOVEC
#ifdef M68010
								decoded->op = M68K_MOVEC;
								immed = fetch(address, data);
								address += 2;
								reg = immed >> 12 & 0x7;
								opmode = immed & 0x8000 ? MODE_AREG : MODE_REG;
								immed &= 0xFFF;
								if (immed & 0x800) {
									if (immed > MAX_HIGH_CR) {
										decoded->op = M68K_INVALID;
										break;
									} else {
										immed = immed - 0x800 + CR_USP;
									}
								} else {
									if (immed > MAX_LOW_CR) {
										decoded->op = M68K_INVALID;
										break;
									}
								}
								if (*start & 1) {
									decoded->src.addr_mode = opmode;
									decoded->src.params.regs.pri = reg;
									decoded->dst.params.immed = immed;
								} else {
									decoded->dst.addr_mode = opmode;
									decoded->dst.params.regs.pri = reg;
									decoded->src.params.immed = immed;
								}
#endif
								break;
							}
						}
						break;
					}
				}
			}
		}
		break;
	case QUICK_ARITH_LOOP:
		size = (opcode >> 6) & 3;
		if (size == 0x3) {
			//DBcc, TRAPcc or Scc
			m68k_decode_cond(opcode, decoded);
			if (((opcode >> 3) & 0x7) == 1) {
				decoded->op = M68K_DBCC;
				decoded->src.addr_mode = MODE_IMMEDIATE;
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = opcode & 0x7;
				decoded->src.params.immed = sign_extend16(fetch(address, data));
				address += 2;
			} else if(((opcode >> 3) & 0x7) == 1 && (opcode & 0x7) > 1 && (opcode & 0x7) < 5) {
#ifdef M68020
				decoded->op = M68K_TRAPCC;
				decoded->src.addr_mode = MODE_IMMEDIATE;
				//TODO: Figure out what to do with OPMODE and optional extention words
#endif
			} else {
				decoded->op = M68K_SCC;
				address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_BYTE, &(decoded->dst));
				if (address == INVALID_ADDRESS || !m68k_valid_immed_limited_dst(&decoded->dst)) {
					decoded->op = M68K_INVALID;
					break;
				}
			}
		} else {
			//ADDQ, SUBQ
			decoded->variant = VAR_QUICK;
			decoded->extra.size = size;
			decoded->src.addr_mode = MODE_IMMEDIATE;
			immed = m68k_reg_quick_field(opcode);
			if (!immed) {
				immed = 8;
			}
			decoded->src.params.immed = immed;
			if (opcode & 0x100) {
				decoded->op = M68K_SUB;
			} else {
				decoded->op = M68K_ADD;
			}
			address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
			if (address == INVALID_ADDRESS || decoded->dst.addr_mode > MODE_ABSOLUTE || (size == OPSIZE_BYTE && decoded->dst.addr_mode == MODE_AREG)) {
				decoded->op = M68K_INVALID;
				break;
			}
		}
		break;
	case BRANCH:
		m68k_decode_cond(opcode, decoded);
		decoded->op = decoded->extra.cond == COND_FALSE ? M68K_BSR : M68K_BCC;
		decoded->src.addr_mode = MODE_IMMEDIATE;
		immed = opcode & 0xFF;
		if (immed == 0) {
			decoded->variant = VAR_WORD;
			immed = fetch(address, data);
			address += 2;
			immed = sign_extend16(immed);
#ifdef M68020
		} else if (immed == 0xFF) {
			decoded->variant = VAR_LONG;
			immed = fetch(address, data) << 16;
			address += 2;
			immed |= fetch(address, data);
			address += 2;
#endif
		} else {
			decoded->variant = VAR_BYTE;
			immed = sign_extend8(immed);
		}
		decoded->src.params.immed = immed;
		break;
	case MOVEQ:
		if (opcode & 0x100) {
			decoded->op = M68K_INVALID;
			break;
		}
		decoded->op = M68K_MOVE;
		decoded->variant = VAR_QUICK;
		decoded->extra.size = OPSIZE_LONG;
		decoded->src.addr_mode = MODE_IMMEDIATE;
		decoded->src.params.immed = sign_extend8(opcode & 0xFF);
		decoded->dst.addr_mode = MODE_REG;
		decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
		immed = opcode & 0xFF;
		break;
	case OR_DIV_SBCD:
		//for OR, if opmode bit 2 is 1, then src = Dn, dst = <ea>
		opmode = (opcode >> 6) & 0x7;
		size = opmode & 0x3;
		if (size == OPSIZE_INVALID || (opmode & 0x4 && !(opcode & 0x30))) {
			switch(opmode)
			{
			case 3:
				decoded->op = M68K_DIVU;
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = (opcode >> 9) & 0x7;
				address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_WORD, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
				break;
			case 4:
				decoded->op = M68K_SBCD;
				decoded->extra.size = OPSIZE_BYTE;
				decoded->dst.addr_mode = decoded->src.addr_mode = opcode & 0x8 ? MODE_AREG_PREDEC : MODE_REG;
				decoded->src.params.regs.pri = opcode & 0x7;
				decoded->dst.params.regs.pri = (opcode >> 9) & 0x7;
				break;
			case 5:
	#ifdef M68020
	#endif
				break;
			case 6:
	#ifdef M68020
	#endif
				break;
			case 7:
				decoded->op = M68K_DIVS;
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = (opcode >> 9) & 0x7;
				address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_WORD, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
				break;
			}
		} else {
			decoded->op = M68K_OR;
			decoded->extra.size = size;
			if (opmode & 0x4) {
				decoded->src.addr_mode = MODE_REG;
				decoded->src.params.regs.pri = (opcode >> 9) & 0x7;
				address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
				if (address == INVALID_ADDRESS || !m68k_valid_full_arith_dst(&(decoded->dst))) {
					decoded->op = M68K_INVALID;
					break;
				}
			} else {
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = (opcode >> 9) & 0x7;
				address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
			}
		}
		break;
	case SUB_SUBX:
		size = (opcode >> 6) & 0x3;
		decoded->op = M68K_SUB;
		if (opcode & 0x100) {
			//<ea> destination, SUBA.l or SUBX
			if (opcode & 0x30 || size == OPSIZE_INVALID) {
				if (size == OPSIZE_INVALID) {
					//SUBA.l
					decoded->extra.size = OPSIZE_LONG;
					decoded->dst.addr_mode = MODE_AREG;
					decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
					address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_LONG, &(decoded->src));
					if (address == INVALID_ADDRESS) {
						decoded->op = M68K_INVALID;
						break;
					}
				} else {
					decoded->extra.size = size;
					decoded->src.addr_mode = MODE_REG;
					decoded->src.params.regs.pri = m68k_reg_quick_field(opcode);
					address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
					if (address == INVALID_ADDRESS || !m68k_valid_full_arith_dst(&decoded->dst)) {
						decoded->op = M68K_INVALID;
						break;
					}
				}
			} else {
				//SUBX
				decoded->op = M68K_SUBX;
				decoded->extra.size = size;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				decoded->src.params.regs.pri = opcode & 0x7;
				if (opcode & 0x8) {
					decoded->dst.addr_mode = decoded->src.addr_mode = MODE_AREG_PREDEC;
				} else {
					decoded->dst.addr_mode = decoded->src.addr_mode = MODE_REG;
				}
			}
		} else {
			if (size == OPSIZE_INVALID) {
				//SUBA.w
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_AREG;
			} else {
				decoded->extra.size = size;
				decoded->dst.addr_mode = MODE_REG;
			}
			decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
			address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
			if (address == INVALID_ADDRESS || (decoded->src.addr_mode == MODE_AREG && decoded->extra.size == OPSIZE_BYTE)) {
				decoded->op = M68K_INVALID;
				break;
			}
		}
		break;
	case A_LINE:
		decoded->op = M68K_A_LINE_TRAP;
		break;
	case CMP_XOR:
		size = (opcode >> 6) & 0x3;
		decoded->op = M68K_CMP;
		if (opcode & 0x100) {
			//CMPM or CMPA.l or EOR
			if (size == OPSIZE_INVALID) {
				decoded->extra.size = OPSIZE_LONG;
				decoded->dst.addr_mode = MODE_AREG;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
				if (address == INVALID_ADDRESS) {
					decoded->op = M68K_INVALID;
					break;
				}
			} else {
				reg = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
				if (address == INVALID_ADDRESS) {
					decoded->op = M68K_INVALID;
					break;
				}
				decoded->extra.size = size;
				if (decoded->dst.addr_mode == MODE_AREG) {
					//CMPM
					decoded->src.addr_mode = decoded->dst.addr_mode = MODE_AREG_POSTINC;
					decoded->src.params.regs.pri = decoded->dst.params.regs.pri;
					decoded->dst.params.regs.pri = reg;
				} else if (!m68k_valid_immed_limited_dst(&decoded->dst)){
					decoded->op = M68K_INVALID;
					break;
				} else {
					//EOR
					decoded->op = M68K_EOR;
					decoded->src.addr_mode = MODE_REG;
					decoded->src.params.regs.pri = reg;
				}
			}
		} else {
			//CMP or CMPA.w
			if (size == OPSIZE_INVALID) {
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_AREG;
			} else {
				decoded->extra.size = size;
				decoded->dst.addr_mode = MODE_REG;
			}
			decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
			address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
			if (address == INVALID_ADDRESS || (decoded->src.addr_mode == MODE_AREG && decoded->extra.size == OPSIZE_BYTE)) {
				decoded->op = M68K_INVALID;
				break;
			}
		}
		break;
	case AND_MUL_ABCD_EXG:
		//page 575 for summary
		//EXG opmodes:
		//01000 -data regs
		//01001 -addr regs
		//10001 -one of each
		//AND opmodes:
		//operand order bit + 2 size bits (00 - 10)
		//no address register direct addressing
		//data register direct not allowed when <ea> is the source (operand order bit of 1)
		if (opcode & 0x100) {
			if ((opcode & 0xC0) == 0xC0) {
				decoded->op = M68K_MULS;
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_WORD, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
			} else if(!(opcode & 0xF0)) {
				decoded->op = M68K_ABCD;
				decoded->extra.size = OPSIZE_BYTE;
				decoded->src.params.regs.pri = opcode & 0x7;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				decoded->dst.addr_mode = decoded->src.addr_mode = (opcode & 8) ? MODE_AREG_PREDEC : MODE_REG;
			} else if(!(opcode & 0x30)) {
				decoded->op = M68K_EXG;
				decoded->extra.size = OPSIZE_LONG;
				decoded->src.params.regs.pri = m68k_reg_quick_field(opcode);
				decoded->dst.params.regs.pri = opcode & 0x7;
				if (opcode & 0x8) {
					if (opcode & 0x80) {
						decoded->src.addr_mode = MODE_REG;
						decoded->dst.addr_mode = MODE_AREG;
					} else {
						decoded->src.addr_mode = decoded->dst.addr_mode = MODE_AREG;
					}
				} else if (opcode & 0x40) {
					decoded->src.addr_mode = decoded->dst.addr_mode = MODE_REG;
				} else {
					decoded->op = M68K_INVALID;
					break;
				}
			} else {
				decoded->op = M68K_AND;
				decoded->extra.size = (opcode >> 6) & 0x3;
				decoded->src.addr_mode = MODE_REG;
				decoded->src.params.regs.pri = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->dst));
				if (address == INVALID_ADDRESS || !m68k_valid_full_arith_dst(&(decoded->dst))) {
					decoded->op = M68K_INVALID;
					break;
				}
			}
		} else {
			if ((opcode & 0xC0) == 0xC0) {
				decoded->op = M68K_MULU;
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_WORD, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
			} else {
				decoded->op = M68K_AND;
				decoded->extra.size = (opcode >> 6) & 0x3;
				decoded->dst.addr_mode = MODE_REG;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
				if (address == INVALID_ADDRESS || decoded->src.addr_mode == MODE_AREG) {
					decoded->op = M68K_INVALID;
					break;
				}
			}
		}
		break;
	case ADD_ADDX:
		size = (opcode >> 6) & 0x3;
		decoded->op = M68K_ADD;
		if (opcode & 0x100) {
			//<ea> destination, ADDA.l or ADDX
			if (opcode & 0x30 || size == OPSIZE_INVALID) {
				if (size == OPSIZE_INVALID) {
					//ADDA.l
					decoded->extra.size = OPSIZE_LONG;
					decoded->dst.addr_mode = MODE_AREG;
					decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
					address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_LONG, &(decoded->src));
					if (address == INVALID_ADDRESS) {
						decoded->op = M68K_INVALID;
						break;
					}
				} else {
					decoded->extra.size = size;
					decoded->src.addr_mode = MODE_REG;
					decoded->src.params.regs.pri = m68k_reg_quick_field(opcode);
					address = m68k_decode_op(opcode, address, fetch, data, size, &(decoded->dst));
					if (address == INVALID_ADDRESS || !m68k_valid_full_arith_dst(&decoded->dst)) {
						decoded->op = M68K_INVALID;
						break;
					}
				}
			} else {
				//ADDX
				decoded->op = M68K_ADDX;
				decoded->extra.size = size;
				decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
				decoded->src.params.regs.pri = opcode & 0x7;
				if (opcode & 0x8) {
					decoded->dst.addr_mode = decoded->src.addr_mode = MODE_AREG_PREDEC;
				} else {
					decoded->dst.addr_mode = decoded->src.addr_mode = MODE_REG;
				}
			}
		} else {
			if (size == OPSIZE_INVALID) {
				//ADDA.w
				decoded->extra.size = OPSIZE_WORD;
				decoded->dst.addr_mode = MODE_AREG;
			} else {
				decoded->extra.size = size;
				decoded->dst.addr_mode = MODE_REG;
			}
			decoded->dst.params.regs.pri = m68k_reg_quick_field(opcode);
			address = m68k_decode_op(opcode, address, fetch, data, decoded->extra.size, &(decoded->src));
			if (address == INVALID_ADDRESS || (decoded->src.addr_mode == MODE_AREG && decoded->extra.size == OPSIZE_BYTE)) {
				decoded->op = M68K_INVALID;
				break;
			}
		}
		break;
	case SHIFT_ROTATE:
		if ((opcode & 0x8C0) == 0xC0) {
			switch((opcode >> 8) & 0x7)
			{
			case 0:
				decoded->op = M68K_ASR;
				break;
			case 1:
				decoded->op = M68K_ASL;
				break;
			case 2:
				decoded->op = M68K_LSR;
				break;
			case 3:
				decoded->op = M68K_LSL;
				break;
			case 4:
				decoded->op = M68K_ROXR;
				break;
			case 5:
				decoded->op = M68K_ROXL;
				break;
			case 6:
				decoded->op = M68K_ROR;
				break;
			case 7:
				decoded->op = M68K_ROL;
				break;
			}
			decoded->extra.size = OPSIZE_WORD;
			address = m68k_decode_op(opcode, address, fetch, data, OPSIZE_WORD, &(decoded->dst));
			if (address == INVALID_ADDRESS || !m68k_valid_full_arith_dst(&decoded->dst)) {
				decoded->op = M68K_INVALID;
				break;
			}
		} else if((opcode & 0xC0) != 0xC0) {
			switch(((opcode >> 2) & 0x6) | ((opcode >> 8) & 1))
			{
			case 0:
				decoded->op = M68K_ASR;
				break;
			case 1:
				decoded->op = M68K_ASL;
				break;
			case 2:
				decoded->op = M68K_LSR;
				break;
			case 3:
				decoded->op = M68K_LSL;
				break;
			case 4:
				decoded->op = M68K_ROXR;
				break;
			case 5:
				decoded->op = M68K_ROXL;
				break;
			case 6:
				decoded->op = M68K_ROR;
				break;
			case 7:
				decoded->op = M68K_ROL;
				break;
			}
			decoded->extra.size = (opcode >> 6) & 0x3;
			immed = (opcode >> 9) & 0x7;
			if (opcode & 0x20) {
				decoded->src.addr_mode = MODE_REG;
				decoded->src.params.regs.pri = immed;
			} else {
				decoded->src.addr_mode = MODE_IMMEDIATE;
				if (!immed) {
					immed = 8;
				}
				decoded->src.params.immed = immed;
				decoded->variant = VAR_QUICK;
			}
			decoded->dst.addr_mode = MODE_REG;
			decoded->dst.params.regs.pri = opcode & 0x7;

		} else {
#ifdef M68020
			//TODO: Implement bitfield instructions for M68020+ support
			switch (opcode >> 8 & 7)
			{
			case 0:
				decoded->op = M68K_BFTST; //<ea>
				break;
			case 1:
				decoded->op = M68K_BFEXTU; //<ea>, Dn
				break;
			case 2:
				decoded->op = M68K_BFCHG; //<ea>
				break;
			case 3:
				decoded->op = M68K_BFEXTS; //<ea>, Dn
				break;
			case 4:
				decoded->op = M68K_BFCLR; //<ea>
				break;
			case 5:
				decoded->op = M68K_BFFFO; //<ea>, Dn
				break;
			case 6:
				decoded->op = M68K_BFSET; //<ea>
				break;
			case 7:
				decoded->op = M68K_BFINS; //Dn, <ea>
				break;
			}
			opmode = opcode >> 3 & 0x7;
			reg = opcode & 0x7;
			m68k_op_info *ea, *other;
			if (decoded->op == M68K_BFEXTU || decoded->op == M68K_BFEXTS || decoded->op == M68K_BFFFO)
			{
				ea = &(decoded->src);
				other = &(decoded->dst);
			} else {
				ea = &(decoded->dst);
				other = &(decoded->dst);
			}
			if (opcode & 0x100)
			{
				immed = fetch(address, data);
				address += 2;
				other->addr_mode = MODE_REG;
				other->params.regs.pri = immed >> 12 & 0x7;
			} else {
				immed = fetch(address, data);
				address += 2;
			}
			decoded->extra.size = OPSIZE_UNSIZED;
			address = m68k_decode_op_ex(opcode, address, fetch, data, opmode, reg, decoded->extra.size, ea);
			ea->addr_mode |= M68K_FLAG_BITFIELD;
			ea->bitfield = immed & 0xFFF;
#endif
		}
		break;
	case F_LINE:
		//TODO: Decode FPU instructions for members of the 68K family with an FPU
		decoded->op = M68K_F_LINE_TRAP;
		break;
	}
	if (decoded->op == M68K_INVALID) {
		decoded->src.params.immed = opcode;
		decoded->bytes = 2;
		return start_address + 2;
	}
	decoded->bytes = address - start_address;
	return address;
}

uint32_t m68k_branch_target(m68kinst * inst, uint32_t *dregs, uint32_t *aregs)
{
	if(inst->op == M68K_BCC || inst->op == M68K_BSR || inst->op == M68K_DBCC) {
		return inst->address + 2 + inst->src.params.immed;
	} else if(inst->op == M68K_JMP || inst->op == M68K_JSR) {
		uint32_t ret = 0;
		switch(inst->src.addr_mode)
		{
		case MODE_AREG_INDIRECT:
			ret = aregs[inst->src.params.regs.pri];
			break;
		case MODE_AREG_DISPLACE:
			ret = aregs[inst->src.params.regs.pri] + inst->src.params.regs.displacement;
			break;
		case MODE_AREG_INDEX_DISP8: {
			uint8_t sec_reg = inst->src.params.regs.sec >> 1 & 0x7;
			ret = aregs[inst->src.params.regs.pri];
			uint32_t * regfile = inst->src.params.regs.sec & 0x10 ? aregs : dregs;
			if (inst->src.params.regs.sec & 1) {
				//32-bit index register
				ret += regfile[sec_reg];
			} else {
				//16-bit index register
				if (regfile[sec_reg] & 0x8000) {
					ret += (0xFFFF0000 | regfile[sec_reg]);
				} else {
					ret += regfile[sec_reg];
				}
			}
			ret += inst->src.params.regs.displacement;
			break;
		}
		case MODE_PC_DISPLACE:
			ret = inst->src.params.regs.displacement + inst->address + 2;
			break;
		case MODE_PC_INDEX_DISP8: {
			uint8_t sec_reg = inst->src.params.regs.sec >> 1 & 0x7;
			ret = inst->address + 2;
			uint32_t * regfile = inst->src.params.regs.sec & 0x10 ? aregs : dregs;
			if (inst->src.params.regs.sec & 1) {
				//32-bit index register
				ret += regfile[sec_reg];
			} else {
				//16-bit index register
				if (regfile[sec_reg] & 0x8000) {
					ret += (0xFFFF0000 | regfile[sec_reg]);
				} else {
					ret += regfile[sec_reg];
				}
			}
			ret += inst->src.params.regs.displacement;
			break;
		}
		case MODE_ABSOLUTE:
		case MODE_ABSOLUTE_SHORT:
			ret = inst->src.params.immed;
			break;
		}
		return ret;
	}
	return 0;
}

uint8_t m68k_is_branch(m68kinst * inst)
{
	return (inst->op == M68K_BCC && inst->extra.cond != COND_FALSE)
		|| (inst->op == M68K_DBCC && inst->extra.cond != COND_TRUE)
		|| inst->op == M68K_BSR || inst->op == M68K_JMP || inst->op == M68K_JSR;
}

uint8_t m68k_is_noncall_branch(m68kinst * inst)
{
	return m68k_is_branch(inst) && inst->op != M68K_BSR && inst->op != M68K_JSR;
}


char * mnemonics[] = {
	"abcd",
	"add",
	"addx",
	"and",
	"andi",//ccr
	"andi",//sr
	"asl",
	"asr",
	"bcc",
	"bchg",
	"bclr",
	"bset",
	"bsr",
	"btst",
	"chk",
	"clr",
	"cmp",
	"dbcc",
	"divs",
	"divu",
	"eor",
	"eori",//ccr
	"eori",//sr
	"exg",
	"ext",
	"illegal",
	"jmp",
	"jsr",
	"lea",
	"link",
	"lsl",
	"lsr",
	"move",
	"move",//ccr
	"move",//from_sr
	"move",//sr
	"move",//usp
	"movem",
	"movep",
	"muls",
	"mulu",
	"nbcd",
	"neg",
	"negx",
	"nop",
	"not",
	"or",
	"ori",//ccr
	"ori",//sr
	"pea",
	"reset",
	"rol",
	"ror",
	"roxl",
	"roxr",
	"rte",
	"rtr",
	"rts",
	"sbcd",
	"scc",
	"stop",
	"sub",
	"subx",
	"swap",
	"tas",
	"trap",
	"trapv",
	"tst",
	"unlk",
	"invalid",
#ifdef M68010
	"bkpt",
	"move", //from ccr
	"movec",
	"moves",
	"rtd",
#endif
#ifdef M68020
	"bfchg",
	"bfclr",
	"bfexts",
	"bfextu",
	"bfffo",
	"bfins",
	"bfset",
	"bftst",
	"callm",
	"cas",
	"cas2",
	"chk2",
	"cmp2",
	"cpbcc",
	"cpdbcc",
	"cpgen",
	"cprestore",
	"cpsave",
	"cpscc",
	"cptrapcc",
	"divsl",
	"divul",
	"extb",
	"pack",
	"rtm",
	"trapcc",
	"unpk"
#endif
};

char * cond_mnem[] = {
	"ra",
	"f",
	"hi",
	"ls",
	"cc",
	"cs",
	"ne",
	"eq",
	"vc",
	"vs",
	"pl",
	"mi",
	"ge",
	"lt",
	"gt",
	"le"
};
#ifdef M68010
char * cr_mnem[] = {
	"SFC",
	"DFC",
#ifdef M68020
	"CACR",
#endif
	"USP",
	"VBR",
#ifdef M68020
	"CAAR",
	"MSP",
	"ISP"
#endif
};
#endif

int m68k_disasm_op(m68k_op_info *decoded, char *dst, int need_comma, uint8_t labels, uint32_t address, format_label_fun label_fun, void * data)
{
	char * c = need_comma ? "," : "";
	int ret = 0;
#ifdef M68020
	uint8_t addr_mode = decoded->addr_mode & (~M68K_FLAG_BITFIELD);
#else
	uint8_t addr_mode = decoded->addr_mode;
#endif
	switch(addr_mode)
	{
	case MODE_REG:
		ret = sprintf(dst, "%s d%d", c, decoded->params.regs.pri);
		break;
	case MODE_AREG:
		ret = sprintf(dst, "%s a%d", c, decoded->params.regs.pri);
		break;
	case MODE_AREG_INDIRECT:
		ret = sprintf(dst, "%s (a%d)", c, decoded->params.regs.pri);
		break;
	case MODE_AREG_POSTINC:
		ret = sprintf(dst, "%s (a%d)+", c, decoded->params.regs.pri);
		break;
	case MODE_AREG_PREDEC:
		ret = sprintf(dst, "%s -(a%d)", c, decoded->params.regs.pri);
		break;
	case MODE_AREG_DISPLACE:
		ret = sprintf(dst, "%s (%d, a%d)", c, decoded->params.regs.displacement, decoded->params.regs.pri);
		break;
	case MODE_AREG_INDEX_DISP8:
#ifdef M68020
		if (decoded->params.regs.scale)
		{
			ret = sprintf(dst, "%s (%d, a%d, %c%d.%c*%d)", c, decoded->params.regs.displacement, decoded->params.regs.pri, (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		} else {
#endif
			ret = sprintf(dst, "%s (%d, a%d, %c%d.%c)", c, decoded->params.regs.displacement, decoded->params.regs.pri, (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w');
#ifdef M68020
		}
#endif
		break;
#ifdef M68020
	case MODE_AREG_INDEX_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, a%d, %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes == 2 ? 'w' : 'l', decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		} else {
			ret = sprintf(dst, "%s (a%d, %c%d.%c*%d)", c, decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		}
		break;
	case MODE_AREG_PREINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([a%d, %c%d.%c*%d])", c, decoded->params.regs.pri,
						  (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
						  (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, a%d, %c%d.%c*%d])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([a%d, %c%d.%c*%d], %d.%c)", c, decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, a%d, %c%d.%c*%d], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_AREG_POSTINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([a%d], %c%d.%c*%d)", c, decoded->params.regs.pri,
						  (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
						  (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, a%d], %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([a%d], %c%d.%c*%d, %d.%c)", c, decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, a%d], %c%d.%c*%d, %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.pri,
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_AREG_MEM_INDIRECT:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([a%d])", c, decoded->params.regs.pri);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, a%d])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.pri);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([a%d], %d.%c)", c, decoded->params.regs.pri, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, a%d], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.pri,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_AREG_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, a%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes == 2 ? 'w' : 'l', decoded->params.regs.pri);
		} else {
			//this is a lossy representation of the encoded instruction
			//not sure if there's a better way to print it though
			ret = sprintf(dst, "%s (a%d)", c, decoded->params.regs.pri);
		}
		break;
	case MODE_INDEX_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		} else {
			ret = sprintf(dst, "%s (%c%d.%c*%d)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
		}
		break;
	case MODE_PREINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([%c%d.%c*%d])", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, %c%d.%c*%d])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([%c%d.%c*%d], %d.%c)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, %c%d.%c*%d], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_POSTINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([], %c%d.%c*%d)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c], %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([], %c%d.%c*%d, %d.%c)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c], %c%d.%c*%d, %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_MEM_INDIRECT:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([])", c);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l');
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([], %d.%c)", c, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l');
		} else {
			ret = sprintf(dst, "%s ()", c);
		}
		break;
#endif
	case MODE_IMMEDIATE:
	case MODE_IMMEDIATE_WORD:
		ret = sprintf(dst, (decoded->params.immed <= 128 ? "%s #%d" : "%s #$%X"), c, decoded->params.immed);
		break;
	case MODE_ABSOLUTE_SHORT:
		if (labels) {
			ret = sprintf(dst, "%s ", c);
			ret += label_fun(dst+ret, decoded->params.immed, data);
			strcat(dst+ret, ".w");
			ret = ret + 2;
		} else {
			ret = sprintf(dst, "%s $%X.w", c, decoded->params.immed);
		}
		break;
	case MODE_ABSOLUTE:
		if (labels) {
			ret = sprintf(dst, "%s ", c);
			ret += label_fun(dst+ret, decoded->params.immed, data);
			strcat(dst+ret, ".l");
			ret = ret + 2;
		} else {
			ret = sprintf(dst, "%s $%X", c, decoded->params.immed);
		}
		break;
	case MODE_PC_DISPLACE:
		if (labels) {
			ret = sprintf(dst, "%s ", c);
			ret += label_fun(dst+ret, address + 2 + decoded->params.regs.displacement, data);
			strcat(dst+ret, "(pc)");
			ret = ret + 4;
		} else {
			ret = sprintf(dst, "%s (%d, pc)", c, decoded->params.regs.displacement);
		}
		break;
	case MODE_PC_INDEX_DISP8:
#ifdef M68020
		if (decoded->params.regs.scale)
		{
			ret = sprintf(dst, "%s (%d, pc, %c%d.%c*%d)", c, decoded->params.regs.displacement, (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		} else {
#endif
			ret = sprintf(dst, "%s (%d, pc, %c%d.%c)", c, decoded->params.regs.displacement, (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w');
#ifdef M68020
		}
#endif
		break;
#ifdef M68020
	case MODE_PC_INDEX_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, pc, %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		} else {
			ret = sprintf(dst, "%s (pc, %c%d.%c*%d)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
		}
		break;
	case MODE_PC_PREINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([pc, %c%d.%c*%d])", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, pc, %c%d.%c*%d])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([pc, %c%d.%c*%d], %d.%c)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, pc, %c%d.%c*%d], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_PC_POSTINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([pc], %c%d.%c*%d)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, pc], %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([pc], %c%d.%c*%d, %d.%c)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, pc], %c%d.%c*%d, %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_PC_MEM_INDIRECT:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([pc])", c);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, pc])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l');
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([pc], %d.%c)", c, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, pc], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_PC_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, pc)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l');
		} else {
			ret = sprintf(dst, "%s (pc)", c);
		}
		break;
	case MODE_ZPC_INDEX_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, zpc, %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
		} else {
			ret = sprintf(dst, "%s (zpc, %c%d.%c*%d)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
		}
		break;
	case MODE_ZPC_PREINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([zpc, %c%d.%c*%d])", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, zpc, %c%d.%c*%d])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([zpc, %c%d.%c*%d], %d.%c)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, zpc, %c%d.%c*%d], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_ZPC_POSTINDEX:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([zpc], %c%d.%c*%d)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, zpc], %c%d.%c*%d)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale);
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([zpc], %c%d.%c*%d, %d.%c)", c, (decoded->params.regs.sec & 0x10) ? 'a': 'd',
			              (decoded->params.regs.sec >> 1) & 0x7, (decoded->params.regs.sec & 1) ? 'l': 'w',
			              1 << decoded->params.regs.scale, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, zpc], %c%d.%c*%d, %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l',
			              (decoded->params.regs.sec & 0x10) ? 'a': 'd', (decoded->params.regs.sec >> 1) & 0x7,
			              (decoded->params.regs.sec & 1) ? 'l': 'w', 1 << decoded->params.regs.scale,
			              decoded->params.regs.outer_disp, decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_ZPC_MEM_INDIRECT:
		switch (decoded->params.regs.disp_sizes)
		{
		case 0x11:
			//no base displacement or outer displacement
			ret = sprintf(dst, "%s ([zpc])", c);
			break;
		case 0x12:
		case 0x13:
			//base displacement only
			ret = sprintf(dst, "%s ([%d.%c, zpc])", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l');
			break;
		case 0x21:
		case 0x31:
			//outer displacement only
			ret = sprintf(dst, "%s ([zpc], %d.%c)", c, decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		case 0x22:
		case 0x23:
		case 0x32:
		case 0x33:
			//both outer and inner displacement
			ret = sprintf(dst, "%s ([%d.%c, zpc], %d.%c)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l', decoded->params.regs.outer_disp,
			              decoded->params.regs.disp_sizes & 0x30 == 0x20 ? 'w' : 'l');
			break;
		}
		break;
	case MODE_ZPC_BASE_DISP:
		if (decoded->params.regs.disp_sizes > 1)
		{
			ret = sprintf(dst, "%s (%d.%c, zpc)", c, decoded->params.regs.displacement,
			              decoded->params.regs.disp_sizes & 3 == 2 ? 'w' : 'l');
		} else {
			ret = sprintf(dst, "%s (zpc)", c);
		}
		break;
#endif
	default:
		ret = 0;
	}
#ifdef M68020
	if (decoded->addr_mode & M68K_FLAG_BITFIELD)
	{
		switch (decoded->bitfield & 0x820)
		{
		case 0:
			return ret + sprintf(dst+ret, " {$%X:%d}", decoded->bitfield >> 6 & 0x1F, decoded->bitfield & 0x1F ? decoded->bitfield & 0x1F : 32);
		case 0x20:
			return ret + sprintf(dst+ret, " {$%X:d%d}", decoded->bitfield >> 6 & 0x1F, decoded->bitfield & 0x7);
		case 0x800:
			return ret + sprintf(dst+ret, " {d%d:%d}", decoded->bitfield >> 6 & 0x7, decoded->bitfield & 0x1F ? decoded->bitfield & 0x1F : 32);
		case 0x820:
			return ret + sprintf(dst+ret, " {d%d:d%d}", decoded->bitfield >> 6 & 0x7, decoded->bitfield & 0x7);
		}
	}
#endif
	return ret;
}

int m68k_disasm_movem_op(m68k_op_info *decoded, m68k_op_info *other, char *dst, int need_comma, uint8_t labels, uint32_t address, format_label_fun label_fun, void * data)
{
	int8_t dir, reg, bit, regnum, last=-1, lastreg, first=-1;
	char *rtype, *last_rtype;
	int oplen;
	if (decoded->addr_mode == MODE_REG) {
		if (other->addr_mode == MODE_AREG_PREDEC) {
			bit = 15;
			dir = -1;
		} else {
			dir = 1;
			bit = 0;
		}
		if (need_comma) {
			strcat(dst, ", ");
			oplen = 2;
		} else {
			strcat(dst, " ");
			oplen = 1;
		}
		for (reg=0; bit < 16 && bit > -1; bit += dir, reg++) {
			if (decoded->params.immed & (1 << bit)) {
				if (reg > 7) {
					rtype = "a";
					regnum = reg - 8;
				} else {
					rtype = "d";
					regnum = reg;
				}
				if (last >= 0 && last == regnum - 1 && lastreg == reg - 1) {
					last = regnum;
					lastreg = reg;
				} else if(last >= 0) {
					if (first != last) {
						oplen += sprintf(dst + oplen, "-%s%d/%s%d",last_rtype, last, rtype, regnum);
					} else {
						oplen += sprintf(dst + oplen, "/%s%d", rtype, regnum);
					}
					first = last = regnum;
					last_rtype = rtype;
					lastreg = reg;
				} else {
					oplen += sprintf(dst + oplen, "%s%d", rtype, regnum);
					first = last = regnum;
					last_rtype = rtype;
					lastreg = reg;
				}
			}
		}
		if (last >= 0 && last != first) {
			oplen += sprintf(dst + oplen, "-%s%d", last_rtype, last);
		}
		return oplen;
	} else {
		return m68k_disasm_op(decoded, dst, need_comma, labels, address, label_fun, data);
	}
}

int m68k_disasm_ex(m68kinst * decoded, char * dst, uint8_t labels, format_label_fun label_fun, disasm_context *data)
{
	int ret,op1len;
	uint8_t size;
	char * special_op = "CCR";
	switch (decoded->op)
	{
	case M68K_BCC:
	case M68K_DBCC:
	case M68K_SCC:
		ret = strlen(mnemonics[decoded->op]) - 2;
		memcpy(dst, mnemonics[decoded->op], ret);
		dst[ret] = 0;
		strcpy(dst+ret, cond_mnem[decoded->extra.cond]);
		ret = strlen(dst);
		if (decoded->op != M68K_SCC) {
			if (labels) {
				if (decoded->op == M68K_DBCC) {
					ret += sprintf(dst+ret, " d%d, ", decoded->dst.params.regs.pri);
					ret += label_fun(dst+ret, decoded->address + 2 + decoded->src.params.immed, data);
				} else {
					dst[ret++] = ' ';
					ret += label_fun(dst+ret, decoded->address + 2 + decoded->src.params.immed, data);
				}
			} else {
				if (decoded->op == M68K_DBCC) {
					ret += sprintf(dst+ret, " d%d, #%d <%X>", decoded->dst.params.regs.pri, decoded->src.params.immed, decoded->address + 2 + decoded->src.params.immed);
				} else {
					ret += sprintf(dst+ret, " #%d <%X>", decoded->src.params.immed, decoded->address + 2 + decoded->src.params.immed);
				}
			}
			return ret;
		}
		break;
	case M68K_BSR:
		if (labels) {
			ret = sprintf(dst, "bsr%s ", decoded->variant == VAR_BYTE ? ".s" : "");
			ret += label_fun(dst+ret, decoded->address + 2 + decoded->src.params.immed, data);
		} else {
			ret = sprintf(dst, "bsr%s #%d <%X>", decoded->variant == VAR_BYTE ? ".s" : "", decoded->src.params.immed, decoded->address + 2 + decoded->src.params.immed);
		}
		return ret;
	case M68K_MOVE_FROM_SR:
		ret = sprintf(dst, "%s", mnemonics[decoded->op]);
		ret += sprintf(dst + ret, " SR");
		ret += m68k_disasm_op(&(decoded->dst), dst + ret, 1, labels, decoded->address, label_fun, data);
		return ret;
	case M68K_ANDI_SR:
	case M68K_EORI_SR:
	case M68K_MOVE_SR:
	case M68K_ORI_SR:
		special_op = "SR";
	case M68K_ANDI_CCR:
	case M68K_EORI_CCR:
	case M68K_MOVE_CCR:
	case M68K_ORI_CCR:
		ret = sprintf(dst, "%s", mnemonics[decoded->op]);
		ret += m68k_disasm_op(&(decoded->src), dst + ret, 0, labels, decoded->address, label_fun, data);
		ret += sprintf(dst + ret, ", %s", special_op);
		return ret;
	case M68K_MOVE_USP:
		ret = sprintf(dst, "%s", mnemonics[decoded->op]);
		if (decoded->src.addr_mode != MODE_UNUSED) {
			ret += m68k_disasm_op(&(decoded->src), dst + ret, 0, labels, decoded->address, label_fun, data);
			ret += sprintf(dst + ret, ", USP");
		} else {
			ret += sprintf(dst + ret, "USP, ");
			ret += m68k_disasm_op(&(decoded->dst), dst + ret, 0, labels, decoded->address, label_fun, data);
		}
		return ret;
	case M68K_INVALID:
		ret = sprintf(dst, "dc.w $%X", decoded->src.params.immed);
		return ret;
#ifdef M68010
	case M68K_MOVEC:
		ret = sprintf(dst, "%s ", mnemonics[decoded->op]);
		if (decoded->src.addr_mode == MODE_UNUSED) {
			ret += sprintf(dst + ret, "%s, ", cr_mnem[decoded->src.params.immed]);
			ret += m68k_disasm_op(&(decoded->dst), dst + ret, 0, labels, decoded->address, label_fun, data);
		} else {
			ret += m68k_disasm_op(&(decoded->src), dst + ret, 0, labels, decoded->address, label_fun, data);
			ret += sprintf(dst + ret, ", %s", cr_mnem[decoded->dst.params.immed]);
		}
		return ret;
#endif
	default:
		size = decoded->extra.size;
		uint8_t is_quick = decoded->variant == VAR_QUICK && decoded->op != M68K_ASL && decoded->op != M68K_ASR
			&& decoded->op != M68K_LSL && decoded->op != M68K_LSR && decoded->op != M68K_ROXR && decoded->op != M68K_ROXL
			&& decoded->op != M68K_ROR && decoded->op != M68K_ROL;
		ret = sprintf(dst, "%s%s%s",
				mnemonics[decoded->op],
				is_quick ? "q" : (decoded->variant == VAR_IMMEDIATE ? "i" : ""),
				size == OPSIZE_BYTE ? ".b" : (size == OPSIZE_WORD ? ".w" : (size == OPSIZE_LONG ? ".l" : "")));
	}
	if (decoded->op == M68K_MOVEM) {
		op1len = m68k_disasm_movem_op(&(decoded->src), &(decoded->dst), dst + ret, 0, labels, decoded->address, label_fun, data);
		ret += op1len;
		ret += m68k_disasm_movem_op(&(decoded->dst), &(decoded->src), dst + ret, op1len, labels, decoded->address, label_fun, data);
	} else {
		op1len = m68k_disasm_op(&(decoded->src), dst + ret, 0, labels, decoded->address, label_fun, data);
		ret += op1len;
		ret += m68k_disasm_op(&(decoded->dst), dst + ret, op1len, labels, decoded->address, label_fun, data);
	}
	return ret;
}

int m68k_disasm(m68kinst * decoded, char * dst)
{
	return m68k_disasm_ex(decoded, dst, 0, NULL, NULL);
}

static uint16_t fetch(uint32_t addr, void *data) {
	uint8_t *buf = data;
	return buf[0] | (buf[1] << 8);
}

int disasm(unsigned char *buffer, long num, long addr, char *output) {
	m68kinst decoded;
	int res = m68k_decode (fetch, buffer, &decoded, addr);
	m68k_disasm_ex (&decoded, output, 0, NULL, NULL);
	return decoded.bytes;
}
