#include "global.h"
u_int32_t getSegmentLimit(Descriptor segment){
        u_int32_t tmp=segment.limit1;
        tmp=tmp<<16+segment.limit2;
        if(segment.g==0){
            return tmp;
        }
        else return tmp<<12|0xFFF;
}
u_int32_t getSegmentBase(Descriptor segment){
      u_int32_t tmp=segment.base1;
        tmp=tmp<<24+segment.base2;
        return tmp;
}
u_int16_t getGateSelector(Descriptor gate){
    return gate.selector;
}
u_int32_t getGateOffset(Descriptor gate){
    u_int32_t tmp=gate.offset1;
        tmp=tmp<<16+gate.offset2;
        return tmp;
}
int8_t isNullSelector(Selector selector){ //the first segment in GDT is null ,index=0,ti=0
    if((selector.selector&NULL_SELECTOR_MASK)==0) return 1;
    else return 0;
}

int8_t checkTableLimit(Selector selector){
    if(selector.ti==0){ //in gdt
        if(selector.index<gdtr.limit) return 1;
        else return 0;
    }
    else{ //in ldt
        if(selector.index*8+getSegmentBase(ldtr.cache)+7<=getSegmentLimit(ldtr.cache)) return 1;
        else return 0;
    }
}

Descriptor* getSegmentDescriptor(Selector selector){
    u_int32_t offset=selector.index*8;
    if(selector.ti==0){ //in gdt
         linear_addr=translate_linear_addr(SEG_REG_DS,offset+gdtr.base);
         return (Descriptor*)get_mem_data();
    }
    else{ //in ldt
        linear_addr=getSegmentBase(ldtr.cache)+offset;
        return (Descriptor*)get_mem_data();
    }
}

int8_t checkSegRights(Descriptor descriptor,u_int8_t rights_mask){
    rights_mask&=0x0F;
    if(descriptor.s==1)//data/code segment
        if((rights_mask>>3==descriptor.type>>3)&&(rights_mask&descriptor.type==rights_mask) )
            return 1;
    return 0;
}

void load_seg(Selector selector,u_int8_t seg){
    if(PROTECTED_MODE){
        if(seg==SEG_REG_SS) {
            if(isNullSelector(selector)){
                printf("#GP(0) exception\n");
                exit(0);
            }
            else if(!checkTableLimit(selector)||cpl!=selector.rpl){
                printf("#GP(%d) exception\n",selector.selector);
                exit(0);
            }
            else{
                Descriptor* descriptor=getSegmentDescriptor(selector);
                if(!checkSegRights(*descriptor,DATA_READ_WRITE)||descriptor->dpl!=cpl){
                    printf("#GP(%d) exception\n",selector.selector);
                    exit(0);
                }else if(descriptor->p==0){
                    printf("#SS(%d) exception\n",selector.selector);
                    exit(0);
                }
                SS.selector=selector.selector;
                SSDesc.descriptor=descriptor->descriptor;
            }
        }else if(!isNullSelector(selector)){
            if(!checkTableLimit(selector)){
                    printf("#GP(%d) exception\n",selector.selector);
                    exit(0);
                }
                else{
                    Descriptor* descriptor=getSegmentDescriptor(selector);
                    if((!checkSegRights(*descriptor,DATA_READ_ONLY)&&!checkSegRights(*descriptor,CODE_EXEC_READ))
                     ||!checkSegRights(*descriptor,CODE_EXEC_ONLY_CONFORMING)&&(descriptor->dpl<cpl||descriptor->dpl>selector.rpl)){
                        printf("#GP(%d) exception\n",selector.selector);
                        exit(0);
                    }else if(descriptor->p==0){
                        printf("#NP(%d) exception\n",selector.selector);
                        exit(0);
                    }
                    sreg[seg].selector.selector=selector.selector;
                    sreg[seg].cache.descriptor=descriptor->descriptor;
                    sreg[seg].selector.valid=1;
                }
        }else{ //null selector
            sreg[seg].selector.selector=0;
            sreg[seg].selector.valid=0;
        }
    }else{ //REAL MODE or V8086 MODE
        sreg[seg].selector.selector=selector.selector;
    }
}
