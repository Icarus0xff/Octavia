#ifndef CPUEMULATOR_INSTRUCTION_H_
#define CPUEMULATOR_INSTRUCTION_H_
#include <cstdlib>
#include <iostream>
#include "__type.hh"

namespace X86Instruction
{

<<<<<<< HEAD

	enum
	{
		CSa,
		SSa,
		DSa,
		ESa,
		FSa,
		GSa,
	};
=======
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
    InstructionPrefix():lock(0), rep(0), repne(0), seg(0), op(0), addr(0), is_opbyte2(0){};

    
    InstructionPrefix(const CpuRegisterType::Byte * curbyte):lock(0), rep(0), repne(0), seg(0), op(0), addr(0),is_opbyte2(0)
    {
      for (int i = 0; i < 3; ++i)
	{
	  switch(*curbyte)
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
  
>>>>>>> inst

	class InstructionPrefix
	{
	public:
		CpuRegisterType::Byte group[4] = { 0,0,0,0 };

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
				group[i] = *index;
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
		Instruction(CpuRegisterType::Byte * cur) : curinst(0), prefix(), modrm_sib()
		{
			curinst = cur;
			prefix = InstructionPrefix(curinst);
		}

<<<<<<< HEAD
	};
=======
  class Instruction
  {
  private:
    CpuRegisterType::Byte * curinst;
    InstructionPrefix prefix;
    CpuRegisterType::Byte opcode[3];
    ModrmSib modrm_sib;
  public:
    
    Instruction() = default;
    Instruction(CpuRegisterType::Byte * cur) : curinst(0),  prefix(), modrm_sib(), opcode{0}
    {
      curinst = cur;
      prefix = InstructionPrefix(curinst);
      if(!prefix.is_opbyte2){
	opcode[0] = * curinst;
	opcode[1] = 0;
	opcode[2] = 0;
      }
      else{
	opcode[0] = * curinst++;
	opcode[1] = * curinst;
	opcode[2] = 0;
      }
    }

    void print_status()
    {
      prefix.print_status();
      printf("opcode[0]: %x\n", (CpuRegisterType::u8)opcode[0]);
      printf("opcode[1]: %x\n", (CpuRegisterType::u8)opcode[1]);
      printf("opcode[2]: %x\n", (CpuRegisterType::u8)opcode[2]);
    }
    
  };
>>>>>>> inst
}
#endif /* CPUEMULATOR_INSTRUCTION_H_ */
