/**
 * codegen_x86.h - x86-32 code generator
 * Translates COIL instructions to x86-32 machine code
 */

#ifndef COP_CODEGEN_X86_H
#define COP_CODEGEN_X86_H

#include <coil/section.h>
#include <nof/nof.h>

/**
 * Generate x86-32 machine code from COIL instructions
 *
 * @param coil_section COIL section containing code
 * @param nof_section Native section to add code to
 * @return 0 on success, non-zero on error
 */
int cop_codegen_x86(coil_section_t* coil_section, nof_section* nof_section);

/**
 * x86 Register enumeration
 */
typedef enum {
    X86_REG_EAX = 0,
    X86_REG_ECX,
    X86_REG_EDX,
    X86_REG_EBX,
    X86_REG_ESP,
    X86_REG_EBP,
    X86_REG_ESI,
    X86_REG_EDI,
    
    X86_REG_COUNT
} x86_register_t;

/**
 * x86 Instruction ModRM byte
 * Used to encode register and memory operands
 */
typedef struct {
    unsigned char mod;  /* Mode (0-3) */
    unsigned char reg;  /* Register operand (0-7) */
    unsigned char rm;   /* Register/memory operand (0-7) */
} x86_modrm_t;

/**
 * x86 Instruction SIB byte
 * Used for complex memory addressing
 */
typedef struct {
    unsigned char scale; /* Scale factor (0-3) for index */
    unsigned char index; /* Index register (0-7) */
    unsigned char base;  /* Base register (0-7) */
} x86_sib_t;

#endif /* COP_CODEGEN_X86_H */