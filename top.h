#include <systemc.h>
#include "alu.h"
#include "reg.h"
#include "datamem.h"
#include "controller.h"
#include "two_one_mux.h"
#include "three_one_mux.h"
#include "four_one_mux.h"
#include "ZS_extension.h"
#include "trans_instruction.h"

SC_MODULE(top)
{
	// input
	sc_in_clk		clock;
	sc_in<sc_logic>		reset;
	sc_in<sc_lv<32> >	instruction;
	// output
	sc_out<sc_logic >	overflow;
	
	// signal declaration
	//controller
	sc_signal<sc_lv<32> > c_instruction;
	
	// alu
	sc_signal<sc_logic >    enable;
	sc_signal<sc_lv<6> >	op;
	sc_signal<sc_lv<5> >	sub_op;

	sc_signal<sc_lv<32> >	alu_output;
	
	// signal declaration	reg
	sc_signal<sc_logic>		regwrite;	
	sc_signal<sc_logic>		regread;

	sc_signal<sc_lv<5> >	r1_addr;
	sc_signal<sc_lv<5> >	r2_addr;
	sc_signal<sc_lv<5> >	rw_addr;
	sc_signal<sc_lv<32> >	rw_data;

	sc_signal<sc_lv<32> >	r1_data;
	sc_signal<sc_lv<32> >	r2_data;
	sc_signal<sc_lv<32> >	r3_data;
	
	// signal declaration	datamem
	sc_signal<sc_logic >		datawrite;	
	sc_signal<sc_logic >		dataread;

	sc_signal<sc_lv<32> >	addr;
	sc_signal<sc_lv<32> >	in_data;

	sc_signal<sc_lv<32> >	out_data;
	
	// ZS
	sc_signal<sc_lv<5> >	zsin1;
	sc_signal<sc_lv<15> >	zsin2;
	sc_signal<sc_lv<20> >	zsin3;
	
	sc_signal<sc_lv<32> >	zsout1;
	sc_signal<sc_lv<32> >	zsout2;
	sc_signal<sc_lv<32> >	zsout3;
	sc_signal<sc_lv<32> >	zsout4;
	
	// signal declaration	mux
	sc_signal<sc_logic >	m21sel;
	sc_signal<sc_lv<2> >	m31sel;
	sc_signal<sc_lv<2> >	m41sel;
	
	sc_signal<sc_lv<32> >	m21out;
	sc_signal<sc_lv<32> >	m31out;
	sc_signal<sc_lv<32> >	m41out;
	
	
	

	// fuction declaration
	void method_func();

	// sub-module
	private:
	trans_instruction *t0;
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
		
		t0 = new trans_instruction("t0");
		con0 = new controller("con0");
		alu0 = new alu("alu0");
		reg0 = new reg("reg0");
		datamem0 = new datamem("datamem0");
		zs0 = new ZS_extension("zs0");
		m21 = new two_one_mux("m21");
		m31 = new three_one_mux("m31");
		m41 = new four_one_mux("m41");
		
		
		//translate instruction
		t0->instruction(instruction);
		
		t0->c_instruction(c_instruction);
		t0->r1_addr(r1_addr);
		t0->r2_addr(r2_addr);
		t0->rw_addr(rw_addr);
		t0->zs1(zsin1);
		t0->zs2(zsin2);
		t0->zs3(zsin3);
	
		
		//controller
		con0->instruction(c_instruction);
		con0->imm_reg_select(m21sel);
		con0->write_back_select(m31sel);
		con0->signexsel(m41sel);
		con0->op(op);
		con0->sub_op(sub_op);
		con0->enable(enable);
		con0->regwrite(regwrite);
		con0->regread(regread);
		con0->datawrite(datawrite);
		con0->dataread(dataread);

		//register
		reg0->clock(clock);
		reg0->write(regwrite);
		reg0->read(regread);
		reg0->reset(reset);
		
		reg0->r1_addr(r1_addr);
		reg0->r2_addr(r2_addr);
		reg0->rw_addr(rw_addr);
		reg0->rw_data(m31out);
		
		reg0->r1_data(r1_data);
		reg0->r2_data(r2_data);
		reg0->r3_data(r3_data);
		
		//alu
		alu0->enable(enable);
		alu0->reset(reset);
		alu0->op(op);
		alu0->sub_op(sub_op);
		alu0->src1(r1_data);
		alu0->src2(r2_data);
		alu0->overflow(overflow);
		alu0->output(alu_output);
		
		
		//datamem
		datamem0->clock(clock);
		datamem0->write(datawrite);
		datamem0->read(dataread);
		datamem0->reset(reset);
		datamem0->addr(alu_output);
		datamem0->in_data(r3_data);
		
		datamem0->out_data(out_data);
		
		//zero signed extension
		zs0->src1(zsin1);
		zs0->src2(zsin2);
		zs0->src3(zsin3);
		
		zs0->out1(zsout1);
		zs0->out2(zsout2);
		zs0->out3(zsout3);
		zs0->out4(zsout4);
		
		//two_one_mux
		m21->first(r2_data);
		m21->second(m41out);
		m21->sel(m21sel);
		
		m21->out(m21out);
		
		//three_one_mux
		m31->first(m21out);
		m31->second(alu_output);
		m31->third(out_data);
		m31->sel(m31sel);
		
		m31->out(m31out);

		//four_one_mux
		m41->first(zsout1);
		m41->second(zsout2);
		m41->third(zsout3);
		m41->forth(zsout4);
		m41->sel(m41sel);
		
		m41->out(m41out);
		
		/*
		//translate instruction
		t0->instruction(instruction);
		
		//controller
		con0->instruction(t0->c_instruction);
		
		//register
		reg0->clock(clock);
		reg0->write(con0->regwrite);
		reg0->read(con0->regread);
		reg0->reset(reset);
		
		reg0->r1_addr(t0->r1_addr);
		reg0->r2_addr(t0->r2_addr);
		reg0->rw_addr(t0->rw_addr);
		reg0->rw_data(m31->out);
		
		//alu
		alu0->enable(con0->enable);
		alu0->reset(reset);
		alu0->op(con0->op);
		alu0->sub_op(con0->sub_op);
		alu0->src1(reg0->r1_data);
		alu0->src2(reg0->r2_data);
		alu0->overflow(overflow);
		

		//datamem
		datamem0->clock(clock);
		datamem0->write(con0->datawrite);
		datamem0->read(con0->dataread);
		datamem0->reset(reset);
		datamem0->addr(alu0->output);
		datamem0->in_data(reg0->r3_data);
		
		
		//zero signed extension
		zs0->src1(t0->zs1);
		zs0->src2(t0->zs2);
		zs0->src3(t0->zs3);
		
		//two_one_mux
		m21->first(reg0->r2_data);
		m21->second(m41->out);
		m21->sel(con0->imm_reg_select);
		
		//three_one_mux
		m31->first(m21->out);
		m31->second(alu0->output);
		m31->third(datamem0->out_data);
		m31->sel(con0->write_back_select);

		//four_one_mux
		m41->first(zs0->out1);
		m41->second(zs0->out2);
		m41->third(zs0->out3);
		m41->forth(zs0->out4);
		m41->sel(con0->signexsel);
		*/
	}
		
};
