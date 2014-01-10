#include <systemc.h>

SC_MODULE(reg)
{
	// signal declaration
	sc_in_clk		clock;
	sc_in<sc_logic>		write;	
	sc_in<sc_logic>		read;
	sc_in<sc_logic>		reset;

	sc_in<sc_lv<5> >	r1_addr;
	sc_in<sc_lv<5> >	r2_addr;
	sc_in<sc_lv<5> >	rw_addr;
	sc_in<sc_lv<32> >	rw_data;

	sc_out<sc_lv<32> >	r1_data;
	sc_out<sc_lv<32> >	r2_data;
	sc_out<sc_lv<32> >	r3_data;
	
	// fuction declaration
	void thread_func();

	private:
	sc_lv<32>		reg_[32];

	public:
	//Constructor 
	SC_CTOR(reg) {
		SC_THREAD(thread_func);
		dont_initialize();
		sensitive << clock.pos();
	}
};
