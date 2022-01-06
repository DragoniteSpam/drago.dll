#ifndef __DRAGO_DDD_MAIN
#define __DRAGO_DDD_MAIN "1.0.1"

#include "core.h"

#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <cstring>

#define WINDOW_NEVERMIND 0.0
#define WINDOW_CLOSE 1.0

std::map<double, SHELLEXECUTEINFO> process_map;
LONG_PTR window_original;
double window_status;
bool disable_close = false;
HWND hwnd_original;

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);

ex double drago_reset_status();
ex double drago_fetch_status();
ex double drago_init(HWND, double);

ex double file_drop_count();
ex char* file_drop_get(double n);
ex double file_drop_flush();

// no point implementing the core version, honestly
ex const char* drago_version();
ex const char* file_dropper_version();

#endif