#include <cstdio>
#include "global.h"
#include "__dec_opcode.hh"
#include "instruction.h"

//main cpu loop
void cpu_loop()
{
  int i = 5;
  
  while (i--)
    {
      fetch();
      CpuRegisterType::Byte * b_curinst = (CpuRegisterType::Byte *)curInst;
      X86Instruction::Instruction inst = X86Instruction::Instruction(b_curinst);
      inst.print_status();
      // dec_prefix();
      // DEBUG("opcode:%02x , prefixLen:%d\n", *curInst, prefixLen);
      // if (prefix_2byte)
      // 	dec_opcode_2byte_run();
      // else
      // 	//dec_opcode_run();
      // 	opcode_run();
      // print();
      // if (*curInst == 0xC9) break;  //leave instruciton as an end
    }
}

void cpu_exec_once()
{
  fetch();
  dec_prefix();
  DEBUG("opcode:%02x , prefixLen:%d\n", *curInst, prefixLen);
  if (prefix_2byte)
    dec_opcode_2byte_run();
  else
    dec_opcode_run();
  print();
}
void fetch()
{
  linear_addr = translate_linear_addr(EIP, SEG_REG_CS);
  curInst = get_mem_data();
}


