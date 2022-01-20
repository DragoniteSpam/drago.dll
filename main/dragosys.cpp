#include "core.h"
#include "dragosys.h"

namespace dragosys {
    SYSTEM_INFO sysInfo{};
    MEMORYSTATUSEX sysMemory;
    char sysCPU[0x40];

    void init() {
        GetSystemInfo(&sysInfo);
        sysMemory.dwLength = sizeof(sysMemory);
        GlobalMemoryStatusEx(&sysMemory);

        // found here: https://stackoverflow.com/a/850812
        int CPUInfo[4] = { -1 };
        unsigned   nExIds, i = 0;
        // Get the information associated with each extended ID.
        __cpuid(CPUInfo, 0x80000000);
        nExIds = CPUInfo[0];
        for (i = 0x80000000; i <= nExIds; ++i) {
            __cpuid(CPUInfo, i);
            // Interpret CPU brand string
            if (i == 0x80000002)
                memcpy(sysCPU, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000003)
                memcpy(sysCPU + 16, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000004)
                memcpy(sysCPU + 32, CPUInfo, sizeof(CPUInfo));
        }

    }

    // system info
    double processor_count() {
        return sysInfo.dwNumberOfProcessors * 1.0;
    }

    // includes manufacturer, model and clockspeed
    const char* processor_info() {
        return sysCPU;
    }

    const char* processor_architecture() {
        switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: {
            return "x64";
        };
        case PROCESSOR_ARCHITECTURE_ARM: {
            return "ARM";
        };
        case PROCESSOR_ARCHITECTURE_ARM64: {
            return "ARM64";
        };
        case PROCESSOR_ARCHITECTURE_IA64: {
            return "Itanium";
        };
        case PROCESSOR_ARCHITECTURE_INTEL: {
            return "x86";
        };
        case PROCESSOR_ARCHITECTURE_UNKNOWN: {
            return "dunno lol";
        };
        }
    }

    unsigned long long memory_total() {
        return sysMemory.ullTotalPhys;
    }

    unsigned long long memory_available() {
        GlobalMemoryStatusEx(&sysMemory);
        return sysMemory.ullAvailPhys;
    }

    int memory_load() {
        GlobalMemoryStatusEx(&sysMemory);
        return (int)sysMemory.dwMemoryLoad;
    }
}