#include "global.h"
void exec_aaa()
{
    DEBUG("start run aaa\n");
    if((AL&0x0F)>9||get_flag(AF)==1)
    {
        AL=AL+6;
        AH=AH+1;
        set_flag(CF);
        set_flag(AF);
    }
    else
    {
        clear_flag(AF);
        clear_flag(CF);
    }
    AL=AL&0x0F;
}
void exec_aad(u_int8_t imm)
{
    DEBUG("start run aad\n");
    AL=(AH*imm+AL)&0xFF;
    AH=0;
    SET_EFLAGS(AX,0,0,0,16,PZS_MASK);
}
void exec_aam(u_int8_t imm)
{
    DEBUG("start run aam\n");
    AH=AL/imm;
    AL=AL%imm;
    SET_EFLAGS(AX,0,0,0,16,PZS_MASK);
}
void exec_aas()
{
    DEBUG("start run aas\n");
    u_int8_t borrow=AL<6?1:0;
    if((AL&0x0F)>9||get_flag(AF)==1)
    {
        AL=(AL-6)&0x0f;
        AH=AH-1-borrow;
        set_flag(CF);
        set_flag(AF);
    }
    else
    {
        clear_flag(AF);
        clear_flag(CF);
        AL=AL & 0x0f;
    }
}
u_int8_t exec_arith_8b(u_int8_t index,u_int8_t dst,u_int8_t src){
	switch(index){
		case 0:return exec_add_8b(dst,src);
		case 1:return exec_or_8b(dst,src);
		case 2:return exec_adc_8b(dst,src);
		case 3:return exec_sbb_8b(dst,src);
		case 4:return exec_and_8b(dst,src);
		case 5:return exec_sub_8b(dst,src);
		case 6:return exec_xor_8b(dst,src);
		case 7:return exec_cmp_8b(dst,src);
	}
}
u_int16_t exec_arith_16b(u_int8_t index,u_int16_t dst,u_int16_t src){
	switch(index){
		case 0:return exec_add_16b(dst,src);
		case 1:return exec_or_16b(dst,src);
		case 2:return exec_adc_16b(dst,src);
		case 3:return exec_sbb_16b(dst,src);
		case 4:return exec_and_16b(dst,src);
		case 5:return exec_sub_16b(dst,src);
		case 6:return exec_xor_16b(dst,src);
        case 7:return exec_cmp_16b(dst,src);
	}
}
u_int32_t exec_arith_32b(u_int8_t index,u_int32_t dst,u_int32_t src){
	switch(index){
		case 0:return exec_add_32b(dst,src);
		case 1:return exec_or_32b(dst,src);
		case 2:return exec_adc_32b(dst,src);
		case 3:return exec_sbb_32b(dst,src);
		case 4:return exec_and_32b(dst,src);
		case 5:return exec_sub_32b(dst,src);
		case 6:return exec_xor_32b(dst,src);
        case 7:return exec_cmp_32b(dst,src);
	}
}
u_int8_t exec_adc_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst+src+get_flag(CF);
     SET_EFLAGS(tmp,dst,src+get_flag(CF),1,8,CPAZSO_MASK);
    return tmp;
}

u_int16_t exec_adc_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst+src+get_flag(CF);
     SET_EFLAGS(tmp,dst,src+get_flag(CF),1,16,CPAZSO_MASK);
    return tmp;
}

u_int32_t exec_adc_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst+src+get_flag(CF);
    SET_EFLAGS(tmp,dst,src+get_flag(CF),1,32,CPAZSO_MASK);
    return tmp;
}

u_int8_t exec_add_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst+src;
    SET_EFLAGS(tmp,dst,src,1,8,CPAZSO_MASK);
    return tmp;
}

u_int16_t exec_add_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst+src;
   SET_EFLAGS(tmp,dst,src,1,16,CPAZSO_MASK);
    return tmp;
}

u_int32_t exec_add_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst+src;
   SET_EFLAGS(tmp,dst,src,1,32,CPAZSO_MASK);
    return tmp;
}

u_int8_t exec_and_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst&src;
    clear_flag(CF);
    clear_flag(OF);
     SET_EFLAGS(tmp,0,0,0,8,PZS_MASK);
    return tmp;
}

u_int16_t exec_and_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst&src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,16,PZS_MASK);
    return tmp;
}

u_int32_t exec_and_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst&src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,32,PZS_MASK);
    return tmp;
}

u_int8_t exec_or_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst|src;
    clear_flag(CF);
    clear_flag(OF);
     SET_EFLAGS(tmp,0,0,0,8,PZS_MASK);
    return tmp;
}

u_int16_t exec_or_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst|src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,16,PZS_MASK);
    return tmp;
}

u_int32_t exec_or_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst|src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,32,PZS_MASK);
    return tmp;
}

u_int8_t exec_cmp_8b(u_int8_t dst,u_int8_t src){
    u_int8_t tmp=dst-src;
     SET_EFLAGS(tmp,dst,src,2,8,CPAZSO_MASK);
     return dst;
}
u_int16_t exec_cmp_16b(u_int16_t dst,u_int16_t src){
    u_int16_t tmp=dst-src;
     SET_EFLAGS(tmp,dst,src,2,16,CPAZSO_MASK);
     return dst;
}
u_int32_t exec_cmp_32b(u_int32_t dst,u_int32_t src){
    u_int32_t tmp=dst-src;
     SET_EFLAGS(tmp,dst,src,2,32,CPAZSO_MASK);
     return dst;
}

u_int16_t exec_arpl(u_int16_t dst,u_int16_t src){
	Selector d,s;
	d.selector=dst;
	s.selector=src;
	if(d.rpl<s.rpl){
		set_flag(ZF);
		d.rpl=s.rpl;
	}
	else
		clear_flag(ZF);
	return d.selector;

}

void exec_bound_16b(int16_t*bound,int16_t index){
	if(index<bound[0]||index>bound[1]+2){
		printf("#BR exception\n");
		exit(0);
	}

}
void exec_bound_32b(int32_t*bound,int32_t index){
	if(index<bound[0]||index>bound[1]+4){
		printf("#BR exception\n");
		exit(0);
	}

}

void exec_bsf_16b(u_int8_t dst,u_int16_t src){
	int i=0;
	while(i<16){
		if((dst&(1<<i))!=0) break;
		i++;
	}
	if(i<16){
		set_flag(ZF);
		write16BitReg(dst,i);
	}
	else clear_flag(ZF);
}
void exec_bsf_32b(u_int8_t dst,u_int32_t src){
	int i=0;
	while(i<32){
		if((dst&(1<<i))!=0) break;
		i++;
	}
	if(i<32){
		set_flag(ZF);
		write16BitReg(dst,i);
	}
	else clear_flag(ZF);
}

void exec_bsr_16b(u_int8_t dst,u_int16_t src){
	int i=0;
	while(i<16){
		if((dst&(1<<(15-i)))!=0) break;
		i--;
	}
	if(i<16){
		set_flag(ZF);
		write16BitReg(dst,15-i);
	}
	else clear_flag(ZF);
}
void exec_bsr_32b(u_int8_t dst,u_int32_t src){
	int i=0;
	while(i<32){
		if((dst&(1<<(31-i)))!=0) break;
		i--;
	}
	if(i<32){
		set_flag(ZF);
		write16BitReg(dst,31-i);
	}
	else clear_flag(ZF);
}

void exec_bswap(u_int8_t reg){
	u_int32_t tmp=read32BitReg(reg);
	tmp=(tmp<<24)+((tmp&0xFF00)<<8)+((tmp&0xFF0000)>>8)+(tmp>>24);
	write32BitReg(reg,tmp);
}

void exec_btx_16b_reg(u_int8_t op,u_int8_t dst,u_int16_t index){
	index=index%16;
	u_int16_t tmp=read16BitReg(dst);
	if(tmp&(1<<index))
		set_flag(CF);
	else
		clear_flag(CF);
	switch(op){
		case 4: //BT
			break;
		case 5: //BTS
			write16BitReg(reg2,tmp|(1<<index));
		case 6://BTR
			write16BitReg(reg2,tmp&(~(1<<index)));
		case 7:	//BTC
			write16BitReg(reg2,tmp^(1<<index));
	}
}
void exec_btx_32b_reg(u_int8_t op,u_int8_t dst,u_int32_t index){
	index=index%32;
	u_int32_t tmp=read32BitReg(dst);
	if(tmp&(1<<index))
		set_flag(CF);
	else
		clear_flag(CF);
	switch(op){
		case 4: //BT
			break;
		case 5: //BTS
			write32BitReg(reg2,tmp|(1<<index));
			break;
		case 6://BTR
			write32BitReg(reg2,tmp&(~(1<<index)));
			break;
		case 7:	//BTC
			write32BitReg(reg2,tmp^(1<<index));
			break;
		default:
			printf("#UD exception");
			exit(0);

	}
}
void exec_btx_mem(u_int8_t op,u_int8_t *dst,int32_t index){
	if(index<0){
		dst=dst+(index+1)/8-1;
		index=1-(index+1)%8;
	}
	else{
		dst=dst+index/8;
		index=index%8;
	}
	if(*dst&(1<<index))
		set_flag(CF);
	else
		clear_flag(CF);
	switch(op){
		case 4: //BT
			break;
		case 5: //BTS
			*dst=*dst|(1<<index);
			break;
		case 6://BTR
			*dst=*dst&(~(1<<index));
			break;
		case 7:	//BTC
			*dst=*dst^(1<<index);
			break;
		default:
			printf("#UD exception");
			exit(0);
	}
}

void exec_call_near_relative( ){
	if(operand_size()==16){
		u_int16_t nextIP=IP+instLen+prefixLen+immLen+1;
		u_int16_t rel=*(u_int16_t*)(curInst+1);
		push_16b(nextIP&0xFFFF);
		EIP=(nextIP+rel)&0xFFFF;
	}
	else{
		u_int32_t nextEIP=EIP+instLen+prefixLen+immLen+1;
		u_int32_t rel=*(u_int32_t*)(curInst+1);
		push_32b(nextEIP);
		EIP=nextEIP+rel;
	}
}

void exec_call_near_absolute(){
	u_int32_t nextEIP=EIP+instLen+prefixLen+immLen+1;
	if(operand_size()==16){
		u_int16_t addr=rm_is_reg?read16BitReg(reg2):*(u_int16_t*)get_mem_data();
		push_16b(nextEIP&0xFFFF);
		EIP=addr;
	}
	else{
		u_int32_t addr=rm_is_reg?read32BitReg(reg2):*(u_int32_t*)get_mem_data();
		push_32b(nextEIP);
		EIP=addr;
	}
}


void exec_cli(){
    if(REAL_MODE){
        clear_flag(IF);
    }
    else if(V8086_MODE){
        if(get_iopl()==3)
            clear_flag(IF);
        else{
            printf("#GP(0) exception\n");
            exit(0);
        }
    }
    else{//protected mode
         if(CPL<=get_iopl())
            clear_flag(IF);
        else{
            printf("#GP(0) exception\n");
            exit(0);
        }
    }
}

void exec_clts(){
    if(!REAL_MODE&&CPL!=0){
        printf("#GP(0) exception\n");
        exit(0);
    }
    cr[0]&=~CRO_TS_MASK;
}

void exec_cmps_8b(){
    while(1){
        u_int8_t *dst=get_string_dst();
        u_int8_t *src=get_string_src();
        exec_cmp_8b(*src,*dst);
        if(get_flag(DF)==0){
            ESI++;
            EDI++;
        }
        else{
            ESI--;
            EDI--;
        }
        if(prefix_rep==0) break;
        else if(rep_condition(1)==0) break;
    }

}


void exec_cmps_16_32b(){
    while(1){
            if(operand_size()==16){
                u_int16_t *dst=(u_int16_t*)get_string_dst();
                u_int16_t *src=(u_int16_t*)get_string_src();
                exec_cmp_16b(*src,*dst);
                 if(get_flag(DF)==0){
                    ESI+=2;
                    EDI+=2;
                }
                else{
                    ESI-=2;
                    EDI-=2;
                }
            }else{
                u_int32_t *dst=(u_int32_t*)get_string_dst();
                u_int32_t *src=(u_int32_t*)get_string_src();
                exec_cmp_32b(*src,*dst);
                 if(get_flag(DF)==0){
                    ESI+=4;
                    EDI+=4;
                }
                else{
                    ESI-=4;
                    EDI-=4;
                }
            }
            if(prefix_rep==0) break;
            else if(rep_condition(1)==0) break;
    }

}

void exec_cmpxchg_8b(u_int8_t src){
    if(rm_is_reg){
        exec_cmp_8b(AL,read8BitReg(reg2));
        if(get_flag(ZF))
                write8BitReg(reg2,src);
        else  AL=read8BitReg(reg2);
    }
    else{
        u_int8_t *data=get_mem_data();
        exec_cmp_8b(AL,*data);
        if(get_flag(ZF))
            *data=src;
        else AL=*data;

    }

}
void exec_cmpxchg_16b(u_int16_t src){
    if(rm_is_reg){
        exec_cmp_16b(AX,read16BitReg(reg2));
        if(get_flag(ZF))
                write16BitReg(reg2,src);
        else  AX=read16BitReg(reg2);
    }
    else{
        u_int16_t *data=(u_int16_t*)get_mem_data();
        exec_cmp_16b(AX,*data);
        if(get_flag(ZF))
            *data=src;
        else AX=*data;

    }

}
void exec_cmpxchg_32b(u_int32_t src)  {
    if(rm_is_reg){
        exec_cmp_32b(EAX,read32BitReg(reg2));
        if(get_flag(ZF))
                write32BitReg(reg2,src);
        else  EAX=read32BitReg(reg2);
    }
    else{
        u_int32_t *data=(u_int32_t*)get_mem_data();
        exec_cmp_32b(EAX,*data);
        if(get_flag(ZF))
            *data=src;
        else EAX=*data;

    }
}

void exec_cpuid(){
    switch(EAX){
        case 0:
            EAX=1;
            EBX=0x756e6547;
            EDX=0x49656e69;
            ECX=0x6c65746e;
            break;
        default:
            EAX=0x0000045B;
            EBX=0x00010000;
            ECX=0;
            EDX=0;
            break;
    }

}
void exec_cwd_cdq(){
    if(operand_size()==16){
        if(AX&(1<<15)){
            DX=0xFFFF;
        }
        else DX=0;
    }else{
        if(AX&(1<<31)){
            EDX=0xFFFFFFFF;
        }
        else EDX=0;

    }
}

void exec_daa(){

    if((AL&0x0F)>9||get_flag(AF)){
        SET_EFLAGS(AL+6,AL,6,1,8,CF_MASK);
        AL=AL+6;
        set_flag(AF);
    }
    else clear_flag(AF);
    if((AL&0xF0)>0x90||get_flag(CF)) {
        AL=AL+0x60;
        set_flag(CF);
    }
    else clear_flag(CF);
    SET_EFLAGS(AL,0,0,0,8,PZS_MASK);
}

void exec_das(){

    if((AL&0x0F)>9||get_flag(AF)){
        SET_EFLAGS(AL-6,AL,6,2,8,CF_MASK);
        AL=AL-6;
        set_flag(AF);
    }
    else clear_flag(AF);
    if((AL&0xF0)>0x90||get_flag(CF)) {
        AL=AL-0x60;
        set_flag(CF);
    }
    else clear_flag(CF);
    SET_EFLAGS(AL,0,0,0,8,PZS_MASK);
}

void exec_dec_8b(){
    if(rm_is_reg){
        u_int8_t dst=read8BitReg(reg2);
        SET_EFLAGS(dst-1,dst,1,2,8, PAZSO_MASK);
        write8BitReg(reg2,dst-1);
    }
    else{
        u_int8_t *dst=get_mem_data();
        SET_EFLAGS(*dst-1,*dst,1,2,8, PAZSO_MASK);
        *dst=*dst-1;
    }
}
void exec_dec_16_32b(){
    if(operand_size()==16){
        if(rm_is_reg){
            u_int16_t dst=read16BitReg(reg2);
            SET_EFLAGS(dst-1,dst,1,2,16, PAZSO_MASK);
            write16BitReg(reg2,dst-1);
        }
        else{
            u_int16_t *dst=(u_int16_t*)get_mem_data();
            SET_EFLAGS(*dst-1,*dst,1,2,16, PAZSO_MASK);
            *dst=*dst-1;
        }
    }else{
        if(rm_is_reg){
            u_int32_t dst=read32BitReg(reg2);
            SET_EFLAGS(dst-1,dst,1,2,32, PAZSO_MASK);
            write32BitReg(reg2,dst-1);
        }
        else{
            u_int32_t *dst=(u_int32_t*)get_mem_data();
            SET_EFLAGS(*dst-1,*dst,1,2,32, PAZSO_MASK);
            *dst=*dst-1;
        }
    }
}
void exec_dec_16_32b_r(u_int8_t reg){
     if(operand_size()==16){
        u_int16_t dst=read16BitReg(reg);
        SET_EFLAGS(dst-1,dst,1,2,16, PAZSO_MASK);
        write16BitReg(reg2,dst-1);
    }else{
        u_int32_t dst=read32BitReg(reg);
        SET_EFLAGS(dst-1,dst,1,2,32, PAZSO_MASK);
        write32BitReg(reg2,dst-1);
    }

}

void exec_div_8b(){
    u_int8_t src;
    if(rm_is_reg){
        src=read8BitReg(reg2);
    }
    else{
        src=*get_mem_data();
    }
    if(src==0){
        printf("#DE exception\n");
        exit(0);
    }
    u_int8_t tmp=AX/src;
    AH=AX%src;
    AL=tmp;
}
void exec_div_16_32b(){
    if(operand_size()==16){
         u_int16_t src;
        if(rm_is_reg){
            src=read16BitReg(reg2);
        }
        else{
            src=*(u_int16_t*)get_mem_data();
        }
        if(src==0){
            printf("#DE exception\n");
            exit(0);
        }
        u_int32_t tmp=DX;
        tmp=tmp<<16+AX;
        AX=tmp%src;
        DX=tmp/src;
    }else{
         u_int32_t src;
        if(rm_is_reg){
            src=read32BitReg(reg2);
        }
        else{
            src=*(u_int32_t*)get_mem_data();
        }
        if(src==0){
            printf("#DE exception\n");
            exit(0);
        }
        unsigned long tmp=EDX;
        tmp=tmp<<32+EAX;
        EAX=tmp%src;
        EDX=tmp/src;
    }
}

void exec_mul_8b(){
    u_int8_t src;
    if(rm_is_reg){
        src=read8BitReg(reg2);
    }
    else{
        src=*get_mem_data();
    }
    AX=AL;
    AX=AL*src;
    if(AH==0){
        clear_flag(OF);
        clear_flag(CF);
    }
    else{
        set_flag(CF);
        set_flag(OF);
    }
}
void exec_mul_16_32b(){
    if(operand_size()==16){
         u_int16_t src;
        if(rm_is_reg){
            src=read16BitReg(reg2);
        }
        else{
            src=*(u_int16_t*)get_mem_data();
        }
        u_int32_t tmp=AX;
        tmp=tmp*src;
        AX=tmp%(1<<16);
        DX=tmp/(1<<16);
        if(DX==0){
            clear_flag(OF);
            clear_flag(CF);
        }
        else{
            set_flag(CF);
            set_flag(OF);
        }
    }else{
         u_int32_t src;
        if(rm_is_reg){
            src=read32BitReg(reg2);
        }
        else{
            src=*(u_int32_t*)get_mem_data();
        }
        unsigned long tmp=EAX;
        tmp=tmp*src;
        EAX=tmp%((unsigned long)1<<32);
        EDX=tmp/((unsigned long)1<<32);
        if(EDX==0){
            clear_flag(OF);
            clear_flag(CF);
        }
        else{
            set_flag(CF);
            set_flag(OF);
        }
    }
}

void exec_neg_8b(){
    if(rm_is_reg){
        int8_t src=read8BitReg(reg2);
        src=-src;
        write8BitReg(reg2,src);
        if(src==0) clear_flag(CF);
        else set_flag(CF);
    }
    else{
        int8_t *src=(int8_t*)get_mem_data();
        *src=-(*src);
        if(*src==0) clear_flag(CF);
        else set_flag(CF);
    }
}
void exec_neg_16_32b(){
    if(operand_size()==16){
        if(rm_is_reg){
            int16_t src=read16BitReg(reg2);
            src=-src;
            write16BitReg(reg2,src);
            if(src==0) clear_flag(CF);
            else set_flag(CF);
        }
        else{
            int16_t* src=(int16_t*)get_mem_data();
             *src=-(*src);
            if(*src==0) clear_flag(CF);
            else set_flag(CF);
        }
    }else{
         if(rm_is_reg){
            int32_t src=read32BitReg(reg2);
            src=-src;
            write32BitReg(reg2,src);
            if(src==0) clear_flag(CF);
            else set_flag(CF);
        }
        else{
            int32_t* src=(int32_t*)get_mem_data();
             *src=-(*src);
            if(*src==0) clear_flag(CF);
            else set_flag(CF);
        }
    }
}

void exec_not_8b(){
    if(rm_is_reg){
        u_int8_t src=read8BitReg(reg2);
        src=~src;
        write8BitReg(reg2,src);
    }
    else{
        u_int8_t *src=get_mem_data();
        *src=~(*src);
    }
}
void exec_not_16_32b(){
    if(operand_size()==16){
        if(rm_is_reg){
            u_int16_t src=read16BitReg(reg2);
            src=~src;
            write16BitReg(reg2,src);
        }
        else{
            u_int16_t* src=(u_int16_t*)get_mem_data();
             *src=~(*src);
        }
    }else{
         if(rm_is_reg){
            u_int32_t src=read32BitReg(reg2);
            src=~src;
            write32BitReg(reg2,src);
        }
        else{
            u_int32_t* src=(u_int32_t*)get_mem_data();
             *src=~(*src);
        }
    }
}
void exec_enter(u_int16_t bytes ,u_int8_t nestLevel){
    nestLevel%=32;
    u_int32_t tmpEBP;
    if(stack_address_size()==32){
        push_32b(EBP);
        tmpEBP=ESP;
    }else{
        push_16b(BP);
        tmpEBP=SP;
    }
    if(nestLevel){
        while(nestLevel){
            if(operand_size()==32){
                if(stack_address_size()==32){
                    EBP=EBP-4;
                }
                else{
                    BP=BP-4;
                }
                 push_32b(*(u_int32_t*)get_stack_base());
            }else{
                if(stack_address_size()==32){
                    EBP=EBP-2;
                }
                else{
                    BP=BP-2;
                }
                 push_16b(*(u_int16_t*)get_stack_base());
            }
            nestLevel--;
        }
        if(operand_size()==32)
            push_32b(tmpEBP);
        else push_16b(tmpEBP);
    }
    if(stack_address_size()==16){
        EBP=tmpEBP;
        ESP=EBP-bytes;
    }
    else{
        BP=tmpEBP;
        SP=SP-bytes;
    }

}

void exec_idiv_8b(){
    int8_t src;
    if(rm_is_reg){
        src=read8BitReg(reg2);
    }
    else{
        src=*get_mem_data();
    }
    if(src==0){
        printf("#DE exception\n");
        exit(0);
    }
    int8_t tmp=(int16_t)AX/src;
    AH=(int16_t)AX%src;
    AL=tmp;
}
void exec_idiv_16_32b(){
    if(operand_size()==16){
         int16_t src;
        if(rm_is_reg){
            src=read16BitReg(reg2);
        }
        else{
            src=*(int16_t*)get_mem_data();
        }
        if(src==0){
            printf("#DE exception\n");
            exit(0);
        }
        int32_t tmp=DX;
        tmp=tmp<<16+AX;
        AX=tmp%src;
        DX=tmp/src;
    }else{
         int32_t src;
        if(rm_is_reg){
            src=read32BitReg(reg2);
        }
        else{
            src=*(int32_t*)get_mem_data();
        }
        if(src==0){
            printf("#DE exception\n");
            exit(0);
        }
        long tmp=EDX;
        tmp=tmp<<32+EAX;
        EAX=tmp%src;
        EDX=tmp/src;
    }
}

void exec_imul_8b(){
     int16_t dst=AL,src;
    if(rm_is_reg){
        src=(int8_t)read8BitReg(reg2);
    }
    else{
        src=(int8_t)*get_mem_data();
    }
    AX=src*dst;
}

void exec_imul_16_32b(u_int8_t operandNum,int32_t imm){
    switch(operandNum){
        case 1:
            if(operand_size()==16){
                 int32_t src;
                if(rm_is_reg){
                    src=(int16_t)read16BitReg(reg2);
                }else{
                    src=*(int16_t*)get_mem_data();
                }
                u_int32_t dst=src*AX;
                AX=dst&0xFFFF;
                DX=dst>>16;
                if(DX!=0&&(DX+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }else{
                int64_t src;
                if(rm_is_reg){
                    src=(int32_t)read32BitReg(reg2);
                }else{
                    src=*(int32_t*)get_mem_data();
                }
                int64_t dst=src*EAX;
                EAX=dst&0xFFFFFFFF;
                EDX=dst>>32;
                if(EDX!=0&&(EDX+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }
            break;
        case 2:
            if(operand_size()==16){
                int32_t src;
                if(rm_is_reg){
                        src=(int16_t)read16BitReg(reg2);
                }else{
                       src=*(int16_t*)get_mem_data();
                }
                u_int32_t dst=src*read16BitReg(reg1);
                write16BitReg(reg1,dst&0xFFFF);
                u_int16_t up16b=dst>>16;
                if(up16b!=0&&(up16b+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }else{
                 int64_t src;
                 if(rm_is_reg){
                        int64_t src=(int32_t)read32BitReg(reg2);

                }else{
                    int64_t src=*(int32_t*)get_mem_data();
                }
                 int64_t dst=read32BitReg(reg1)*src;
                 write32BitReg(reg1,dst&0xFFFFFFFF);
                 u_int32_t up32b=dst>>32;
                if(up32b!=0&&(up32b+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }
            break;
        case 3:
             if(operand_size()==16){
                int32_t src;
                if(rm_is_reg){
                        src=(int16_t)read16BitReg(reg2);
                }else{
                       src=*(int16_t*)get_mem_data();
                }
                u_int32_t dst=src*imm;
                write16BitReg(reg1,dst&0xFFFF);
                u_int16_t up16b=dst>>16;
                if(up16b!=0&&(up16b+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }else{
                 int64_t src;
                 if(rm_is_reg){
                        int64_t src=(int32_t)read32BitReg(reg2);

                }else{
                    int64_t src=*(int32_t*)get_mem_data();
                }
                 int64_t dst=src*imm;
                 write32BitReg(reg1,dst&0xFFFFFFFF);
                 u_int32_t up32b=dst>>32;
                if(up32b!=0&&(up32b+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }
        default:
            break;
    }

}
void exec_lahf(){
    AH=eflags&0xFF;
}

void exec_load_seg(u_int8_t seg){
    u_int8_t* operand=get_mem_data();
    Selector  selector;
    if(operand_size()==16){
        write16BitReg(reg1,*(u_int16_t*)operand);
        selector.selector=*(u_int16_t*)(operand+2);
    }else{
        write32BitReg(reg1,*(u_int32_t*)operand);
        selector.selector=*(u_int16_t*)(operand+4);
    }
   load_seg(selector,seg);
}

void exec_lea(){
    if(rm_is_reg){
        printf("#UD exception\n");
        exit(0);
    }
    if(operand_size()==16){
        if(address_size()==16){
            write16BitReg(reg1,eAddr16);
        }else{
            write16BitReg(reg1,eAddr32);
        }
    } else{
        if(address_size()==16){
            write32BitReg(reg1,eAddr16);
        }else{
            write32BitReg(reg1,eAddr32);
        }
    }
}

void exec_leave(){
    if(stack_address_size()==16)SP=BP;
    else ESP=EBP;
    if(operand_size()==16) BP=pop_16b();
    else EBP=pop_32b();
}

void exec_lgdt(){
    if(rm_is_reg){
        printf("#UD exception\n");
        exit(0);
    }
    if(!REAL_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    u_int8_t* operand=get_mem_data();
    if(operand_size()==16){
        gdtr.limit=*(u_int16_t*)operand;
        gdtr.base=*(u_int32_t*)(operand+2)&0x00FFFFFF;
    }else{
        gdtr.limit=*(u_int16_t*)operand;
        gdtr.base=*(u_int32_t*)(operand+2);
    }
}
void exec_lidt(){
    if(rm_is_reg){
        printf("#UD exception\n");
        exit(0);
    }
    if(!REAL_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    u_int8_t* operand=get_mem_data();
    if(operand_size()==16){
        idtr.limit=*(u_int16_t*)operand;
        idtr.base=*(u_int32_t*)(operand+2)&0x00FFFFFF;
    }else{
        idtr.limit=*(u_int16_t*)operand;
        idtr.base=*(u_int32_t*)(operand+2);
    }
}

void exec_lldt(){
    Selector selector;
    if(rm_is_reg){
        selector.selector=read16BitReg(reg2);
    }else{
        selector.selector=*(u_int16_t*)get_mem_data();
    }
    if(!REAL_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    if(isNullSelector(selector)){
        ldtr.selector.valid=0;
        ldtr.selector.selector=0;
    }else if(selector.ti!=0||!checkTableLimit(selector)){
        printf("#GP(%d) exception\n",selector.selector);
        exit(0);
    }else{
        Descriptor *descriptor=getSegmentDescriptor(selector);
        if(descriptor->type!=SYS_SEGMENT_LDT){
            printf("#GP(%d) exception\n",selector.selector);
            exit(0);
        }else if(descriptor->p==0){
            printf("#NP(%d) exception\n",selector.selector);
            exit(0);
        }
        LDTR.selector=selector.selector;
        LDTRDesc.descriptor=descriptor->descriptor;
        LDTR.valid=1;
    }
}

void exec_lmsw(){
    u_int16_t src;
    if(rm_is_reg){
        src=read16BitReg(reg2);
    }else{
        src=*(u_int16_t*)get_mem_data();
    }
    if(!REAL_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    cr[0]=(cr[0]&0xFFFFFFF0)|(src&0xF);

}
void exec_lods_8b(){
    while(1){
        u_int8_t *dst=get_string_dst();
         AL=*dst;
        if(get_flag(DF)==0){
            ESI++;
        }
        else{
            ESI--;
        }
        if(prefix_rep==0) break;
        else if(rep_condition(1)==0) break;
    }
}
void exec_lods_16_32b(){
      while(1){
        u_int8_t *dst=get_string_dst();
        if(operand_size()==16) AX=*(u_int16_t*)dst;
        else EAX=*(u_int32_t*)dst;
        if(get_flag(DF)==0){
            ESI+=operand_size()/8;
        }
        else{
            ESI-=operand_size()/8;
        }
        if(prefix_rep==0) break;
        else if(rep_condition(1)==0) break;
    }
}

u_int8_t exec_loop(){
    u_int8_t condition=0;
   if(address_size()==16){
        CX--;
        if(CX!=0){
            condition=1;
        }
    }else{
        ECX--;
         if(ECX!=0){
            condition=1;
        }
    }
    int32_t offset=*(int8_t*)(curInst+1);
    u_int32_t newIP=offset+EIP;
    if(condition){
        if(operand_size()==16) IP=newIP&0xFFFF;
        else EIP=newIP;
    }
    return condition;
}

u_int8_t exec_loope(){
    u_int8_t condition=0;
    if(address_size()==16){
        CX--;
        if(CX!=0&&get_flag(ZF)==1){
            condition=1;
        }
    }else{
        ECX--;
         if(ECX!=0&&get_flag(ZF)==1){
            condition=1;
        }
    }
    int32_t offset=*(int8_t*)(curInst+1);
    u_int32_t newIP=offset+EIP;
    if(condition){
        if(operand_size()==16) IP=newIP&0xFFFF;
        else EIP=newIP;
    }
    return condition;
}

u_int8_t exec_loopne(){
    u_int8_t condition=0;
    if(address_size()==16){
        CX--;
        if(CX!=0&&get_flag(ZF)==0){
            condition=1;
        }
    }else{
        ECX--;
         if(ECX!=0&&get_flag(ZF)==0){
            condition=1;
        }
    }
    int32_t offset=*(int8_t*)(curInst+1);
    u_int32_t newIP=offset+EIP;
    if(condition){
        if(operand_size()==16) IP=newIP&0xFFFF;
        else EIP=newIP;
    }
    return condition;
}

void exec_ltr(){
    Selector selector;
    if(rm_is_reg){
        selector.selector=read16BitReg(reg2);
    }else{
        selector.selector=*(u_int16_t*)get_mem_data();
    }
    if(!REAL_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    if(isNullSelector(selector)){
        tr.selector.valid=0;
        tr.selector.selector=0;
    }else if(selector.ti!=0||!checkTableLimit(selector)){
        printf("#GP(%d) exception\n",selector.selector);
        exit(0);
    }else{
        Descriptor *descriptor=getSegmentDescriptor(selector);
        if(descriptor->type!=SYS_SEGMENT_AVAIL_286_TSS&&descriptor->type!=SYS_SEGMENT_AVAIL_386_TSS){
            printf("#GP(%d) exception\n",selector.selector);
            exit(0);
        }else if(descriptor->p==0){
            printf("#NP(%d) exception\n",selector.selector);
            exit(0);
        }
        descriptor->type|=0x2;
        TR.selector=selector.selector;
        TRDesc.descriptor=descriptor->descriptor;
        TR.valid=1;
    }
}
void exec_mov_8b_2rm(u_int8_t src){
    if(rm_is_reg){
        write8BitReg(reg2,src);
    }else{
        u_int8_t *dst=get_mem_data();
        *dst=src;
    }
}
void exec_mov_8b_2reg(u_int8_t src,u_int8_t dstReg){
    write8BitReg(dstReg,src);
}
void exec_mov_16b_2rm(u_int16_t src){
  if(rm_is_reg){
        write16BitReg(reg2,src);
    }else{
        u_int16_t *dst=(u_int16_t*)get_mem_data();
        *dst=src;
    }
}
void exec_mov_16b_2reg(u_int16_t src,u_int8_t dstReg){
    write16BitReg(dstReg,src);
}
void exec_mov_32b_2rm(u_int32_t src){
    if(rm_is_reg){
        write32BitReg(reg2,src);
    }else{
        u_int32_t *dst=(u_int32_t*)get_mem_data();
        *dst=src;
    }
}
void exec_mov_32b_2reg(u_int32_t src,u_int8_t dstReg){
      write32BitReg(dstReg,src);
}
void exec_mov_seg(u_int8_t seg){
    if(rm_is_reg){
        write16BitReg(reg2,sreg[seg].selector.selector);
    }else{
        u_int16_t *dst=(u_int16_t*)get_mem_data();
        *dst=sreg[seg].selector.selector;
    }
}
void exec_mov_2seg(u_int8_t seg){
    Selector selector;
    if(rm_is_reg){
       selector.selector= read16BitReg(reg2);
    }else{
        u_int16_t *dst=(u_int16_t*)get_mem_data();
        selector.selector=*dst;
    }
    load_seg(selector,seg);
}

void exec_mov_2ctrl(){
    if(PROTECTED_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    cr[reg1]=read32BitReg(reg2);
}
void exec_mov_ctrl(){
    if(PROTECTED_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    write32BitReg(reg2,cr[reg1]);
}

void exec_mov_2debug(){
    if(PROTECTED_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    if((cr[4]&CR4_DE_MASK)&&(reg1==4||reg1==5)){
        printf("#UD exception\n");
        exit(0);
    }
    dr[reg1]=read32BitReg(reg2);
}
void exec_mov_debug(){
    if(PROTECTED_MODE&&cpl!=0){
        printf("#GP(0) exception\n");
        exit(0);
    }
    if((cr[4]&CR4_DE_MASK)&&(reg1==4||reg1==5)){
        printf("#UD exception\n");
        exit(0);
    }
    write32BitReg(reg2,dr[reg1]);
}

void exec_movs_8b(){
    while(1){
        u_int8_t *dst=get_string_dst();
        u_int8_t *src=get_string_src();
        *dst=*src;
        if(get_flag(DF)==0){
            ESI++;
            EDI++;
        }
        else{
            ESI--;
            EDI--;
        }
        if(prefix_rep==0) break;
        else if(rep_condition(0)==0) break;
    }

}


void exec_movs_16_32b(){
    while(1){
            if(operand_size()==16){
                u_int16_t *dst=(u_int16_t*)get_string_dst();
                u_int16_t *src=(u_int16_t*)get_string_src();
               *dst=*src;
                 if(get_flag(DF)==0){
                    ESI+=2;
                    EDI+=2;
                }
                else{
                    ESI-=2;
                    EDI-=2;
                }
            }else{
                u_int32_t *dst=(u_int32_t*)get_string_dst();
                u_int32_t *src=(u_int32_t*)get_string_src();
                *dst=*src;
                 if(get_flag(DF)==0){
                    ESI+=4;
                    EDI+=4;
                }
                else{
                    ESI-=4;
                    EDI-=4;
                }
            }
            if(prefix_rep==0) break;
            else if(rep_condition(0)==0) break;
    }
}

void exec_movsx_8b(){
    int8_t src;
    if(rm_is_reg)  src=(int8_t)read8BitReg(reg2);
    else src=*(int8_t*)get_mem_data();
    if(operand_size()==16) write16BitReg(reg1,(int16_t)src);
    else write32BitReg(reg1,(int32_t)src);
}
void exec_movsx_16b(){
    int32_t src;
    if(rm_is_reg)  src=(int16_t)read16BitReg(reg2);
    else src=*(int16_t*)get_mem_data();
    write32BitReg(reg1,src);
}

void exec_movzx_8b(){
    u_int8_t src;
    if(rm_is_reg)  src=read8BitReg(reg2);
    else src=*get_mem_data();
    if(operand_size()==16) write16BitReg(reg1,src);
    else write32BitReg(reg1,src);
}
void exec_movzx_16b(){
    u_int32_t src;
    if(rm_is_reg)  src=read16BitReg(reg2);
    else src=*get_mem_data();
    write32BitReg(reg1,src);
}
/* zpy part */
//RET— Return from Procedure
void exec_ret_near()
{
    if(operand_size()==16)
    {
        IP=pop_16b();
        EIP&=0x0000FFFF;
    }
    else{
        EIP=pop_32b();
    }
}
void exec_ret_near_para(u_int16_t imm){
    exec_ret_near();
    ESP+=imm;
}
/*void exec_ret_far()
{
    if((cr0&CRO_PE_MASK==0)||((cr0&CRO_PE_MASK==1)&&get_flag(VM)==1))
    (
        if(operand_size()==16){
            IP=pop_16b();
            EIP&=0x0000FFFF;
            CS=pop_16b();
        }
        else
        {
            EIP=pop_32b();
            CS=pop_32b();
        }
    )
    else if((cr0&CRO_PE_MASK==1)&&get_flag(VM)==0)
    {
        if(operand_size()==32)
        {
            //Third word on stack must be within stack limits else
             printf("#SS(0)");
             exit(0);
        }
        else
        {
             //Second word on stack must be within stack limits else
             printf("#SS(0)");
             exit(0);
        }
        //if()
    }
}
void exec_ret_far_para(u_int16_t imm)
{
    exec_ret_far();
    ESP+=imm;
}*/
//POPA/POPAD— Pop all General Registers
void exec_popa()
{
    if(operand_size()==16)
    {
        DI=pop_16b();
        SI=pop_16b();
        BP=pop_16b();
        ESP=ESP+2;
        BX=pop_16b();
        DX=pop_16b();
        CX=pop_16b();
        AX=pop_16b();
    }
    else
    {
        EDI=pop_32b();
        ESI=pop_32b();
        EBP=pop_32b();
        ESP=ESP+4;
        EBX=pop_32b();
        EDX=pop_32b();
        ECX=pop_32b();
        EAX=pop_32b();
    }
}
//PUSH— Push Operand onto the Stack
void exec_popf()
{
    if(get_flag(VM)==0)
    {
        if(operand_size()==32)
            eflags=(pop_32b())&0x277FD7;
        else
            eflags=(eflags&0xFFFF0000)|pop_16b();
    }
    else
    {
        if(get_iopl()==3)
        {
            if(operand_size()==32)
                eflags = (eflags&0x1B3000)|(pop_32b()&(~0x1B3000));
            else
                eflags=(eflags&0xFFFF0000)|pop_16b();
        }
        else
        {
            printf("#GP(0)");
            exit(0);
        }
    }
}
//PUSHA/PUSHAD— Push all General Registers
void exec_pusha() //16
{
    if(operand_size()==16)
    {
        u_int16_t tmp=SP;
        push_16b(AX);
        push_16b(CX);
        push_16b(DX);
        push_16b(BX);
        push_16b(tmp);
        push_16b(BP);
        push_16b(SI);
        push_16b(DI);
    }
    else {
        u_int16_t tmp=ESP;
        push_32b(EAX);
        push_32b(ECX);
        push_32b(EDX);
        push_32b(EBX);
        push_32b(tmp);
        push_32b(EBP);
        push_32b(ESI);
        push_32b(EDI);
    }
}
//PUSHF/PUSHFD— Push Flags Register onto the Stack
void exec_pushf()
{
    if(get_flag(VM)==0||get_iopl()==3)
    {
        if(operand_size()==32)
            push_32b(eflags&0x0FCFFF);
        else
            push_16b(eflags);
    }
    else
    {
        printf("#GP(0)");
        exit(0);
    }
}

//RCL/RCR/ROL/ROR-— Rotate
u_int8_t exec_rol_8b(u_int8_t rm,u_int8_t count){
    u_int8_t tmp=count;
    while(tmp!=0)
    {
        rm=rm*2+(rm&(0x80)>>7);
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x80)>>7)!=get_flag(CF))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
//    else OF: undefined
    return rm;
}
u_int16_t exec_rol_16b(u_int16_t rm,u_int8_t count){
    u_int8_t tmp=count;
    while(tmp!=0)
    {
        rm=rm*2+(rm&(0x8000)>>15);
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x8000)>>15)!=get_flag(CF))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    return rm;
//    else OF: undefined
}
u_int32_t exec_rol_32b(u_int32_t rm,u_int8_t count){
    u_int8_t tmp=count;
    while(tmp!=0)
    {
        rm=rm*2+(rm&(0x80000000)>>31);
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x80000000)>>31)!=get_flag(CF))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    return rm;
//    else OF: undefined
}
u_int8_t exec_ror_8b(u_int8_t rm,u_int8_t count){
    u_int8_t tmp=count;
    while(tmp!=0)
    {
        rm=rm/2+((rm&1)>>7);
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x80)>>7)!=((rm&0x40)>>6))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    return rm;
//    else OF: undefined
}
u_int16_t exec_ror_16b(u_int16_t rm,u_int8_t count){
    u_int8_t tmp=count;
    while(tmp!=0)
    {
        rm=rm/2+((rm&1)>>15);
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x8000)>>15)!=((rm&0x4000)>>14))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    return rm;
//    else OF: undefined
}
u_int32_t exec_ror_32b(u_int32_t rm,u_int8_t count){
    u_int8_t tmp=count;
    while(tmp!=0)
    {
        rm=rm/2+((rm&1)>>31);
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x80000000)>>31)!=((rm&0x40000000)>>30))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    return rm;
//    else OF: undefined
}
//Store AH into Flags
void exec_sahf()
{
  if(AH&CF_MASK)
  {
    set_flag(CF);
  }
  else
  {
    clear_flag(CF);
  }

  if(AH&PF_MASK)
  {
    set_flag(PF);
  }
  else
  {
    clear_flag(PF);
  }

  if(AH&AF_MASK)
  {
    set_flag(AF);
  }
  else
  {
    clear_flag(AF);
  }

  if(AH&ZF_MASK)
  {
    set_flag(CF);
  }
  else
  {
    clear_flag(ZF);
  }

  if(AH&SF_MASK)
  {
    set_flag(SF);
  }
  else
  {
    clear_flag(SF);
  }
}
//SAL/SAR/SHL/SHR— Shift Instructions
u_int8_t exec_sal_8b(u_int8_t rm,u_int8_t count) //SAL & SHL
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&0x80)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm*2;
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x80)>>7)!=get_flag(CF))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    SET_EFLAGS(rm,0,0,0,8,PZS_MASK);
    return rm;
}
u_int16_t exec_sal_16b(u_int16_t rm,u_int8_t count) //SAL & SHL
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&0x8000)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm*2;
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x8000)>>15)!=get_flag(CF))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    SET_EFLAGS(rm,0,0,0,16,PZS_MASK);
    return rm;
}
u_int32_t exec_sal_32b(u_int32_t rm,u_int8_t count) //SAL & SHL
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&0x80000000)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm*2;
        tmp--;
    }
    if(count==1)
    {
        if(((rm&0x80000000)>>31)!=get_flag(CF))
        {
            set_flag(OF);
        }
        else{
            clear_flag(OF);
        }
    }
    SET_EFLAGS(rm,0,0,0,32,PZS_MASK);
    return rm;
}

u_int8_t exec_shr_8b(u_int8_t rm,u_int8_t count)
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&1)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm/2;
        tmp--;
    }
    if(count==1)
    {
        if((rm&0x80)==0)
        {
            clear_flag(OF);
        }
        else{
            set_flag(OF);
        }
    }
    SET_EFLAGS(rm,0,0,0,8,PZS_MASK);
    return rm;
}
u_int16_t exec_shr_16b(u_int16_t rm,u_int8_t count)
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&1)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm/2;
        tmp--;
    }
    if(count==1)
    {
        if((rm&0x8000)==0)
        {
            clear_flag(OF);
        }
        else{
            set_flag(OF);
        }
    }
    SET_EFLAGS(rm,0,0,0,16,PZS_MASK);
    return rm;
}
u_int32_t exec_shr_32b(u_int32_t rm,u_int8_t count)
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&1)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm/2;
        tmp--;
    }
    if(count==1)
    {
        if((rm&0x80000000)==0)
        {
            clear_flag(OF);
        }
        else{
            set_flag(OF);
        }
    }
    SET_EFLAGS(rm,0,0,0,32,PZS_MASK);
    return rm;
}

u_int8_t exec_sar_8b(int8_t rm,u_int8_t count)
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&1)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm/2;
        tmp--;
    }
    if(count==1)
    {
        clear_flag(OF);
    }
    SET_EFLAGS(rm,0,0,0,8,PZS_MASK);
    return (u_int8_t)rm;
}
u_int16_t exec_sar_16b(int16_t rm,u_int8_t count) //SAR
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&1)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm/2;
        tmp--;
    }
    if(count==1)
    {
        clear_flag(OF);
    }
    SET_EFLAGS(rm,0,0,0,16,PZS_MASK);
    return (u_int16_t)rm;
}
u_int32_t exec_sar_32b(int32_t rm,u_int8_t count)  //SAR
{
    u_int8_t tmp = count;
    while(tmp!=0)
    {
        if((rm&1)==0)
        {
            clear_flag(CF);
        }
        else{
            set_flag(CF);
        }
        rm=rm/2;
        tmp--;
    }
    if(count==1)
    {
        clear_flag(OF);
    }
    SET_EFLAGS(rm,0,0,0,32,PZS_MASK);
    return (u_int32_t)rm;
}
//SBB Integer Subtraction with Borrow
u_int8_t exec_sbb_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst-(src+get_flag(CF));
    SET_EFLAGS(tmp,dst,src,2,8,CPAZSO_MASK);
    return tmp;
}

u_int16_t exec_sbb_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst-(src+get_flag(CF));
    SET_EFLAGS(tmp,dst,src,2,16,CPAZSO_MASK);
    return tmp;
}

u_int32_t exec_sbb_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst-(src+get_flag(CF));
    SET_EFLAGS(tmp,dst,src,2,32,CPAZSO_MASK);
    return tmp;
}

//SCAS/SCASB/SCASW/SCASD— Compare String Data
void exec_scas_8b()
{
    u_int8_t* src=get_string_src();
    exec_cmp_8b(*src,AL);
    if(address_size()==16)
    {
        if(get_flag(DF)==0)
        {
            DI++;
        }
        else
        {
            DI--;
        }
    }
    else
    {
       if(get_flag(DF)==0)
        {
            EDI++;
        }
        else
        {
            EDI--;
        }
    }
}
void exec_scas_16b()
{
    u_int16_t *src=(u_int16_t*)get_string_src();
    exec_cmp_16b(*src,AX);
    if(address_size()==16)
    {
       // linear_addr=translate_linear_addr(DI,SEG_REG_ES);
        if(get_flag(DF)==0)
        {
            DI+=2;
        }
        else
        {
            DI-=2;
        }
    }
    else
    {
        //linear_addr=translate_linear_addr(EDI,SEG_REG_ES);
        if(get_flag(DF)==0)
        {
            EDI+=2;
        }
        else
        {
            EDI-=2;
        }
    }
}
void exec_scas_32b()
{
    u_int32_t *src=(u_int32_t*)get_string_src();
    exec_cmp_32b(*src,EAX);
    if(address_size()==16)
    {
        if(get_flag(DF)==0)
        {
            DI+=4;
        }
        else
        {
            DI-=4;
        }
    }
    else
    {
       if(get_flag(DF)==0)
        {
            EDI+=4;
        }
        else
        {
            EDI-=4;
        }
    }
}
//SHLD— Double Precision Shift Left
u_int16_t exec_shld_16(u_int8_t count,u_int16_t inBIshits,u_int16_t rm )
{
    u_int8_t shiftamt = count%32;
    if((rm>>(16-shiftamt))&1==1)
        set_flag(CF);
    else
        clear_flag(CF);
    while(shiftamt>0)
    {
        rm=(rm<<1)&0xFFFE|(inBIshits&1);
        inBIshits=inBIshits>>1;
        shiftamt--;
    }
    //Set SF, ZF, PF (r/m);
    SET_EFLAGS(rm,0,0,0,16,PZS_MASK);
    return rm;
}

u_int32_t exec_shld_32(u_int8_t count,u_int32_t inBIshits,u_int32_t rm )
{
    u_int8_t shiftamt = count%32;
    if((rm>>(32-shiftamt))&1==1)
        set_flag(CF);
    else
        clear_flag(CF);
    while(shiftamt>0)
    {
        rm=(rm<<1)&0xFFFFFFFE|(inBIshits&1);
        inBIshits=inBIshits>>1;
        shiftamt--;
    }
    SET_EFLAGS(rm,0,0,0,32,PZS_MASK);
    return rm;
}
void exec_shld(u_int8_t count)
{
    u_int8_t shiftamt = count%32;
    if(shiftamt==0)
        return;
    else
    {
        if(shiftamt>=operand_size()) //bad parameters
            /*r/m ← UNDEFINED; CF, OF, SF, ZF, AF, PF ← UNDEFINED;*/
            return;
        else
        {
            if(operand_size()==16)
            {
                if(rm_is_reg)
                {
                    u_int16_t *data=(u_int16_t*)get_mem_data();
                    *data=exec_shld_16(shiftamt,reg1,*data);
                }
                else
                {
                    write16BitReg(reg2,exec_shld_16(shiftamt,reg1,read16BitReg(reg2)));
                }
            }
            else
            {
                if(rm_is_reg)
                {
                    u_int32_t *data=(u_int32_t*)get_mem_data();
                    *data=exec_shld_32(shiftamt,reg1,*data);
                }
                else
                {
                    write32BitReg(reg2,exec_shld_32(shiftamt,reg1,read32BitReg(reg2)));
                }
            }
        }
    }
}
//SHRD— Double Precision Shift Right
u_int16_t exec_shrd_16(u_int8_t count,u_int16_t inBIshits,u_int16_t rm )
{
    u_int8_t shiftamt = count%32;
    if((rm>>(shiftamt-1))&1==1)
        set_flag(CF);
    else
        clear_flag(CF);
    while(shiftamt>0)
    {
        rm=(rm>>1)|(inBIshits&0x8000);
        inBIshits=inBIshits<<1;
        shiftamt--;
    }
    //Set SF, ZF, PF (r/m);
    SET_EFLAGS(rm,0,0,0,16,PZS_MASK);
    return rm;
}

u_int32_t exec_shrd_32(u_int8_t count,u_int32_t inBIshits,u_int32_t rm )
{
    u_int8_t shiftamt = count%32;
    if((rm>>(shiftamt-1))&1==1)
        set_flag(CF);
    else
        clear_flag(CF);
    while(shiftamt>0)
    {
        rm=(rm>>1)|(inBIshits&0x80000000);
        inBIshits=inBIshits<<1;
        shiftamt--;
    }
    SET_EFLAGS(rm,0,0,0,32,PZS_MASK);
    return rm;
}
void exec_shrd(u_int8_t count)
{
    u_int8_t shiftamt = count%32;
    if(shiftamt==0)
        return;
    else
    {
        if(shiftamt>=operand_size()) //bad parameters
            /*r/m ← UNDEFINED; CF, OF, SF, ZF, AF, PF ← UNDEFINED;*/
            return;
        else
        {
            if(operand_size()==16)
            {
                if(rm_is_reg)
                {
                    u_int16_t *data=(u_int16_t*)get_mem_data();
                    *data=exec_shrd_16(shiftamt,reg1,*data);
                }
                else
                {
                    write16BitReg(reg2,exec_shrd_16(shiftamt,reg1,read16BitReg(reg2)));
                }
            }
            else
            {
                if(rm_is_reg)
                {
                    u_int32_t *data=(u_int32_t*)get_mem_data();
                    *data=exec_shrd_32(shiftamt,reg1,*data);
                }
                else
                {
                    write32BitReg(reg2,exec_shrd_32(shiftamt,reg1,read32BitReg(reg2)));
                }
            }
        }
    }
}
//STOS/STOSB/STOSW/STOSD— Store String Data
void exec_stos_8b()
{
    u_int8_t *data=get_string_src();
    *data = AL;
    if(address_size()==16)
    {
       // linear_addr=translate_linear_addr(DI,SEG_REG_ES);
        if(get_flag(DF)==0)
        {
            DI=DI+1;
        }
        else
        {
            DI=DI-1;
        }
    }
    else
    {
        //linear_addr=translate_linear_addr(EDI,SEG_REG_ES);
        if(get_flag(DF)==0)
        {
            EDI=EDI+1;
        }
        else
        {
            EDI=EDI-1;
        }
    }
}
void exec_stos_16b()
{
    u_int16_t *data=(u_int16_t*)get_string_src();
    *data = AX;
    if(address_size()==16)
    {
        /*linear_addr=translate_linear_addr(DI,SEG_REG_ES);
        u_int16_t *data=(u_int16_t*)get_mem_data();
        *data = AX;*/
        if(get_flag(DF)==0)
        {
            DI=DI+2;
        }
        else
        {
            DI=DI-2;
        }
    }
    else
    {
        /*linear_addr=translate_linear_addr(EDI,SEG_REG_ES);
        u_int16_t *data=(u_int16_t*)get_mem_data();
        *data = AX;*/
        if(get_flag(DF)==0)
        {
            EDI=EDI+2;
        }
        else
        {
            EDI=EDI-2;
        }
    }
}
void exec_stos_32b()
{
    u_int32_t *data=(u_int32_t*)get_string_src();
    *data = EAX;
    if(address_size()==16)
    {
        /*linear_addr=translate_linear_addr(DI,SEG_REG_ES);
        u_int32_t *data=(u_int32_t*)get_mem_data();
        *data = EAX;*/
        if(get_flag(DF)==0)
        {
            DI=DI+4;
        }
        else
        {
            DI=DI-4;
        }
    }
    else
    {
        /*linear_addr=translate_linear_addr(EDI,SEG_REG_ES);
        u_int32_t *data=(u_int32_t*)get_mem_data();
        *data = EAX;*/
        if(get_flag(DF)==0)
        {
            EDI=EDI+4;
        }
        else
        {
            EDI=EDI-4;
        }
    }
}

//SUB Integer Subtraction
u_int8_t exec_sub_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst-src;
    SET_EFLAGS(tmp,dst,src,2,8,CPAZSO_MASK);
    return tmp;
}

u_int16_t exec_sub_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst-src;
    SET_EFLAGS(tmp,dst,src,2,16,CPAZSO_MASK);
    return tmp;
}

u_int32_t exec_sub_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst-src;
    SET_EFLAGS(tmp,dst,src,2,32,CPAZSO_MASK);
    return tmp;
}

//SMSW— Store Machine Status Word
void exec_smsw()
{
    u_int16_t machine_word=cr[0];
    if(rm_is_reg){
        write16BitReg(reg2,machine_word);
    }
    else
    {
        u_int16_t *data=(u_int16_t*)get_mem_data();
        *data = machine_word;
    }
}
//The STC instruction sets the CF flag
void exec_stc()
{
    set_flag(CF);
}
/*
The STD instruction sets the direction flag, causing all subsequent string operations to
decrement the index registers, (E)SI and/or (E)DI, on which they operate.
*/
void exec_std()
{
    set_flag(DF);
}

//The STI instruction sets the IF
void exec_sti()
{
     if(cr[0]&CRO_PE_MASK==0)
     {
        set_flag(IF);
     }
     else
     {
        if(get_flag(VM)==0)
        {
            if((get_iopl()==3)||(get_iopl()>=CPL))
            {
                set_flag(IF);
            }
            else
            {
                printf("this is gp(0)\n");
            }
        }
        else
        {
            printf("this is gp(0)\n");
        }
     }
}
//Exchange and Add
//the following function receive the reg and the value,return sum and set reg to the value
u_int8_t exec_xadd_8b(u_int8_t dst)
{
    u_int8_t src=read8BitReg(reg1),tmp=exec_add_8b(dst,src);
    write8BitReg(reg1,dst);
    return tmp;
}

u_int16_t exec_xadd_16b(u_int16_t dst)
{
    u_int16_t src=read16BitReg(reg1),tmp=exec_add_16b(dst,src);
    write16BitReg(reg1,dst);
    return tmp;
}

u_int32_t exec_xadd_32b(u_int32_t dst)
{
    u_int32_t src=read32BitReg(reg1),tmp=exec_add_32b(dst,src);
    write32BitReg(reg1,dst);
    return tmp;
}

//Exchange Register/Memory with Register
void exec_xchg_reg(u_int8_t reg){
    if(address_size()==16)
     {
         u_int16_t tmp=read16BitReg(reg);
         write16BitReg(reg,AX);
         AX=tmp;
     }
     else
     {
        u_int32_t tmp=read32BitReg(reg);
        write32BitReg(reg,EAX);
        EAX=tmp;
     }
}
void exec_xchg_mem_8b(){
    u_int8_t tmp=read8BitReg(reg1);
    if(rm_is_reg)
    {
        write8BitReg(reg1,read8BitReg(reg2));
        write8BitReg(reg2,tmp);
    }
    else
    {
        u_int8_t* data =(u_int8_t*)get_mem_data();
        write8BitReg(reg1,*data);
        *data=tmp;
    }
}
void exec_xchg_mem_16b(){
    u_int16_t tmp=read16BitReg(reg1);
    if(rm_is_reg)
    {
        write16BitReg(reg1,read16BitReg(reg2));
        write16BitReg(reg2,tmp);
    }
    else
    {
        u_int16_t* data =(u_int16_t*)get_mem_data();
        write16BitReg(reg1,*data);
        *data=tmp;
    }
}

void exec_xchg_mem_32b(){
    u_int32_t tmp=read32BitReg(reg1);
    if(rm_is_reg)
    {
        write32BitReg(reg1,read32BitReg(reg2));
        write32BitReg(reg2,tmp);
    }
    else
    {
        u_int32_t* data =(u_int32_t*)get_mem_data();
        write8BitReg(reg1,*data);
        *data=tmp;
    }
}

// The XLAT instruction changes the AL register from the table index to the table entry.
//??????? AL BX EBX?
void exec_xlat()
{
     if(address_size()==16)
     {
        AL = (u_int8_t)(BX+AL);
     }
     else
     {
        AL = (u_int8_t)(EBX+AL);
     }
}


u_int8_t exec_xor_8b(u_int8_t dst,u_int8_t src)
{
    u_int8_t tmp=dst^src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,8,PZS_MASK);
    return tmp;
}

u_int16_t exec_xor_16b(u_int16_t dst,u_int16_t src)
{
    u_int16_t tmp=dst^src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,16,PZS_MASK);
    return tmp;
}

u_int32_t exec_xor_32b(u_int32_t dst,u_int32_t src)
{
    u_int32_t tmp=dst^src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,32,PZS_MASK);
    return tmp;
}

u_int8_t exec_shift_8b(u_int8_t index,u_int8_t src,u_int8_t count){
	switch(index){
		case 0: return exec_rol_8b(src,count);
		case 1: return exec_ror_8b(src,count);
		case 4: return exec_sal_8b(src,count);
		case 5: return exec_shr_8b(src,count);
		case 7: return exec_sar_8b((int8_t)src,count);
	}
}

u_int16_t exec_shift_16b(u_int8_t index,u_int16_t src,u_int8_t count){
	switch(index){
		case 0: return exec_rol_16b(src,count);
		case 1: return exec_ror_16b(src,count);
		case 4: return exec_sal_16b(src,count);
		case 5: return exec_shr_16b(src,count);
		case 7: return exec_sar_16b((int16_t)src,count);
	}
}

u_int32_t exec_shift_32b(u_int8_t index,u_int32_t src,u_int8_t count){
	switch(index){
		case 0: return exec_rol_32b(src,count);
		case 1: return exec_ror_32b(src,count);
		case 4: return exec_sal_32b(src,count);
		case 5: return exec_shr_32b(src,count);
		case 7: return exec_sar_32b((int32_t)src,count);
	}
}
