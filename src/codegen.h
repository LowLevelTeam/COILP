/**
* @file src/codegen.h
* @brief Main API header for code generation in the COIL Object Processor (COP)
*
* This file defines the interface for generating code within COIL
*/

#ifndef __COP_INCLUDE_GUARD_CODEGEN_H
#define __COP_INCLUDE_GUARD_CODEGEN_H

#include <cop.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Standard generator function for internal generators
*/
typedef coil_err_t (*cop_codegen_ft)(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect);

#ifdef __cplusplus
}
#endif

#endif /* __COP_INCLUDE_GUARD_CODEGEN_H */