#ifndef TYPE_HEADER
#define TYPE_HEADER
#include <cstdio>
#include <cstdlib>

//general 8/16/32bit register
typedef struct{
  union{
    struct{
      u_int32_t erx;                 //32 bit register
    }dword;
    struct{
      union{
	u_int16_t rx;
	struct{
	  u_int8_t rl;             //low 8-bit register
	  u_int8_t rh;
	} byte;
      };
      u_int16_t idle;
    }word;
  };
}Reg;

//segment register
typedef struct{
  union{
    u_int16_t selector;
    struct{
      u_int16_t rpl:2;
      u_int16_t ti:1;
      u_int16_t index:13;
    };
  };
  u_int8_t valid;
}Selector;
/* For system & gate descriptors: type ：
 *  0 = invalid descriptor (reserved)
 *  1 = 286 available Task State Segment (TSS)
 *  2 = LDT descriptor
 *  3 = 286 busy Task State Segment (TSS)
 *  4 = 286 call gate
 *  5 = task gate
 *  6 = 286 interrupt gate
 *  7 = 286 trap gate
 *  8 = (reserved)
 *  9 = 386 available TSS
 * 10 = (reserved)
 * 11 = 386 busy TSS
 * 12 = 386 call gate
 * 13 = (reserved)
 * 14 = 386 interrupt gate
 * 15 = 386 trap gate */
typedef  union{
  int64_t descriptor;
  struct{
    int64_t limit2:16;
    int64_t base2:24;
    int64_t type:4;
    int64_t s:1;  //0=system/gate,1=data/code segment
    int64_t dpl:2;  //descriptor privilege level
    int64_t  p:1; //segment present
    int64_t limit1:4;
    int64_t avl:1;  //available for use by system software
    int64_t reserved1:1;  //=0
    int64_t d_b:1;//default address/operand size:0=16bit,1=32bit
    int64_t  g:1; //limit granularity：0=byte,1=4k
    int64_t base1:8;
  };//segment descriptor
  struct{
    int64_t offset2:16;
    int64_t selector:16;
    int64_t paramCount:5;    //used in call gate
    int64_t reserved2:3;
    int64_t override_part:8;
    int64_t offset1:16;
  }; //gate descriptor
}Descriptor;
typedef struct{
  Selector selector;
  Descriptor cache;
}Sreg;

//global segment reg:gdtr,idtr
typedef struct{
  u_int32_t base;
  u_int16_t limit;
}GlobalSreg;
#endif
