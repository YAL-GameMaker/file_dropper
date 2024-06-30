draw_set_font(fnt_test);
draw_set_color(c_white);
draw_text(5, 5, text);

if (highlight) {
	draw_rectangle(3, 3, (room_width div 2) - 3, room_height - 3, true);
}