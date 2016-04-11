#include "instruction.h"
#include <cstdio>

void X86Instruction::Instruction::exec_lea()
{
  if (modrm_sib.is_rm_a_reg)
    {
      printf("#UD exception\n");
      exit(0);
    }
  if (prefix.is_opsize16)
    {
      if (prefix.is_addrsize16)
	{
	  general_reg[modrm_sib.reg_dest].rx = modrm_sib.effective_address_16;
	}
      else
	{
	  general_reg[modrm_sib.reg_dest].rx = modrm_sib.effective_address_32;
	}
      
    }
  else
    {
      if (prefix.is_addrsize16)
	{
	  CpuRegisterType::Dword temp = 0x0000ffff & modrm_sib.effective_address_16;
	  general_reg[modrm_sib.reg_dest].erx = temp;
	}
      else
	{
	  general_reg[modrm_sib.reg_dest].erx = modrm_sib.effective_address_32;
	}
    }
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
