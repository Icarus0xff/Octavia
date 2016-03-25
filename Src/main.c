#include "global.h"

  /*
    Initialize variables.
  */
  u_int8_t *memBase = 0;
  u_int8_t *memBase_rtl = 0;
  Sreg sreg[6] = {0};
  u_int8_t *curInst = 0;  //current instruction location
  u_int8_t prefixLen = 0;  //prefix length
  u_int8_t prefix_seg = 0;  //segment override
  u_int8_t prefix_lock = 0;	//lock
  u_int8_t prefix_rep = 0;	//repeat
  u_int8_t prefix_2byte = 0;   //2byte opcode
  u_int8_t prefix_operand = 0; //operand size
  u_int8_t prefix_address = 0;  //address size
  Reg ipreg = {0};

  u_int8_t instLen = 0;
  u_int8_t reg1 = 0, reg2 = 0;
  u_int8_t rm_is_reg = 0;
  u_int16_t eAddr16 = 0;
  u_int32_t eAddr32 = 0;
  u_int8_t eAddr_sreg = 0;
  u_int32_t linear_addr = 0;

  Reg greg[8] = {0};
  u_int8_t immLen = 0;
  u_int8_t cpl = 0;
  Sreg ldtr = {0}, tr = {0};
  GlobalSreg gdtr = {0}, idtr = {0};
  u_int32_t eflags = 0;
  u_int32_t cr[5] = {0};
u_int32_t dr[8] = {0};

int main(){
  init();
  cpu_loop();
  return 0;
}

void init(){
  EAX=0x0A;
  EBX=0;
  ECX=0;
  EDX=0;
  EBP=0;
  ESP=0;
  EDI=0;
  ESI=0;

  EIP=0;

  CS.selector=0;
  DS.selector=0;
  FS.selector=0;
  SS.selector=0;
  GS.selector=0;
  ES.selector=0;

  LDTR.selector=0;
  TR.selector=0;
  eflags=0;
  cr[0]=0x60000000;
  cr[0]|=CRO_PE_MASK;
  DEBUG("mode:%s\n",REAL_MODE?"real mode":"protected mode");
  CSDesc.d_b=1;
  gdtr.base=0;
  gdtr.limit=0xFFFF;
  idtr.base=0;
  idtr.limit=0xFFFF;
  print();
  mem_init();

}


void print(){
  DEBUG("EIP=0x%08x\n",EIP);
  DEBUG("EAX=0x%08x\n",EAX);
  DEBUG("EBX=0x%08x\n",EBX);
  DEBUG("ECX=0x%08x\n",ECX);
  DEBUG("EDX=0x%08x\n",EDX);
  DEBUG("EBP=0x%08x\n",EBP);
  DEBUG("ESP=0x%08x\n",ESP);
  DEBUG("ESI=0x%08x\n",ESI);
  DEBUG("EDI=0x%08x\n",EDI);
  DEBUG("EFLAGS=0x%08x\n",eflags);
  /*DEBUG("CS=0x%x\n",CS.selector);
    DEBUG("DS=0x%x\n",DS.selector);
    DEBUG("FS=0x%x\n",FS.selector);
    DEBUG("GS=0x%x\n",GS.selector);
    DEBUG("SS=0x%x\n",SS.selector);
    DEBUG("ES=0x%x\n",ES.selector);*/
}

