#ifndef CPUEMULATOR_INSTRUCTION_H_
#define CPUEMULATOR_INSTRUCTION_H_
#include <cstdlib>
#include <iostream>
#include "__type.hh"

using namespace CpuRegisterType;

namespace X86Instruction
{

  enum
    {
      XCS = 0,
      XSS,
      XDS,
      XES,
      XFS,
      XGS,
    };

  enum
    {
      EAX_MM0,
      ECX_MM1,
      EDX_MM2,
      EBX_MM3,
      ESP_MM4,
      EBP_MM5,
      ESI_MM6,
      EDI_MM7,
    };

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
    bool op;
    //group 4
    bool addr;

    bool is_opbyte2;
    InstructionPrefix() :lock(0), rep(0), repne(0), seg(6), op(0), addr(0), is_opbyte2(0) {};


    InstructionPrefix(const CpuRegisterType::Byte * curbyte) :lock(0), rep(0), repne(0), seg(6), op(0), addr(0), is_opbyte2(0)
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
	      seg = XCS;
	      break;
	    case 0x36: //SS
	      seg = XSS;
	      break;
	    case 0x3E: //DS
	      seg = XDS;
	      break;
	    case 0x26: //ES
	      seg = XES;
	      break;
	    case 0x64: //FS
	      seg = XFS;
	      break;
	    case 0x65: //GS
	      seg = XGS;
	      break;
	    case 0x66: //op-size
	      op = true;
	      break;
	    case 0x67: // addr
	      addr = true;
	      break;
	    case 0x0F:
	      is_opbyte2 = true;
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
      printf("print prifix: %d, %d, %d, %d, %d, %d, %d\n", lock, rep, repne, seg, op, addr, is_opbyte2);
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
    ModrmSib() = default;

    ModrmSib(const CpuRegisterType::Byte * cur) : modrm(0), sib(0), is_address_size16(true), effective_address_16(0), effective_addr_seg_reg(6)
    {
      modrm = *cur++;

      if (is_address_size16)
	{
	  auto mod = modrm >> 6;
	  auto rm = (modrm >> 3) & 0x7;
	  auto reg = modrm & 0x7;
	  auto disp = 0;
	  auto is_rm_a_reg = false;
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
	      effective_address_16 = XEBX.rx + XESI.rx + disp;
	      effective_addr_seg_reg = XDS;
	      break;
	    case 1:
	      effective_address_16 = XEBX.rx + XEDI.rx + disp;
	      effective_addr_seg_reg = XDS;
	    case 2:
	      effective_address_16 = XEBP.rx + XESI.rx + disp;
	      effective_addr_seg_reg = XSS;
	    case 3:
	      effective_address_16 = XEBP.rx + XEDI.rx + disp;
	      effective_addr_seg_reg = XSS;
	    case 4:
	      effective_address_16 = XESI.rx + disp;
	      effective_addr_seg_reg = XDS;
	    case 5:
	      effective_address_16 = XEDI.rx + disp;
	      effective_addr_seg_reg = XDS;
	    case 6:
	      switch(mod)
		{
		case 0:
		  effective_address_16 = * cur;
		  cur++;
		  effective_addr_seg_reg = XDS;
		default:
		  effective_address_16 = XEBP.rx + disp;
		  effective_addr_seg_reg = XSS;
		}
	      break;
	    case 7:
	      effective_address_16 = XEBX.rx + disp;
	      effective_addr_seg_reg = XSS;
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
    CpuRegisterType::Byte opcode[3];
    ModrmSib modrm_sib;
  public:
    
    Instruction() = default;
    Instruction(const CpuRegisterType::Byte * cur) : curinst(0), prefix(), modrm_sib(), opcode{ 0 }
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

  };
}
#endif /* CPUEMULATOR_INSTRUCTION_H_ */
