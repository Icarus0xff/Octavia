#include "global.h"

//segment reg read and write
u_int16_t readSegmentSelector(u_int8_t index){
  return sreg[index].selector.selector;
}

