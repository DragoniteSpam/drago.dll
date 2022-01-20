#ifndef __DRAGO_DDD_SYS
#define __DRAGO_DDD_SYS "1.0.0"

#include "core.h"

#include <windows.h>
#include <sysinfoapi.h>
#include <intrin.h>

namespace dragosys {
    extern SYSTEM_INFO sysInfo;
    extern MEMORYSTATUSEX sysMemory;
    extern char sysCPU[0x40];

	void init();
    
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