/**
* @file include/src/opt.h
* @brief Defines the private interface for optimizing code.
*/

/**
* @brief The optimizer context structure
*/
typedef struct cop_opt cop_opt_t;

/**
* @brief Initalize the optimizer
*
* @param opt The context structure to hold optimizer information
* @param conf The configuration structure to hold optimization information
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_opt_init(cop_opt_t *opt, cop_conf_t *conf);

/**
* @brief Deinitalize the optimizer
*
* @param opt The context structure to hold optimizer information
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_opt_deinit(cop_opt_t *opt);

/**
* @brief Process a COIL section into a faster and more optimized coil section
*
* @param opt The context structure to hold optimizer information
* @param dest The destination COIL object to hold optimized results
* @param src The source COIL object to be optimized
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_optimize(cop_opt_t *opt, coil_section_t *dest, coil_section_t *src);


