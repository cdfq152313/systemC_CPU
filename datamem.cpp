#include "datamem.h"

void datamem::thread_func()
{
	while(1){
		if(reset.read()  == '1'){
			// clear registers
			for(int a = 0 ; a <  262144 ; a++){
				mem[a] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
			}
			// clear output
			out_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
		}else{
			//32bits -> 18bits
			t = addr.read();
			t_addr = t.range(17,0);
			
			// if write enable
			if(write.read()  == '1'){
				mem[t_addr.to_uint()] = in_data.read();
				out_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
			}
			// if read enable
			if(read.read()  == '1' ){
				out_data.write(mem[t_addr.to_uint()]);
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


