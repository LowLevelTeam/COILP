// Source Header file, only included once in x86 main.c

// Each function will need to find out the type operands then construct the corresponding instructions for the functionality.
// since 64 bit integers are supported instructions may have to compile into multiple instructions with higher and lower
// like add lower 16 add higher 16 for 32 bit addition or extended for 64 bit integers.
// this emulation is not supported with floats as of yet, this is a more complex task and will be completed in the future.
// floats don't have to be supported at all.

// Control Flow Operations
coil_err_t __x86_codegen_comp64_nop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_br(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_jmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_call(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_ret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_cmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_tes(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Memory Operations
coil_err_t __x86_codegen_comp64_mov(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_push(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_pop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_lea(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Arithmetic Operations
coil_err_t __x86_codegen_comp64_add(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sub(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_mul(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_div(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_mod(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_inc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_dec(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_neg(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Control Flow Operations
coil_err_t __x86_codegen_comp64_and(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_or(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_xor(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_not(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_shl(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_shr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sal(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sar(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Type Operations
coil_err_t __x86_codegen_comp64_cvt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// PU Operations
coil_err_t __x86_codegen_comp64_int(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_iret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_cli(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sti(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_syscall(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sysret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_rdtsc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Arch Operations
coil_err_t __x86_codegen_comp64_cpuid(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_rdmsr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_wrmsr(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_lgdt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sgdt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_lidt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sidt(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_rdpmc(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

// Directive Operations
coil_err_t __x86_codegen_comp64_sparam(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_gparam(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_sret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp64_gret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}

