#pragma once
#include "stdafx.h"

// As per http://help.yoyogames.com/hc/en-us/articles/216755258:
typedef int gml_ds_map;
//
typedef void (*gml_event_perform_async_t)(gml_ds_map map, int event_type);
typedef int (*gml_ds_map_create_ext_t)(int n, ...);
typedef bool (*gml_ds_map_set_double_t)(gml_ds_map map, char* key, double value);
typedef bool (*gml_ds_map_set_string_t)(gml_ds_map map, char* key, const char* value);
//
extern gml_event_perform_async_t gml_event_perform_async;
extern gml_ds_map_create_ext_t gml_ds_map_create_ext;
extern gml_ds_map_set_double_t gml_ds_map_set_double;
extern gml_ds_map_set_string_t gml_ds_map_set_string;
//
inline gml_ds_map gml_ds_map_create() {
	return gml_ds_map_create_ext(0);
}

// A wrapper for queuing async events for GML easier.
class gml_async_event {
private:
	gml_ds_map map;
public:
	gml_async_event() {
		map = gml_ds_map_create();
	}
	gml_async_event(char* type) {
		map = gml_ds_map_create();
		gml_ds_map_set_string(map, "event_type", type);
	}
	~gml_async_event() {
		//
	}
	/// Dispatches this event and cleans up the map.
	void dispatch(int kind) {
		gml_event_perform_async(map, kind);
	}
	bool set(char* key, double value) {
		return gml_ds_map_set_double(map, key, value);
	}
	bool set(char* key, const char* value) {
		return gml_ds_map_set_string(map, key, value);
	}
};