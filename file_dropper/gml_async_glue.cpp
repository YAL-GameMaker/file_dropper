#include "gml_async_glue.h"

gml_event_perform_async_t gml_event_perform_async = nullptr;
gml_ds_map_create_ext_t gml_ds_map_create_ext = nullptr;
gml_ds_map_set_double_t gml_ds_map_set_double = nullptr;
gml_ds_map_set_string_t gml_ds_map_set_string = nullptr;

// Called by GM on DLL init
dllx double RegisterCallbacks(void* f1, void* f2, void* f3, void* f4) {
	gml_event_perform_async = (gml_event_perform_async_t)f1;
	gml_ds_map_create_ext = (gml_ds_map_create_ext_t)f2;
	gml_ds_map_set_double = (gml_ds_map_set_double_t)f3;
	gml_ds_map_set_string = (gml_ds_map_set_string_t)f4;
	return 0;
}