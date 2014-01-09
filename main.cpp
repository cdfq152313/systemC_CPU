#include <systemc.h>
#include "newtop.h"
#include "test_define.h"

int sc_main(int argc, char* argv[])
{
	
	// signal declaration
	sc_clock		clk("clk", 1, SC_US, 0.5);
	sc_signal<sc_lv<1> >	write;
	sc_signal<sc_lv<1> >	read;
	sc_signal<sc_lv<1> >	reset;

	sc_signal<sc_lv<18> >	addr;		// 32 KBytes
	sc_signal<sc_lv<32> >	in_data;	// 4 Bytes

	sc_signal<sc_lv<32> >	out_data;

	sc_signal<sc_lv<32> >	instruction;

	// module declaration
	newtop		top0("top0");

	// signal connection
	top0.clock(clk);
	top0.instruction(instruction);
	top0.reset(reset);
	/*
	// Open VCD file
  	sc_trace_file *wf = sc_create_vcd_trace_file("test_DM_wave");
  	wf->set_time_unit(1, SC_NS);

	// error counter for tb
	int tb_error = 0;
	sc_lv<32> temp_output;
    	
	// set signal to .vcd wave file
	sc_trace(wf,clk,"clk");
	sc_trace(wf,write,"write");
	sc_trace(wf,read,"read");
	sc_trace(wf,reset,"reset");	
	sc_trace(wf,addr,"addr");
	sc_trace(wf,in_data,"in_data");
	sc_trace(wf,out_data,"out_data");

	// init
	write = sc_logic('0');
	read = sc_logic('0');
	reset = sc_logic('0');
	
	addr = sc_lv<18>("000000000000000000");
	in_data = sc_lv<32>("00000000000000000000000000000000");

	// run simulation
	sc_start(0,SC_US);
  	
	// start testing here
	for(int i=0 ; i<SIZE_OF_TEST ; i++)
	{
		read = sc_logic(read_list[i]);
		write = sc_logic(write_list[i]);
		reset = sc_logic(reset_list[i]);
		addr = sc_lv<18>(addr_list[i]);
		in_data = sc_lv<32>(in_data_list[i]);

		// add simulation time	
		sc_start(1,SC_US);

		cout << "@" << sc_time_stamp() <<" ,read : " << read << " ,write : " << write
		     << " ,reset : " << reset << " ,addr : " << addr << " ,in_data : " << in_data
		     << " ,out_data : " << out_data << endl;

		// error check!
		temp_output = out_data_list[i];
		if(out_data.read() != temp_output){
			tb_error++;
#ifdef REG_DEBUG
			cout << " error! " << endl;
#endif
		}
	}

	if(tb_error != 0)
		cout << tb_error << " errors!" << endl;
	else
		cout << "pass!" << endl;

	sc_start(2,SC_NS);
	sc_close_vcd_trace_file(wf);
	*/
	return 0;
}
