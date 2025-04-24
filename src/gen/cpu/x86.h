

typedef struct conf_cpu_x86 {
  int mode; // 0 = x86, 1 = protected, 2 = long
  
  // Add x86 extensions
} conf_cpu_x86_t;

/**
* @brief Write a COIL instruction to a x86 native instruction
*/
void coil_x86_write_native(config *conf, coil_section_t *csect, native_section_t *nsect);




