#include "three_one_mux.h"

void three_one_mux::method_func()
{
	if(sel.read() == "00"){
		out = first;
	}
	else if(sel.read() == "01"){
		out = second;
	}
	else{
		out = third;
	}
}


