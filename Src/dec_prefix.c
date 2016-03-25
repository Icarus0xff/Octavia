#include "global.h"
void dec_prefix(){
	prefixLen=0;
	u_int8_t isPrefix=0;
	prefix_lock=0;
	prefix_rep=0;
	prefix_seg=7;
	prefix_2byte=0;
	prefix_operand=0;
	prefix_address=0;
	do{
		switch(*curInst){
			case 0xF2:  //group1 repne/repnz
				prefix_rep=1;
				isPrefix=1;
				break;
			case 0xF3: //group1 rep
				prefix_rep=2;
				isPrefix=1;
				break;
			case 0xF0://group1 lock
				prefix_lock=1;
				isPrefix=1;
				break;
			case 0x26://group2 ES
				prefix_seg=0;
				isPrefix=1;
				break;
			case 0x2E://group2 ES
				prefix_seg=1;
				isPrefix=1;
				break;
			case 0x36://group2 SS
				prefix_seg=2;
				isPrefix=1;
				break;
			case 0x3E://group2 DS
				prefix_seg=3;
				isPrefix=1;
				break;
			case 0x64://group2 FS
				prefix_seg=4;
				isPrefix=1;
				break;
			case 0x65://group2 GS
				prefix_seg=5;
				isPrefix=1;
				break;
			case 0x66://group3 operand-size
				prefix_operand=1;
				isPrefix=1;
				break;
			case 0x67://group4 Address-size
				prefix_address=1;
				isPrefix=1;
				break;
			case 0x0F:
				prefix_2byte=1;
				break;
			default:
				isPrefix=0;

		}
		if(isPrefix||prefix_2byte){
			prefixLen++;
			curInst++;
		}
	}while(isPrefix);
//	DEBUG("prefix length:%d\n",prefixLen);
}

//isCmpOp is used to distinguish REP（0） and REPE／REPNE(1）
u_int8_t rep_condition(u_int8_t isCmpOp){
        u_int8_t terminal;
        if(operand_size()==16)
            terminal=(--CX==0);
        else
            terminal=(--ECX==0);
        if(isCmpOp){
                if(prefix_rep==1) {//REPNE
                      terminal|=get_flag(ZF);
                }
                else { //REPE
                     terminal|=~get_flag(ZF);
                }
        }
}
