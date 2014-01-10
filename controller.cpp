#include "controller.h"

void controller::method_func()
{

	//讀入接線
	t_instruction = instruction.read();
	//讀取op, 讀取sub_op
	inop  		= t_instruction.range(30,25);
	insub_op 	= t_instruction.range(4,0);
	insub_op 	= t_instruction.range(7,0);
	
	
	// 反正alu都是要動啊 ...
	enable="1";
	
	//依照op來輸出值
	if(inop=="100000"){ 
		// NOP ADD SUB AND OR XOR
		// 輸出訊號 (mux)
		regwrite="1";
		regread="1";
		imm_reg_select="0";
		write_back_select="10";
		signexsel="01";
				
		// 輸出訊號 (datamem)
		datawrite="0";	
		dataread="0";
	}
	else if(inop=="101000" || inop=="101100" || inop=="101011" || inop=="100010"){
		//ADDI ORI XORI MOVI
		// 輸出訊號 (mux)
		regwrite="1";
		regread="1";
		imm_reg_select="1";
		write_back_select="01";
		
				
		// 輸出訊號 (datamem)
		datawrite="0";	
		dataread="0";
		
		if(inop=="100010")//MOVI
			signexsel="11";
		else if(inop=="101000")//ADDI
			signexsel="01";
		else{//ORI , XORI
			signexsel="10";
		}
	}
	else if(inop=="011100"){
		//LW SW
		// 輸出訊號 (mux)	
		imm_reg_select="0";
		write_back_select="10";
		signexsel="00";
		regread="1";
		
		
		//看sub_op
		if(insub_op2=="00000010"){//LW
			regwrite="1";
			// 輸出訊號 (datamem)
			datawrite="0";	
			dataread="1";
		}
		else if(insub_op2=="00001010"){//SW
			regwrite="0";
			// 輸出訊號 (datamem)
			datawrite="1";	
			dataread="0";
		}
	}
	
	// 輸出訊號 (alu)
	op= inop;
	sub_op = insub_op;
}
