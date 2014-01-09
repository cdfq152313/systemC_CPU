#include "datamem.h"

void datamem::thread_func()
{
	while(1){
		if(reset.read()  == '1'){
			// clear registers
			for(int a = 0 ; a <  2^18 ; a++){
				mem[a] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
			}
			// clear output
			out_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
		}else{
			// if write enable
			if(write.read()  == '1'){
				mem[addr.read().to_uint()] = in_data.read();
				out_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
			}
			// if read enable
			if(read.read()  == '1' ){
				out_data.write(mem[addr.read().to_uint()]);
			}
		}	
#ifdef REG_DEBUG		
		cout << "#" << sc_time_stamp() <<" ,read : " << read << " ,write : " << write
		     << " ,reset : " << reset << " ,addr : " << addr << " ,in_data : " << in_data
		     << " ,out_data : " << out_data << endl;
#endif

		// wait next clock	
		wait();
	}
}


