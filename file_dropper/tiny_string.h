#pragma once
#include "stdafx.h"

template<typename T> T* malloc_arr(size_t count) {
	return (T*)malloc(sizeof(T) * count);
}
template<typename T> T* realloc_arr(T* arr, size_t count) {
	return (T*)realloc(arr, sizeof(T) * count);
}
template<typename T> T* memcpy_arr(T* dst, const T* src, size_t count) {
	return (T*)memcpy(dst, src, sizeof(T) * count);
}

template<typename C> class tiny_string_t {
	C* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
public:
	tiny_string_t() {}
	inline void init(size_t capacity = 32) {
		_data = malloc_arr<C>(capacity);
		_size = 0;
		_capacity = capacity;
	}
	inline void init(const C* val) {
		init(4);
		set(val);
	}

	/// Returns current size, in characters (not including final NUL)
	inline size_t size() { return _size; }
	inline void setSize(size_t size) { _size = size; }

	inline bool empty() {
		return _size == 0;
	}
	inline C* c_str() {
		return _data;
	}
	inline C* prepare(size_t capacity) {
		if (_capacity < capacity) {
			auto new_data = realloc_arr(_data, capacity);
			if (new_data == nullptr) {
				trace("Failed to reallocate %zu bytes in tiny_string::prepare", sizeof(C) * capacity);
				return nullptr;
			}
			_data = new_data;
			_capacity = capacity;
		}
		return _data;
	}
	inline const C* set(const C* value, size_t len = SIZE_MAX) {
		if (len == SIZE_MAX) {
			const C* iter = value;
			len = 1;
			while (*iter) { iter++; len++; }
		}
		C* result = prepare(len);
		memcpy_arr(result, value, len);
		_size = len - 1;
		return result;
	}
	//
	inline void operator=(const C* value) { set(value); }
	template<size_t size> inline void operator =(const C(&value)[size]) { set(value, size); }
};
struct tiny_string : public tiny_string_t<char> {
public:
	inline char* conv(const wchar_t* wstr) {
		auto size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		auto str = prepare(size);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, size, NULL, NULL);
		setSize(size - 1);
		return str;
	}

	inline void operator=(const char* value) { set(value); }
	template<size_t size> inline void operator =(const char(&value)[size]) { set(value, size); }
};
struct tiny_wstring : public tiny_string_t<wchar_t> {
public:
	inline wchar_t* conv(const char* str) {
		auto size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		auto wstr = prepare(size);
		MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, size);
		setSize(size - 1);
		return wstr;
	}

	inline void operator=(const wchar_t* value) { set(value); }
	template<size_t size> inline void operator =(const wchar_t(&value)[size]) { set(value, size); }
};