#ifndef CPUEMULATOR_INSTRUCTION_H_
#define CPUEMULATOR_INSTRUCTION_H_
#include <cstdlib>
#include "__type.hh"

namespace X86Instruction{

  enum
  {
    XCS,
    XSS,
    XDS,
    XES,
    XFS,
    XGS,
  };
  
  class InstructionPrefix
  {
  public:
    CpuRegisterType::Byte group[4] = {0,0,0,0};
  
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

    InstructionPrefix() = default;
    
    InstructionPrefix(const CpuRegisterType::Byte * curbyte)
    {
      for (int i = 0; i < 3; ++i)
	{
	  group[i] = * curbyte;
	  switch(*curbyte){
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
	  default:
	    goto out;
	  }
	  curbyte++;
	}
    out:
      return;
    }
  };
  

  class ModrmSib
  {
  public:
    CpuRegisterType::Byte modrm;
    CpuRegisterType::Byte sib;
  };

  class Instruction
  {
  private:
    CpuRegisterType::Byte * curinst;
    InstructionPrefix prefix;
    ModrmSib modrm_sib;
  public:
    Instruction() = default;
    Instruction(CpuRegisterType::Byte * cur) : curinst(0),  prefix(), modrm_sib()
    {
      curinst = cur;
      prefix = InstructionPrefix(curinst);
    }
    
  };
}
#endif /* CPUEMULATOR_INSTRUCTION_H_ */
