#ifndef __DRAGO_FILE_DROPPER
#define __DRAGO_FILE_DROPPER "1.0.1"

#include "main/core.h"

#include <windows.h>
#include <fstream>
#include <vector>

namespace file_dropper {
	extern LONG_PTR window_original;
	extern std::vector<std::wstring> names;
	LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
	
	const char* version();
	void init(HWND);

	int count();
	char* get(int n);
	void flush();

	void handle(HWND, UINT, WPARAM, LPARAM);
}

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
#endif