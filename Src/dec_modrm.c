#include "global.h"
void dec_modrm(){
	if(address_size()==16){
		dec_modrm_16b();
		if(rm_is_reg){
			if(prefix_seg!=7)
				eAddr_sreg=prefix_seg;
			linear_addr=translate_linear_addr(eAddr16,eAddr_sreg);
		}
	}
	else{
		dec_modrm_32b();
		if(rm_is_reg){
			if(prefix_seg!=7)
				eAddr_sreg=prefix_seg;
			linear_addr=translate_linear_addr(eAddr32,eAddr_sreg);
		}
	}
}
void dec_modrm_16b(){
	DEBUG("addressSize is 16bit\n");
	u_int8_t modrm,mod,rm;
	u_int16_t offset=0;
	modrm=*(curInst+1);
	mod=modrm>>6;
	reg1=(modrm&0x38)>>3;
	rm=modrm&0x07;
	if(mod==3){   //mod= 11, r/m is a register
		reg2=rm;
		instLen=1;
		rm_is_reg=1;
	}
	else{
		switch(mod){
			case 1:   //mod= 01,8-bit displacement
 				offset=*(Bit8s*)(curInst+2);
				instLen=2;
				break;
			case 2:   //mod= 10, 16-bit displacement
				offset=*(u_int16_t*)(curInst+2);
				instLen=3;
				break;
			default:  //mod =00 ,no displacement
				instLen=1;
				offset=0;
				break;
		}
		switch(rm){
			case 0:
				eAddr16=BX+SI+offset;
				eAddr_sreg=SEG_REG_DS; //DS
				break;
			case 1:
				eAddr16=BX+DI+offset;
				eAddr_sreg=SEG_REG_DS;
				break;
			case 2:
				eAddr16=BP+SI+offset;
				eAddr_sreg=SEG_REG_SS; //SS
				break;
			case 3:
				eAddr16=BP+DI+offset;
				eAddr_sreg=SEG_REG_SS; //SS
				break;
			case 4:
				eAddr16=SI+offset;
				eAddr_sreg=SEG_REG_DS; //DS
				break;
			case 5:
				eAddr16=DI+offset;
				eAddr_sreg=SEG_REG_DS; //DS
				break;
			case 6:
				switch(mod){
					case 0:  //00 110
		 				eAddr16=*(curInst+2);
						eAddr_sreg=SEG_REG_DS;
						instLen=3;
						break;
					default:
						eAddr16=BP+offset;
						eAddr_sreg=SEG_REG_SS; //SS
						break;
				}
				break;
			case 7:
				eAddr16=BX+offset;
				eAddr_sreg=SEG_REG_DS; //DS
				break;
			default:
				break;
		}
		rm_is_reg=0;
	}
	//DEBUG("modrm:%02x,mod:%d,reg:%d,rm:%d,instLen:%d\n",modrm,mod,reg1,rm,instLen);

}
void dec_modrm_32b(){
	DEBUG("addressSize is 32bit\n");
	u_int8_t modrm,mod,rm;
	u_int32_t offset=0;
	modrm=*(curInst+1);
	mod=modrm>>6;
	reg1=(modrm&0x38)>>3;
	rm=modrm&0x07;
	if(mod==3){   //mod= 11, r/m is a register
		reg2=rm;
		rm_is_reg=1;
		instLen=1;
	}
	else if(rm!=4){
		switch(mod){
			case 1:   //mod= 01,8-bit displacement
 				offset=*(Bit8s*)(curInst+2);
				instLen=2;
				break;
			case 2:   //mod= 10, 32-bit displacement
				offset=*(u_int32_t*)(curInst+2);
				instLen=5;
				break;
			default:  //mod =00 ,no displacement
				offset=0;
				instLen=1;
				break;
		}
		switch(rm){
			case 0:
				eAddr32=EAX+offset;
				eAddr_sreg=SEG_REG_DS; //DS
				break;
			case 1:
				eAddr32=EBX+offset;
				eAddr_sreg=SEG_REG_DS;
				break;
			case 2:
				eAddr32=EDX+offset;
				eAddr_sreg=SEG_REG_DS;
				break;
			case 3:
				eAddr32=EBX+offset;
				eAddr_sreg=SEG_REG_DS;
				break;
			case 5:
				switch(mod){
					case 0:   //
		 				eAddr32=*(u_int32_t*)(curInst+2);
						instLen=5;
						eAddr_sreg=SEG_REG_DS;
						break;
					default:  //mod =00 ,no displacement
						eAddr32=EBP+offset;
						eAddr_sreg=SEG_REG_SS; //SS
						break;
				}
				break;
			case 6:
				eAddr32=ESI+offset;
				eAddr_sreg=SEG_REG_DS;
				break;
			case 7:
				eAddr32=EDI+offset;
				eAddr_sreg=SEG_REG_DS; //DS
				break;
			default:
				break;
		}

		rm_is_reg=0;
	}
	else{
		dec_sib();
		rm_is_reg=0;
	}
	//DEBUG("modrm:%02x,mod:%d,reg:%d,rm:%d,instLen:%d\n",modrm,mod,reg1,rm,instLen);
}


void dec_sib(){
	u_int8_t modrm,sib,mod,ss,index,base;
	u_int32_t scale,index_reg;
	u_int32_t offset=0;
	modrm=*(curInst+1);
	sib=*(curInst+2);
	mod=modrm>>6;
	ss=sib>>6;
	index=(sib&0x38)>>3;
	base=sib&0x07;
	switch(mod){
		case 0:  //mod =00 ,no displacement
			offset=0;
			instLen=2;
			break;
		case 1:   //mod= 01,8-bit displacement
			offset=*(Bit8s*)(curInst+3);
			instLen=3;
			break;
		case 2:   //mod= 10, 32-bit displacement
			offset=*(u_int32_t*)(curInst+3);
			instLen=6;
			break;
		default:
			printf("ND exception\n");
			exit(0);
	}
	switch(ss){
		case 0: scale=1;break;
		case 1: scale=2;break;
		case 2: scale=3;break;
		case 3: scale=4;break;
		default:
			break;
	}
	if(index!=4) index_reg=read32BitReg(index);
	else index_reg=0;
	if(mod==0&&base==5){
		offset=*(u_int32_t*)(curInst+3);
		instLen=6;
		eAddr32=offset+index_reg*scale;
	}
	else{
		eAddr32=read32BitReg(base)+index_reg*scale+offset;
	}
	if((mod==0&&base==5)||(base!=5&&base!=6)){
		eAddr_sreg=SEG_REG_DS;
	}
	else{
		eAddr_sreg=SEG_REG_SS;
	}
	//DEBUG("sib:%02x,mod:%d,ss:%d(%d),index:%08x(%d),base:%08x(%d),addr:%08x(%d)\n",sib,mod,scale,ss,index_reg,index,read32BitReg(base),base,eAddr32,offset);
}

