#include "ZS_extension.h"

void ZS_extension::method_func()
{
	
	//read data
	t_src1 = src1.read();
	t_src2 = src2.read();
	t_src3 = src3.read();
	
	//extension
	//out1
	t_out1 = ("000000000000000000000000000", t_src1);
	
	//out2
	if(t_src2[31] == '1')
		t_out2 = ("11111111111111111", t_src2);
	else
		t_out2 = ("00000000000000000", t_src2);
	
	//out3
	t_out3 = ("00000000000000000", t_src2);
	
	//out4
	if(t_src3[31] == '1')
		t_out4 = ("111111111111", t_src3);
	else
		t_out4 = ("000000000000", t_src3);
	
	//output
	out1.write(t_out1);
	out2.write(t_out2);
	out3.write(t_out3);
	out4.write(t_out4);
}


