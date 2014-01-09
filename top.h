#include <systemc.h>
#include "alu.h"
#include "reg.h"
#include "datamem.h"
#include "controller.h"
#include "two_one_mux.h"
#include "three_one_mux.h"
#include "four_one_mux.h"
#include "ZS_extension.h"

SC_MODULE(top)
{
	// signal declaration
	sc_in_clk		clock;
	sc_in<sc_logic>		write;	
	sc_in<sc_logic>		read;
	sc_in<sc_logic>		reset;

	sc_in<sc_lv<18> >	addr;
	sc_in<sc_lv<32> >	in_data;

	sc_out<sc_lv<32> >	out_data;

	// fuction declaration
	void method_func();

	// sub-module
	private:
	datamem 		datamem0;

	//Constructor 
	public:
	SC_CTOR(top):
		datamem0("datamem0") {
		// link signals
		datamem0.clock(clock);
		datamem0.write(write);
		datamem0.read(read);
		datamem0.reset(reset);
		datamem0.addr(addr);
		datamem0.in_data(in_data);		
		datamem0.out_data(out_data);
	}
};
