#include <systemc.h>

SC_MODULE(ZS_extension)
{
	// signal declaration
	sc_in<sc_lv<5> >	src1;
	sc_in<sc_lv<15> >	src2;
	sc_in<sc_lv<20> >	src3;

	sc_out<sc_lv<32> >	out1;
	sc_out<sc_lv<32> >	out2;
	sc_out<sc_lv<32> >	out3;
	sc_out<sc_lv<32> >	out4;
	

	// fuction declaration
	void method_func();

	private:
	sc_lv<5> t_src1;
	sc_lv<15> t_src2;
	sc_lv<20> t_src3;
	sc_lv<32> t_out1, t_out2, t_out3, t_out4;

	public:
	//Constructor 
	SC_CTOR(ZS_extension) {
		SC_METHOD(method_func);
		sensitive << src1 << src2 << src3;
	}
};
