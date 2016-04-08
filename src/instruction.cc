#include "instruction.h"
#include <cstdio>

void X86Instruction::Instruction::dec_opcode()
{
  switch(opcode[0])
    {
    case 0x8D:
      modrm_sib = ModrmSib(curinst);     
      break;
    default:
      printf("#UD\n");
      return;
    }
}

void X86Instruction::Instruction::exec_inst()
{
  if (!prefix.is_opbyte2)
    {
      dec_opcode();
    }
}
