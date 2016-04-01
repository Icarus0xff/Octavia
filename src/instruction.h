#ifndef CPUEMULATOR_INSTRUCTION_H_
#define CPUEMULATOR_INSTRUCTION_H_
#include <cstdlib>
#include "__type.hh"

namespace X86Instruction{

  
  enum
    {
      CSa,
      SSa,
      DSa,
      ESa,
      FSa,
      GSa,
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
    CpuRegisterType::u8 op;
    //group 4
    CpuRegisterType::u8 addr;

    InstructionPrefix() = default;
    
    InstructionPrefix(const CpuRegisterType::Byte * byte)
    {
      const CpuRegisterType::Byte * index = byte;
      for (int i = 0; i < 3; ++i)
	{
	  group[i] = * index;
	  index++;
	}
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

