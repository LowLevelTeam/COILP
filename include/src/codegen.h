/**
* @file include/src/codegen.h
* @brief Defines the private interface for generating code.
*/

/**
* @brief The code generator context structure
*/
typedef struct cop_gen cop_gen_t;

/**
* @brief Initalize the code generator
*
* @param gen The context structure to hold generator information
* @param conf The configuration structure to hold native compilation information
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_codegen_init(cop_gen_t *gen, cop_conf_t *conf);

/**
* @brief Deinitalize the code generator
*
* @param gen The context structure to hold generator information
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_codegen_deinit(cop_gen_t *gen);

/**
* @brief Process a COIL section into native machine code
*
* @param gen The context structure to hold generator information
* @param dest The destination native object section to hold the machine code
* @param src The source COIL code to be compiled
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_generate(cop_gen_t *gen, nof_section_t *dest, coil_section_t *src);
