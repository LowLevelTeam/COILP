/**
 * processor.h - COIL Object Processor core
 * Core processing logic for the COIL Object Processor
 */

#ifndef COP_PROCESSOR_H
#define COP_PROCESSOR_H

#include <coil/obj.h>
#include <coil/section.h>
#include <coil/instr.h>
#include <nof/nof.h>

/**
 * Process a COIL object file and generate a native object file
 *
 * @param input_file Path to the input COIL object file
 * @param output_file Path to the output native object file
 * @param arch Target architecture (NOF_ARCH_*)
 * @return 0 on success, non-zero on error
 */
int cop_process_file(const char* input_file, const char* output_file, int arch);

/**
 * Process a single COIL section and add it to the native object
 *
 * @param coil_obj COIL object 
 * @param coil_section COIL section to process
 * @param nof_ctx Native object context
 * @param is_code Whether the section contains executable code
 * @return 0 on success, non-zero on error
 */
int cop_process_section(coil_object_t* coil_obj, coil_section_t* coil_section, 
                        nof_context* nof_ctx, int is_code, int arch);

/**
 * Generate native code for a COIL code section
 *
 * @param coil_section COIL section containing code
 * @param nof_section Native section to add code to
 * @param arch Target architecture (NOF_ARCH_*)
 * @return 0 on success, non-zero on error
 */
int cop_generate_code(coil_section_t* coil_section, nof_section* nof_section, int arch);

/**
 * Copy data from a COIL data section to a native data section
 *
 * @param coil_section COIL section containing data
 * @param nof_section Native section to add data to
 * @return 0 on success, non-zero on error
 */
int cop_copy_data(coil_section_t* coil_section, nof_section* nof_section);

#endif /* COP_PROCESSOR_H */