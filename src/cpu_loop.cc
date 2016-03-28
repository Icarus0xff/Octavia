#include "global.h"
#include "__dec_opcode.hh"

//main cpu loop
void cpu_loop(){
  int i=5;
  while(i--){
    fetch();
    dec_prefix();
    DEBUG("opcode:%02x , prefixLen:%d\n",*curInst,prefixLen);
    if(prefix_2byte)
      dec_opcode_2byte_run();
    else
      //dec_opcode_run();
      opcode_run();
    print();
    if(*curInst==0xC9) break;  //leave instruciton as an end
  }
}

void cpu_exec_once(){
  fetch();
  dec_prefix();
  DEBUG("opcode:%02x , prefixLen:%d\n",*curInst,prefixLen);
  if(prefix_2byte)
    dec_opcode_2byte_run();
  else
    dec_opcode_run();
  print();
}
void fetch(){
  linear_addr=translate_linear_addr(EIP,SEG_REG_CS);
  curInst=get_mem_data();
}


