/**
* @file include/cop/conf.h
* @brief Defines the standard interface for creating, modifying and deleting configurations
*
* Handles parsing the configuration 
*/

/**
* @brief ABI Information
*/
typedef struct cop_conf_abi {
  uint64_t ID; // A target ABI to address in COIL code

  // TODO...
} cop_conf_abi_t;

/**
* @brief Target Information
*/
typedef struct cop_conf_target {
  uint64_t ID; // A target ID to address in COIL code

  coilt_pu_t pu;
  coilt_arch_t arch;

  // TODO...
} cop_conf_target_t;

/**
* @brief The configuration parser context structure
*/
typedef struct cop_conf {
  // Output information
  nof_fmt_t fmt;
  nof_type_t type; // executable, static library, etc...

  // Optimization
  int size;   // 0-3 (Low program size cost)
  int speed;  // 0-3 (Low overhead cost)
  int memory; // 0-3 (Low runtime memory cost)

  // Targets
  cop_conf_target_t *targets;

  // ABIs
  cop_conf_abi_t *ABIs;
} cop_conf_t;

/**
* @brief Initalize the configuration parser
*
* @param conf The context structure to hold the parsing results
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_conf_init(cop_conf_t *conf);

/**
* @brief Deinitalize the configuration parser
*
* @param conf The context structure to hold the parsing results
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_conf_deinit(cop_conf_t *conf);

/**
* @brief Process a COIL configuration
*
* @param conf The context structure to hold the parsing results
* @param confsrc The loaded configuration data
* @return Standardized COIL Toolchain Error Code
*/
coilt_err_t cop_process(cop_conf_t *conf, const void *confsrc);


