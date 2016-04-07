#include <cstring>
#include "global.h"

//memory init
void mem_init(){
  memBase=(u_int8_t*)malloc(MEMSIZE);
  int cur=0;
  FILE *memFile;
  unsigned char buf[512];
  memFile=fopen("mem_rom","rb");
  if(memFile==NULL){
    printf("mem initial file not exist\n");
    exit(1);
  }
  memset(buf,0,512);
  int rc;
  int start=0,end=0;
  while((rc=fread(buf,sizeof(unsigned char),512,memFile))!=0){
    int i=0;
    while(i<1024){
      if(start==0){
	//find ud2(0f 0b) instruciton as start
	if(buf[i]==0x0f && buf[i+1]==0x0b){
	  i+=2;
	  start=1;
	}
	else{
	  i++;
	  continue;
	}
      }
      memBase[cur++]=buf[i];
      //find leave(c90) instruciton as end
      if(buf[i]==0xc9){
	end=1;
	break;
      }
      i++;
    }
    if(end>0) break;
  }
  DEBUG("cur=%d,%d\n",cur,memBase[cur-1]);
}


u_int32_t translate_linear_addr(u_int32_t offset,u_int8_t sreg){
  printf("offset: %08x\n", offset);
  return (readSegmentSelector(sreg)<<4)+offset;
}
u_int8_t* get_mem_data(){
  DEBUG("data:0x%08x\n",*(memBase+linear_addr));
  return memBase+linear_addr;
}
void* get_stack_top(){
  if(stack_address_size()==16){
    u_int32_t top_address=translate_linear_addr(SP,SEG_REG_SS);
    return memBase+top_address;
  }
  else{
    u_int32_t top_address=translate_linear_addr(ESP,SEG_REG_SS);
    return memBase+top_address;
  }
}

void* get_stack_base(){
  if(stack_address_size()==16){
    u_int32_t top_address=translate_linear_addr(BP,SEG_REG_SS);
    return memBase+top_address;
  }
  else{
    u_int32_t top_address=translate_linear_addr(EBP,SEG_REG_SS);
    return memBase+top_address;
  }
}
void push_16b(u_int16_t data){
  ESP=ESP-2;
  u_int16_t* top=(u_int16_t*)get_stack_top();
  *top=data;
}
void push_32b(u_int32_t data){
  ESP=ESP-4;
  u_int32_t* top=(u_int32_t*)get_stack_top();
  *top=data;
}
u_int16_t pop_16b(){
  u_int16_t* top=(u_int16_t*)get_stack_top();
  ESP=ESP+2;
  return *top;
}
u_int32_t pop_32b(){
  u_int32_t* top=(u_int32_t*)get_stack_top();
  ESP=ESP+4;
  return *top;
}

u_int8_t* get_string_src(){ //DS：（ESI）
  u_int8_t dstSreg=prefix_seg==7?SEG_REG_DS:prefix_seg;
  if(address_size()==16)
    linear_addr=translate_linear_addr(SI,dstSreg);
  else
    linear_addr=translate_linear_addr(ESI,dstSreg);
  return get_mem_data();
}

u_int8_t* get_string_dst(){ //ES：（EDI）
  if(address_size()==16)
    linear_addr=translate_linear_addr(DI,SEG_REG_ES);
  else
    linear_addr=translate_linear_addr(EDI,SEG_REG_ES);
  return get_mem_data();
}
