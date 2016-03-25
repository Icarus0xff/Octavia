#include "global.h"

//general register read and write
u_int8_t read8BitReg(u_int8_t index){
  if(index>3)
    return greg[index-4].word.byte.rh;
  else
    return greg[index].word.byte.rl;
}
void write8BitReg(u_int8_t index,u_int8_t data){
  if(index>3)
    greg[index-4].word.byte.rh=data;
  else
    greg[index].word.byte.rl=data;
}
u_int16_t read16BitReg(u_int8_t index){
  return greg[index].word.rx;
}
void write16BitReg(u_int8_t index,u_int16_t data){
  greg[index].word.rx=data;
}

u_int32_t read32BitReg(u_int8_t index){
  return greg[index].dword.erx;
}
void write32BitReg(u_int8_t index,u_int32_t data){
  greg[index].dword.erx=data;
}

//segment reg read and write
u_int16_t readSegmentSelector(u_int8_t index){
  return sreg[index].selector.selector;
}

