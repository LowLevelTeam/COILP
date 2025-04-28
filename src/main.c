/**
 * main.c - COIL Object Processor (COP)
 * Entry point for the COIL Object Processor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <coil/obj.h>
#include <coil/section.h>
#include <coil/err.h>
#include <nof/nof.h>

#include "processor.h"
#include "utils.h"

/* Version information */
#define COP_VERSION_MAJOR 0
#define COP_VERSION_MINOR 1
#define COP_VERSION_PATCH 0

/* Default values */
#define DEFAULT_OUTPUT_SUFFIX ".o"

/* Program options */
typedef struct {
    const char* input_file;
    const char* output_file;
    int arch;
    int verbose;
    int show_version;
    int show_help;
} cop_options_t;

/* Print usage information */
static void print_usage(const char* program_name) {
    printf("Usage: %s [options] <input-file>\n", program_name);
    printf("\nOptions:\n");
    printf("  -o, --output <file>    Specify output file name\n");
    printf("  -a, --arch <arch>      Target architecture (default: x86_32)\n");
    printf("                         Supported: x86_32\n");
    printf("  -v, --verbose          Enable verbose output\n");
    printf("  --version              Display version information\n");
    printf("  -h, --help             Display this help and exit\n");
}

/* Print version information */
static void print_version() {
    printf("COIL Object Processor (COP) version %d.%d.%d\n", 
           COP_VERSION_MAJOR, COP_VERSION_MINOR, COP_VERSION_PATCH);
}

/* Parse command line options */
static int parse_options(int argc, char* argv[], cop_options_t* options) {
    int c;
    int option_index = 0;
    
    static struct option long_options[] = {
        {"output",  required_argument, 0, 'o'},
        {"arch",    required_argument, 0, 'a'},
        {"verbose", no_argument,       0, 'v'},
        {"version", no_argument,       0, 0},
        {"help",    no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };
    
    /* Set defaults */
    options->input_file = NULL;
    options->output_file = NULL;
    options->arch = NOF_ARCH_X86;  /* Default to x86-32 */
    options->verbose = 0;
    options->show_version = 0;
    options->show_help = 0;
    
    while ((c = getopt_long(argc, argv, "o:a:vh", long_options, &option_index)) != -1) {
        switch (c) {
            case 0:
                /* Long option without a short equivalent */
                if (strcmp(long_options[option_index].name, "version") == 0) {
                    options->show_version = 1;
                }
                break;
                
            case 'o':
                options->output_file = optarg;
                break;
                
            case 'a':
                if (strcmp(optarg, "x86_32") == 0) {
                    options->arch = NOF_ARCH_X86;
                } else {
                    fprintf(stderr, "Unsupported architecture: %s\n", optarg);
                    return -1;
                }
                break;
                
            case 'v':
                options->verbose = 1;
                break;
                
            case 'h':
                options->show_help = 1;
                break;
                
            case '?':
                /* getopt_long already printed an error message */
                return -1;
                
            default:
                fprintf(stderr, "Unexpected option: %c\n", c);
                return -1;
        }
    }
    
    /* Get input file */
    if (optind < argc) {
        options->input_file = argv[optind];
    }
    
    return 0;
}

/* Generate default output filename if none specified */
static char* generate_output_filename(const char* input_file) {
    char* result;
    const char* extension;
    size_t base_len;
    
    /* Find the extension */
    extension = strrchr(input_file, '.');
    if (extension == NULL) {
        /* No extension, just append .o */
        base_len = strlen(input_file);
        result = (char*)malloc(base_len + strlen(DEFAULT_OUTPUT_SUFFIX) + 1);
        if (result == NULL) {
            return NULL;
        }
        
        strcpy(result, input_file);
        strcat(result, DEFAULT_OUTPUT_SUFFIX);
    } else {
        /* Replace extension with .o */
        base_len = extension - input_file;
        result = (char*)malloc(base_len + strlen(DEFAULT_OUTPUT_SUFFIX) + 1);
        if (result == NULL) {
            return NULL;
        }
        
        strncpy(result, input_file, base_len);
        result[base_len] = '\0';
        strcat(result, DEFAULT_OUTPUT_SUFFIX);
    }
    
    return result;
}

/* Application entry point */
int main(int argc, char* argv[]) {
    cop_options_t options;
    char* auto_output_file = NULL;
    int result = EXIT_FAILURE;
    
    /* Initialize error handling */
    cop_init_error_handling();
    
    /* Parse command line options */
    if (parse_options(argc, argv, &options) != 0) {
        goto cleanup;
    }
    
    /* Show version and exit if requested */
    if (options.show_version) {
        print_version();
        result = EXIT_SUCCESS;
        goto cleanup;
    }
    
    /* Show help and exit if requested */
    if (options.show_help) {
        print_usage(argv[0]);
        result = EXIT_SUCCESS;
        goto cleanup;
    }
    
    /* Validate input */
    if (options.input_file == NULL) {
        fprintf(stderr, "Error: No input file specified\n");
        print_usage(argv[0]);
        goto cleanup;
    }
    
    /* Generate output filename if not specified */
    if (options.output_file == NULL) {
        auto_output_file = generate_output_filename(options.input_file);
        if (auto_output_file == NULL) {
            fprintf(stderr, "Error: Failed to generate output filename\n");
            goto cleanup;
        }
        options.output_file = auto_output_file;
    }
    
    /* Set verbosity level */
    cop_set_verbose(options.verbose);
    
    if (options.verbose) {
        printf("COIL Object Processor (COP)\n");
        printf("Input file: %s\n", options.input_file);
        printf("Output file: %s\n", options.output_file);
        printf("Target architecture: %s\n", (options.arch == NOF_ARCH_X86) ? "x86-32" : "Unknown");
    }
    
    /* Process the COIL object file */
    if (cop_process_file(options.input_file, options.output_file, options.arch) != 0) {
        fprintf(stderr, "Error: Failed to process COIL object file\n");
        goto cleanup;
    }
    
    result = EXIT_SUCCESS;
    if (options.verbose) {
        printf("Successfully processed COIL object file\n");
    }
    
cleanup:
    free(auto_output_file);
    cop_cleanup_error_handling();
    return result;
}