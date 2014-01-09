#include <systemc.h>

SC_MODULE(alu)
{
	// signal declaration
	sc_in<sc_logic>		enable;
	sc_in<sc_logic>		reset;
	sc_in<sc_lv<6> >	op;
	sc_in<sc_lv<5> >	sub_op;
	sc_in<sc_lv<32> >	src1;
	sc_in<sc_lv<32> >	src2;

	sc_out<sc_lv<32> >	output;
	sc_out<sc_logic>	overflow;

	// fuction declaration
	void method_func();

	private:
	sc_int<33> num_temp_src1, num_temp_src2;
	sc_lv<33> temp_src1, temp_src2, temp;
	sc_lv<32> t_src1, t_src2, result;

	public:
	//Constructor 
	SC_CTOR(alu) {
		SC_METHOD(method_func);
		sensitive << reset << enable << op << sub_op << src1 << src2;
	}
};
