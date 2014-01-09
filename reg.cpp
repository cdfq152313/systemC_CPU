#include "reg.h"

void reg::thread_func()
{
	while(1){
		if(reset.read()  == '1'){
			// clear registers
			for(int i = 0; i < 32; ++i)
				reg_[i] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
			// clear output
			r1_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
			r2_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
		}else{
			// if write enable
			if(write.read()  == '1'){
				//write_back data
				reg_[rw_addr.read().to_uint()] = rw_data.read();
				r1_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
				r2_data.write(sc_lv<32>("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"));
			}
			// if read enable
			if(read.read()  == '1' ){
				//r1 data, r2 data
				r1_data.write((reg_[r1_addr.read().to_unit()]));
				r2_data.write((reg_[r2_addr.read().to_unit()]));
			}
		}
#ifdef REG_DEBUG		
		cout << "#" << sc_time_stamp()  <<" ,reg_ : "<< reg_
		<<" ,read : "<< read.read()    <<",write : "<< write.read()
		<<" ,input_rw : "<< rw_data.read() <<" ,output_r1 : "<< r1_data.read() << endl;
#endif

		// wait next clock	
		wait();
	}
}


