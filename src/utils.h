/**
 * utils.h - COIL Object Processor utilities
 * Utility functions for the COIL Object Processor
 */

#ifndef COP_UTILS_H
#define COP_UTILS_H

#include <coil/err.h>

/**
 * Initialize error handling system
 */
void cop_init_error_handling(void);

/**
 * Clean up error handling system
 */
void cop_cleanup_error_handling(void);

/**
 * Set verbosity level
 *
 * @param verbose Non-zero to enable verbose output
 */
void cop_set_verbose(int verbose);

/**
 * Get verbosity level
 *
 * @return Current verbosity level
 */
int cop_get_verbose(void);

/**
 * Log a verbose message
 *
 * @param format Format string (printf-style)
 * @param ... Arguments for the format string
 */
void cop_log_verbose(const char* format, ...);

/**
 * Custom error callback for COIL errors
 *
 * @param level Error severity level
 * @param message Error message
 * @param position Error position information
 * @param user_data User data pointer
 */
void cop_error_callback(coil_error_level_t level, const char* message, 
                        const coil_error_position_t* position, void* user_data);

#endif /* COP_UTILS_H */