#include "gml_ext.h"
extern bool file_dropper_init(GAME_HWND hwnd);
dllx double file_dropper_init_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	GAME_HWND _arg_hwnd;
	_arg_hwnd = (GAME_HWND)_in.read<uint64_t>();
	return file_dropper_init(_arg_hwnd);
}

