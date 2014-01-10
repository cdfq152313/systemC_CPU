LIB_DIR=-L/usr/local/systemc-2.3.0/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.0/include
LIB=-lsystemc-2.3.0
RPATH=-Wl,-rpath=/usr/local/systemc-2.3.0/lib-linux64

APP=datamem
BPP=main

CPP=two_one_mux
DPP=three_one_mux
EPP=four_one_mux

FPP=controller
GPP=alu
HPP=ZS_extension
IPP=trans_instruction


all:
	g++ -o $(APP)  $(BPP).cpp  $(LIB_DIR) $(INC_DIR) $(LIB) $(RPATH) 

debug:
	g++ -o $(APP) $(APP).cpp $(BPP).cpp $(CPP).cpp $(DPP).cpp $(EPP).cpp $(FPP).cpp $(GPP).cpp $(HPP).cpp $(LIB_DIR) $(INC_DIR) $(LIB) $(RPATH) $(CFLAG)

clean:
	rm -rf $(APP)
