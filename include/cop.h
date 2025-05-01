/**
* @file cop.h
* @brief Main public API header for the COIL Object Processor (COP)
*
* This file defines the public interface for the COIL Object Processor,
* which translates COIL IR to native machine code.
*/

#ifndef __COP_INCLUDE_GUARD_H
#define __COP_INCLUDE_GUARD_H

#include <coil.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Process the COIL IR and generate native code
*
* Calls underlying code generator process function based on config
*
* @param ssrc Source COIL object
* @param dest Destination COIL object
* @param conf Compilation target
* 
* @return cop_err_t COP_ERR_GOOD on success
* @return cop_err_t Error code on failure
*/
cop_err_t cop_process(coil_object_t *dest, coil_object_t *src);

#ifdef __cplusplus
}
#endif

#endif /* __COP_INCLUDE_GUARD_H */