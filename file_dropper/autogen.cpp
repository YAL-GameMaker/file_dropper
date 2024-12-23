#include "gml_ext.h"
extern bool file_dropper_init(GAME_HWND hwnd);
dllx double file_dropper_init_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	GAME_HWND _arg_hwnd = (GAME_HWND)_in.read<uint64_t>();
	return file_dropper_init(_arg_hwnd);
}

extern bool file_dropper_get_allow();
dllx double file_dropper_get_allow_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	return file_dropper_get_allow();
}

extern void file_dropper_set_allow(bool allow);
dllx double file_dropper_set_allow_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	bool _arg_allow = _in.read<bool>();
	file_dropper_set_allow(_arg_allow);
	return 1;
}

extern double file_dropper_get_effect(int effect);
dllx double file_dropper_get_effect_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_effect = _in.read<int>();
	return file_dropper_get_effect(_arg_effect);
}

extern double file_dropper_set_effect(int effect);
dllx double file_dropper_set_effect_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_effect = _in.read<int>();
	return file_dropper_set_effect(_arg_effect);
}

extern bool file_dropper_get_default_allow();
dllx double file_dropper_get_default_allow_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	return file_dropper_get_default_allow();
}

extern void file_dropper_set_default_allow(bool allow);
dllx double file_dropper_set_default_allow_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	bool _arg_allow = _in.read<bool>();
	file_dropper_set_default_allow(_arg_allow);
	return 1;
}

extern double file_dropper_get_default_effect(int effect);
dllx double file_dropper_get_default_effect_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_effect = _in.read<int>();
	return file_dropper_get_default_effect(_arg_effect);
}

extern double file_dropper_set_default_effect(int effect);
dllx double file_dropper_set_default_effect_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_effect = _in.read<int>();
	return file_dropper_set_default_effect(_arg_effect);
}

