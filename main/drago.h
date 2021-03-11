#ifndef __DRAGO_DDD_MAIN
#define __DRAGO_DDD_MAIN "1.0.1"

#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include <map>
#include <vector>
#include <cstring>
#include "core.h"

#define WINDOW_NEVERMIND 0.0
#define WINDOW_CLOSE 1.0

std::map<double, SHELLEXECUTEINFO> process_map;
LONG_PTR window_original;
double window_status;
bool disable_close = false;
HWND hwnd_original;
std::vector<std::string> file_drop_names;

ex double process(const char*, const char*);
LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);

ex double help(const char*, const char*);
ex double copy(const char*, const char*);
ex double process_complete(double);
ex double kill(double);
ex double open(const char*);
ex double edit(const char*);
ex double reset_status();
ex double fetch_status();
ex double init(HWND, double);

ex double file_drop_count();
ex char* file_drop_get(double n);
ex double file_drop_flush();

ex double pack_textures(int*, double);

// no point implementing the core version, honestly
ex const char* version();
ex const char* sprite_atlas_version();

#endif