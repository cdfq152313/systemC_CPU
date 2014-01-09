#include <systemc.h>
#include "alu.h"
#include "reg.h"
#include "datamem.h"
#include "controller.h"
#include "two_one_mux.h"
#include "three_one_mux.h"
#include "four_one_mux.h"
#include "ZS_extension.h"

SC_MODULE(newtop)
{
	// signal declaration	alu
	
	sc_in<sc_lv<1> >		reset;
	sc_in_clk		clock;
	sc_in<sc_lv<32> >	instruction;
	
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
	controller		con0;
	alu 			alu0;
	reg				reg0;
	datamem			datamem0;
	ZS_extension	zs0;
	
	two_one_mux m21;
	three_one_mux m31;
	four_one_mux m41;

	//Constructor 
	public:
	//controller
	SC_CTOR(newtop){
		con0("con0") {
			// link signals
			con0.instruction(instruction);
			//mux
			con0.alusrc(m21sel);
			con0.memtoreg(m31sel);
			con0.signexsel(m41sel);
			//alu
			con0.op(op);
			con0.sub_op(sub_op);
			con0.enable(enable);
			//reg
			con0.regwrite(write);
			con0.regread(read);
			//datamem
			con0.datawrite(datawrite);
			con0.dataread(dataread);
		}

		//ZS
		zs0("zs0") {
			// link signals
			zs0.src1(instruction.range(14,10));
			zs0.src2(instruction.range(14,0));
			zs0.src3(instruction.range(19,0));
			zs0.out1(zsout1);
			zs0.out2(zsout2);
			zs0.out3(zsout3);
			zs0.out4(zsout4);
			
		}
		//ALU
		alu0("alu0") {
			// link signals
			alu0.reset(reset);
			
			// 以下由control path來送
			alu0.enable(enable);
			alu0.op(op);
			alu0.sub_op(sub_op);
			
			// 以下自己吃
			alu0.src1(r1_data);
			alu0.src2(m21out);
			alu0.output(output);		
			alu0.overflow(overflow);
		}
		//m21
		m21("m21") {
			// link signals
			m21.sel(m21sel);
			m21.first(r2_data);
			m21.second(m41out);
			m21.out(m21out);
		}
		//m31
		m31("m31") {
			// link signals
			m31.sel(m31sel);
			m31.first(m21out);
			m31.second(output);
			m31.third(out_data);
			m31.out(m31out);
		}
		//m41
		m41("m41") {
			// link signals
			m41.sel(m41sel);
			m41.first(zsout1);
			m41.second(zsout2);
			m41.third(zsout3);
			m41.forth(zsout4);
			m41.out(m41out);
		}
		//reg
		reg0("reg0") {
			
			// link signals
			reg0.clock(clock);
			reg0.reset(reset);
			
			// 以下由control path來送
			reg0.write(write);
			reg0.read(read);
			
			//這些接線是instruction接出來的 (自己吃..)
			reg0.r1_addr(instruction.range(24,20));
			reg0.r2_addr(instruction.range(19,15));
			reg0.rw_addr(instruction.range(14,10));
			reg0.rw_data(m31out);	
			// output
			reg0.r1_data(r1_data);
			reg0.r2_data(r2_data);
		}
		//datamem
		datamem0("datamem0") {
			// link signals
			datamem0.clock(clock);
			datamem0.reset(reset);
			
			// 以下由control path來送
			datamem0.write(datawrite);
			datamem0.read(dataread);
			
			
			datamem0.addr(output);//從alu的output來
			datamem0.in_data(m21out);//從m21的m21out來
			datamem0.out_data(out_data);
		}
	}
};
