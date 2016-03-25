#ifndef TYPE_HEADER
#define TYPE_HEADER
#include <cstdio>
#include <cstdlib>

typedef u_int8_t u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef signed char Bit8s;
typedef signed short Bit16s;
typedef signed int Bit32s;
typedef signed long Bit64;
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
            u_int16_t   rpl:2;
            u_int16_t   ti:1;
            u_int16_t 	index:13;
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
        Bit64 descriptor;
        struct{
            Bit64 limit2:16;
            Bit64 base2:24;
            Bit64 type:4;
            Bit64 s:1;  //0=system/gate,1=data/code segment
            Bit64 dpl:2;  //descriptor privilege level
            Bit64  p:1; //segment present
            Bit64 limit1:4;
            Bit64 avl:1;  //available for use by system software
            Bit64 reserved1:1;  //=0
            Bit64 d_b:1;//default address/operand size:0=16bit,1=32bit
            Bit64  g:1; //limit granularity：0=byte,1=4k
            Bit64 base1:8;
        };//segment descriptor
        struct{
            Bit64 offset2:16;
            Bit64 selector:16;
            Bit64 paramCount:5;    //used in call gate
            Bit64 reserved2:3;
            Bit64 override_part:8;
            Bit64 offset1:16;
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
