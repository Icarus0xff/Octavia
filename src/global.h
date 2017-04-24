#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER
#include "__type.hh"
#include "type.h"
#include <cstdlib>
#include <vector>

using CpuRegisterType::Register;
using namespace Enum;

namespace GeneralReg {
extern std::vector<Register> general_reg;
}
/********************************
        general register
*********************************/
extern Reg greg[8];
// 8-bit general reg
using GeneralReg::general_reg;
#define AL (general_reg[enum_EAX].rl)
#define CL (general_reg[enum_ECX].rl)
#define DL (general_reg[enum_EDX].rl)
#define BL (general_reg[enum_EBX].rl)
#define AH (general_reg[enum_EAX].rh)
#define CH (general_reg[enum_ECX].rh)
#define DH (general_reg[enum_EDX].rh)
#define BH (general_reg[enum_EBX].rh)
u_int8_t read8BitReg(u_int8_t index);
void write8BitReg(u_int8_t index, u_int8_t data);
// 16-bit general reg
#define AX (general_reg[enum_EAX].rx)
#define CX (general_reg[enum_ECX].rx)
#define DX (general_reg[enum_EDX].rx)
#define BX (general_reg[enum_EBX].rx)
#define SP (general_reg[enum_ESP].rx)
#define BP (general_reg[enum_EBP].rx)
#define SI (general_reg[enum_ESI].rx)
#define DI (general_reg[enum_EDI].rx)
u_int16_t read16BitReg(u_int8_t index);
void write16BitReg(u_int8_t index, u_int16_t data);
// 32-bit general reg
#define EAX (general_reg[enum_EAX].erx)
#define ECX (general_reg[enum_ECX].erx)
#define EDX (general_reg[enum_EDX].erx)
#define EBX (general_reg[enum_EBX].erx)
#define ESP (general_reg[enum_ESP].erx)
#define EBP (general_reg[enum_EBP].erx)
#define ESI (general_reg[enum_ESI].erx)
#define EDI (general_reg[enum_EDI].erx)
u_int32_t read32BitReg(u_int8_t index);
void write32BitReg(u_int8_t index, u_int32_t data);
// instruction pointer
extern Register ip_reg;
#define EIP (ip_reg.erx)
#define IP (ip_reg.rx)

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
#define GATE_TYPE_NONE (0x0)
#define SYS_SEGMENT_AVAIL_286_TSS (0x1)
#define SYS_SEGMENT_LDT (0x2)
#define SYS_SEGMENT_BUSY_286_TSS (0x3)
#define CALL_GATE_286 (0x4)
#define TASK_GATE (0x5)
#define INTERRUPT_GATE_286 (0x6)
#define TRAP_GATE_286 (0x7)
/* 0x8 reserved */
#define SYS_SEGMENT_AVAIL_386_TSS (0x9)
/* 0xa reserved */
#define SYS_SEGMENT_BUSY_386_TSS (0xb)
#define CALL_GATE_386 (0xc)
/* 0xd reserved */
#define INTERRUPT_GATE_386 (0xe)
#define TRAP_GATE_386 (0xf)

// For data/code descriptors:
#define DATA_READ_ONLY (0x0)
#define DATA_READ_ONLY_ACCESSED (0x1)
#define DATA_READ_WRITE (0x2)
#define DATA_READ_WRITE_ACCESSED (0x3)
#define DATA_READ_ONLY_EXPAND_DOWN (0x4)
#define DATA_READ_ONLY_EXPAND_DOWN_ACCESSED (0x5)
#define DATA_READ_WRITE_EXPAND_DOWN (0x6)
#define DATA_READ_WRITE_EXPAND_DOWN_ACCESSED (0x7)
#define CODE_EXEC_ONLY (0x8)
#define CODE_EXEC_ONLY_ACCESSED (0x9)
#define CODE_EXEC_READ (0xa)
#define CODE_EXEC_READ_ACCESSED (0xb)
#define CODE_EXEC_ONLY_CONFORMING (0xc)
#define CODE_EXEC_ONLY_CONFORMING_ACCESSED (0xd)
#define CODE_EXEC_READ_CONFORMING (0xe)
#define CODE_EXEC_READ_CONFORMING_ACCESSED (0xf)
extern Sreg sreg[6];
enum {
  SEG_REG_ES = 0,
  SEG_REG_CS = 1,
  SEG_REG_SS = 2,
  SEG_REG_DS = 3,
  SEG_REG_FS = 4,
  SEG_REG_GS = 5
};
extern GlobalSreg gdtr, idtr;
extern Sreg ldtr, tr;
#define ES sreg[0].selector
#define ESDesc sreg[0].cache
#define CS sreg[1].selector
#define CSDesc sreg[1].cache
#define SS sreg[2].selector
#define SSDesc sreg[2].cache
#define DS sreg[3].selector
#define DSDesc sreg[3].cache
#define FS sreg[4].selector
#define FSDesc sreg[4].cache
#define GS sreg[5].selector
#define GSDesc sreg[5].cache
#define LDTR ldtr.selector
#define LDTRDesc ldtr.cache
#define TR tr.selector
#define TRDesc tr.cache
#define CPL (CS.selector & 3)
#define NULL_SELECTOR_MASK 0xFFFC
extern u_int8_t cpl;
extern u_int32_t getSegmentLimit(Descriptor segment);
extern u_int32_t getSegmentBase(Descriptor segment);
extern u_int16_t getGateSelector(Descriptor gate);
extern u_int32_t getGateOffset(Descriptor gate);
extern int8_t isNullSelector(Selector selector);
extern int8_t checkTableLimit(Selector selector);
extern Descriptor *getSegmentDescriptor(Selector selector);
extern int8_t checkSegRights(Descriptor descriptor, u_int8_t rights);
void load_seg(Selector selector, u_int8_t seg);
/********************************
        EFLAGS
********************************/
extern u_int32_t eflags;
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

#define flag_bit(n) (1 << n)
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
#define IOPL_MASK (3 << 12)
#define RF_MASK flag_bit(16)
#define VM_MASK flag_bit(17)
#define AC_MASK flag_bit(18)
#define VIF_MASK flag_bit(19)
#define VIP_MASK flag_bit(20)
#define ID_MASK flag_bit(21)
#define CPAZSO_MASK (CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK)
#define PZS_MASK (SF_MASK | ZF_MASK | PF_MASK)
#define PAZSO_MASK (PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK)
// const u_int32_t EflagsValidMASK=0x003f7fd5;
#define SET_EFLAGS(result, dst, src, add_or_sub, bits, flag_mask)              \
  {                                                                            \
    u_int32_t set_flags = 0;                                                   \
    if (result == 0)                                                           \
      set_flags |= 1 << ZF;                                                    \
    if (result & (1 << bits - 1))                                              \
      set_flags |= 1 << SF;                                                    \
    u_int8_t bitNum = 0, i;                                                    \
    for (i = 0; i < 8; i++) {                                                  \
      bitNum += (result & (1 << i)) ? 1 : 0;                                   \
    }                                                                          \
    if (bitNum % 2 == 0)                                                       \
      set_flags |= 1 << PF;                                                    \
    if (add_or_sub == 1) {                                                     \
      long tmp = (long)dst + src;                                              \
      if (tmp != result)                                                       \
        set_flags |= 1 << CF;                                                  \
      tmp = (dst & 0x0f) + (src & 0x0f);                                       \
      if (tmp & 0x10)                                                          \
        set_flags |= 1 << AF;                                                  \
      if ((src & (1 << bits - 1)) == (dst & (1 << bits - 1)) &&                \
          (dst & (1 << bits - 1)) != (result & (1 << bits - 1)))               \
        set_flags |= 1 << OF;                                                  \
    } else if (add_or_sub == 2) {                                              \
      long tmp = (long)dst - src;                                              \
      if (tmp != result)                                                       \
        set_flags |= 1 << CF;                                                  \
      tmp = (dst & 0x0f) - (src & 0x0f);                                       \
      if (tmp & 0x10)                                                          \
        set_flags |= 1 << AF;                                                  \
      if ((src & (1 << bits - 1)) != (dst & (1 << bits - 1)) &&                \
          (dst & (1 << bits - 1)) != (result & (1 << bits - 1)))               \
        set_flags |= 1 << OF;                                                  \
    }                                                                          \
    eflags &= ~flag_mask;                                                      \
    eflags |= set_flags;                                                       \
  }

/**************************************
        Control register
**************************************/
extern u_int32_t cr[5];
#define CRO_PE_MASK 1
#define CRO_MP_MASK (1 << 1)
#define CRO_EM_MASK (1 << 2)
#define CRO_TS_MASK (1 << 3)
#define CRO_ET_MASK (1 << 4)
#define CRO_NE_MASK (1 << 5)
#define CRO_WP_MASK (1 << 16)
#define CRO_AM_MASK (1 << 18)
#define CRO_NW_MASK (1 << 29)
#define CRO_CD_MASK (1 << 30)
#define CRO_PG_MASK (1 << 31)
#define CR3_PCD_MASK (1 << 3)
#define CR3_PWT_MASK (1 << 4)
#define CR3_PDB_MASK FFFFF000
#define CR4_VME_MASK 1
#define CR4_PVI_MASK (1 << 1)
#define CR4_TSD_MASK (1 << 2)
#define CR4_DE_MASK (1 << 3)
#define CR4_PSE_MASK (1 << 4)
#define CR4_PAE_MASK (1 << 5)
#define CR4_MCE_MASK (1 << 6)
#define CR4_PGE_MASK (1 << 7)
#define CR4_PCE_MASK (1 << 8)

/**************************************
        Debug register
**************************************/
extern u_int32_t dr[8];
#define DR7_GD_MASK                                                            \
  (1 << 13) // enable the dr protection condition flagged by BD of DR6
#define DR7_LE_MASK (1 << 8)              // local exact data breakpoint match
#define DR7_GE_MASK (1 << 9)              // global exact data breakpoint match
#define DR7_Gx_MASK(n) (1 << (2 * n + 1)) // enable global level breakpoint
#define DR7_Lx_MASK(n) (1 << 2 * n)       // enable local level brekpoint
#define DR7_RWx_MASK(n) (3 << (16 + 4 * n))  // break condition
#define DR7_LENx_MASK(n) (3 << (17 + 4 * n)) // size of breakpointed location
#define DR6_BD_MASK                                                            \
  (1 << 13) // the next instruction will read or write debug register
#define DR6_BS_MASK (1 << 14)   // associated with TF flag
#define DR6_BT_MASK (1 << 15)   // associated with T bit of TSS
#define DR6_Bx_MASK(n) (1 << n) // set if the debug condition is true
/*********************************
        execution mode
*********************************/
#define REAL_MODE (cr[0] & CRO_PE_MASK == 0)
#define PROTECTED_MODE ((cr[0] & CRO_PE_MASK) && (eflags & VM_MASK))
#define V8086_MODE ((cr[0] & CRO_PE_MASK) && (eflags & VM_MASK == 0))
/****************************
        AddressSize function
******************************/
u_int8_t address_size(); /* 16 or 32 */
u_int8_t operand_size(); /* 16 or 32 */
u_int8_t stack_address_size();

/****************************
        exec
******************************/
extern u_int8_t *memBase;
extern u_int8_t *memBase_rtl;
#define MEMSIZE (1024 * 1024)
extern u_int8_t *curInst; // current instruction location
// prefix related
extern u_int8_t prefixLen;      // prefix length
extern u_int8_t prefix_seg;     // segment override
extern u_int8_t prefix_lock;    // lock
extern u_int8_t prefix_rep;     // repeat
extern u_int8_t prefix_2byte;   // 2byte opcode
extern u_int8_t prefix_operand; // operand size
extern u_int8_t prefix_address; // address size
// opcode decoder
extern u_int8_t immLen;
// modrm decoder
extern u_int8_t instLen;
extern u_int8_t reg1, reg2;
extern u_int8_t rm_is_reg;
extern u_int16_t effective_address_16;
extern u_int32_t effective_address_32;
extern u_int8_t eAddr_sreg;
extern u_int32_t linear_addr;
/*******************************
                function
********************************/
void print();
void init();
void cpu_loop();
void cpu_exec_once(); // execute one instruction
void fetch();
void dec_prefix();
void dec_opcode_run();
void dec_opcode_2byte_run();
void dec_modrm();
void dec_modrm_16b();
void dec_modrm_32b();
void dec_sib();
// memory
void mem_init();
void rtl_mem_init();
u_int32_t translate_linear_addr(u_int32_t offset, u_int8_t sreg);
u_int8_t *get_mem_data();
void *get_stack_top();
void *get_stack_base();
void push_16b(u_int16_t data);
void push_32b(u_int32_t data);
u_int16_t pop_16b();
u_int32_t pop_32b();
u_int8_t *get_string_dst();
u_int8_t *get_string_src();
// eflags
u_int8_t get_flag(u_int8_t FLAG);
void set_flag(u_int8_t FLAG);
void clear_flag(u_int8_t FLAG);
u_int8_t get_iopl();
int8_t conditions_judge(u_int8_t condition);
// others
u_int8_t rep_condition(u_int8_t isCmpOp);
u_int16_t readSegmentSelector(u_int8_t index);
/********************************************
        instruction execution
********************************************/
void exec_aaa();
void exec_aad(u_int8_t imm);
void exec_aam(u_int8_t imm);
void exec_aas();
u_int8_t exec_arith_8b(u_int8_t index, u_int8_t dst, u_int8_t src);
u_int16_t exec_arith_16b(u_int8_t index, u_int16_t dst, u_int16_t src);
u_int32_t exec_arith_32b(u_int8_t index, u_int32_t dst, u_int32_t src);
u_int8_t exec_adc_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_adc_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_adc_32b(u_int32_t dst, u_int32_t src);
u_int8_t exec_add_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_add_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_add_32b(u_int32_t dst, u_int32_t src);
u_int8_t exec_and_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_and_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_and_32b(u_int32_t dst, u_int32_t src);
u_int8_t exec_or_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_or_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_or_32b(u_int32_t dst, u_int32_t src);
u_int8_t exec_xor_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_xor_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_xor_32b(u_int32_t dst, u_int32_t src);
u_int8_t exec_cmp_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_cmp_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_cmp_32b(u_int32_t dst, u_int32_t src);
u_int16_t exec_arpl(u_int16_t dst, u_int16_t src);
void exec_bound_16b(int16_t *bound, int16_t index);
void exec_bound_32b(int32_t *bound, int32_t index);
void exec_bsf_16b(u_int8_t dst, u_int16_t src);
void exec_bsf_32b(u_int8_t dst, u_int32_t src);
void exec_bsr_16b(u_int8_t dst, u_int16_t src);
void exec_bsr_32b(u_int8_t dst, u_int32_t src);
void exec_bswap(u_int8_t reg);
void exec_btx_16b_reg(u_int8_t op, u_int8_t dst, u_int16_t index);
void exec_btx_32b_reg(u_int8_t op, u_int8_t dst, u_int32_t index);
void exec_btx_mem(u_int8_t op, u_int8_t *dst, int32_t index);
void exec_call_near_relative();
void exec_call_near_absolute();
void exec_cli();
void exec_clts();
void exec_cmc();
void exec_cmps_8b();
void exec_cmps_16_32b();
void exec_cmpxchg_8b(u_int8_t src);
void exec_cmpxchg_16b(u_int16_t src);
void exec_cmpxchg_32b(u_int32_t src);
void exec_cpuid();
void exec_cwd_cdq();
void exec_daa();
void exec_das();
void exec_dec_8b();
void exec_dec_16_32b();
void exec_dec_16_32b_r(u_int8_t reg);
void exec_div_8b();
void exec_div_16_32b();
void exec_enter(u_int16_t bytes, u_int8_t nestLevel);
void exec_idiv_8b();
void exec_idiv_16_32b();
void exec_imul_8b();
void exec_imul_16_32b(u_int8_t operandNum, int32_t imm);
void exec_lahf();
void exec_load_seg(u_int8_t seg);
void exec_lea();
void exec_leave();
void exec_lgdt();
void exec_lidt();
void exec_lldt();
void exec_lmsw();
void exec_lods_8b();
void exec_lods_16_32b();
u_int8_t exec_loop();
u_int8_t exec_loope();
u_int8_t exec_loopne();
void exec_ltr();
void exec_mov_8b_2rm(u_int8_t src);
void exec_mov_8b_2reg(u_int8_t src, u_int8_t dstReg);
void exec_mov_16b_2rm(u_int16_t src);
void exec_mov_16b_2reg(u_int16_t src, u_int8_t dstReg);
void exec_mov_32b_2rm(u_int32_t src);
void exec_mov_32b_2reg(u_int32_t src, u_int8_t dstReg);
void exec_mov_seg(u_int8_t seg);
void exec_mov_2seg(u_int8_t seg);
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
u_int8_t exec_sbb_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_sbb_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_sbb_32b(u_int32_t dst, u_int32_t src);
u_int8_t exec_shift_8b(u_int8_t index, u_int8_t src, u_int8_t count);
u_int16_t exec_shift_16b(u_int8_t index, u_int16_t src, u_int8_t count);
u_int32_t exec_shift_32b(u_int8_t index, u_int32_t src, u_int8_t count);
void exec_scas_8b();
void exec_scas_16b();
void exec_scas_32b();
void exec_shld(u_int8_t count);
void exec_shrd(u_int8_t count);
void exec_smsw();
void exec_stc();
void exec_std();
void exec_sti();
void exec_shrd(u_int8_t count);
void exec_stos_8b();
void exec_stos_16b();
void exec_stos_32b();
void exec_xchg_reg(u_int8_t reg);
void exec_xchg_mem_8b();
void exec_xchg_mem_16b();
void exec_xchg_mem_32b();
u_int8_t exec_xadd_8b(u_int8_t dst);
u_int16_t exec_xadd_16b(u_int16_t dst);
u_int32_t exec_xadd_32b(u_int32_t dst);
u_int8_t exec_sub_8b(u_int8_t dst, u_int8_t src);
u_int16_t exec_sub_16b(u_int16_t dst, u_int16_t src);
u_int32_t exec_sub_32b(u_int32_t dst, u_int32_t src);
void exec_xlat();

#define DEBUG printf
#endif
