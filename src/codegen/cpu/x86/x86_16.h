// Source Header file, only included once in x86 main.c

// Each function will need to find out the type operands then construct the corresponding instructions for the functionality.
// since 64 bit integers are supported instructions may have to compile into multiple instructions with higher and lower
// like add lower 16 add higher 16 for 32 bit addition or extended for 64 bit integers.
// this emulation is not supported with floats as of yet, this is a more complex task and will be completed in the future.
// floats don't have to be supported at all.

// Control Flow Operations
coil_err_t __x86_codegen_comp16_nop(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  char nopbyte = 0x90;
  return coil_section_write(sect, &nopbyte, 1, NULL);
}
coil_err_t __x86_codegen_comp16_br(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  coil_err_t err;
  
  // Get the operands from the section
  coil_size_t pos = sect->rindex;
  
  // Decode first operand
  coil_operand_header_t op1_header;
  coil_offset_t op1_offset;
  pos = coil_operand_decode(sect, pos, &op1_header, &op1_offset);
  if (!pos) return coil_error_get_last();
  
  // Decode second operand
  coil_operand_header_t op2_header;
  coil_offset_t op2_offset;
  pos = coil_operand_decode(sect, pos, &op2_header, &op2_offset);
  if (!pos) return coil_error_get_last();
  
  
  // Example: Handle register-to-register add for different sizes
  if (op1_header.type == COIL_TYPEOP_REG && op2_header.type == COIL_TYPEOP_REG) {
    // Decode register values
    coil_u32_t reg1, reg2;
    coil_size_t valsize;
    
    pos = coil_operand_decode_data(sect, pos, &reg1, sizeof(reg1), &valsize, &op1_header);
    if (!pos) return coil_error_get_last();
    
    pos = coil_operand_decode_data(sect, pos, &reg2, sizeof(reg2), &valsize, &op2_header);
    if (!pos) return coil_error_get_last();
    
    // Generate x86-64 add instruction based on operand sizes
    // For simplicity, we're just generating a simple ADD opcode without proper ModR/M encoding
    
    coil_byte_t x86_add_r64_r64[] = {0x48, 0x01, 0xC0}; // ADD RAX, RAX (as a placeholder)
    coil_byte_t x86_add_r32_r32[] = {0x01, 0xC0};       // ADD EAX, EAX (as a placeholder)
    coil_byte_t x86_add_r16_r16[] = {0x66, 0x01, 0xC0}; // ADD AX, AX (as a placeholder)
    coil_byte_t x86_add_r8_r8[] = {0x00, 0xC0};         // ADD AL, AL (as a placeholder)
    
    coil_size_t bytes_written;
    
    switch (op1_header.value_type) {
      case COIL_VAL_I64:
      case COIL_VAL_U64:
        // Adjust the instruction for the actual registers (simplified)
        x86_add_r64_r64[2] = 0xC0 | ((reg1 & 0x7) << 3) | (reg2 & 0x7);
        err = coil_section_write(native_sect, x86_add_r64_r64, sizeof(x86_add_r64_r64), &bytes_written);
        break;
        
      case COIL_VAL_I32:
      case COIL_VAL_U32:
        // Adjust the instruction for the actual registers (simplified)
        x86_add_r32_r32[1] = 0xC0 | ((reg1 & 0x7) << 3) | (reg2 & 0x7);
        err = coil_section_write(native_sect, x86_add_r32_r32, sizeof(x86_add_r32_r32), &bytes_written);
        break;
        
      case COIL_VAL_I16:
      case COIL_VAL_U16:
        // Adjust the instruction for the actual registers (simplified)
        x86_add_r16_r16[2] = 0xC0 | ((reg1 & 0x7) << 3) | (reg2 & 0x7);
        err = coil_section_write(native_sect, x86_add_r16_r16, sizeof(x86_add_r16_r16), &bytes_written);
        break;
        
      case COIL_VAL_I8:
      case COIL_VAL_U8:
        // Adjust the instruction for the actual registers (simplified)
        x86_add_r8_r8[1] = 0xC0 | ((reg1 & 0x7) << 3) | (reg2 & 0x7);
        err = coil_section_write(native_sect, x86_add_r8_r8, sizeof(x86_add_r8_r8), &bytes_written);
        break;
        
      default:
        // Unsupported value type
        coil_log(COIL_LEVEL_ERROR, "Unsupported value type for ADD: %d", op1_header.value_type);
        return COIL_ERR_NOTSUP;
    }
    
    if (err != COIL_ERR_GOOD) {
      return err;
    }
  }

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_jmp(coil_object_t *obj, coil_section_header_tw *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_call(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_ret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  char nopbyte = 0xC3;
  return coil_section_write(sect, &nopbyte, 1, NULL);
}
coil_err_t __x86_codegen_comp16_cmp(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_test(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {

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
  char nopbyte = 0xCF;
  return coil_section_write(sect, &nopbyte, 1, NULL);
}
coil_err_t __x86_codegen_comp16_cli(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  char nopbyte = 0xFA;
  return coil_section_write(sect, &nopbyte, 1, NULL);
}
coil_err_t __x86_codegen_comp16_sti(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  char nopbyte = 0xFB;
  return coil_section_write(sect, &nopbyte, 1, NULL);
}
coil_err_t __x86_codegen_comp16_syscall(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  // Encode __x86_codegen_comp16_int with 0x80
  return COIL_ERR_GOOD;
}
coil_err_t __x86_codegen_comp16_sysret(coil_object_t *obj, coil_section_header_t *header, coil_section_t *sect) {
  return __x86_codegen_comp16_iret(obj, header, sect);
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

