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

dllex double drago_reset_status();
dllex double drago_fetch_status();
dllex double drago_init(HWND, double);

dllex double file_drop_count();
dllex char* file_drop_get(double n);
dllex double file_drop_flush();

// no point implementing the core version, honestly
dllex const char* drago_version();
dllex const char* file_dropper_version();

#endif