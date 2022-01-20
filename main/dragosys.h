#ifndef __DRAGO_DDD_SYS
#define __DRAGO_DDD_SYS "1.0.0"

#include "core.h"

#include <windows.h>
#include <sysinfoapi.h>
#include <intrin.h>
#include "comutil.h"

#define _WIN32_DCOM
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

namespace dragosys {
    extern SYSTEM_INFO sysInfo;
    extern MEMORYSTATUSEX sysMemory;
    extern char sysCPU[0x40];
    extern char* sysOS;

	void init();
    void init_wmi();

    // system
    const char* os_info();
    
    // cpu
    double processor_count();
    const char* processor_info();
    const char* processor_architecture();

    // memory
    unsigned long long memory_total();
    unsigned long long memory_available();
    int memory_load();
}

#endif