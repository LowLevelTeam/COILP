/**
 * codegen_x86.c - x86-32 code generator
 * Translates COIL instructions to x86-32 machine code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <coil/section.h>
#include <coil/instr.h>
#include <coil/types.h>
#include <nof/nof.h>

#include "codegen_x86.h"
#include "utils.h"

/* Maximum size of a single x86 instruction (for buffer allocation) */
#define MAX_X86_INSTRUCTION_SIZE 15

/* Temporary buffer for instruction encoding */
static unsigned char instruction_buffer[MAX_X86_INSTRUCTION_SIZE];

/* Function declarations for instruction handlers */
static int handle_nop(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_mov(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_push(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_pop(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_add(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_sub(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_ret(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_jmp(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_call(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);
static int handle_cmp(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output);

/* Lookup table for instruction handlers */
typedef int (*instruction_handler_t)(coil_instrmem_t*, coil_section_t*, coil_size_t*, nof_section*);

static instruction_handler_t instruction_handlers[256] = {0};

/* Initialize instruction handler table */
static void init_instruction_handlers(void) {
    memset(instruction_handlers, 0, sizeof(instruction_handlers));
    
    instruction_handlers[COIL_OP_NOP] = handle_nop;
    instruction_handlers[COIL_OP_MOV] = handle_mov;
    instruction_handlers[COIL_OP_PUSH] = handle_push;
    instruction_handlers[COIL_OP_POP] = handle_pop;
    instruction_handlers[COIL_OP_ADD] = handle_add;
    instruction_handlers[COIL_OP_SUB] = handle_sub;
    instruction_handlers[COIL_OP_RET] = handle_ret;
    instruction_handlers[COIL_OP_JMP] = handle_jmp;
    instruction_handlers[COIL_OP_CALL] = handle_call;
    instruction_handlers[COIL_OP_CMP] = handle_cmp;
}

/* Helper function to encode ModRM byte */
static unsigned char encode_modrm(unsigned char mod, unsigned char reg, unsigned char rm) {
    return ((mod & 0x3) << 6) | ((reg & 0x7) << 3) | (rm & 0x7);
}

/* Helper function to encode SIB byte */
static unsigned char encode_sib(unsigned char scale, unsigned char index, unsigned char base) {
    return ((scale & 0x3) << 6) | ((index & 0x7) << 3) | (base & 0x7);
}

/* Helper function to read an operand and advance the position */
static coil_size_t read_operand(coil_section_t* section, coil_size_t pos,
                             coil_operand_header_t* header, coil_offset_t* offset,
                             void* data, coil_size_t data_size) {
    coil_size_t new_pos;
    coil_size_t value_size;
    
    /* Read operand header */
    new_pos = coil_operand_decode(section, pos, header, offset);
    if (new_pos == 0) {
        return 0;
    }
    
    /* Read operand data if needed */
    if (header->type != COIL_TYPEOP_NONE) {
        new_pos = coil_operand_decode_data(section, new_pos, data, data_size, &value_size, header);
        if (new_pos == 0) {
            return 0;
        }
    }
    
    return new_pos;
}

/**
 * Generate x86-32 machine code from COIL instructions
 */
int cop_codegen_x86(coil_section_t* coil_section, nof_section* nof_section) {
    coil_size_t pos = 0;
    coil_instrmem_t instr;
    coil_instrfmt_t fmt;
    
    /* Initialize instruction handlers */
    init_instruction_handlers();
    
    /* Process each instruction in the COIL section */
    while (pos < coil_section->size) {
        /* Decode instruction header */
        coil_size_t new_pos = coil_instr_decode(coil_section, pos, &instr, &fmt);
        if (new_pos == 0) {
            fprintf(stderr, "Failed to decode instruction at position %zu\n", pos);
            return -1;
        }
        
        /* Check if we have a handler for this instruction */
        if (instr.opcode >= 256 || instruction_handlers[instr.opcode] == NULL) {
            fprintf(stderr, "Unsupported instruction: 0x%02X at position %zu\n", instr.opcode, pos);
            return -1;
        }
        
        /* Call the appropriate handler */
        if (instruction_handlers[instr.opcode](&instr, coil_section, &new_pos, nof_section) != 0) {
            fprintf(stderr, "Failed to generate code for instruction: 0x%02X at position %zu\n", 
                   instr.opcode, pos);
            return -1;
        }
        
        /* Move to the next instruction */
        pos = new_pos;
    }
    
    cop_log_verbose("Generated x86-32 code from %zu bytes of COIL instructions", coil_section->size);
    return 0;
}

/* Handle NOP instruction */
static int handle_nop(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    (void)instr;  /* Unused */
    (void)section;  /* Unused */
    
    /* x86 NOP is 0x90 */
    instruction_buffer[0] = 0x90;
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, 1) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle MOV instruction */
static int handle_mov(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t dst_header, src_header;
    coil_offset_t dst_offset, src_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand values */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
        coil_u8_t imm8;
    } dst_value, src_value;
    
    /* Read destination operand */
    new_pos = read_operand(section, new_pos, &dst_header, &dst_offset, 
                          &dst_value, sizeof(dst_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Read source operand */
    new_pos = read_operand(section, new_pos, &src_header, &src_offset, 
                          &src_value, sizeof(src_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand combinations */
    if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_IMM) {
        /* MOV reg, imm */
        coil_u32_t reg = dst_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        if (src_header.value_type == COIL_VAL_I32 || src_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate */
            instruction_buffer[buffer_index++] = 0xB8 + (reg & 0x7); /* MOV r32, imm32 */
            memcpy(instruction_buffer + buffer_index, &src_value.imm32, 4);
            buffer_index += 4;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", src_header.value_type);
            return -1;
        }
    } else {
        fprintf(stderr, "Unsupported operand combination for MOV instruction\n");
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle PUSH instruction */
static int handle_push(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t op_header;
    coil_offset_t op_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand value */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
        coil_u8_t imm8;
    } op_value;
    
    /* Read operand */
    new_pos = read_operand(section, new_pos, &op_header, &op_offset, 
                          &op_value, sizeof(op_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand types */
    if (op_header.type == COIL_TYPEOP_REG) {
        /* PUSH reg */
        coil_u32_t reg = op_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0x50 + (reg & 0x7); /* PUSH r32 */
    } else if (op_header.type == COIL_TYPEOP_IMM) {
        /* PUSH imm */
        if (op_header.value_type == COIL_VAL_I32 || op_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate */
            instruction_buffer[buffer_index++] = 0x68; /* PUSH imm32 */
            memcpy(instruction_buffer + buffer_index, &op_value.imm32, 4);
            buffer_index += 4;
        } else if (op_header.value_type == COIL_VAL_I8 || op_header.value_type == COIL_VAL_U8) {
            /* 8-bit immediate */
            instruction_buffer[buffer_index++] = 0x6A; /* PUSH imm8 */
            instruction_buffer[buffer_index++] = op_value.imm8;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", op_header.value_type);
            return -1;
        }
    } else {
        fprintf(stderr, "Unsupported operand type for PUSH instruction: %u\n", op_header.type);
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle POP instruction */
static int handle_pop(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t op_header;
    coil_offset_t op_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand value */
    union {
        coil_u32_t reg_id;
    } op_value;
    
    /* Read operand */
    new_pos = read_operand(section, new_pos, &op_header, &op_offset, 
                          &op_value, sizeof(op_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand types */
    if (op_header.type == COIL_TYPEOP_REG) {
        /* POP reg */
        coil_u32_t reg = op_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0x58 + (reg & 0x7); /* POP r32 */
    } else {
        fprintf(stderr, "Unsupported operand type for POP instruction: %u\n", op_header.type);
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle ADD instruction */
static int handle_add(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t dst_header, src_header;
    coil_offset_t dst_offset, src_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand values */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
        coil_u8_t imm8;
    } dst_value, src_value;
    
    /* Read destination operand */
    new_pos = read_operand(section, new_pos, &dst_header, &dst_offset, 
                          &dst_value, sizeof(dst_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Read source operand */
    new_pos = read_operand(section, new_pos, &src_header, &src_offset, 
                          &src_value, sizeof(src_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand combinations */
    if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_IMM) {
        /* ADD reg, imm */
        coil_u32_t reg = dst_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        if (src_header.value_type == COIL_VAL_I32 || src_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate */
            instruction_buffer[buffer_index++] = 0x81; /* ADD r32, imm32 */
            instruction_buffer[buffer_index++] = 0xC0 + (reg & 0x7); /* ModRM */
            memcpy(instruction_buffer + buffer_index, &src_value.imm32, 4);
            buffer_index += 4;
        } else if (src_header.value_type == COIL_VAL_I8 || src_header.value_type == COIL_VAL_U8) {
            /* 8-bit immediate */
            instruction_buffer[buffer_index++] = 0x83; /* ADD r32, imm8 */
            instruction_buffer[buffer_index++] = 0xC0 + (reg & 0x7); /* ModRM */
            instruction_buffer[buffer_index++] = src_value.imm8;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", src_header.value_type);
            return -1;
        }
    } else if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_REG) {
        /* ADD reg, reg */
        coil_u32_t dst_reg = dst_value.reg_id;
        coil_u32_t src_reg = src_value.reg_id;
        
        if (dst_reg >= X86_REG_COUNT || src_reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID\n");
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0x01; /* ADD r/m32, r32 */
        instruction_buffer[buffer_index++] = 0xC0 + ((src_reg & 0x7) << 3) + (dst_reg & 0x7); /* ModRM */
    } else {
        fprintf(stderr, "Unsupported operand combination for ADD instruction\n");
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle SUB instruction */
static int handle_sub(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t dst_header, src_header;
    coil_offset_t dst_offset, src_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand values */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
        coil_u8_t imm8;
    } dst_value, src_value;
    
    /* Read destination operand */
    new_pos = read_operand(section, new_pos, &dst_header, &dst_offset, 
                          &dst_value, sizeof(dst_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Read source operand */
    new_pos = read_operand(section, new_pos, &src_header, &src_offset, 
                          &src_value, sizeof(src_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand combinations */
    if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_IMM) {
        /* SUB reg, imm */
        coil_u32_t reg = dst_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        if (src_header.value_type == COIL_VAL_I32 || src_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate */
            instruction_buffer[buffer_index++] = 0x81; /* SUB r32, imm32 */
            instruction_buffer[buffer_index++] = 0xE8 + (reg & 0x7); /* ModRM */
            memcpy(instruction_buffer + buffer_index, &src_value.imm32, 4);
            buffer_index += 4;
        } else if (src_header.value_type == COIL_VAL_I8 || src_header.value_type == COIL_VAL_U8) {
            /* 8-bit immediate */
            instruction_buffer[buffer_index++] = 0x83; /* SUB r32, imm8 */
            instruction_buffer[buffer_index++] = 0xE8 + (reg & 0x7); /* ModRM */
            instruction_buffer[buffer_index++] = src_value.imm8;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", src_header.value_type);
            return -1;
        }
    } else if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_REG) {
        /* SUB reg, reg */
        coil_u32_t dst_reg = dst_value.reg_id;
        coil_u32_t src_reg = src_value.reg_id;
        
        if (dst_reg >= X86_REG_COUNT || src_reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID\n");
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0x29; /* SUB r/m32, r32 */
        instruction_buffer[buffer_index++] = 0xC0 + ((src_reg & 0x7) << 3) + (dst_reg & 0x7); /* ModRM */
    } else {
        fprintf(stderr, "Unsupported operand combination for SUB instruction\n");
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle RET instruction */
static int handle_ret(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    (void)instr;  /* Unused */
    (void)section;  /* Unused */
    (void)pos;  /* Unused */
    
    /* x86 RET is 0xC3 */
    instruction_buffer[0] = 0xC3;
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, 1) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle JMP instruction */
static int handle_jmp(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t op_header;
    coil_offset_t op_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand value */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
        coil_u8_t imm8;
    } op_value;
    
    /* Read operand */
    new_pos = read_operand(section, new_pos, &op_header, &op_offset, 
                          &op_value, sizeof(op_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand types */
    if (op_header.type == COIL_TYPEOP_REG) {
        /* JMP reg */
        coil_u32_t reg = op_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0xFF; /* JMP r/m32 */
        instruction_buffer[buffer_index++] = 0xE0 + (reg & 0x7); /* ModRM */
    } else if (op_header.type == COIL_TYPEOP_IMM) {
        /* JMP imm (relative) */
        if (op_header.value_type == COIL_VAL_I32 || op_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate (relative) */
            instruction_buffer[buffer_index++] = 0xE9; /* JMP rel32 */
            memcpy(instruction_buffer + buffer_index, &op_value.imm32, 4);
            buffer_index += 4;
        } else if (op_header.value_type == COIL_VAL_I8 || op_header.value_type == COIL_VAL_U8) {
            /* 8-bit immediate (relative) */
            instruction_buffer[buffer_index++] = 0xEB; /* JMP rel8 */
            instruction_buffer[buffer_index++] = op_value.imm8;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", op_header.value_type);
            return -1;
        }
    } else {
        fprintf(stderr, "Unsupported operand type for JMP instruction: %u\n", op_header.type);
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle CALL instruction */
static int handle_call(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t op_header;
    coil_offset_t op_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand value */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
    } op_value;
    
    /* Read operand */
    new_pos = read_operand(section, new_pos, &op_header, &op_offset, 
                          &op_value, sizeof(op_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand types */
    if (op_header.type == COIL_TYPEOP_REG) {
        /* CALL reg */
        coil_u32_t reg = op_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0xFF; /* CALL r/m32 */
        instruction_buffer[buffer_index++] = 0xD0 + (reg & 0x7); /* ModRM */
    } else if (op_header.type == COIL_TYPEOP_IMM) {
        /* CALL imm (relative) */
        if (op_header.value_type == COIL_VAL_I32 || op_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate (relative) */
            instruction_buffer[buffer_index++] = 0xE8; /* CALL rel32 */
            memcpy(instruction_buffer + buffer_index, &op_value.imm32, 4);
            buffer_index += 4;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", op_header.value_type);
            return -1;
        }
    } else {
        fprintf(stderr, "Unsupported operand type for CALL instruction: %u\n", op_header.type);
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}

/* Handle CMP instruction */
static int handle_cmp(coil_instrmem_t* instr, coil_section_t* section, coil_size_t* pos, nof_section* output) {
    coil_operand_header_t dst_header, src_header;
    coil_offset_t dst_offset, src_offset;
    coil_size_t new_pos = *pos;
    unsigned char buffer_index = 0;
    
    /* Storage for operand values */
    union {
        coil_u32_t reg_id;
        coil_i32_t imm32;
        coil_u8_t imm8;
    } dst_value, src_value;
    
    /* Read destination operand */
    new_pos = read_operand(section, new_pos, &dst_header, &dst_offset, 
                          &dst_value, sizeof(dst_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Read source operand */
    new_pos = read_operand(section, new_pos, &src_header, &src_offset, 
                          &src_value, sizeof(src_value));
    if (new_pos == 0) {
        return -1;
    }
    
    /* Update position */
    *pos = new_pos;
    
    /* Handle different operand combinations */
    if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_IMM) {
        /* CMP reg, imm */
        coil_u32_t reg = dst_value.reg_id;
        
        if (reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID: %u\n", reg);
            return -1;
        }
        
        if (src_header.value_type == COIL_VAL_I32 || src_header.value_type == COIL_VAL_U32) {
            /* 32-bit immediate */
            instruction_buffer[buffer_index++] = 0x81; /* CMP r32, imm32 */
            instruction_buffer[buffer_index++] = 0xF8 + (reg & 0x7); /* ModRM */
            memcpy(instruction_buffer + buffer_index, &src_value.imm32, 4);
            buffer_index += 4;
        } else if (src_header.value_type == COIL_VAL_I8 || src_header.value_type == COIL_VAL_U8) {
            /* 8-bit immediate */
            instruction_buffer[buffer_index++] = 0x83; /* CMP r32, imm8 */
            instruction_buffer[buffer_index++] = 0xF8 + (reg & 0x7); /* ModRM */
            instruction_buffer[buffer_index++] = src_value.imm8;
        } else {
            fprintf(stderr, "Unsupported immediate value type: %u\n", src_header.value_type);
            return -1;
        }
    } else if (dst_header.type == COIL_TYPEOP_REG && src_header.type == COIL_TYPEOP_REG) {
        /* CMP reg, reg */
        coil_u32_t dst_reg = dst_value.reg_id;
        coil_u32_t src_reg = src_value.reg_id;
        
        if (dst_reg >= X86_REG_COUNT || src_reg >= X86_REG_COUNT) {
            fprintf(stderr, "Invalid register ID\n");
            return -1;
        }
        
        instruction_buffer[buffer_index++] = 0x39; /* CMP r/m32, r32 */
        instruction_buffer[buffer_index++] = 0xC0 + ((src_reg & 0x7) << 3) + (dst_reg & 0x7); /* ModRM */
    } else {
        fprintf(stderr, "Unsupported operand combination for CMP instruction\n");
        return -1;
    }
    
    /* Write to output section */
    if (nof_write_section(output, instruction_buffer, buffer_index) != 0) {
        return -1;
    }
    
    return 0;
}