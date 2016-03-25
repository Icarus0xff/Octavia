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
void exec_aad(Bit8u imm)
{
    DEBUG("start run aad\n");
    AL=(AH*imm+AL)&0xFF;
    AH=0;
    SET_EFLAGS(AX,0,0,0,16,PZS_MASK);
}
void exec_aam(Bit8u imm)
{
    DEBUG("start run aam\n");
    AH=AL/imm;
    AL=AL%imm;
    SET_EFLAGS(AX,0,0,0,16,PZS_MASK);
}
void exec_aas()
{
    DEBUG("start run aas\n");
    Bit8u borrow=AL<6?1:0;
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
Bit8u exec_arith_8b(Bit8u index,Bit8u dst,Bit8u src){
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
Bit16u exec_arith_16b(Bit8u index,Bit16u dst,Bit16u src){
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
Bit32u exec_arith_32b(Bit8u index,Bit32u dst,Bit32u src){
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
Bit8u exec_adc_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst+src+get_flag(CF);
     SET_EFLAGS(tmp,dst,src+get_flag(CF),1,8,CPAZSO_MASK);
    return tmp;
}

Bit16u exec_adc_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst+src+get_flag(CF);
     SET_EFLAGS(tmp,dst,src+get_flag(CF),1,16,CPAZSO_MASK);
    return tmp;
}

Bit32u exec_adc_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst+src+get_flag(CF);
    SET_EFLAGS(tmp,dst,src+get_flag(CF),1,32,CPAZSO_MASK);
    return tmp;
}

Bit8u exec_add_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst+src;
    SET_EFLAGS(tmp,dst,src,1,8,CPAZSO_MASK);
    return tmp;
}

Bit16u exec_add_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst+src;
   SET_EFLAGS(tmp,dst,src,1,16,CPAZSO_MASK);
    return tmp;
}

Bit32u exec_add_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst+src;
   SET_EFLAGS(tmp,dst,src,1,32,CPAZSO_MASK);
    return tmp;
}

Bit8u exec_and_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst&src;
    clear_flag(CF);
    clear_flag(OF);
     SET_EFLAGS(tmp,0,0,0,8,PZS_MASK);
    return tmp;
}

Bit16u exec_and_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst&src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,16,PZS_MASK);
    return tmp;
}

Bit32u exec_and_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst&src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,32,PZS_MASK);
    return tmp;
}

Bit8u exec_or_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst|src;
    clear_flag(CF);
    clear_flag(OF);
     SET_EFLAGS(tmp,0,0,0,8,PZS_MASK);
    return tmp;
}

Bit16u exec_or_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst|src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,16,PZS_MASK);
    return tmp;
}

Bit32u exec_or_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst|src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,32,PZS_MASK);
    return tmp;
}

Bit8u exec_cmp_8b(Bit8u dst,Bit8u src){
    Bit8u tmp=dst-src;
     SET_EFLAGS(tmp,dst,src,2,8,CPAZSO_MASK);
     return dst;
}
Bit16u exec_cmp_16b(Bit16u dst,Bit16u src){
    Bit16u tmp=dst-src;
     SET_EFLAGS(tmp,dst,src,2,16,CPAZSO_MASK);
     return dst;
}
Bit32u exec_cmp_32b(Bit32u dst,Bit32u src){
    Bit32u tmp=dst-src;
     SET_EFLAGS(tmp,dst,src,2,32,CPAZSO_MASK);
     return dst;
}

Bit16u exec_arpl(Bit16u dst,Bit16u src){
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

void exec_bound_16b(Bit16s*bound,Bit16s index){
	if(index<bound[0]||index>bound[1]+2){
		printf("#BR exception\n");
		exit(0);
	}

}
void exec_bound_32b(Bit32s*bound,Bit32s index){
	if(index<bound[0]||index>bound[1]+4){
		printf("#BR exception\n");
		exit(0);
	}

}

void exec_bsf_16b(Bit8u dst,Bit16u src){
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
void exec_bsf_32b(Bit8u dst,Bit32u src){
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

void exec_bsr_16b(Bit8u dst,Bit16u src){
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
void exec_bsr_32b(Bit8u dst,Bit32u src){
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

void exec_bswap(Bit8u reg){
	Bit32u tmp=read32BitReg(reg);
	tmp=(tmp<<24)+((tmp&0xFF00)<<8)+((tmp&0xFF0000)>>8)+(tmp>>24);
	write32BitReg(reg,tmp);
}

void exec_btx_16b_reg(Bit8u op,Bit8u dst,Bit16u index){
	index=index%16;
	Bit16u tmp=read16BitReg(dst);
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
void exec_btx_32b_reg(Bit8u op,Bit8u dst,Bit32u index){
	index=index%32;
	Bit32u tmp=read32BitReg(dst);
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
void exec_btx_mem(Bit8u op,Bit8u *dst,Bit32s index){
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
		Bit16u nextIP=IP+instLen+prefixLen+immLen+1;
		Bit16u rel=*(Bit16u*)(curInst+1);
		push_16b(nextIP&0xFFFF);
		EIP=(nextIP+rel)&0xFFFF;
	}
	else{
		Bit32u nextEIP=EIP+instLen+prefixLen+immLen+1;
		Bit32u rel=*(Bit32u*)(curInst+1);
		push_32b(nextEIP);
		EIP=nextEIP+rel;
	}
}

void exec_call_near_absolute(){
	Bit32u nextEIP=EIP+instLen+prefixLen+immLen+1;
	if(operand_size()==16){
		Bit16u addr=rm_is_reg?read16BitReg(reg2):*(Bit16u*)get_mem_data();
		push_16b(nextEIP&0xFFFF);
		EIP=addr;
	}
	else{
		Bit32u addr=rm_is_reg?read32BitReg(reg2):*(Bit32u*)get_mem_data();
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
        Bit8u *dst=get_string_dst();
        Bit8u *src=get_string_src();
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
                Bit16u *dst=(Bit16u*)get_string_dst();
                Bit16u *src=(Bit16u*)get_string_src();
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
                Bit32u *dst=(Bit32u*)get_string_dst();
                Bit32u *src=(Bit32u*)get_string_src();
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

void exec_cmpxchg_8b(Bit8u src){
    if(rm_is_reg){
        exec_cmp_8b(AL,read8BitReg(reg2));
        if(get_flag(ZF))
                write8BitReg(reg2,src);
        else  AL=read8BitReg(reg2);
    }
    else{
        Bit8u *data=get_mem_data();
        exec_cmp_8b(AL,*data);
        if(get_flag(ZF))
            *data=src;
        else AL=*data;

    }

}
void exec_cmpxchg_16b(Bit16u src){
    if(rm_is_reg){
        exec_cmp_16b(AX,read16BitReg(reg2));
        if(get_flag(ZF))
                write16BitReg(reg2,src);
        else  AX=read16BitReg(reg2);
    }
    else{
        Bit16u *data=(Bit16u*)get_mem_data();
        exec_cmp_16b(AX,*data);
        if(get_flag(ZF))
            *data=src;
        else AX=*data;

    }

}
void exec_cmpxchg_32b(Bit32u src)  {
    if(rm_is_reg){
        exec_cmp_32b(EAX,read32BitReg(reg2));
        if(get_flag(ZF))
                write32BitReg(reg2,src);
        else  EAX=read32BitReg(reg2);
    }
    else{
        Bit32u *data=(Bit32u*)get_mem_data();
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
        Bit8u dst=read8BitReg(reg2);
        SET_EFLAGS(dst-1,dst,1,2,8, PAZSO_MASK);
        write8BitReg(reg2,dst-1);
    }
    else{
        Bit8u *dst=get_mem_data();
        SET_EFLAGS(*dst-1,*dst,1,2,8, PAZSO_MASK);
        *dst=*dst-1;
    }
}
void exec_dec_16_32b(){
    if(operand_size()==16){
        if(rm_is_reg){
            Bit16u dst=read16BitReg(reg2);
            SET_EFLAGS(dst-1,dst,1,2,16, PAZSO_MASK);
            write16BitReg(reg2,dst-1);
        }
        else{
            Bit16u *dst=(Bit16u*)get_mem_data();
            SET_EFLAGS(*dst-1,*dst,1,2,16, PAZSO_MASK);
            *dst=*dst-1;
        }
    }else{
        if(rm_is_reg){
            Bit32u dst=read32BitReg(reg2);
            SET_EFLAGS(dst-1,dst,1,2,32, PAZSO_MASK);
            write32BitReg(reg2,dst-1);
        }
        else{
            Bit32u *dst=(Bit32u*)get_mem_data();
            SET_EFLAGS(*dst-1,*dst,1,2,32, PAZSO_MASK);
            *dst=*dst-1;
        }
    }
}
void exec_dec_16_32b_r(Bit8u reg){
     if(operand_size()==16){
        Bit16u dst=read16BitReg(reg);
        SET_EFLAGS(dst-1,dst,1,2,16, PAZSO_MASK);
        write16BitReg(reg2,dst-1);
    }else{
        Bit32u dst=read32BitReg(reg);
        SET_EFLAGS(dst-1,dst,1,2,32, PAZSO_MASK);
        write32BitReg(reg2,dst-1);
    }

}

void exec_div_8b(){
    Bit8u src;
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
    Bit8u tmp=AX/src;
    AH=AX%src;
    AL=tmp;
}
void exec_div_16_32b(){
    if(operand_size()==16){
         Bit16u src;
        if(rm_is_reg){
            src=read16BitReg(reg2);
        }
        else{
            src=*(Bit16u*)get_mem_data();
        }
        if(src==0){
            printf("#DE exception\n");
            exit(0);
        }
        Bit32u tmp=DX;
        tmp=tmp<<16+AX;
        AX=tmp%src;
        DX=tmp/src;
    }else{
         Bit32u src;
        if(rm_is_reg){
            src=read32BitReg(reg2);
        }
        else{
            src=*(Bit32u*)get_mem_data();
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
    Bit8u src;
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
         Bit16u src;
        if(rm_is_reg){
            src=read16BitReg(reg2);
        }
        else{
            src=*(Bit16u*)get_mem_data();
        }
        Bit32u tmp=AX;
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
         Bit32u src;
        if(rm_is_reg){
            src=read32BitReg(reg2);
        }
        else{
            src=*(Bit32u*)get_mem_data();
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
        Bit8s src=read8BitReg(reg2);
        src=-src;
        write8BitReg(reg2,src);
        if(src==0) clear_flag(CF);
        else set_flag(CF);
    }
    else{
        Bit8s *src=(Bit8s*)get_mem_data();
        *src=-(*src);
        if(*src==0) clear_flag(CF);
        else set_flag(CF);
    }
}
void exec_neg_16_32b(){
    if(operand_size()==16){
        if(rm_is_reg){
            Bit16s src=read16BitReg(reg2);
            src=-src;
            write16BitReg(reg2,src);
            if(src==0) clear_flag(CF);
            else set_flag(CF);
        }
        else{
            Bit16s* src=(Bit16s*)get_mem_data();
             *src=-(*src);
            if(*src==0) clear_flag(CF);
            else set_flag(CF);
        }
    }else{
         if(rm_is_reg){
            Bit32s src=read32BitReg(reg2);
            src=-src;
            write32BitReg(reg2,src);
            if(src==0) clear_flag(CF);
            else set_flag(CF);
        }
        else{
            Bit32s* src=(Bit32s*)get_mem_data();
             *src=-(*src);
            if(*src==0) clear_flag(CF);
            else set_flag(CF);
        }
    }
}

void exec_not_8b(){
    if(rm_is_reg){
        Bit8u src=read8BitReg(reg2);
        src=~src;
        write8BitReg(reg2,src);
    }
    else{
        Bit8u *src=get_mem_data();
        *src=~(*src);
    }
}
void exec_not_16_32b(){
    if(operand_size()==16){
        if(rm_is_reg){
            Bit16u src=read16BitReg(reg2);
            src=~src;
            write16BitReg(reg2,src);
        }
        else{
            Bit16u* src=(Bit16u*)get_mem_data();
             *src=~(*src);
        }
    }else{
         if(rm_is_reg){
            Bit32u src=read32BitReg(reg2);
            src=~src;
            write32BitReg(reg2,src);
        }
        else{
            Bit32u* src=(Bit32u*)get_mem_data();
             *src=~(*src);
        }
    }
}
void exec_enter(Bit16u bytes ,Bit8u nestLevel){
    nestLevel%=32;
    Bit32u tmpEBP;
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
                 push_32b(*(Bit32u*)get_stack_base());
            }else{
                if(stack_address_size()==32){
                    EBP=EBP-2;
                }
                else{
                    BP=BP-2;
                }
                 push_16b(*(Bit16u*)get_stack_base());
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
    Bit8s src;
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
    Bit8s tmp=(Bit16s)AX/src;
    AH=(Bit16s)AX%src;
    AL=tmp;
}
void exec_idiv_16_32b(){
    if(operand_size()==16){
         Bit16s src;
        if(rm_is_reg){
            src=read16BitReg(reg2);
        }
        else{
            src=*(Bit16s*)get_mem_data();
        }
        if(src==0){
            printf("#DE exception\n");
            exit(0);
        }
        Bit32s tmp=DX;
        tmp=tmp<<16+AX;
        AX=tmp%src;
        DX=tmp/src;
    }else{
         Bit32s src;
        if(rm_is_reg){
            src=read32BitReg(reg2);
        }
        else{
            src=*(Bit32s*)get_mem_data();
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
     Bit16s dst=AL,src;
    if(rm_is_reg){
        src=(Bit8s)read8BitReg(reg2);
    }
    else{
        src=(Bit8s)*get_mem_data();
    }
    AX=src*dst;
}

void exec_imul_16_32b(Bit8u operandNum,Bit32s imm){
    switch(operandNum){
        case 1:
            if(operand_size()==16){
                 Bit32s src;
                if(rm_is_reg){
                    src=(Bit16s)read16BitReg(reg2);
                }else{
                    src=*(Bit16s*)get_mem_data();
                }
                Bit32u dst=src*AX;
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
                Bit64 src;
                if(rm_is_reg){
                    src=(Bit32s)read32BitReg(reg2);
                }else{
                    src=*(Bit32s*)get_mem_data();
                }
                Bit64 dst=src*EAX;
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
                Bit32s src;
                if(rm_is_reg){
                        src=(Bit16s)read16BitReg(reg2);
                }else{
                       src=*(Bit16s*)get_mem_data();
                }
                Bit32u dst=src*read16BitReg(reg1);
                write16BitReg(reg1,dst&0xFFFF);
                Bit16u up16b=dst>>16;
                if(up16b!=0&&(up16b+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }else{
                 Bit64 src;
                 if(rm_is_reg){
                        Bit64 src=(Bit32s)read32BitReg(reg2);

                }else{
                    Bit64 src=*(Bit32s*)get_mem_data();
                }
                 Bit64 dst=read32BitReg(reg1)*src;
                 write32BitReg(reg1,dst&0xFFFFFFFF);
                 Bit32u up32b=dst>>32;
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
                Bit32s src;
                if(rm_is_reg){
                        src=(Bit16s)read16BitReg(reg2);
                }else{
                       src=*(Bit16s*)get_mem_data();
                }
                Bit32u dst=src*imm;
                write16BitReg(reg1,dst&0xFFFF);
                Bit16u up16b=dst>>16;
                if(up16b!=0&&(up16b+1)!=0){
                        set_flag(CF);
                        set_flag(OF);
                }else{
                        clear_flag(CF);
                        clear_flag(OF);
                }
            }else{
                 Bit64 src;
                 if(rm_is_reg){
                        Bit64 src=(Bit32s)read32BitReg(reg2);

                }else{
                    Bit64 src=*(Bit32s*)get_mem_data();
                }
                 Bit64 dst=src*imm;
                 write32BitReg(reg1,dst&0xFFFFFFFF);
                 Bit32u up32b=dst>>32;
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

void exec_load_seg(Bit8u seg){
    Bit8u* operand=get_mem_data();
    Selector  selector;
    if(operand_size()==16){
        write16BitReg(reg1,*(Bit16u*)operand);
        selector.selector=*(Bit16u*)(operand+2);
    }else{
        write32BitReg(reg1,*(Bit32u*)operand);
        selector.selector=*(Bit16u*)(operand+4);
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
    Bit8u* operand=get_mem_data();
    if(operand_size()==16){
        gdtr.limit=*(Bit16u*)operand;
        gdtr.base=*(Bit32u*)(operand+2)&0x00FFFFFF;
    }else{
        gdtr.limit=*(Bit16u*)operand;
        gdtr.base=*(Bit32u*)(operand+2);
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
    Bit8u* operand=get_mem_data();
    if(operand_size()==16){
        idtr.limit=*(Bit16u*)operand;
        idtr.base=*(Bit32u*)(operand+2)&0x00FFFFFF;
    }else{
        idtr.limit=*(Bit16u*)operand;
        idtr.base=*(Bit32u*)(operand+2);
    }
}

void exec_lldt(){
    Selector selector;
    if(rm_is_reg){
        selector.selector=read16BitReg(reg2);
    }else{
        selector.selector=*(Bit16u*)get_mem_data();
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
    Bit16u src;
    if(rm_is_reg){
        src=read16BitReg(reg2);
    }else{
        src=*(Bit16u*)get_mem_data();
    }
    if(!REAL_MODE&&cpl!=0){
         printf("#GP(0) exception\n");
        exit(0);
    }
    cr[0]=(cr[0]&0xFFFFFFF0)|(src&0xF);

}
void exec_lods_8b(){
    while(1){
        Bit8u *dst=get_string_dst();
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
        Bit8u *dst=get_string_dst();
        if(operand_size()==16) AX=*(Bit16u*)dst;
        else EAX=*(Bit32u*)dst;
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

Bit8u exec_loop(){
    Bit8u condition=0;
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
    Bit32s offset=*(Bit8s*)(curInst+1);
    Bit32u newIP=offset+EIP;
    if(condition){
        if(operand_size()==16) IP=newIP&0xFFFF;
        else EIP=newIP;
    }
    return condition;
}

Bit8u exec_loope(){
    Bit8u condition=0;
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
    Bit32s offset=*(Bit8s*)(curInst+1);
    Bit32u newIP=offset+EIP;
    if(condition){
        if(operand_size()==16) IP=newIP&0xFFFF;
        else EIP=newIP;
    }
    return condition;
}

Bit8u exec_loopne(){
    Bit8u condition=0;
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
    Bit32s offset=*(Bit8s*)(curInst+1);
    Bit32u newIP=offset+EIP;
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
        selector.selector=*(Bit16u*)get_mem_data();
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
void exec_mov_8b_2rm(Bit8u src){
    if(rm_is_reg){
        write8BitReg(reg2,src);
    }else{
        Bit8u *dst=get_mem_data();
        *dst=src;
    }
}
void exec_mov_8b_2reg(Bit8u src,Bit8u dstReg){
    write8BitReg(dstReg,src);
}
void exec_mov_16b_2rm(Bit16u src){
  if(rm_is_reg){
        write16BitReg(reg2,src);
    }else{
        Bit16u *dst=(Bit16u*)get_mem_data();
        *dst=src;
    }
}
void exec_mov_16b_2reg(Bit16u src,Bit8u dstReg){
    write16BitReg(dstReg,src);
}
void exec_mov_32b_2rm(Bit32u src){
    if(rm_is_reg){
        write32BitReg(reg2,src);
    }else{
        Bit32u *dst=(Bit32u*)get_mem_data();
        *dst=src;
    }
}
void exec_mov_32b_2reg(Bit32u src,Bit8u dstReg){
      write32BitReg(dstReg,src);
}
void exec_mov_seg(Bit8u seg){
    if(rm_is_reg){
        write16BitReg(reg2,sreg[seg].selector.selector);
    }else{
        Bit16u *dst=(Bit16u*)get_mem_data();
        *dst=sreg[seg].selector.selector;
    }
}
void exec_mov_2seg(Bit8u seg){
    Selector selector;
    if(rm_is_reg){
       selector.selector= read16BitReg(reg2);
    }else{
        Bit16u *dst=(Bit16u*)get_mem_data();
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
        Bit8u *dst=get_string_dst();
        Bit8u *src=get_string_src();
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
                Bit16u *dst=(Bit16u*)get_string_dst();
                Bit16u *src=(Bit16u*)get_string_src();
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
                Bit32u *dst=(Bit32u*)get_string_dst();
                Bit32u *src=(Bit32u*)get_string_src();
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
    Bit8s src;
    if(rm_is_reg)  src=(Bit8s)read8BitReg(reg2);
    else src=*(Bit8s*)get_mem_data();
    if(operand_size()==16) write16BitReg(reg1,(Bit16s)src);
    else write32BitReg(reg1,(Bit32s)src);
}
void exec_movsx_16b(){
    Bit32s src;
    if(rm_is_reg)  src=(Bit16s)read16BitReg(reg2);
    else src=*(Bit16s*)get_mem_data();
    write32BitReg(reg1,src);
}

void exec_movzx_8b(){
    Bit8u src;
    if(rm_is_reg)  src=read8BitReg(reg2);
    else src=*get_mem_data();
    if(operand_size()==16) write16BitReg(reg1,src);
    else write32BitReg(reg1,src);
}
void exec_movzx_16b(){
    Bit32u src;
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
void exec_ret_near_para(Bit16u imm){
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
void exec_ret_far_para(Bit16u imm)
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
        Bit16u tmp=SP;
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
        Bit16u tmp=ESP;
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
Bit8u exec_rol_8b(Bit8u rm,Bit8u count){
    Bit8u tmp=count;
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
Bit16u exec_rol_16b(Bit16u rm,Bit8u count){
    Bit8u tmp=count;
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
Bit32u exec_rol_32b(Bit32u rm,Bit8u count){
    Bit8u tmp=count;
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
Bit8u exec_ror_8b(Bit8u rm,Bit8u count){
    Bit8u tmp=count;
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
Bit16u exec_ror_16b(Bit16u rm,Bit8u count){
    Bit8u tmp=count;
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
Bit32u exec_ror_32b(Bit32u rm,Bit8u count){
    Bit8u tmp=count;
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
Bit8u exec_sal_8b(Bit8u rm,Bit8u count) //SAL & SHL
{
    Bit8u tmp = count;
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
Bit16u exec_sal_16b(Bit16u rm,Bit8u count) //SAL & SHL
{
    Bit8u tmp = count;
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
Bit32u exec_sal_32b(Bit32u rm,Bit8u count) //SAL & SHL
{
    Bit8u tmp = count;
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

Bit8u exec_shr_8b(Bit8u rm,Bit8u count)
{
    Bit8u tmp = count;
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
Bit16u exec_shr_16b(Bit16u rm,Bit8u count)
{
    Bit8u tmp = count;
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
Bit32u exec_shr_32b(Bit32u rm,Bit8u count)
{
    Bit8u tmp = count;
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

Bit8u exec_sar_8b(Bit8s rm,Bit8u count)
{
    Bit8u tmp = count;
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
    return (Bit8u)rm;
}
Bit16u exec_sar_16b(Bit16s rm,Bit8u count) //SAR
{
    Bit8u tmp = count;
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
    return (Bit16u)rm;
}
Bit32u exec_sar_32b(Bit32s rm,Bit8u count)  //SAR
{
    Bit8u tmp = count;
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
    return (Bit32u)rm;
}
//SBB Integer Subtraction with Borrow
Bit8u exec_sbb_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst-(src+get_flag(CF));
    SET_EFLAGS(tmp,dst,src,2,8,CPAZSO_MASK);
    return tmp;
}

Bit16u exec_sbb_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst-(src+get_flag(CF));
    SET_EFLAGS(tmp,dst,src,2,16,CPAZSO_MASK);
    return tmp;
}

Bit32u exec_sbb_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst-(src+get_flag(CF));
    SET_EFLAGS(tmp,dst,src,2,32,CPAZSO_MASK);
    return tmp;
}

//SCAS/SCASB/SCASW/SCASD— Compare String Data
void exec_scas_8b()
{
    Bit8u* src=get_string_src();
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
    Bit16u *src=(Bit16u*)get_string_src();
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
    Bit32u *src=(Bit32u*)get_string_src();
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
Bit16u exec_shld_16(Bit8u count,Bit16u inBIshits,Bit16u rm )
{
    Bit8u shiftamt = count%32;
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

Bit32u exec_shld_32(Bit8u count,Bit32u inBIshits,Bit32u rm )
{
    Bit8u shiftamt = count%32;
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
void exec_shld(Bit8u count)
{
    Bit8u shiftamt = count%32;
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
                    Bit16u *data=(Bit16u*)get_mem_data();
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
                    Bit32u *data=(Bit32u*)get_mem_data();
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
Bit16u exec_shrd_16(Bit8u count,Bit16u inBIshits,Bit16u rm )
{
    Bit8u shiftamt = count%32;
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

Bit32u exec_shrd_32(Bit8u count,Bit32u inBIshits,Bit32u rm )
{
    Bit8u shiftamt = count%32;
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
void exec_shrd(Bit8u count)
{
    Bit8u shiftamt = count%32;
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
                    Bit16u *data=(Bit16u*)get_mem_data();
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
                    Bit32u *data=(Bit32u*)get_mem_data();
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
    Bit8u *data=get_string_src();
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
    Bit16u *data=(Bit16u*)get_string_src();
    *data = AX;
    if(address_size()==16)
    {
        /*linear_addr=translate_linear_addr(DI,SEG_REG_ES);
        Bit16u *data=(Bit16u*)get_mem_data();
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
        Bit16u *data=(Bit16u*)get_mem_data();
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
    Bit32u *data=(Bit32u*)get_string_src();
    *data = EAX;
    if(address_size()==16)
    {
        /*linear_addr=translate_linear_addr(DI,SEG_REG_ES);
        Bit32u *data=(Bit32u*)get_mem_data();
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
        Bit32u *data=(Bit32u*)get_mem_data();
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
Bit8u exec_sub_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst-src;
    SET_EFLAGS(tmp,dst,src,2,8,CPAZSO_MASK);
    return tmp;
}

Bit16u exec_sub_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst-src;
    SET_EFLAGS(tmp,dst,src,2,16,CPAZSO_MASK);
    return tmp;
}

Bit32u exec_sub_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst-src;
    SET_EFLAGS(tmp,dst,src,2,32,CPAZSO_MASK);
    return tmp;
}

//SMSW— Store Machine Status Word
void exec_smsw()
{
    Bit16u machine_word=cr[0];
    if(rm_is_reg){
        write16BitReg(reg2,machine_word);
    }
    else
    {
        Bit16u *data=(Bit16u*)get_mem_data();
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
Bit8u exec_xadd_8b(Bit8u dst)
{
    Bit8u src=read8BitReg(reg1),tmp=exec_add_8b(dst,src);
    write8BitReg(reg1,dst);
    return tmp;
}

Bit16u exec_xadd_16b(Bit16u dst)
{
    Bit16u src=read16BitReg(reg1),tmp=exec_add_16b(dst,src);
    write16BitReg(reg1,dst);
    return tmp;
}

Bit32u exec_xadd_32b(Bit32u dst)
{
    Bit32u src=read32BitReg(reg1),tmp=exec_add_32b(dst,src);
    write32BitReg(reg1,dst);
    return tmp;
}

//Exchange Register/Memory with Register
void exec_xchg_reg(Bit8u reg){
    if(address_size()==16)
     {
         Bit16u tmp=read16BitReg(reg);
         write16BitReg(reg,AX);
         AX=tmp;
     }
     else
     {
        Bit32u tmp=read32BitReg(reg);
        write32BitReg(reg,EAX);
        EAX=tmp;
     }
}
void exec_xchg_mem_8b(){
    Bit8u tmp=read8BitReg(reg1);
    if(rm_is_reg)
    {
        write8BitReg(reg1,read8BitReg(reg2));
        write8BitReg(reg2,tmp);
    }
    else
    {
        Bit8u* data =(Bit8u*)get_mem_data();
        write8BitReg(reg1,*data);
        *data=tmp;
    }
}
void exec_xchg_mem_16b(){
    Bit16u tmp=read16BitReg(reg1);
    if(rm_is_reg)
    {
        write16BitReg(reg1,read16BitReg(reg2));
        write16BitReg(reg2,tmp);
    }
    else
    {
        Bit16u* data =(Bit16u*)get_mem_data();
        write16BitReg(reg1,*data);
        *data=tmp;
    }
}

void exec_xchg_mem_32b(){
    Bit32u tmp=read32BitReg(reg1);
    if(rm_is_reg)
    {
        write32BitReg(reg1,read32BitReg(reg2));
        write32BitReg(reg2,tmp);
    }
    else
    {
        Bit32u* data =(Bit32u*)get_mem_data();
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
        AL = (Bit8u)(BX+AL);
     }
     else
     {
        AL = (Bit8u)(EBX+AL);
     }
}


Bit8u exec_xor_8b(Bit8u dst,Bit8u src)
{
    Bit8u tmp=dst^src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,8,PZS_MASK);
    return tmp;
}

Bit16u exec_xor_16b(Bit16u dst,Bit16u src)
{
    Bit16u tmp=dst^src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,16,PZS_MASK);
    return tmp;
}

Bit32u exec_xor_32b(Bit32u dst,Bit32u src)
{
    Bit32u tmp=dst^src;
    clear_flag(CF);
    clear_flag(OF);
    SET_EFLAGS(tmp,0,0,0,32,PZS_MASK);
    return tmp;
}

Bit8u exec_shift_8b(Bit8u index,Bit8u src,Bit8u count){
	switch(index){
		case 0: return exec_rol_8b(src,count);
		case 1: return exec_ror_8b(src,count);
		case 4: return exec_sal_8b(src,count);
		case 5: return exec_shr_8b(src,count);
		case 7: return exec_sar_8b((Bit8s)src,count);
	}
}

Bit16u exec_shift_16b(Bit8u index,Bit16u src,Bit8u count){
	switch(index){
		case 0: return exec_rol_16b(src,count);
		case 1: return exec_ror_16b(src,count);
		case 4: return exec_sal_16b(src,count);
		case 5: return exec_shr_16b(src,count);
		case 7: return exec_sar_16b((Bit16s)src,count);
	}
}

Bit32u exec_shift_32b(Bit8u index,Bit32u src,Bit8u count){
	switch(index){
		case 0: return exec_rol_32b(src,count);
		case 1: return exec_ror_32b(src,count);
		case 4: return exec_sal_32b(src,count);
		case 5: return exec_shr_32b(src,count);
		case 7: return exec_sar_32b((Bit32s)src,count);
	}
}
