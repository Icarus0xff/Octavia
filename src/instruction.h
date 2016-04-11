#ifndef CPUEMULATOR_INSTRUCTION_H_
#define CPUEMULATOR_INSTRUCTION_H_
#include <cstdlib>
#include <iostream>
#include <vector>
#include "__type.hh"
#include "global.h"

using namespace CpuRegisterType;
using namespace Enum;

namespace X86Instruction
{
  class InstructionPrefix
  {
  public:
    //group1
    bool lock;
    bool rep;
    bool repne;
    //group 2
    CpuRegisterType::u8 seg;
    //group 3
    bool is_opsize16;
    //group 4
    bool is_addrsize16;

    bool is_opbyte2;
    InstructionPrefix() :lock(0), rep(0), repne(0), seg(6), is_opsize16(0), is_addrsize16(0), is_opbyte2(0) {};


    InstructionPrefix(const CpuRegisterType::Byte * curbyte) :lock(0), rep(0), repne(0), seg(6), is_opsize16(0), is_addrsize16(1), is_opbyte2(0)
    {
      for (int i = 0; i < 3; ++i)
	{
	  switch (*curbyte)
	    {
	    case 0xF0: //lock
	      lock = true;
	      break;
	    case 0xF2: //repne
	      repne = true;
	      break;
	    case 0xF3: //rep
	      rep = true;
	      break;
	    case 0x2E: //CS
	      seg = enum_CS;
	      break;
	    case 0x36: //SS
	      seg = enum_SS;
	      break;
	    case 0x3E: //DS
	      seg = enum_DS;
	      break;
	    case 0x26: //ES
	      seg = enum_ES;
	      break;
	    case 0x64: //FS
	      seg = enum_FS;
	      break;
	    case 0x65: //GS
	      seg = enum_GS;
	      break;
	    case 0x66: //op-size
	      is_opsize16 = true;
	      break;
	    case 0x67: // addr
	      is_addrsize16 = true;
	      break;
	    case 0x0F:
	      is_opbyte2 = true;
	      break;
	    default:
	      goto out;
	    }
	  curbyte++;
	}
    out:
      return;
    }

    void print_status()
    {
      printf("print prifix: lock: %d, rep: %d, repne: %d, seg: %d, op: %d, addr: %d, is_opbyte2: %d\n", lock, rep, repne, seg, is_opsize16, is_addrsize16, is_opbyte2);
    }
  };


  class ModrmSib
  {
  public:
    CpuRegisterType::Byte modrm;
    CpuRegisterType::Byte sib;
    bool is_address_size16;
    u_int16_t effective_address_16;
    u_int32_t effective_address_32;
    u_int8_t effective_addr_seg_reg;
    u_int8_t reg_dest;
    bool is_rm_a_reg;
    ModrmSib() = default;

    ModrmSib(const CpuRegisterType::Byte * cur) : modrm(0), sib(0), is_address_size16(true), effective_address_16(0), effective_address_32(0), effective_addr_seg_reg(0), reg_dest(0), is_rm_a_reg(false)
    {
      modrm = *cur;
      cur++;

      if (is_address_size16)
	{
	  auto mod = modrm >> 6;
	  auto reg = (modrm >> 3) & 0x7;
	  auto rm = modrm & 0x7;
	  reg_dest = reg;
	  auto disp = 0;
	  switch (mod)
	    {
	    case 0:
	      disp = 0;
	      break;
	    case 1:
	      disp = (int8_t)(*cur);
	      cur++;
	      break;
	    case 2:
	      disp = (u_int16_t)(*cur);
	      cur++;
	      break;
	    case 3:
	      is_rm_a_reg = true;
	      break;
	    default:
	      printf("error!panic!\n");
	    }
	  switch (rm)
	    {
	    case 0:
	      effective_address_16 = EBX + ESI + disp;
	      effective_addr_seg_reg = enum_DS;
	      break;
	    case 1:
	      effective_address_16 = EBX + EDI + disp;
	      effective_addr_seg_reg = enum_DS;
	      break;
	    case 2:
	      effective_address_16 = EBP + ESI + disp;
	      effective_addr_seg_reg = enum_DS;
	      break;
	    case 3:
	      effective_address_16 = EBP + EDI + disp;
	      effective_addr_seg_reg = enum_DS;
	      break;
	    case 4:
	      effective_address_16 = ESI + disp;
	      effective_addr_seg_reg = enum_DS;
	      break;
	    case 5:
	      effective_address_16 = EDI + disp;
	      effective_addr_seg_reg = enum_DS;
	      break;
	    case 6:
	      switch(mod)
		{
		case 0:
		  effective_address_16 = * cur;
		  cur++;
		  effective_addr_seg_reg = enum_DS;
		  break;
		default:
		  effective_address_16 = EBP + disp;
		  effective_addr_seg_reg = enum_SS;
		}
	      break;
	    case 7:
	      effective_address_16 = EBX + disp;
	      effective_addr_seg_reg = enum_SS;
	      break;
	    default:
	      break;
	    }
	}
      else
	{
	}
    }
    
    void print_status()
    {
      printf("modrm: %x\n", (u8)modrm);
      printf("effective_address: %x\n", effective_address_16);
    }


  };

  class Instruction
  {
  private:
    const CpuRegisterType::Byte * curinst;
    InstructionPrefix prefix;
    //CpuRegisterType::Byte opcode[3];
    std::vector<CpuRegisterType::Byte> opcode{3}; 
    ModrmSib modrm_sib;
  public:
    
    Instruction() = default;
    Instruction(const CpuRegisterType::Byte * cur) : curinst(0), prefix(), opcode{3}, modrm_sib()
    {
      curinst = cur;
      prefix = InstructionPrefix(curinst);
      if (!prefix.is_opbyte2)
	{
	  opcode[0] = *curinst;
	  opcode[1] = 0;
	  opcode[2] = 0;
	}
      else
	{
	  opcode[0] = *curinst++;
	  opcode[1] = *curinst;
	  opcode[2] = 0;
	}
      curinst++;
      cur = curinst;
    }

    void set_modrm_sib(){
      modrm_sib = ModrmSib(curinst);
    }

    void print_status()
    {
      prefix.print_status();
      printf("opcode[0]: %x\n", (CpuRegisterType::u8)opcode[0]);
      printf("opcode[1]: %x\n", (CpuRegisterType::u8)opcode[1]);
      printf("opcode[2]: %x\n", (CpuRegisterType::u8)opcode[2]);
      modrm_sib.print_status();
    }

    void dec_opcode();
    void exec_inst();

    void exec_lea();

  };
}
#endif /* CPUEMULATOR_INSTRUCTION_H_ */
