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
	sc_in<sc_logic>		reset;
	sc_in<sc_lv<32> >	instruction;

	sc_out<sc_logic >	overflow;
	
	// alu
	sc_signal<sc_lv<1> >    enable;
	sc_signal<sc_lv<6> >	op;
	sc_signal<sc_lv<5> >	sub_op;
	sc_signal<sc_lv<32> >	src1;
	sc_signal<sc_lv<32> >	src2;

	sc_signal<sc_lv<32> >	output;
	sc_signal<sc_lv<1> >	overflow;
	
	// signal declaration	reg
	
	sc_signal<sc_lv<1> >		write;	
	sc_signal<sc_lv<1> >		read;

	sc_signal<sc_lv<5> >	r1_addr;
	sc_signal<sc_lv<5> >	r2_addr;
	sc_signal<sc_lv<5> >	rw_addr;
	sc_signal<sc_lv<32> >	rw_data;

	sc_signal<sc_lv<32> >	r1_data;
	sc_signal<sc_lv<32> >	r2_data;
	
	// signal declaration	datamem
	sc_signal<sc_lv<1> >		datawrite;	
	sc_signal<sc_lv<1> >		dataread;

	sc_signal<sc_lv<18> >	addr;
	sc_signal<sc_lv<32> >	in_data;

	sc_signal<sc_lv<32> >	out_data;
	
	// ZS
	sc_signal<sc_lv<32> >	zsout1;
	sc_signal<sc_lv<32> >	zsout2;
	sc_signal<sc_lv<32> >	zsout3;
	sc_signal<sc_lv<32> >	zsout4;
	
	// signal declaration	mux
	sc_signal<sc_lv<1> >	m21sel;
	sc_signal<sc_lv<2> >	m31sel;
	sc_signal<sc_lv<2> >	m41sel;
	
	sc_signal<sc_lv<32> >	m21out;
	sc_signal<sc_lv<32> >	m31out;
	sc_signal<sc_lv<32> >	m41out;

	// fuction declaration
	void method_func();

	// sub-module
	private:
	controller		*con0;
	alu 			*alu0;
	reg				*reg0;
	datamem			*datamem0;
	ZS_extension	*zs0;
	
	two_one_mux *m21;
	three_one_mux *m31;
	four_one_mux *m41;
	

	//Constructor 
	public:
	SC_CTOR(top){
		con0 = new controller("con0");
		alu0 = new alu("alu0");
		reg0 = new reg("reg0");
		datamem0 = new datamem("datamem0")
		zs0 = new ZS_extension("zs0");
		m21 = new two_one_mux("m21");
		m31 = new three_one_mux("m31");
		m41 = new four_one_mux("m41");
		
		reg0->clock(clock);
		reg0->write(write);
		reg0->read(read);
		reg0->reset(reset);
		
		reg0->r1_addr(r1_addr);
		reg0->r2_addr(r2_addr);
		
		reg0->rw_addr(rw_addr);
		reg0->rw_data(wd); //
		reg0->r1_data(r1_data);
		reg0->r2_data(r2_data);

		alu0->op(op);
		alu0->sub_op(sub_op);
		alu0->src1(r1_data);
		alu0->src2(r2_data);
		alu0->overflow(overflow);
		alu0->output(output);

		wbmux0->in1(output);
		wbmux0->sel(sel);
		wbmux0->out(wd);
	}
		
};
