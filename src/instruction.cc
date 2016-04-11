#include "instruction.h"
#include <cstdio>

void X86Instruction::Instruction::exec_lea()
{
  printf("%s\n", __func__);
}

void X86Instruction::Instruction::dec_opcode()
{
  switch(opcode[0])
    {
    case 0x8d:
      modrm_sib = ModrmSib(curinst);
      exec_lea();
    }
  return;
}

void X86Instruction::Instruction::exec_inst()
{
  dec_opcode();
  return;
}
