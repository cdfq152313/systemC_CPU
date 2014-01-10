#include "trans_instruction.h"

void trans_instruction::method_func()
{
	temp = instruction.read();
	c_instruction= temp;
	r1_addr = temp.range(24,20);
	r2_addr = temp.range(19,15);
	rw_addr = temp.range(14,10);
	zs1 = temp.range(14,10);
	zs2 = temp.range(14,0);
	zs3 = temp.range(19,0);
}
