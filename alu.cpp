#include "alu.h"

void alu::method_func()
{
	if(enable.read() == '1'){
		overflow.write(SC_LOGIC_0);
		
		if(sub_op.read() == "00000"){ //NOP
			result = "00000000000000000000000000000000";
		}
		else if(sub_op.read() == "00001"){ // ADD
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read();
			// extend src1
			if(t_src1[31] == '1')
				num_temp_src1 = temp_src1 = ("1",t_src1);
			else
				num_temp_src1 = temp_src1 = ("0",t_src1);
			// extend src2
			if(t_src2[31] == '1')
				num_temp_src2 = temp_src2 = ("1",t_src2);
			else
				num_temp_src2 = temp_src2 = ("0",t_src2);

			// excute add
			temp = num_temp_src1 + num_temp_src2;
			
			if(temp[31] != temp[32])
				overflow.write(SC_LOGIC_1);
			else
				overflow.write(SC_LOGIC_0);
			result = temp.range(31,0);
		}
		else if(sub_op.read() == "00010") {//SUB
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read
			// extend src1
			if(t_src1[31] == '1')
				num_temp_src1 = temp_src1 = ("1",t_src1);
			else
				num_temp_src1 = temp_src1 = ("0",t_src1);
			// extend src2
			if(t_src2[31] == '1')
				num_temp_src2 = temp_src2 = ("1",t_src2);
			else
				num_temp_src2 = temp_src2 = ("0",t_src2);

			// excute sub
			temp = num_temp_src1 - num_temp_src2;

			if(temp[31] != temp[32])
				overflow.write(SC_LOGIC_1);
			else
				overflow.write(SC_LOGIC_0);
			result = temp.range(31,0);
		}
		else if(sub_op.read() ==  "00011") {//AND
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read
			// excute AND
			result = t_src1 & t_src2;
		}
		else if(sub_op.read() ==  "00100") {//OR
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read
			// excute OR
			result = t_src1 | t_src2;
		}
		else if(sub_op.read() ==  "00101") {//XOR
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read
			// excute OR
			result = t_src1 ^ t_src2;
		}
		else if(sub_op.read() ==  "00110") {//SRLI
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read

			num_temp_src1=temp_src1 = ("0",t_src1);
			num_temp_src2=temp_src2 = ("0",t_src2);
			temp = num_temp_src1 >> num_temp_src2;
			result = temp.range(31,0);
			
		}
		else if(sub_op.read() ==  "00111") {//SLL
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read
			
			num_temp_src1=temp_src1 = ("0",t_src1);
			num_temp_src2=temp_src2 = ("0",t_src2);
			temp = num_temp_src1 << num_temp_src2;
			result = temp.range(31,0);
		}
		else if(sub_op.read() ==  "01000") {//ROTR
			t_src1 = src1.read(); // src1 read
			t_src2 = src2.read(); // src2 read

			num_temp_src1=temp_src1 = ("0",t_src1);
			num_temp_src2=temp_src2 = ("0",t_src2);
			temp = num_temp_src1 >> num_temp_src2;

			// Let temp_src1.range(src2-1 0) be at the top of temp
			if(num_temp_src2>0)
				temp.range(31,31-num_temp_src2+1) = 
				temp_src1.range(num_temp_src2-1,0);
			
			result = temp.range(31,0);
		}
		else{
			result = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
		}
		
		output.write(result);

#ifdef ALU_DEBUG
		cout << "#" << sc_time_stamp()  <<" ,temp_src1 : " << temp_src1 
		<<" ,temp_src2 : " << temp_src2 <<" ,result : "    << result
		<<" ,output : "    << output    <<",overflow : "   << overflow << endl;
#endif
	}else{
		output.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
		overflow.write(sc_logic('X'));
	}
}


