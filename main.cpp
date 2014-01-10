#include <systemc.h>
#include "test_define.h"
#include "top.h"

int sc_main(int argc, char* argv[])
{
	// signal declaration
	sc_clock		clk("clk", 1, SC_US, 0.5);
	sc_signal<sc_logic>	reset;

	sc_signal<sc_lv<32> >	instruction;
	sc_signal<sc_logic> overflow;

	// module declaration
	top		top0("top0");

	// signal connection
	top0.clock(clk);
	top0.reset(reset);
	top0.instruction(instruction);
	top0.overflow(overflow);

	// Open VCD file
  	sc_trace_file *wf = sc_create_vcd_trace_file("test_DM_wave");
  	wf->set_time_unit(1, SC_NS);

	// error counter for tb
	int tb_error = 0;
    	
	// set signal to .vcd wave file
	sc_trace(wf,clk,"clk");
	sc_trace(wf,instruction,"instruction");
	sc_trace(wf,overflow,"overflow");
	sc_trace(wf,reset,"reset");	
	sc_trace(wf,top0.r1_data,"r1_data");
	sc_trace(wf,top0.r2_data,"r2_data");
	sc_trace(wf,top0.r3_data,"r3_data");
	sc_trace(wf,top0.out_data,"mem_output");
	sc_trace(wf,top0.alu_output,"alu_output");
	sc_trace(wf,top0.m31out,"rw_data");


	// init
	reset = sc_logic('0');
	instruction = sc_lv<32>("00000000000000000000000000000000");

	// run simulation
	sc_start(0,SC_US);
  	instruction = sc_lv<32>("01000100000000000000001111111111");
  	sc_start(1,SC_US);
  	
  	cout << "@" << sc_time_stamp() << endl
		<<	"instruction : " << instruction << endl
		<< "reset : " << reset << endl
		<< "r1data :" << top0.r1_data << endl
		<< "r2data :" << top0.r2_data << endl
		<< "r3data :" << top0.r3_data << endl
		<< "mem_output :" << top0.out_data << endl
		<< "alu_output :" << top0.alu_output << endl
		<< "rw_data :" << top0.m31out << endl

		<< endl;
  	/*
	// start testing here
	for(int i=0 ; i<SIZE_OF_TEST ; i++)
	{
		instruction = sc_lv<32>(in_data_list[i]);

		// add simulation time	
		sc_start(1,SC_US);

		cout << "@" << sc_time_stamp() <<" ,instruction : " << instruction << " ,reset : " << reset
		     << endl;

		// error check!
		
		temp_output = out_data_list[i];
		if(out_data.read() != temp_output){
			tb_error++;
#ifdef REG_DEBUG
			cout << " error! " << endl;
#endif
		}
		
	}
	*/
	if(tb_error != 0)
		cout << tb_error << " errors!" << endl;
	else
		cout << "pass!" << endl;

	sc_start(2,SC_NS);
	sc_close_vcd_trace_file(wf);
	
	return 0;
}
