/**
 * utils.c - COIL Object Processor utilities
 * Utility functions for the COIL Object Processor
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <coil/err.h>

#include "utils.h"

/* Global verbosity setting */
static int g_verbose = 0;

/**
 * Initialize error handling system
 */
void cop_init_error_handling(void) {
    coil_error_init();
    coil_error_set_callback(cop_error_callback, NULL);
}

/**
 * Clean up error handling system
 */
void cop_cleanup_error_handling(void) {
    coil_error_shutdown();
}

/**
 * Set verbosity level
 */
void cop_set_verbose(int verbose) {
    g_verbose = verbose;
}

/**
 * Get verbosity level
 */
int cop_get_verbose(void) {
    return g_verbose;
}

/**
 * Log a verbose message
 */
void cop_log_verbose(const char* format, ...) {
    va_list args;
    
    if (!g_verbose) {
        return;
    }
    
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    /* Add a newline if not already present */
    if (format[0] != '\0' && format[strlen(format) - 1] != '\n') {
        printf("\n");
    }
}

/**
 * Custom error callback for COIL errors
 */
void cop_error_callback(coil_error_level_t level, const char* message, 
                        const coil_error_position_t* position, void* user_data) {
    (void)user_data; /* Unused */
    
    const char* level_str = "UNKNOWN";
    FILE* stream = stdout;
    
    /* Determine level string and output stream */
    switch (level) {
        case COIL_LEVEL_INFO:
            level_str = "INFO";
            break;
            
        case COIL_LEVEL_WARNING:
            level_str = "WARNING";
            break;
            
        case COIL_LEVEL_ERROR:
            level_str = "ERROR";
            stream = stderr;
            break;
            
        case COIL_LEVEL_FATAL:
            level_str = "FATAL";
            stream = stderr;
            break;
    }
    
    /* Print message with or without position information */
    if (position && position->file) {
        fprintf(stream, "[%s] %s (%s:%zu)\n", level_str, message, position->file, position->line);
    } else {
        fprintf(stream, "[%s] %s\n", level_str, message);
    }
}