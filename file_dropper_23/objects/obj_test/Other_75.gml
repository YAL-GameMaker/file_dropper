var _type = async_load[?"event_type"];
var _tmp = json_decode(json_encode(async_load));
ds_map_delete(_tmp, "event_type");
show_debug_message(string(_type) + ": " + json_encode(_tmp));
ds_map_destroy(_tmp);

switch (async_load[?"event_type"]) {
	case "file_drag_over":
		var _x = async_load[?"x"] - window_get_x();
		var _y = async_load[?"y"] - window_get_y();
		file_dropper_set_allow(point_in_rectangle(_x, _y,
			0, 0, window_get_width() div 2, window_get_height()
		));
		break;
	case "file_drop":
		text += "\n" + async_load[?"filename"];
		highlight = false;
		break;
	case "file_drag_enter":
		highlight = true;
		break;
	case "file_drag_leave":
	case "file_drop_end":
		highlight = false;
		break;
}