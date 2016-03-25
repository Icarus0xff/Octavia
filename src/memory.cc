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
	memset(buf,'\0',512);
	int rc;
	int start=0,end=0;
	while((rc=fread(buf,sizeof(unsigned char),512,memFile))!=0){
		int i=0;
		while(i<1024){
			if(start==0){
				if(buf[i]==15&&buf[i+1]==11){
					i+=2;
					start=1;
				}
				else{
					i++;
					continue;
				}
			}
			memBase[cur++]=buf[i];
			if(buf[i]==201){
				end=1;
				break;
			}
			i++;
		}
		if(end>0) break;
	}
	DEBUG("cur=%d,%d\n",cur,memBase[cur-1]);
}

void rtl_mem_init(){
	memBase_rtl=(u_int8_t*)malloc(MEMSIZE);
	int cur=0;
	FILE *memFile;
	unsigned char buf[512];
	memFile=fopen("mem_rom","rb");
	if(memFile==NULL){
		printf("mem initial file not exist\n");
		exit(1);
	}
	memset(buf,'\0',512);
	int rc;
	int start=0,end=0;
	while((rc=fread(buf,sizeof(unsigned char),512,memFile))!=0){
		int i=0;
		while(i<1024){
			if(start==0){
				if(buf[i]==15&&buf[i+1]==11){
					i+=2;
					start=1;
				}
				else{
					i++;
					continue;
				}
			}
			memBase_rtl[cur++]=buf[i];
			if(buf[i]==201){
				end=1;
				break;
			}
			i++;
		}
		if(end>0) break;
	}
	
	int counter = 0;

	while (counter <= 10)
	{
	    printf("mem[%d] = %x\n",counter, memBase_rtl[counter]);
	    counter = counter + 1;
	}
	DEBUG("cur=%d,%d\n",cur,memBase_rtl[cur-1]);
}

u_int32_t translate_linear_addr(u_int32_t offset,u_int8_t sreg){
	return (readSegmentSelector(sreg)<<4)+offset;
	//DEBUG("linear address:%08x(%d)\n",linear_addr,offset);
}
u_int8_t* get_mem_data(){
	DEBUG("data:%0x",*(memBase+linear_addr));
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
