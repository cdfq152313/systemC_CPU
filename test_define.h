
#define SIZE_OF_TEST 5

// test data input
const char  read_list[] = {'0', '0', '1', '0', '1'};
const char  write_list[] = {'0', '1', '0', '1', '0'};
const char  reset_list[] = {'1', '0', '0', '0', '0'};

const char* addr_list[] = {"000000000000000000", "000000000000000000", "000000000000000000", "000000000000000001", "000000000000000001"};

const char* in_data_list[] = {"0000000000000000000000000000000X", \
			      "11111111111111111111111111111111", \
			      "00000000000000000000000000001101", \
			      "00000000001000000011000000001100", \
			      "11111110001111111111111111111111"};
// test data output

const char* out_data_list[] = {"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", \
			      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", \
			      "11111111111111111111111111111111", \
			      "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", \
			      "00000000001000000011000000001100"};
