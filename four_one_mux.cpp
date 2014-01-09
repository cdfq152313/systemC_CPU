#include "four_one_mux.h"

void four_one_mux::method_func()
{
	if(sel.read() == "00"){
		out = first;
	}
	else if(sel.read() == "01"){
		out = second;
	}
	else if(sel.read() == "10"){
		out = third;
	}
	else{
		out = forth;
	}
}


