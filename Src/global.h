#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER
#include "type.h"
#include <stdlib.h>
/********************************
	general register
*********************************/
extern Reg greg[8];
//8-bit general reg
#define AL (greg[0].word.byte.rl)
#define CL (greg[1].word.byte.rl)
#define DL (greg[2].word.byte.rl)
#define BL (greg[3].word.byte.rl)
#define AH (greg[0].word.byte.rh)
#define CH (greg[1].word.byte.rh)
#define DH (greg[2].word.byte.rh)
#define BH (greg[3].word.byte.rh)
Bit8u read8BitReg(Bit8u index);
void write8BitReg(Bit8u index,Bit8u data);
//16-bit general reg
#define AX (greg[0].word.rx)
#define CX (greg[1].word.rx)
#define DX (greg[2].word.rx)
#define BX (greg[3].word.rx)
#define SP (greg[4].word.rx)
#define BP (greg[5].word.rx)
#define SI (greg[6].word.rx)
#define DI (greg[7].word.rx)
Bit16u read16BitReg(Bit8u index);
void write16BitReg(Bit8u index,Bit16u data);
//32-bit general reg
#define EAX (greg[0].dword.erx)
#define ECX (greg[1].dword.erx)
#define EDX (greg[2].dword.erx)
#define EBX (greg[3].dword.erx)
#define ESP (greg[4].dword.erx)
#define EBP (greg[5].dword.erx)
#define ESI (greg[6].dword.erx)
#define EDI (greg[7].dword.erx)
Bit32u read32BitReg(Bit8u index);
void write32BitReg(Bit8u index,Bit32u data);
// instruction pointer
extern Reg ipreg;
#define EIP (ipreg.dword.erx)
#define IP (ipreg.word.rx)

/**********************************
	segment reg
**********************************/
#define SEG_NULL 7
/*#define SegValidCache  (0x01)
#define SegAccessROK   (0x02)
#define SegAccessWOK   (0x04)
#define SegAccessROK4G (0x08)
#define SegAccessWOK4G (0x10)*/
// For system & gate descriptors:
#define GATE_TYPE_NONE                       (0x0)
#define SYS_SEGMENT_AVAIL_286_TSS            (0x1)
#define SYS_SEGMENT_LDT                      (0x2)
#define SYS_SEGMENT_BUSY_286_TSS             (0x3)
#define CALL_GATE_286                        (0x4)
#define TASK_GATE                            (0x5)
#define INTERRUPT_GATE_286                   (0x6)
#define TRAP_GATE_286                        (0x7)
                                              /* 0x8 reserved */
#define SYS_SEGMENT_AVAIL_386_TSS            (0x9)
                                              /* 0xa reserved */
#define SYS_SEGMENT_BUSY_386_TSS             (0xb)
#define CALL_GATE_386                        (0xc)
                                              /* 0xd reserved */
#define INTERRUPT_GATE_386                   (0xe)
#define TRAP_GATE_386                        (0xf)

// For data/code descriptors:
#define DATA_READ_ONLY                       (0x0)
#define DATA_READ_ONLY_ACCESSED              (0x1)
#define DATA_READ_WRITE                      (0x2)
#define DATA_READ_WRITE_ACCESSED             (0x3)
#define DATA_READ_ONLY_EXPAND_DOWN           (0x4)
#define DATA_READ_ONLY_EXPAND_DOWN_ACCESSED  (0x5)
#define DATA_READ_WRITE_EXPAND_DOWN          (0x6)
#define DATA_READ_WRITE_EXPAND_DOWN_ACCESSED (0x7)
#define CODE_EXEC_ONLY                       (0x8)
#define CODE_EXEC_ONLY_ACCESSED              (0x9)
#define CODE_EXEC_READ                       (0xa)
#define CODE_EXEC_READ_ACCESSED              (0xb)
#define CODE_EXEC_ONLY_CONFORMING            (0xc)
#define CODE_EXEC_ONLY_CONFORMING_ACCESSED   (0xd)
#define CODE_EXEC_READ_CONFORMING            (0xe)
#define CODE_EXEC_READ_CONFORMING_ACCESSED   (0xf)
extern Sreg sreg[6];
enum{
	SEG_REG_ES=0,
	SEG_REG_CS=1,
	SEG_REG_SS=2,
	SEG_REG_DS=3,
	SEG_REG_FS=4,
	SEG_REG_GS=5
};
extern GlobalSreg gdtr,idtr;
extern Sreg ldtr,tr;
#define ES sreg[0].selector
#define ESDesc	sreg[0].cache
#define CS sreg[1].selector
#define CSDesc	sreg[1].cache
#define SS sreg[2].selector
#define SSDesc	sreg[2].cache
#define DS sreg[3].selector
#define DSDesc	sreg[3].cache
#define FS sreg[4].selector
#define FSDesc	sreg[4].cache
#define GS sreg[5].selector
#define GSDesc	sreg[5].cache
#define LDTR ldtr.selector
#define LDTRDesc	ldtr.cache
#define TR tr.selector
#define TRDesc	tr.cache
#define CPL (CS.selector&3)
#define NULL_SELECTOR_MASK 0xFFFC
extern Bit8u cpl;
extern Bit32u getSegmentLimit(Descriptor segment);
extern Bit32u getSegmentBase(Descriptor segment);
extern Bit16u getGateSelector(Descriptor gate);
extern Bit32u getGateOffset(Descriptor gate);
extern Bit8s isNullSelector(Selector selector);
extern Bit8s checkTableLimit(Selector selector);
extern Descriptor* getSegmentDescriptor(Selector selector);
extern Bit8s checkSegRights(Descriptor descriptor,Bit8u rights);
void load_seg(Selector selector,Bit8u seg);
/********************************
	EFLAGS
********************************/
extern Bit32u eflags;
#define CF 0
#define PF 2
#define AF 4
#define ZF 6
#define SF 7
#define TF 8
#define IF 9
#define DF 10
#define OF 11
#define NT 14
#define RF 16
#define VM 17
#define AC 18
#define VIF 19
#define VIP 20
#define ID 21

#define flag_bit(n) (1<<n)
#define CF_MASK flag_bit(0)
#define PF_MASK flag_bit(2)
#define AF_MASK flag_bit(4)
#define ZF_MASK flag_bit(6)
#define SF_MASK flag_bit(7)
#define TF_MASK flag_bit(8)
#define IF_MASK flag_bit(9)
#define DF_MASK flag_bit(10)
#define OF_MASK flag_bit(11)
#define NT_MASK flag_bit(14)
#define IOPL_MASK (3<<12)
#define RF_MASK flag_bit(16)
#define VM_MASK flag_bit(17)
#define AC_MASK flag_bit(18)
#define VIF_MASK flag_bit(19)
#define VIP_MASK flag_bit(20)
#define ID_MASK flag_bit(21)
#define CPAZSO_MASK (CF_MASK|PF_MASK|AF_MASK|ZF_MASK|SF_MASK|OF_MASK)
#define PZS_MASK (SF_MASK|ZF_MASK|PF_MASK)
#define PAZSO_MASK (PF_MASK|AF_MASK|ZF_MASK|SF_MASK|OF_MASK)
//const Bit32u EflagsValidMASK=0x003f7fd5;
#define SET_EFLAGS(result,dst,src,add_or_sub,bits,flag_mask){\
	Bit32u set_flags=0; \
	if(result==0) set_flags|=1<<ZF; \
	if(result&(1<<bits-1)) set_flags|=1<<SF;\
	Bit8u bitNum=0,i;\
	for(i=0;i<8;i++){\
		 bitNum+=(result&(1<<i))?1:0;\
	}\
	if(bitNum%2==0)\
		set_flags|=1<<PF;\
	if(add_or_sub==1){ \
		long tmp=(long)dst+src; \
		if(tmp!=result) set_flags|=1<<CF;\
		tmp=(dst&0x0f)+(src&0x0f);\
		if(tmp&0x10) set_flags|=1<<AF;\
		if((src&(1<<bits-1))==(dst&(1<<bits-1))&&(dst&(1<<bits-1))!=(result&(1<<bits-1)))\
			set_flags|=1<<OF;\
	}\
	else if(add_or_sub==2){\
		long tmp=(long)dst-src; \
		if(tmp!=result) set_flags|=1<<CF;\
		tmp=(dst&0x0f)-(src&0x0f);\
		if(tmp&0x10) set_flags|=1<<AF;\
		if((src&(1<<bits-1))!=(dst&(1<<bits-1))&&(dst&(1<<bits-1))!=(result&(1<<bits-1)))\
			set_flags|=1<<OF;\
	}\
	eflags&=~flag_mask; \
	eflags|=set_flags; \
}

/**************************************
	Control register
**************************************/
extern Bit32u cr[5];
#define CRO_PE_MASK 1
#define CRO_MP_MASK (1<<1)
#define CRO_EM_MASK (1<<2)
#define CRO_TS_MASK (1<<3)
#define CRO_ET_MASK (1<<4)
#define CRO_NE_MASK (1<<5)
#define CRO_WP_MASK (1<<16)
#define CRO_AM_MASK (1<<18)
#define CRO_NW_MASK (1<<29)
#define CRO_CD_MASK (1<<30)
#define CRO_PG_MASK (1<<31)
#define CR3_PCD_MASK (1<<3)
#define CR3_PWT_MASK (1<<4)
#define CR3_PDB_MASK FFFFF000
#define CR4_VME_MASK 1
#define CR4_PVI_MASK (1<<1)
#define CR4_TSD_MASK (1<<2)
#define CR4_DE_MASK (1<<3)
#define CR4_PSE_MASK (1<<4)
#define CR4_PAE_MASK (1<<5)
#define CR4_MCE_MASK (1<<6)
#define CR4_PGE_MASK (1<<7)
#define CR4_PCE_MASK (1<<8)

/**************************************
	Debug register
**************************************/
extern Bit32u dr[8];
#define DR7_GD_MASK (1<<13)  //enable the dr protection condition flagged by BD of DR6
#define DR7_LE_MASK (1<<8)  //local exact data breakpoint match
#define DR7_GE_MASK (1<<9)  //global exact data breakpoint match
#define DR7_Gx_MASK(n) (1<<(2*n+1))   //enable global level breakpoint
#define DR7_Lx_MASK(n)  (1<<2*n)  //enable local level brekpoint
#define DR7_RWx_MASK(n) (3<<(16+4*n))   //break condition
#define DR7_LENx_MASK(n) (3<<(17+4*n))      //size of breakpointed location
#define DR6_BD_MASK (1<<13)  //the next instruction will read or write debug register
#define DR6_BS_MASK  (1<<14)  //associated with TF flag
#define DR6_BT_MASK (1<<15)  //associated with T bit of TSS
#define DR6_Bx_MASK(n) (1<<n) //set if the debug condition is true
/*********************************
	execution mode
*********************************/
#define REAL_MODE (cr[0]&CRO_PE_MASK==0)
#define PROTECTED_MODE ((cr[0]&CRO_PE_MASK)&&(eflags&VM_MASK))
#define V8086_MODE ((cr[0]&CRO_PE_MASK)&&(eflags&VM_MASK==0))
/****************************
	AddressSize function
******************************/
Bit8u address_size(); /* 16 or 32 */
Bit8u operand_size(); /* 16 or 32 */
Bit8u stack_address_size();

/****************************
	exec
******************************/
extern Bit8u *memBase;
extern Bit8u *memBase_rtl;
#define MEMSIZE (1024*1024)
extern Bit8u *curInst;  //current instruction location
//prefix related
extern Bit8u prefixLen;  //prefix length
extern Bit8u prefix_seg;  //segment override
extern Bit8u prefix_lock;	//lock
extern Bit8u prefix_rep;	//repeat
extern Bit8u prefix_2byte;   //2byte opcode
extern Bit8u prefix_operand; //operand size
extern Bit8u prefix_address;  //address size
//opcode decoder
extern Bit8u immLen;
//modrm decoder
extern Bit8u instLen;
extern Bit8u reg1,reg2;
extern Bit8u rm_is_reg;
extern Bit16u eAddr16;
extern Bit32u eAddr32;
extern Bit8u eAddr_sreg;
extern Bit32u linear_addr;
/*******************************
		function
********************************/
void print();
void init();
void cpu_loop();
void cpu_exec_once();   //execute one instruction
void fetch();
void dec_prefix();
void dec_opcode_run();
void dec_opcode_2byte_run();
void dec_modrm();
void dec_modrm_16b();
void dec_modrm_32b();
void dec_sib();
//memory
void mem_init();
void rtl_mem_init();
Bit32u translate_linear_addr(Bit32u offset,Bit8u sreg);
Bit8u* get_mem_data();
void* get_stack_top();
void* get_stack_base();
void push_16b(Bit16u data);
void push_32b(Bit32u data);
Bit16u pop_16b();
Bit32u pop_32b();
Bit8u * get_string_dst();
Bit8u *get_string_src();
//eflags
Bit8u get_flag(Bit8u FLAG);
void set_flag(Bit8u FLAG);
void clear_flag(Bit8u FLAG);
Bit8u get_iopl();
Bit8s conditions_judge(Bit8u condition);
//others
Bit8u rep_condition(Bit8u isCmpOp);
Bit16u readSegmentSelector(Bit8u index);
/********************************************
	instruction execution
********************************************/
void exec_aaa();
void exec_aad(Bit8u imm);
void exec_aam(Bit8u imm);
void exec_aas();
Bit8u exec_arith_8b(Bit8u index,Bit8u dst,Bit8u src);
Bit16u exec_arith_16b(Bit8u index,Bit16u dst,Bit16u src);
Bit32u exec_arith_32b(Bit8u index,Bit32u dst,Bit32u src);
Bit8u exec_adc_8b(Bit8u dst,Bit8u src);
Bit16u exec_adc_16b(Bit16u dst,Bit16u src);
Bit32u exec_adc_32b(Bit32u dst,Bit32u src);
Bit8u exec_add_8b(Bit8u dst,Bit8u src);
Bit16u exec_add_16b(Bit16u dst,Bit16u src);
Bit32u exec_add_32b(Bit32u dst,Bit32u src);
Bit8u exec_and_8b(Bit8u dst,Bit8u src);
Bit16u exec_and_16b(Bit16u dst,Bit16u src);
Bit32u exec_and_32b(Bit32u dst,Bit32u src);
Bit8u exec_or_8b(Bit8u dst,Bit8u src);
Bit16u exec_or_16b(Bit16u dst,Bit16u src);
Bit32u exec_or_32b(Bit32u dst,Bit32u src);
Bit8u exec_xor_8b(Bit8u dst,Bit8u src);
Bit16u exec_xor_16b(Bit16u dst,Bit16u src);
Bit32u exec_xor_32b(Bit32u dst,Bit32u src);
Bit8u exec_cmp_8b(Bit8u dst,Bit8u src);
Bit16u exec_cmp_16b(Bit16u dst,Bit16u src);
Bit32u exec_cmp_32b(Bit32u dst,Bit32u src);
Bit16u exec_arpl(Bit16u dst,Bit16u src);
void exec_bound_16b(Bit16s*bound,Bit16s index);
void exec_bound_32b(Bit32s*bound,Bit32s index);
void exec_bsf_16b(Bit8u dst,Bit16u src);
void exec_bsf_32b(Bit8u dst,Bit32u src);
void exec_bsr_16b(Bit8u dst,Bit16u src);
void exec_bsr_32b(Bit8u dst,Bit32u src);
void exec_bswap(Bit8u reg);
void exec_btx_16b_reg(Bit8u op,Bit8u dst,Bit16u index);
void exec_btx_32b_reg(Bit8u op,Bit8u dst,Bit32u index);
void exec_btx_mem(Bit8u op,Bit8u *dst,Bit32s index);
void exec_call_near_relative();
void exec_call_near_absolute();
void exec_cli();
void exec_clts();
void exec_cmc();
void exec_cmps_8b();
void exec_cmps_16_32b();
void exec_cmpxchg_8b(Bit8u src);
void exec_cmpxchg_16b(Bit16u src);
void exec_cmpxchg_32b(Bit32u src);
void exec_cpuid();
void exec_cwd_cdq();
void exec_daa();
void  exec_das();
void exec_dec_8b();
void exec_dec_16_32b();
void exec_dec_16_32b_r(Bit8u reg);
void exec_div_8b();
void exec_div_16_32b();
void exec_enter(Bit16u bytes ,Bit8u nestLevel);
void exec_idiv_8b();
void exec_idiv_16_32b();
void exec_imul_8b();
void exec_imul_16_32b(Bit8u operandNum,Bit32s imm);
void exec_lahf();
void exec_load_seg(Bit8u seg);
void exec_lea();
void exec_leave();
void exec_lgdt();
void exec_lidt();
void exec_lldt();
void exec_lmsw();
void exec_lods_8b();
void exec_lods_16_32b();
Bit8u exec_loop();
Bit8u exec_loope();
Bit8u exec_loopne();
void exec_ltr();
void exec_mov_8b_2rm(Bit8u src);
void exec_mov_8b_2reg(Bit8u src,Bit8u dstReg);
void exec_mov_16b_2rm(Bit16u src);
void exec_mov_16b_2reg(Bit16u src,Bit8u dstReg);
void exec_mov_32b_2rm(Bit32u src);
void exec_mov_32b_2reg(Bit32u src,Bit8u dstReg);
void exec_mov_seg(Bit8u seg);
void exec_mov_2seg(Bit8u seg);
void exec_mov_ctrl();
void exec_mov_2ctrl();
void exec_mov_debug();
void exec_mov_2debug();
void exec_movs_8b();
void exec_movs_16_32b();
void exec_movsx_8b();
void exec_movsx_16b();
void exec_movzx_8b();
void exec_movzx_16b();
void exec_mul_8b();
void exec_mul_16_32b();
void exec_neg_8b();
void exec_neg_16_32b();
void exec_not_8b();
void exec_not_16_32b();
void exec_sahf();
void exec_popa();
void exec_popf();
void exec_pusha();
void exec_pushf();
Bit8u exec_sbb_8b(Bit8u dst,Bit8u src);
Bit16u exec_sbb_16b(Bit16u dst,Bit16u src);
Bit32u exec_sbb_32b(Bit32u dst,Bit32u src);
Bit8u exec_shift_8b(Bit8u index,Bit8u src,Bit8u count);
Bit16u exec_shift_16b(Bit8u index,Bit16u src,Bit8u count);
Bit32u exec_shift_32b(Bit8u index,Bit32u src,Bit8u count);
void exec_scas_8b();
void exec_scas_16b();
void exec_scas_32b();
void exec_shld(Bit8u count);
void exec_shrd(Bit8u count);
void exec_smsw();
void exec_stc();
void exec_std();
void exec_sti();
void exec_shrd(Bit8u count);
void exec_stos_8b();
void exec_stos_16b();
void exec_stos_32b();
void exec_xchg_reg(Bit8u reg);
void exec_xchg_mem_8b();
void exec_xchg_mem_16b();
void exec_xchg_mem_32b();
Bit8u exec_xadd_8b(Bit8u dst);
Bit16u exec_xadd_16b(Bit16u dst);
Bit32u exec_xadd_32b(Bit32u dst);
Bit8u exec_sub_8b(Bit8u dst,Bit8u src);
Bit16u exec_sub_16b(Bit16u dst,Bit16u src);
Bit32u exec_sub_32b(Bit32u dst,Bit32u src);
void exec_xlat();

#define DEBUG printf
#endif


