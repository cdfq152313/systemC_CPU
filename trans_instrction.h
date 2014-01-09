#include <systemc.h>

SC_MODULE(trans_instruction)
{
	// signal declaration
	sc_in<sc_lv<32> >	instruction;
	
	sc_out<sc_lv<32> >	c_instruction;
	sc_out<sc_lv<5> >	r1_addr;
	sc_out<sc_lv<5> >	r2_addr;
	sc_out<sc_lv<5> >	rw_addr;
	sc_out<sc_lv<5> >	zs1;
	sc_out<sc_lv<15> >	zs2;
	sc_out<sc_lv<20> >	zs3;
	
	// fuction declaration
	void thread_func();

	public:
	//Constructor 
	SC_CTOR(reg) {
		SC_METHOD(method_func);
		dont_initialize();
		sensitive << instruction;
	}
};
