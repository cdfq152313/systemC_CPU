#include "two_one_mux.h"

void two_one_mux::method_func()
{
	if(sel.read() == '0'){
		out = first;
	}
	else{
		out = second;
	}
}


