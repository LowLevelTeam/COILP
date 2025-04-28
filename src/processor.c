/**
 * processor.c - COIL Object Processor core
 * Core processing logic for the COIL Object Processor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <coil/obj.h>
#include <coil/section.h>
#include <coil/instr.h>
#include <coil/types.h>
#include <nof/nof.h>
#include <nof/elf.h>

#include "processor.h"
#include "codegen_x86.h"
#include "utils.h"

/**
 * Process a COIL object file and generate a native object file
 */
int cop_process_file(const char* input_file, const char* output_file, int arch) {
    coil_object_t coil_obj;
    nof_context* nof_ctx = NULL;
    int result = -1;
    coil_err_t err;
    
    /* Initialize the COIL object */
    err = coil_obj_init(&coil_obj, 0);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to initialize COIL object\n");
        return -1;
    }
    
    /* Load the COIL object file */
    err = coil_obj_load_file(&coil_obj, input_file);
    if (err != COIL_ERR_GOOD) {
        fprintf(stderr, "Failed to load COIL object file: %s\n", input_file);
        goto cleanup_coil;
    }
    
    cop_log_verbose("Loaded COIL object file with %d sections", coil_obj.header.section_count);
    
    /* Create a new native object file */
    nof_ctx = nof_create(NOF_FORMAT_ELF, arch);
    if (nof_ctx == NULL) {
        fprintf(stderr, "Failed to create native object context\n");
        goto cleanup_coil;
    }
    
    /* Process each section in the COIL object */
    for (coil_u16_t i = 0; i < coil_obj.header.section_count; i++) {
        coil_section_t coil_section;
        int section_flags = 0;
        int is_code = 0;
        
        /* Load the section */
        err = coil_obj_load_section(&coil_obj, i, &coil_section, COIL_SECT_MODE_R);
        if (err != COIL_ERR_GOOD) {
            fprintf(stderr, "Failed to load section %d\n", i);
            goto cleanup;
        }
        
        /* Get section flags */
        section_flags = coil_obj.sectheaders[i].flags;
        
        /* Check if this is a code section */
        is_code = (section_flags & COIL_SECTION_FLAG_CODE) != 0;
        
        /* Process the section */
        if (cop_process_section(&coil_obj, &coil_section, nof_ctx, is_code, arch) != 0) {
            fprintf(stderr, "Failed to process section %d\n", i);
            goto cleanup;
        }
    }
    
    /* Save the native object file */
    if (nof_save(nof_ctx, output_file) != 0) {
        fprintf(stderr, "Failed to save native object file: %s\n", output_file);
        goto cleanup;
    }
    
    cop_log_verbose("Successfully created native object file: %s", output_file);
    result = 0;
    
cleanup:
    if (nof_ctx != NULL) {
        nof_free(nof_ctx);
    }
    
cleanup_coil:
    coil_obj_cleanup(&coil_obj);
    return result;
}

/**
 * Process a single COIL section and add it to the native object
 */
int cop_process_section(coil_object_t* coil_obj, coil_section_t* coil_section, 
                       nof_context* nof_ctx, int is_code, int arch) {
    nof_section* nof_section;
    int section_flags = 0;
    const char* section_name = NULL;
    char default_name[32];
    
    /* Get section name if available */
    if (coil_section->name != 0) {
        /* Look up section name in string table */
        coil_u16_t strtab_index;
        coil_section_t strtab;
        
        if (coil_obj_find_section(coil_obj, ".strtab", &strtab_index) == COIL_ERR_GOOD) {
            if (coil_obj_load_section(coil_obj, strtab_index, &strtab, COIL_SECT_MODE_R) == COIL_ERR_GOOD) {
                const char* str;
                if (coil_section_getstr(&strtab, coil_section->name, &str) == COIL_ERR_GOOD) {
                    section_name = str;
                }
            }
        }
    }
    
    /* Create a default name if no name found */
    if (section_name == NULL) {
        snprintf(default_name, sizeof(default_name), ".coil%u", (unsigned)coil_section->name);
        section_name = default_name;
    }
    
    cop_log_verbose("Processing section: %s (size: %zu, code: %s)",
                   section_name, coil_section->size, is_code ? "yes" : "no");
    
    /* Determine section flags */
    if (is_code) {
        section_flags = NOF_SECTION_CODE;
    } else {
        section_flags = NOF_SECTION_DATA;
    }
    
    /* Create native section */
    nof_section = nof_create_section(nof_ctx, section_name, section_flags);
    if (nof_section == NULL) {
        fprintf(stderr, "Failed to create native section: %s\n", section_name);
        return -1;
    }
    
    /* Process the section content */
    if (is_code) {
        return cop_generate_code(coil_section, nof_section, arch);
    } else {
        return cop_copy_data(coil_section, nof_section);
    }
}

/**
 * Generate native code for a COIL code section
 */
int cop_generate_code(coil_section_t* coil_section, nof_section* nof_section, int arch) {
    coil_size_t pos = 0;
    int result = -1;
    
    cop_log_verbose("Generating native code...");
    
    /* Select code generator based on architecture */
    switch (arch) {
        case NOF_ARCH_X86:
            result = cop_codegen_x86(coil_section, nof_section);
            break;
            
        default:
            fprintf(stderr, "Unsupported architecture for code generation\n");
            result = -1;
            break;
    }
    
    return result;
}

/**
 * Copy data from a COIL data section to a native data section
 */
int cop_copy_data(coil_section_t* coil_section, nof_section* nof_section) {
    /* Simply copy the data */
    if (coil_section->data != NULL && coil_section->size > 0) {
        if (nof_write_section(nof_section, coil_section->data, coil_section->size) != 0) {
            fprintf(stderr, "Failed to write data to native section\n");
            return -1;
        }
    }
    
    cop_log_verbose("Copied %zu bytes of data", coil_section->size);
    return 0;
}