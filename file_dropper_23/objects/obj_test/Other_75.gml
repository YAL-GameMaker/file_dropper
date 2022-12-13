show_debug_message(json_encode(async_load));
if (async_load[?"event_type"] == "file_drop") {
    text += "\n" + async_load[?"filename"];
}