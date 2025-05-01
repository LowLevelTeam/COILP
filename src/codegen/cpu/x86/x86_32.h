// Source Header file, only included once in x86 main.c

// Each function will need to find out the type operands then construct the corresponding instructions for the functionality.
// since 64 bit integers are supported instructions may have to compile into multiple instructions with higher and lower
// like add lower 16 add higher 16 for 32 bit addition or extended for 64 bit integers.
// this emulation is not supported with floats as of yet, this is a more complex task and will be completed in the future.
// floats don't have to be supported at all.

// Control Flow Operations
coil_err_t __x86_codegen_comp32_nop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_br(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_jmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_call(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_ret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_cmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_tes(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Memory Operations
coil_err_t __x86_codegen_comp32_mov(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_push(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_pop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_lea(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Arithmetic Operations
coil_err_t __x86_codegen_comp32_add(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sub(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_mul(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_div(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_mod(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_inc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_dec(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_neg(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Control Flow Operations
coil_err_t __x86_codegen_comp32_and(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_or(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_xor(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_not(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_shl(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_shr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sal(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sar(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Type Operations
coil_err_t __x86_codegen_comp32_cvt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// PU Operations
coil_err_t __x86_codegen_comp32_int(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_iret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_cli(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sti(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_syscall(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sysret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_rdtsc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Arch Operations
coil_err_t __x86_codegen_comp32_cpuid(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_rdmsr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_wrmsr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_lgdt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sgdt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_lidt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sidt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_rdpmc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Directive Operations
coil_err_t __x86_codegen_comp32_sparam(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_gparam(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_sret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp32_gret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

