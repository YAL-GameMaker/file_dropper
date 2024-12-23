file_dropper_init();
text = "Dropped files:";
highlight = false;
has_valid_files = true;
file_is_valid = function(_path) /*=>*/ {
	// except for ZIPs!
	return string_lower(filename_ext(_path)) != ".zip";
}
file_dropper_set_default_allow(false);
//file_dropper_set_default_effect(file_dropper_effect_move);