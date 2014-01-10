#include <systemc.h>

SC_MODULE(datamem)
{
	// signal declaration
	sc_in_clk		clock;
	sc_in<sc_logic>		write;	
	sc_in<sc_logic>		read;
	sc_in<sc_logic>		reset;

	sc_in<sc_lv<32> >	addr;
	sc_in<sc_lv<32> >	in_data;

	sc_out<sc_lv<32> >	out_data;

	// sc_interface
	//** void datamem_rw();

	// fuction declaration
	void thread_func();

	private:
	sc_lv<32>		mem[2^18];
	sc_lv<32>	t;
	sc_lv<18>	t_addr;
	
	public:
	//Constructor 
	SC_CTOR(datamem) {
		SC_THREAD(thread_func);
		dont_initialize();
		sensitive << clock.pos();
	}
};
