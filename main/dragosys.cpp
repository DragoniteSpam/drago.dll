#include "core.h"
#include "dragosys.h"

namespace dragosys {
    SYSTEM_INFO sysInfo{};
    MEMORYSTATUSEX sysMemory;
    char sysCPU[0x40];
    char sysOS[0x100];

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

        init_wmi();
    }

    void init_wmi() {
        // from https://docs.microsoft.com/en-us/windows/win32/wmisdk/example--getting-wmi-data-from-the-local-computer
        HRESULT hres;

        // Step 1: --------------------------------------------------
        // Initialize COM. ------------------------------------------

        hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
        if (FAILED(hres)) {
            std::cout << "Failed to initialize COM library. Error code = 0x"
                << std::hex << hres << std::endl;
            return;
        }

        // Step 2: --------------------------------------------------
        // Set general COM security levels --------------------------

        hres = CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities 
            NULL                         // Reserved
        );


        if (FAILED(hres)) {
            std::cout << "Failed to initialize security. Error code = 0x"
                << std::hex << hres << std::endl;
            CoUninitialize();
            return;
        }

        // Step 3: ---------------------------------------------------
        // Obtain the initial locator to WMI -------------------------

        IWbemLocator* pLoc = NULL;

        hres = CoCreateInstance(
            CLSID_WbemLocator,
            0,
            CLSCTX_INPROC_SERVER,
            IID_IWbemLocator, (LPVOID*)&pLoc);

        if (FAILED(hres)) {
            std::cout << "Failed to create IWbemLocator object."
                << " Err code = 0x"
                << std::hex << hres << std::endl;
            CoUninitialize();
            return;
        }

        // Step 4: -----------------------------------------------------
        // Connect to WMI through the IWbemLocator::ConnectServer method

        IWbemServices* pSvc = NULL;

        // Connect to the root\cimv2 namespace with
        // the current user and obtain pointer pSvc
        // to make IWbemServices calls.
        hres = pLoc->ConnectServer(
            _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
            NULL,                    // User name. NULL = current user
            NULL,                    // User password. NULL = current
            0,                       // Locale. NULL indicates current
            NULL,                    // Security flags.
            0,                       // Authority (for example, Kerberos)
            0,                       // Context object 
            &pSvc                    // pointer to IWbemServices proxy
        );

        if (FAILED(hres)) {
            std::cout << "Could not connect. Error code = 0x"
                << std::hex << hres << std::endl;
            pLoc->Release();
            CoUninitialize();
            return;
        }

        std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;


        // Step 5: --------------------------------------------------
        // Set security levels on the proxy -------------------------

        hres = CoSetProxyBlanket(
            pSvc,                        // Indicates the proxy to set
            RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
            RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
            NULL,                        // Server principal name 
            RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
            RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
            NULL,                        // client identity
            EOAC_NONE                    // proxy capabilities 
        );

        if (FAILED(hres)) {
            std::cout << "Could not set proxy blanket. Error code = 0x"
                << std::hex << hres << std::endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return;
        }

        // Step 6: --------------------------------------------------
        // Use the IWbemServices pointer to make requests of WMI ----

        // For example, get the name of the operating system
        IEnumWbemClassObject* pEnumerator = NULL;
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t("SELECT * FROM Win32_OperatingSystem"),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pEnumerator);

        if (FAILED(hres)) {
            std::cout << "Query for operating system name failed."
                << " Error code = 0x"
                << std::hex << hres << std::endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return;
        }

        // Step 7: -------------------------------------------------
        // Get the data from the query in step 6 -------------------

        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (pEnumerator) {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
                &pclsObj, &uReturn);

            if (0 == uReturn) {
                break;
            }

            VARIANT vtProp{};

            // Get the value of the Name property
            hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
            _bstr_t interim_os(vtProp.bstrVal, false);
            char* osDescription = (char*)interim_os;
            strncpy_s(sysOS, osDescription, interim_os.length());
            // after "windows 10 whatever" you'll find a bit of info that, in
            // all likelihood, we don't care about
            for (unsigned int i = 0; i < interim_os.length(); i++) {
                if (sysOS[i] == '|') {
                    sysOS[i] = '\0';
                    break;
                }
            }
            VariantClear(&vtProp);

            pclsObj->Release();
        }

        // Use the IWbemServices pointer to make requests of WMI ----
        IWbemClassObject* pClass = NULL;
        _bstr_t value = "Win32_VideoController";
        hres = pSvc->GetObject(value, 0, NULL, &pClass, NULL);

        if (FAILED(hres)) {
            std::cout << "GetObject failed" << " Error code = 0x" << std::hex << hres << std::endl;
            std::cout << _com_error(hres).ErrorMessage() << std::endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return;
        }

        SAFEARRAY* psaNames = NULL;
        hres = pClass->GetNames(
            NULL,
            WBEM_FLAG_ALWAYS | WBEM_FLAG_NONSYSTEM_ONLY,
            NULL,
            &psaNames);


        if (FAILED(hres)) {
            std::cout << "GetNames failed" << " Error code = 0x" << std::hex << hres << std::endl;
            std::cout << _com_error(hres).ErrorMessage() << std::endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return;
        }


        // Get the number of properties.
        long lLower, lUpper;
        BSTR PropName = NULL;
        SafeArrayGetLBound(psaNames, 1, &lLower);
        SafeArrayGetUBound(psaNames, 1, &lUpper);
        //figure out a nice way to retrieve a specific attribute on demand (probably by putting the important ones in a map)
        for (long i = lLower; i <= lUpper; i++) {
            // Get this property.
            hres = SafeArrayGetElement(
                psaNames,
                &i,
                &PropName);

            SysFreeString(PropName);
        }

        SafeArrayDestroy(psaNames);

        // Cleanup
        // ========

        pSvc->Release();
        pLoc->Release();
        pEnumerator->Release();
        CoUninitialize();

    }

    // system
    const char* os_info() {
        return sysOS;
    }

    // cpu
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
        case PROCESSOR_ARCHITECTURE_UNKNOWN:
        default: {
            return "dunno lol";
        };
        }
    }

    // memory
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