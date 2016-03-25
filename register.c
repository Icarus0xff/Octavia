#include "global.h"

//general register read and write
Bit8u read8BitReg(Bit8u index){
	if(index>3)
		return greg[index-4].word.byte.rh;
	else
		return greg[index].word.byte.rl;
}
void write8BitReg(Bit8u index,Bit8u data){
	if(index>3)
		greg[index-4].word.byte.rh=data;
	else
		greg[index].word.byte.rl=data;
}
Bit16u read16BitReg(Bit8u index){
	return greg[index].word.rx;
}
void write16BitReg(Bit8u index,Bit16u data){
	greg[index].word.rx=data;
}

Bit32u read32BitReg(Bit8u index){
	return greg[index].dword.erx;
}
void write32BitReg(Bit8u index,Bit32u data){
	greg[index].dword.erx=data;
}

//segment reg read and write
Bit16u readSegmentSelector(Bit8u index){
	return sreg[index].selector.selector;
}

