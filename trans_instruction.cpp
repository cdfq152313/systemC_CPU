#include "trans_instruction.h"

void trans_instruction::method_func()
{
	c_instruction= instruction.read();
	r1_addr = instruction.read().range(24,20);
	r2_addr = instruction.read().range();
	rw_addr = instruction.read().range();
	zs1 = instruction.read().range();
	zs2 = instruction.read().range();
	zs3 = instruction.read().range();
}
