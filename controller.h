#include <systemc.h>

SC_MODULE(controller)
{

	// 輸入訊號
	sc_in<sc_lv<32> >	instruction;
	
	
	// 輸出訊號	(mux)
	sc_out<sc_logic  >	imm_reg_select;
	sc_out<sc_lv<2> >	write_back_select;
	sc_out<sc_lv<2> >	signexsel;
	
	// 輸出訊號 (alu)
	sc_out<sc_lv<6> >	op;
	sc_out<sc_lv<5> >	sub_op;
	sc_out<sc_logic >	enable;
	
	// 輸出訊號 (reg)
	sc_out<sc_logic >	regwrite;	
	sc_out<sc_logic >	regread;
	
	// 輸出訊號 (datamem)
	sc_out<sc_logic >	datawrite;	
	sc_out<sc_logic >	dataread;
	
	
	// sc_interface
	//** void datamem_rw();

	// fuction declaration
	void method_func();
	sc_logic t;
	sc_logic f;

	// 內部使用的接線
	private:
	sc_lv<32> t_instruction;
	sc_lv<6> 	inop;
	sc_lv<5> 	insub_op;
	sc_lv<8> 	insub_op2;
	
	public:
	//Constructor 
	SC_CTOR(controller) {
		t = '1';
		f = '0';
		SC_METHOD(method_func);
		sensitive << instruction;
	}
};
