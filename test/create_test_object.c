/**
 * create_test_object.c
 * Creates a simple COIL object file with an "add_one" function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <coil/obj.h>
#include <coil/section.h>
#include <coil/instr.h>
#include <coil/types.h>

/**
 * Create a .text section with the add_one function
 * 
 * Function: int add_one(int x)
 * Implementation:
 *   - Takes an argument in register 0 (r0/eax)
 *   - Adds 1 to it
 *   - Returns result in register 0 (r0/eax)
 */
static coil_err_t create_text_section(coil_section_t *section) {
    coil_err_t err;
    
    // Function prologue (save old EBP, set up stack frame)
    // PUSH EBP
    err = coil_instrflag_encode(section, COIL_OP_PUSH, COIL_INSTRFLAG_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    coil_u32_t reg_ebp = 5; // EBP is register 5
    err = coil_operand_encode_data(section, &reg_ebp, sizeof(reg_ebp));
    if (err != COIL_ERR_GOOD) return err;

    // MOV EBP, ESP
    err = coil_instrflag_encode(section, COIL_OP_MOV, COIL_INSTRFLAG_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &reg_ebp, sizeof(reg_ebp));
    if (err != COIL_ERR_GOOD) return err;
    
    coil_u32_t reg_esp = 4; // ESP is register 4
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &reg_esp, sizeof(reg_esp));
    if (err != COIL_ERR_GOOD) return err;
    
    // Function body - ADD EAX, 1
    // In CDECL calling convention, first parameter is in EAX (reg 0)
    err = coil_instrflag_encode(section, COIL_OP_ADD, COIL_INSTRFLAG_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    coil_u32_t reg_eax = 0; // EAX is register 0
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &reg_eax, sizeof(reg_eax));
    if (err != COIL_ERR_GOOD) return err;
    
    coil_i32_t value = 1;
    err = coil_operand_encode(section, COIL_TYPEOP_IMM, COIL_VAL_I32, COIL_MOD_CONST);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &value, sizeof(value));
    if (err != COIL_ERR_GOOD) return err;
    
    // Function epilogue - Restore old EBP and return
    // MOV ESP, EBP
    err = coil_instrflag_encode(section, COIL_OP_MOV, COIL_INSTRFLAG_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &reg_esp, sizeof(reg_esp));
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &reg_ebp, sizeof(reg_ebp));
    if (err != COIL_ERR_GOOD) return err;
    
    // POP EBP
    err = coil_instrflag_encode(section, COIL_OP_POP, COIL_INSTRFLAG_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode(section, COIL_TYPEOP_REG, COIL_VAL_REG, COIL_MOD_NONE);
    if (err != COIL_ERR_GOOD) return err;
    
    err = coil_operand_encode_data(section, &reg_ebp, sizeof(reg_ebp));
    if (err != COIL_ERR_GOOD) return err;
    
    // RET
    err = coil_instr_encode(section, COIL_OP_RET);
    if (err != COIL_ERR_GOOD) return err;
    
    return COIL_ERR_GOOD;
}

/**
 * Create the string table section
 */
static coil_err_t create_strtab_section(coil_section_t *section) {
    coil_err_t err;
    
    // Null string (required at index 0)
    err = coil_section_putstr(section, "");
    if (err != COIL_ERR_GOOD) return err;
    
    // Function name
    err = coil_section_putstr(section, "add_one");
    if (err != COIL_ERR_GOOD) return err;
    
    return COIL_ERR_GOOD;
}

/**
 * Create the symbol table section
 */
static coil_err_t create_symtab_section(coil_section_t *section, coil_u16_t text_index) {
    // This is a simplified implementation - in a real implementation,
    // you would properly encode symbol table entries according to the COIL format
    // For this example, we'll just leave it empty
    (void)section;
    (void)text_index;
    return COIL_ERR_GOOD;
}

int main(int argc, char *argv[]) {
    coil_object_t obj;
    coil_section_t text_section, strtab_section, symtab_section;
    coil_err_t err;
    const char *output_file = "add_one.coil";
    
    if (argc > 1) {
        output_file = argv[1];
    }
    
    // Initialize error handling
    coil_error_init();
    
    // Initialize COIL object
    err = coil_obj_init(&obj, COIL_OBJ_INIT_EMPTY);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to initialize COIL object\n");
        return 1;
    }
    
    // Create text section
    err = coil_section_init(&text_section, 1024, COIL_SECT_MODE_R | COIL_SECT_MODE_W);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to create text section\n");
        coil_obj_cleanup(&obj);
        return 1;
    }
    
    err = create_text_section(&text_section);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to initialize text section content\n");
        coil_section_cleanup(&text_section);
        coil_obj_cleanup(&obj);
        return 1;
    }
    
    // Create string table section
    err = coil_section_init(&strtab_section, 256, COIL_SECT_MODE_R | COIL_SECT_MODE_W);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to create string table section\n");
        coil_section_cleanup(&text_section);
        coil_obj_cleanup(&obj);
        return 1;
    }
    
    err = create_strtab_section(&strtab_section);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to initialize string table section content\n");
        coil_section_cleanup(&strtab_section);
        coil_section_cleanup(&text_section);
        coil_obj_cleanup(&obj);
        return 1;
    }
    
    // Create symbol table section
    err = coil_section_init(&symtab_section, 512, COIL_SECT_MODE_R | COIL_SECT_MODE_W);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to create symbol table section\n");
        coil_section_cleanup(&strtab_section);
        coil_section_cleanup(&text_section);
        coil_obj_cleanup(&obj);
        return 1;
    }
    
    // Add sections to the object file
    coil_u16_t text_index, strtab_index, symtab_index;
    
    err = coil_obj_create_section(&obj, COIL_SECTION_PROGBITS, ".text", 
                               COIL_SECTION_FLAG_CODE | COIL_SECTION_FLAG_ALLOC,
                               &text_section, &text_index);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to add text section to object\n");
        goto cleanup;
    }
    
    err = coil_obj_create_section(&obj, COIL_SECTION_STRTAB, ".strtab", 
                               COIL_SECTION_FLAG_NONE,
                               &strtab_section, &strtab_index);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to add string table section to object\n");
        goto cleanup;
    }
    
    err = create_symtab_section(&symtab_section, text_index);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to initialize symbol table section content\n");
        goto cleanup;
    }
    
    err = coil_obj_create_section(&obj, COIL_SECTION_SYMTAB, ".symtab", 
                               COIL_SECTION_FLAG_NONE,
                               &symtab_section, &symtab_index);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to add symbol table section to object\n");
        goto cleanup;
    }
    
    // Save the object file
    err = coil_obj_save_file(&obj, output_file);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to save COIL object file\n");
        goto cleanup;
    }
    
    printf("Successfully created COIL object file: %s\n", output_file);
    
cleanup:
    coil_obj_cleanup(&obj);
    coil_error_shutdown();
    
    return (err == COIL_ERR_GOOD) ? 0 : 1;
}