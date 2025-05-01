// Source Header file, only included once in x86 main.c

// Each function will need to find out the type operands then construct the corresponding instructions for the functionality.
// since 64 bit integers are supported instructions may have to compile into multiple instructions with higher and lower
// like add lower 16 add higher 16 for 32 bit addition or extended for 64 bit integers.
// this emulation is not supported with floats as of yet, this is a more complex task and will be completed in the future.
// floats don't have to be supported at all.

// Control Flow Operations
coil_err_t __x86_codegen_comp16_nop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_br(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_jmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_call(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_ret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_cmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_tes(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Memory Operations
coil_err_t __x86_codegen_comp16_mov(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_push(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_pop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_lea(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Arithmetic Operations
coil_err_t __x86_codegen_comp16_add(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sub(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_mul(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_div(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_mod(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_inc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_dec(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_neg(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Control Flow Operations
coil_err_t __x86_codegen_comp16_and(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_or(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_xor(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_not(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_shl(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_shr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sal(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sar(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Type Operations
coil_err_t __x86_codegen_comp16_cvt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// PU Operations
coil_err_t __x86_codegen_comp16_int(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_iret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_cli(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sti(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_syscall(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sysret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_rdtsc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Arch Operations
coil_err_t __x86_codegen_comp16_cpuid(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_rdmsr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_wrmsr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_lgdt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sgdt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_lidt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sidt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_rdpmc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Directive Operations
coil_err_t __x86_codegen_comp16_sparam(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_gparam(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_gret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

