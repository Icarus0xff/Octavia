#include "global.h"
//eflags operation
u_int8_t get_flag(u_int8_t FLAG){
	return (eflags&(1<<FLAG))>0;
}
void set_flag(u_int8_t FLAG){
	eflags=eflags|(1<<FLAG);
}
void clear_flag(u_int8_t FLAG){
	eflags=eflags|(~(0xFFFFFFFF&(1<<FLAG)));
}
u_int8_t get_iopl(){
	return (eflags<<18)>>30;
}

int8_t conditions_judge(u_int8_t condition){
    switch(condition){
        case 0: return get_flag(OF)==1;
        case 1: return get_flag(OF)==0;
        case 2: return get_flag(CF)==1;
        case 3: return get_flag(CF)==0;
        case 4: return get_flag(ZF)==1;
        case 5: return get_flag(ZF)==0;
        case 6: return get_flag(CF)==1|| get_flag(ZF)==1;
        case 7:return get_flag(CF)==0&&get_flag(ZF)==0;
        case 8:return get_flag(SF)==1;
        case 9:return get_flag(SF)==0;
        case 10:return get_flag(PF)==1;
        case 11:return get_flag(PF)==0;
        case 12:return get_flag(SF)!=get_flag(OF);
        case 13:return get_flag(SF)==get_flag(OF);
        case 14:return get_flag(SF)!=get_flag(OF)||get_flag(ZF)==1;
        case 15: return get_flag(SF)==get_flag(OF)&&get_flag(ZF)==0;
        default: ;
    }
    return 0;
}

