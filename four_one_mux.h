#include <systemc.h>
//兩個32bits近來 , 一個選擇信號 , 一個32bits輸出
SC_MODULE(four_one_mux)
{

	// 輸入訊號
	sc_in<sc_lv<32> >	first;
	sc_in<sc_lv<32> >	second;
	sc_in<sc_lv<32> >	third;
	sc_in<sc_lv<32> >	forth;
	sc_in<sc_lv<2> >	sel;
	
	// 輸出訊號	(mux)
	sc_out<sc_lv<32> >	out;
	
	
	// sc_interface
	//** void datamem_rw();

	// fuction declaration
	void method_func();

	// 內部使用的接線
	private:
	public:
	//Constructor 
	SC_CTOR(four_one_mux) {
		SC_METHOD(method_func);
		sensitive << first << second << third << forth << sel;// << sub_op << src1 << src2;
	}
};
