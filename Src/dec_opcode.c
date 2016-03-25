#include "global.h"
void dec_opcode_run(){
	u_int8_t nojmp=1;
	instLen=immLen=0;
	switch(*curInst){
		// bcd conversion instruction
		case 0x37: //AAA
			exec_aaa();
			break;
		case 0x3F: //AAS
			exec_aas();
			break;
		case 0xD5: //AAD
			immLen=1;
			exec_aad(*(curInst+1));
			break;
		case 0xD4: //AAM
			immLen=1;
			exec_aam(*(curInst+1));
			break;
		case 0x04://ADD AL,imm8
		case 0x0C://OR AL,imm8
		case 0x14://ADC AL,imm8
		case 0x24://AND AL,imm8
		case 0x2C://SUB AL,imm8
		case 0x34://XOR AL,imm8
		case 0x1C://SBB AL,imm8
		case 0x3C://CMP AL,imm8
			immLen=1;
			AL=exec_arith_8b((*curInst&38)>>3,AL,*(curInst+1));
			break;
		case 0x05://ADD AX/EAX,imm16/imm32
        case 0x0D://OR AX/EAX,imm16/imm32
		case 0x15://ADC AX/EAX,imm16/imm32
		case 0x25://AND AX/EAX,imm16/imm32
		case 0x2D://SUB AX/EAX,imm16/imm32
		case 0x35://AND AX/EAX,imm16/imm32
		case 0x1D://SBB AX/EAX,imm16/imm32
        case 0x3D://CMP AX/EAX,imm16/imm32
			if(operand_size()==16){
				immLen=2;
				AX=exec_arith_16b((*curInst&38)>>3,AX,*(u_int16_t*)(curInst+1));
			}
			else {
				immLen=4;
				EAX=exec_arith_32b((*curInst&38)>>3,EAX,*(u_int32_t*)(curInst+1));
			}
			break;
		case 0x00: //ADD r/m8,r8
        case 0x08: //OR r/m8,r8
		case 0x10: //ADC r/m8,r8
		case 0x20: //AND r/m8,r8
		case 0x28: //SUB r/m8,r8
		case 0x30: //OR r/m8,r8
		case 0x18: //SBB r/m8,r8
        case 0x38: //CMP r/m8,r8
			dec_modrm();
			if(rm_is_reg){
				u_int8_t tmp=exec_arith_8b((*curInst&38)>>3,read8BitReg(reg2),read8BitReg(reg1));
				write8BitReg(reg2,tmp);
				break;
			} else{
				u_int8_t *data=(u_int8_t*)get_mem_data();
				*data=exec_arith_8b((*curInst&38)>>3,*data,read8BitReg(reg1));
				break;
			}
		case 0x01://ADD r/m16/32,r16/32
		case 0x09://OR r/m16/32,r16/32
		case 0x11://ADC r/m16/32,r16/32
		case 0x21://AND r/m16/32,r16/32
		case 0x29://SUB r/m16/32,r16/32
		case 0x31: //OR r/m16/32,r16/32
		case 0x19://SBB r/m16/32,r16/32
        case 0x39://CMP r/m16/32,r16/32
			dec_modrm();
			if(operand_size()==16){
				if(rm_is_reg){
					u_int16_t tmp=exec_arith_16b((*curInst&38)>>3,read16BitReg(reg2),read16BitReg(reg1));
					write16BitReg(reg2,tmp);
					break;
				} else{
					u_int16_t* data=(u_int16_t*)get_mem_data();
					*data=exec_arith_16b((*curInst&38)>>3,*data,read16BitReg(reg1));
				}
			}
			else {
				if(rm_is_reg){
					u_int32_t tmp=exec_arith_32b((*curInst&38)>>3,read32BitReg(reg2),read32BitReg(reg1));
					write32BitReg(reg2,tmp);
					break;
				}else{
					u_int32_t* data=(u_int32_t*)get_mem_data();
					*data=exec_arith_32b((*curInst&38)>>3,*data,read32BitReg(reg1));
				}
			}
			break;
		case 0x02: //ADD r8,r/m8
		case 0x0A: //OR r8,r/m8
		case 0x12: //ADC r8,r/m8
		case 0x22: //AND r8,r/m8
		case 0x2A: //SUB r8,r/m8
		case 0x32: //OR r/m8,r8
		case 0x1A: //SBB r8,r/m8
		case 0x3A: //CMP r8,r/m8
			dec_modrm();
			{
				u_int8_t src;
				if(rm_is_reg==0){
					src=*(u_int8_t*)get_mem_data();
				}
				else src=read8BitReg(reg2);
				u_int8_t tmp=exec_arith_8b((*curInst&38)>>3,read8BitReg(reg1),src);
				write8BitReg(reg1,tmp);
			}
			break;
		case 0x03: //ADD r16/32,r/m16/32
		case 0x0B: //ADD r16/32,r/m16/32
		case 0x13: //ADC r16/32,r/m16/32
		case 0x23: //AND r16/32,r/m16/32
		case 0x2B: //SUB r16/32,r/m16/32
		case 0x33: //OR r16/32,r/m16/32
		case 0x1B: //SBB r16/32,r/m16/32
		case 0x3B: //CMP r16/32,r/m16/32
			dec_modrm();
			if(operand_size()==16){
				u_int16_t src;
				if(rm_is_reg==0){
					src=*(u_int16_t*)get_mem_data();
				}
				else src=read16BitReg(reg2);
				u_int16_t tmp=exec_arith_16b((*curInst&38)>>3,read8BitReg(reg1),src);
				write16BitReg(reg1,tmp);
			}
			else {
				u_int32_t src;
				if(rm_is_reg==0){
					src=*(u_int32_t*)get_mem_data();
				}
				else src=read32BitReg(reg2);
				u_int32_t tmp=exec_arith_32b((*curInst&38)>>3,read32BitReg(reg1),src);
				write32BitReg(reg1,tmp);
			}
			break;
		case 0x80:  //arith op
			immLen=1;
			if(rm_is_reg){
				u_int8_t tmp=exec_arith_8b(reg1,read8BitReg(reg2),*(curInst+1+instLen));
				write8BitReg(reg2,tmp);
				break;
			} else{
				u_int8_t *data=(u_int8_t*)get_mem_data();
				*data=exec_arith_8b((*curInst&38)>>3,*data,*(curInst+1+instLen));
				break;
			}
		case 0x81://arith op
			dec_modrm();
			if(operand_size()==16){
				immLen=2;
				if(rm_is_reg){
					u_int16_t tmp=exec_arith_16b(reg1,read16BitReg(reg2),*(u_int16_t*)(curInst+1+instLen));
					write16BitReg(reg2,tmp);
					break;
				}
				u_int16_t* data=(u_int16_t*)get_mem_data();
				*data=exec_arith_16b(reg1,*data,*(u_int16_t*)(curInst+1+instLen));
			}
			else {
				immLen=4;
				if(rm_is_reg){
					u_int32_t tmp=exec_arith_32b(reg1,read32BitReg(reg2),*(u_int32_t*)(curInst+1+instLen));
					write32BitReg(reg2,tmp);
					break;
				}
				//
				u_int32_t* data=(u_int32_t*)get_mem_data();
				*data=exec_arith_32b(reg1,*data,*(u_int32_t*)(curInst+1+instLen));
			}
			break;
        case 0x83://arith op
			dec_modrm();
			if(operand_size()==16){
				immLen=1;
				Bit16s imm=*(Bit8s*)(curInst+1+instLen);
				if(rm_is_reg){
					u_int16_t tmp=exec_arith_16b(reg1,read16BitReg(reg2),imm);
					write16BitReg(reg2,tmp);
					break;
				}
				u_int16_t *data=(u_int16_t*)get_mem_data();
				*data=exec_arith_16b(reg1,*data,imm);
			}
			else {
				immLen=1;
				Bit32s imm=*(Bit8s*)(curInst+1+instLen);
				if(rm_is_reg){
					u_int32_t tmp=exec_arith_32b(reg1,read32BitReg(reg2),imm);
					write32BitReg(reg2,tmp);
					break;
				}
				u_int32_t *data=(u_int32_t*)get_mem_data();
				*data=exec_arith_32b(reg1,*data,imm);
			}
			break;
		case 0x63://arpl
			dec_modrm();
			if(rm_is_reg){
				u_int16_t tmp=exec_arpl(read8BitReg(reg2),read8BitReg(reg1));
				write8BitReg(reg2,tmp);
				break;
			} else{
				u_int8_t *data=(u_int8_t*)get_mem_data();
				*data=exec_arpl(*data,read8BitReg(reg1));
				break;
			}
		case 0x62://Bound
			dec_modrm();
			if(rm_is_reg){
				printf("#UD exception\n");
				exit(0);
			} else{
				u_int8_t *data=(u_int8_t*)get_mem_data();
				if(operand_size()==16)
					exec_bound_16b((Bit16s*)data,(Bit16s)read16BitReg(reg1));
				else
					exec_bound_32b((Bit32s*)data,(Bit32s)read32BitReg(reg1));
				break;
			}
		case 0xE8: //call near relative
			exec_call_near_relative();
			break;
		case 0xFF://call
			dec_modrm();
			switch(reg1){
				case 2:
					exec_call_near_absolute();
					break;
                case 1:
                    exec_dec_16_32b();
                    break;
                case 6://push
                    if(operand_size()==16){
                        if(rm_is_reg){
                            push_16b(read16BitReg(reg2));
                        }
                        else{
                            u_int16_t* data=(u_int16_t*)get_mem_data();
                            push_16b(*data);
                        }
                    }
                    else{
                        if(rm_is_reg){
                            push_32b(read32BitReg(reg2));
                        }
                        else{
                            u_int32_t* data=(u_int32_t*)get_mem_data();
                            push_32b(*data);
                        }
                    }
                    break;
				default:
					printf("#UD exception\n");
					exit(0);
			}
		case 0x98://CBW/CWDE
			if(operand_size()==16){
				Bit16s tmp=(Bit8s)AL;
				AX=tmp;
			}
			else {
				Bit32s tmp=(Bit32s)AX;
				EAX=tmp;
			}
			break;
		case 0xF8://CLC
			clear_flag(CF);
			break;
		case 0xFC://CLD
			clear_flag(DF);
			break;
        case 0x99: //CWD/CDQ
            exec_cwd_cdq();
            break;
        case 0x27: //DAA
            exec_daa();
            break;
        case 0x2F: //DAS
            exec_das();
            break;
        case 0xFE://DEC
            dec_modrm();
            if(reg1==1)
                exec_dec_8b();
            break;
        case 0xC8://ENTER
            immLen=3;
            exec_enter(*(u_int16_t*)(curInst+1),*(curInst+3));
            break;
        case 0xF4://HLT
            if(REAL_MODE||cpl==0){
                printf("enter hlt state\n");
            }else{
                printf("#GP(0) exception\n");
            }
            exit(0);
        case 0x6B:// imul r16/32,r/m16/32,imm8
            dec_modrm();
            immLen=1;
	    {
		Bit32s imm=*(Bit8s*)(curInst+instLen+1);
		exec_imul_16_32b(3,imm);
	    }
            break;
        case 0x69:// imul r16/32,r/m16/32,imm16/32
            dec_modrm();
            {
                Bit32s imm;
                if(operand_size()==16){
                    imm=*(Bit16s*)(curInst+instLen+1);
                    immLen=2;
                }else{
                    imm=*(Bit32s*)(curInst+instLen+1);
                    immLen=2;
                }
                exec_imul_16_32b(3,imm);
            }
            break;
        case 0x8F:
            dec_modrm();
            switch(reg1)
            {
                case 0://pop
                {
                    if(operand_size()==16){
                        u_int16_t* data =(u_int16_t*)get_mem_data();
                        *data=pop_16b();
                    }
                    else
                    {
                        u_int32_t* data =(u_int32_t*)get_mem_data();
                        *data=pop_32b();
                    }
                    break;
                }
            }
            break;
        case 0x1f: //POP DS
            {
                Selector selector;
                selector.selector=pop_16b();
                load_seg(selector,SEG_REG_DS);
            }
            break;
        case 0x17: //POP SS
            {
                Selector selector;
                selector.selector=pop_16b();
                load_seg(selector,SEG_REG_SS);
            }
            break;
        case 0x07: //POP ES
            {
                Selector selector;
                selector.selector=pop_16b();
                load_seg(selector,SEG_REG_ES);
            }
            break;;
        case 0x61: //POPA
            exec_popa();
            break;
        case 0x9D: //POPF
            exec_popf();
            break;
        case 0x0E: //PUSH CS
            push_16b(CS.selector);
            break;
        case 0x16: //PUSH SS
            push_16b(SS.selector);
            break;
        case 0x1E: //PUSH DS
            push_16b(DS.selector);
            break;
        case 0x06: //PUSH ES
            push_16b(ES.selector);
            break;
        case 0x6A: //push
            immLen=1;
            push_16b(*(curInst+1+instLen));
            break;
        case 0x68: //push
            if(operand_size()==16)
            {
                immLen=2;
                push_16b(*(u_int16_t*)(curInst+1+instLen));
            }
            else
            {
                immLen=4;
                push_32b(*(u_int32_t*)(curInst+1+instLen));
            }
            break;
        case 0x60://PUSHA/PUSHAD
            exec_pusha();
        case 0x9C://PUSHF/PUSHFD
            exec_pushf();
            break;
        case 0x9F://LAHF
            exec_lahf();
            break;
        case 0xC5://LDS
            dec_modrm();
            exec_load_seg(SEG_REG_DS);
            break;
        case 0xC4://LES
            dec_modrm();
            exec_load_seg(SEG_REG_ES);
            break;
        case 0xBD://LEA
            dec_modrm();
            exec_lea();
            break;
        case 0xC9://LEAVE
            exec_leave();
            break;
        case 0xAC: //lods m8
            exec_lods_8b();
            break;
        case 0xAD://lods m16/32
            exec_lods_16_32b();
            break;
        case 0xE2://loop
            immLen=1;
             nojmp=exec_loop();
            break;
        case 0xE1://loope/loopz
            immLen=1;
            nojmp= exec_loope();
            break;
        case 0xE0://loopne/loopnz
            immLen=1;
             nojmp=exec_loopne();
            break;
        case 0x88://mov r/m,r8
            dec_modrm();
            exec_mov_8b_2rm(read8BitReg(reg1));
            break;
        case 0x89://mov r/m,r16/32
            dec_modrm();
            if(operand_size()==16) exec_mov_16b_2rm(read16BitReg(reg1));
            else exec_mov_32b_2rm(read32BitReg(reg1));
            break;
        case 0x8A://mov r8,r/m
            dec_modrm();
            exec_mov_8b_2reg(*get_mem_data(),reg1);
            break;
        case 0x8B://mov  r16/32,r/m
            dec_modrm();
            if(operand_size()==16) exec_mov_16b_2reg(*(u_int16_t*)get_mem_data(),reg1);
            else exec_mov_32b_2reg(*(u_int32_t*)get_mem_data(),reg1);
            break;
        case 0x8C://mov r/m16,Sreg
            dec_modrm();
            exec_mov_2seg(reg1);
            break;
        case 0x8E://mov Sreg,r/m
            dec_modrm();
            exec_mov_seg(reg1);
            break;
        case 0xA0: //mov al,seg:ofset
            immLen=address_size()/8;
            if(address_size()==16)     linear_addr=translate_linear_addr(*(u_int16_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            else   linear_addr=translate_linear_addr(*(u_int32_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            exec_mov_8b_2reg(*get_mem_data(),0);
            break;
        case 0xA1://mov ax/eax,seg:offset
            immLen=address_size()/8;
            if(address_size()==16)     linear_addr=translate_linear_addr(*(u_int16_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            else   linear_addr=translate_linear_addr(*(u_int32_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            if(operand_size()==16){
                exec_mov_16b_2reg(*(u_int16_t*)get_mem_data(),0);
            }else{
                exec_mov_32b_2reg(*(u_int32_t*)get_mem_data(),0);
            }
            break;
        case 0xA2://mov seg:offset,al
              immLen=address_size()/8;
            if(address_size()==16)     linear_addr=translate_linear_addr(*(u_int16_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            else   linear_addr=translate_linear_addr(*(u_int32_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            exec_mov_8b_2rm(0);
            break;
        case 0xA3://mov seg:offset,AX/EAX
             immLen=address_size()/8;
            if(address_size()==16)     linear_addr=translate_linear_addr(*(u_int16_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            else   linear_addr=translate_linear_addr(*(u_int32_t*)(curInst+1),prefix_seg==7?prefix_seg:SEG_REG_DS);
            if(operand_size()==16){
                exec_mov_16b_2rm(0);
            }else{
                exec_mov_32b_2rm(0);
            }
            break;
        case 0xC6:
            dec_modrm();
            switch(reg1){
                case 0://mov r/m8,imm
                    immLen=1;
                    exec_mov_8b_2rm(*(curInst+1));
                    break;
                default:
                    printf("＃UD exception\n");
                    exit(0);
            }
            break;
        case 0xC7:
         dec_modrm();
            switch(reg1){
                case 0://mov r/m16/32,imm
                    immLen=operand_size()/8;
                    if(immLen==2) exec_mov_16b_2reg(*(u_int16_t*)(curInst+1),*curInst&0x07);
                    else exec_mov_32b_2reg(*(u_int32_t*)(curInst+1),*curInst&0x07);
                    break;
                default:
                    printf("＃UD exception\n");
                    exit(0);
            }
            break;
        case 0xA4://movs m8,m8
            exec_movs_8b();
            break;
        case 0xA5://movs m16/32,m16/32
            exec_movs_16_32b();
            break;
        case 0x90://NOP
            break;
		case 0x9E://sahf
			exec_sahf();
			break;
        case 0xD0:
            dec_modrm();
            switch(reg1){
                case 0: //ROL
                case 1: //ROR
                case 4: //SAL
                case 5: //SHR
                case 7: //SAR
                    if(rm_is_reg)
                         write8BitReg(reg2,exec_shift_8b(reg1,read8BitReg(reg2),1));
                    else
                    {
                        u_int8_t *data=get_mem_data();
                        *data=exec_shift_8b(reg1,*data,1);
                    }
                    break;
            }
            break;
        case 0xD2:
            dec_modrm();
            switch(reg1){
                case 0: //ROL
                case 1: //ROR
                case 4: //SAL
                case 5: //SHR
                case 7: //SAR
                   if(rm_is_reg)
                         write8BitReg(reg2,exec_shift_8b(reg1,read8BitReg(reg2),CL));
                    else
                    {
                        u_int8_t *data=get_mem_data();
                        *data=exec_shift_8b(reg1,*data,CL);
                    }
                    break;
            }
             break;
         case 0xC0:
            dec_modrm();
            switch(reg1){
                case 0: //ROL
                case 1: //ROR
                case 4: //SAL
                case 5: //SHR
                case 7: //SAR
                    immLen=1;
                    if(rm_is_reg)
                         write8BitReg(reg2,exec_shift_8b(reg1,read8BitReg(reg2),*(curInst+1+instLen)));
                    else
                    {
                        u_int8_t *data=get_mem_data();
                        *data=exec_shift_8b(reg1,*data,*(curInst+1+instLen));
                    }
                    break;
            }
            break;
        case 0xD1:
            dec_modrm();
            switch(reg1){
                case 0: //ROL
                case 1: //ROR
                case 4: //SAL
                case 5: //SHR
                case 7: //SAR
                     if(operand_size()==16){
                        if(rm_is_reg)
                            write16BitReg(reg2,exec_shift_16b(reg1,read16BitReg(reg2),1));
                        else
                        {
                            u_int16_t *data=(u_int16_t*)get_mem_data();
                            *data=exec_shift_16b(reg1,*data,1);
                        }
                    }
                    else{
                        if(rm_is_reg)
                            write32BitReg(reg2,exec_shift_32b(reg1,read32BitReg(reg2),1));
                        else
                        {
                            u_int32_t *data=(u_int32_t*)get_mem_data();
                            *data=exec_shift_32b(reg1,*data,1);
                        }
                    }
                    break;
             }
             break;
         case 0xD3:
            dec_modrm();
            switch(reg1){
                case 0: //ROL
                case 1: //ROR
                case 4: //SAL
                case 5: //SHR
                case 7: //SAR
                    if(operand_size()==16){
                        if(rm_is_reg)
                            write16BitReg(reg2,exec_shift_16b(reg1,read16BitReg(reg2),CL));
                        else
                        {
                            u_int16_t *data=(u_int16_t*)get_mem_data();
                            *data=exec_shift_16b(reg1,*data,CL);
                        }
                    }
                    else{
                        if(rm_is_reg)
                            write32BitReg(reg2,exec_shift_32b(reg1,read32BitReg(reg2),CL));
                        else
                        {
                            u_int32_t *data=(u_int32_t*)get_mem_data();
                            *data=exec_shift_32b(reg1,*data,CL);
                        }
                    }
                    break;
             }
             break;
        case 0xC1:
            dec_modrm();
            switch(reg1){
                case 0: //ROL
                case 1: //ROR
                case 4: //SAL
                case 5: //SHR
                case 7: //SAR
                    immLen=1;
                    if(operand_size()==16){
                        if(rm_is_reg)
                            write16BitReg(reg2,exec_shift_16b(reg1,read16BitReg(reg2),*(curInst+1+instLen)));
                        else
                        {
                            u_int16_t *data=(u_int16_t*)get_mem_data();
                            *data=exec_shift_16b(reg1,*data,*(curInst+1+instLen));
                        }
                    }
                    else{
                        if(rm_is_reg)
                            write32BitReg(reg2,exec_shift_32b(reg1,read32BitReg(reg2 ),*(curInst+1+instLen)));
                        else
                        {
                            u_int32_t *data=(u_int32_t*)get_mem_data();
                            *data=exec_shift_32b(reg1,*data,*(curInst+1+instLen));
                        }
                    }
                    break;
             }
             break;
        case 0xAE://SACS
            exec_scas_8b();
            break;
        case 0xAF://SACS
            if(operand_size()==16)
                exec_scas_16b();
            else
                exec_scas_32b();
            break;
		case 0xF9://STC
			exec_stc();
			break;
		case 0xFD://STD
			exec_std();
			break;
		case 0xFB://STI
			exec_sti();
			break;
      		case 0xD7://XLAT/XLATB
			exec_xlat();
			break;
        case 0xAA: //STOS
            exec_stos_8b();
        case 0xAB: //STOS
            if(operand_size()==16)
            {
                 exec_stos_16b();
                 break;
            }
            else
            {
                 exec_stos_32b();
                 break;
            }
        case 0xA8: //TEST
            immLen=1;
			exec_and_8b(AL,*(curInst+1));
            break;
        case 0xA9: //TEST
            if(operand_size()==16)
            {
                immLen=2;
                exec_and_8b(AX,*(u_int16_t*)(curInst+1));
            }
			else
			{
                immLen=4;
                exec_and_32b(EAX,*(u_int32_t*)(curInst+1));
			}
			 break;
        case 0xF6:
            dec_modrm();
            switch(reg1){
                case 0://TEST
                    immLen=1;
                    if(rm_is_reg)
                    {
                        u_int8_t imm=*(u_int8_t*)(curInst+1+instLen);
                        exec_and_8b(read8BitReg(reg1),imm);
                    }
                    else
                    {
                        u_int8_t imm=*(u_int8_t*)(curInst+1+instLen);
                        exec_and_8b(*(get_mem_data()),imm);
                    }
                    break;
                case 2: //not r/m8
                    exec_not_8b();
                    break;
                case 3://negr/m8
                    exec_neg_8b();
                    break;
                case 4://mull AL,r/m8
                    exec_mul_8b();
                    break;
                case 5://imul r/m8
                    exec_imul_8b();
                    break;
                case 6: //DIV
                    exec_div_8b();
                    break;
                case 7://IDIV
                    exec_idiv_8b();
                    break;
                default:
                    printf("#UD exception\n");
                    exit(0);
            }
            break;
        case 0xF7:
            dec_modrm();
            switch(reg1){
                case 0://TEST
                    if(operand_size()==16)
                    {
                        immLen=2;
                        u_int16_t imm=*(u_int16_t*)(curInst+1+instLen);
                        if(rm_is_reg)
                        {
                            exec_and_16b(read16BitReg(reg1),imm);
                        }
                        else
                        {
                             exec_and_16b(*(u_int16_t*)get_mem_data(),imm);
                        }
                    }
                    else
                    {
                        immLen=4;
                        u_int32_t imm=*(u_int32_t*)(curInst+1+instLen);
                        if(rm_is_reg)
                        {
                            exec_and_32b(read32BitReg(reg1),imm);
                        }
                        else
                        {
                             exec_and_32b(*(u_int32_t*)get_mem_data(),imm);
                        }
                    }
                    break;
                case 2://not r/m 16/32
                    exec_not_16_32b();
                    break;
                case 3://neg r/m16/32
                    exec_neg_16_32b();
                    break;
                case 4://MUL AX／EAX，r/m16/32
                    exec_mul_16_32b();
                    break;
                case 5://IMUL r/m16/32
                    exec_imul_16_32b(1,0);
                    break;
                case 6: //DIV
                    exec_div_16_32b();
                    break;
                case 7://IDIV
                    exec_idiv_16_32b();
                    break;
                default:
                    printf("#UD exception\n");
                    exit(0);
            }
            break;
        case 0x84: //TEST
            dec_modrm();
            if(rm_is_reg)
            {
                exec_and_8b(read8BitReg(reg1),read8BitReg(reg2));
            }
            else
            {
                exec_and_8b(read8BitReg(reg1),*(get_mem_data()));
            }
             break;
        case 0x85: //TEST
            if(operand_size()==16)
            {
                if(rm_is_reg)
                {
                    exec_and_16b(read16BitReg(reg1),read16BitReg(reg2));
                }
                else
                {
                     exec_and_16b(read16BitReg(reg1),*(u_int16_t*)get_mem_data());
                }
            }
            else
            {
                if(rm_is_reg)
                {
                    exec_and_32b(read32BitReg(reg1),read32BitReg(reg2));
                }
                else
                {
                     exec_and_32b(read32BitReg(reg1),*(u_int32_t*)get_mem_data());
                }
            }
             break;
        case 0x86://XCHG
            dec_modrm();
			exec_xchg_mem_8b();
			break;
        case 0x87://XCHG
            dec_modrm();
			if(operand_size()==16){
                exec_xchg_mem_16b();
			}
			else {
				exec_xchg_mem_32b();
			}
			break;
		default:
		{
            if(*curInst&0xF0==0x70){ //jcc imm8
                Bit8s disp=*(curInst+1);
                immLen=1;
                if(conditions_judge(*curInst&0x0F)){
                    nojmp=0;
                    EIP=EIP+disp;
                    if(operand_size()==16) EIP=EIP&0xFFFF;
                }
                break;
            }
            else{
                switch(*curInst&0xF8) {
                    case 0x90: //XCHG
                        exec_xchg_reg(*curInst&0x07);
                        break;
                    case 0x48: //dec
                        exec_dec_16_32b_r(*curInst&0x07);
                        break;
                    case 0xB0://mov reg8,imm8
                        immLen=1;
                        exec_mov_8b_2reg(*(curInst+1),*curInst&0x07);
                        break;
                    case 0xB8://mov reg16/32,imm
                        immLen=operand_size()/8;
                        if(immLen==2) exec_mov_16b_2reg(*(u_int16_t*)(curInst+1),*curInst&0x07);
                        else exec_mov_32b_2reg(*(u_int32_t*)(curInst+1),*curInst&0x07);
                        break;
                    case 0x58://pop
                        if(operand_size()==16)
                        {
                            write16BitReg(reg1,pop_16b());
                        }
                        else
                        {
                            write32BitReg(reg1,pop_32b());
                        }
                        break;
                    case 0x50://push
                        if(operand_size()==16)
                        {
                            push_16b(read16BitReg(*curInst&07));
                        }
                        else
                        {
                            push_32b(read32BitReg(*curInst&07));
                        }
                        break;
                    default:
                        printf("#UD exception\n");
                        exit(0);
                    }
            }
		}

	}
	//DEBUG("instruction length:%d(%d,%d,%d,%d)\n",instLen+prefixLen+immLen+1,prefixLen,1,instLen,immLen);
	if(nojmp) EIP=EIP+instLen+prefixLen+immLen+1;
}

void dec_opcode_2byte_run(){
	u_int8_t nojmp=1;
	instLen=immLen=0;
	switch(*curInst){
		case 0xBC://BSF
			dec_modrm();
			if(operand_size()==16){
				if(rm_is_reg){
					exec_bsf_16b(reg1,read16BitReg(reg2));
					break;
				}
				u_int16_t *data=(u_int16_t*)get_mem_data();
				exec_bsf_16b(reg1,*data);
			}
			else {
				if(rm_is_reg){
					exec_bsf_32b(reg1,read32BitReg(reg2));
					break;
				}
				u_int32_t *data=(u_int32_t*)get_mem_data();
				exec_bsf_32b(reg1,*data);
			}
			break;
		case 0xBD://BSF
			dec_modrm();
			if(operand_size()==16){
				if(rm_is_reg){
					exec_bsr_16b(reg1,read16BitReg(reg2));
					break;
				}
				u_int16_t *data=(u_int16_t*)get_mem_data();
				exec_bsr_16b(reg1,*data);
			}
			else {
				if(rm_is_reg){
					exec_bsr_32b(reg1,read32BitReg(reg2));
					break;
				}
				u_int32_t *data=(u_int32_t*)get_mem_data();
				exec_bsr_32b(reg1,*data);
			}
			break;
		case 0xA3://BT 4
		case 0xBB://BTC 7
		case 0xB3://BTR 6
		case 0xAB://BTS 5
			dec_modrm();
			if(operand_size()==16){
				if(rm_is_reg){
					exec_btx_16b_reg((*curInst&0x38)>>3,reg2,read16BitReg(reg1));
					break;
				}
				u_int8_t *data=get_mem_data();
				exec_btx_mem((*curInst&0x38)>>3,data,(Bit16s)read16BitReg(reg1));
			}
			else {
				if(rm_is_reg){
					exec_btx_32b_reg((*curInst&0x38)>>3,reg2,read32BitReg(reg1));
					break;
				}
				u_int8_t *data=get_mem_data();
				exec_btx_mem((*curInst&0x38)>>3,data,(Bit32s)read32BitReg(reg1));
			}
			break;
		case 0xBA://BTx
			immLen=1;
			dec_modrm();
			if(operand_size()==16){
				if(rm_is_reg){
					exec_btx_16b_reg(reg1,reg2,*(curInst+instLen+1));
					break;
				}
				u_int8_t *data=get_mem_data();
				exec_btx_mem(reg1,data,*(curInst+instLen+1));
			}
			else {
				if(rm_is_reg){
					exec_btx_32b_reg(reg1,reg2,*(curInst+instLen+1));
					break;
                }
				u_int8_t *data=get_mem_data();
				exec_btx_mem(reg1,data,*(curInst+instLen+1));
			}
			break;
        case 0x22://mov  cr,r32
            dec_modrm();
            exec_mov_ctrl();
            break;
        case 0x20://mov r32,cr
            dec_modrm();
            exec_mov_2ctrl();
            break;
        case 0x21://mov  r32,dr
            dec_modrm();
            exec_mov_debug();
            break;
        case 0x23://mov dr,r32
            dec_modrm();
            exec_mov_2debug();
            break;
        case 0xBE://movsx r16/32,r/m8
            dec_modrm();
            exec_movsx_8b();
            break;
        case 0xBF://movsx r32.r/m16
            dec_modrm();
            exec_movsx_16b();
            break;
        case 0xB6://movzx r16/32,r/m8
            dec_modrm();
            exec_movzx_8b();
            break;
        case 0xB7://movzx r32.r/m16
            dec_modrm();
            exec_movzx_16b();
            break;
        case 0xA1: //POP FS
           {
                Selector selector;
                selector.selector=pop_16b();
                load_seg(selector,SEG_REG_FS);
            }
            break;
        case 0xA9: //POP GS
            {
                Selector selector;
                selector.selector=pop_16b();
                load_seg(selector,SEG_REG_GS);
            }
            break;
        case 0xA0: //PUSH FS
            push_16b(FS.selector);
            break;
        case 0xA8: //PUSH GS
            push_16b(GS.selector);
            break;
        case 0xA4: //SHLD
            immLen=1;
            {
                u_int8_t count =*(curInst+instLen+1);
                exec_shld(count);
            }
            break;
        case 0xA5: //SHLD
            exec_shld(CL);
            break;
        case 0xAC: //SHRD
            immLen=1;
            {
                u_int8_t count =*(curInst+instLen+1);
                exec_shrd(count);
            }
            break;
        case 0xAD: //SHRD
            exec_shrd(CL);
            break;
        case 0x00:
			dec_modrm();
			switch(reg1){
                case 0: //SLDT
               {
                    if(operand_size()==16)
                    {
                        if(rm_is_reg){
                            write16BitReg(reg2,LDTR.selector);
                            break;
                        }
                        u_int16_t *data=(u_int16_t*)get_mem_data();
                        *data = LDTR.selector;
                        break;
                    }
                    else
                    {
                        if(rm_is_reg){
                            write32BitReg(reg2,LDTR.selector);
                            break;
                        }
                        u_int32_t *data=(u_int32_t*)get_mem_data();
                        *data = LDTR.selector;
                        break;
                    }
               }
               case 1: //str
                    if(rm_is_reg){
                        if(operand_size()==16)
                        {
                            write16BitReg(reg2,TR.selector);
                            break;
                        }
                        else
                        {
                            write32BitReg(reg2,TR.selector);
                            break;
                        }
                    }
                    {
                        u_int16_t *data=(u_int16_t*)get_mem_data();
                        *data = TR.selector;
                    }
                    break;
               case 2: //LLDT
                    exec_lldt();
                    break;
                case 3://LTR
                    exec_ltr();
                    break;
                default:
                    printf("#UD exception\n");
                    exit(0);
            }
            break;
        case 0x01:
            dec_modrm();
            switch(reg1){
                case 0: //SGDT
                {
                    u_int16_t *data=(u_int16_t*)get_mem_data();
                    *data=gdtr.limit;
                    if(operand_size()==16)
                    {
                        u_int32_t *baseadd=(u_int32_t*)(data+1);
                        *baseadd=gdtr.base;
                        //the fourth byte is undefined
                    }
                    else
                    {
                        u_int32_t *baseadd=(u_int32_t*)(data+1);
                        *baseadd=gdtr.base;
                    }
                    break;
                }
                case 1://SIDT
                {
                    u_int16_t *data=(u_int16_t*)get_mem_data();
                    *data=idtr.limit;
                    if(operand_size()==16)
                    {
                        u_int32_t *baseadd=(u_int32_t*)(data+1);
                        *baseadd=idtr.base;
                        //the fourth byte is undefined
                    }
                    else
                    {
                        u_int32_t *baseadd=(u_int32_t*)(data+1);
                        *baseadd=idtr.base;
                    }
                    break;
                }
                case 2: //LGDT
                    exec_lgdt();
                    break;
                case 3: //LIDT
                    exec_lidt();
                    break;
                case 4: //smsw
                    exec_smsw();
                    break;
                case 6://LMSW
                    exec_lmsw();
                    break;
                default:
                   printf("#UD exception\n");
                    exit(0);
            }
            break;
        case 0xC0://xadd
			dec_modrm();
			if(rm_is_reg){
                write8BitReg(reg2,exec_xadd_8b(read8BitReg(reg2)));
                break;
            }
            {
                u_int8_t *data=get_mem_data();
				*data = exec_xadd_8b(*data);
            }
            break;
        case 0xB2: //LSS
            dec_modrm();
            exec_load_seg(SEG_REG_SS);
            break;
        case 0xB4://LFS
            dec_modrm();
            exec_load_seg(SEG_REG_FS);
            break;
        case 0xB5://LGS
            dec_modrm();
            exec_load_seg(SEG_REG_GS);
            break;
        case 0xc1://xadd
            dec_modrm();
            if(operand_size()==16){
				if(rm_is_reg){
                    write16BitReg(reg2,exec_xadd_16b(read16BitReg(reg2)));
					break;
				}
				u_int16_t *data=(u_int16_t*)get_mem_data();
				*data = exec_xadd_16b(*data);
			}
			else {
				if(rm_is_reg){
                    write32BitReg(reg2,exec_xadd_32b(read32BitReg(reg2)));
					break;
				}
				u_int32_t *data=(u_int32_t*)get_mem_data();
				*data = exec_xadd_32b(*data);
			}
			break;
        case 0xB0:// CMPXCHG  r/m8,r8
            dec_modrm();
            exec_cmpxchg_8b(read8BitReg(reg1));
            break;
        case 0xB1://CMPXCHG   r/m16/32,r16/r32
             dec_modrm();
             if(operand_size()==16)
                exec_cmpxchg_16b(read16BitReg(reg1));
            else
                exec_cmpxchg_32b(read32BitReg(reg1));
            break;
        case 0xA2://CPUID
            exec_cpuid();
            break;
        case 0xAF://imul r16/32,r/m 16/32
            dec_modrm();
            exec_imul_16_32b(2,0);
            break;
		default:
		{
            if((*curInst&0xF8)==0xC8)  //BSWAP
			{
                exec_bswap(*curInst&07);
                break;
			}
			else if(*curInst&0xF0==0x80){ //Jcc imm16/32
                 Bit32s disp;
                 if(operand_size()==16) {
                    disp=*(Bit16s*)(curInst+1);
                    immLen=2;
                }else{
                   disp=*(Bit32s*)(curInst+1);
                    immLen=4;
                }
                if(conditions_judge(*curInst&0x0F)){
                    nojmp=0;
                    EIP=EIP+disp;
                    if(operand_size()==16) EIP=EIP&0xFFFF;
                }
                break;
			}
			else if((*curInst&0xF0)==0x90){ //SETcc
               dec_modrm();
               if(conditions_judge(*curInst&0x0F)){
                    if(rm_is_reg)
                    {
                        reg2=1;
                    }
                    else
                    {
                        u_int8_t *data=get_mem_data();
                        *data = 1;
                    }
                }
                else{
                    if(rm_is_reg)
                    {
                        reg2=0;
                    }
                    else
                    {
                        u_int8_t *data=get_mem_data();
                        *data = 0;
                    }
                }
			}
			printf("#UD exception\n");
			exit(0);
		}
	}
	if(nojmp) EIP=EIP+instLen+prefixLen+immLen+1;
}
