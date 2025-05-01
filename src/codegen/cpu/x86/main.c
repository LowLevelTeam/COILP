#include <src/codegen.h>

extern coil_err_t __cop_codegen_x86   (coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect);
extern coil_err_t __cop_codegen_x86_32(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect);
extern coil_err_t __cop_codegen_x86_64(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect);

// the higher bit architecture may utilize some previous compilation functions but never the other way around

#include "x86_16.h"

coil_err_t __cop_codegen_x86(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  // process each instruction and filter based on opcode into a specific __x86_codegen_comp16_* function
}

#include "x86_32.h"

coil_err_t __cop_codegen_x86_32(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  // process each instruction and filter based on opcode into a specific __x86_codegen_comp32_* function
}

#include "x86_64.h"

coil_err_t __cop_codegen_x86_64(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  // process each instruction and filter based on opcode into a specific __x86_codegen_comp64_* function
}
