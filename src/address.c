#include "global.h"
//get address size : 32 or 16
u_int8_t address_size(){
	if(REAL_MODE){
		u_int8_t addressSize=prefix_address?32:16;
		return addressSize;
	}
	DEBUG("cs.d_b:%d,prefix:%d\n",CSDesc.d_b,prefix_address);
	return ((CSDesc.d_b-prefix_address)==0)?16:32;
} 
u_int8_t operand_size(){
	if(REAL_MODE){
		u_int8_t operandSize=prefix_operand?32:16;
		return operandSize;
	}
	return ((CSDesc.d_b-prefix_operand)==0)?16:32;
} 

u_int8_t stack_address_size(){
	
	return SSDesc.d_b?32:16;
} 
