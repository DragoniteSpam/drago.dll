#include "filedropper.h"

namespace file_dropper {
    std::vector<std::string> names;

    void init(HWND hWnd) {
        DragAcceptFiles(hWnd, true);
    }
    
	const char* version() {
		return __DRAGO_FILE_DROPPER;
	}
    
	int count() {
		return (int)names.size();
	}
    
	char* get(int n) {
		std::string path(names.at(n));
		char* cstr = new char[path.size() + 1];
		strcpy_s(cstr, path.size() + 1, path.c_str());
		return cstr;
        return (char*)"";
	}
    
	void flush() {
        names.clear();
	}
    
	void handle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        HDROP hdr = ((HDROP)wParam);

        flush();
        int count = DragQueryFileW(hdr, 0xffffffff, NULL, 0);

        std::vector<wchar_t> buffer;
        
        for (int i = 0; i < count; i++) {
            int size = (int)DragQueryFileW(hdr, i, NULL, 0);
            if (size > 0) {
                buffer.resize(size + (size_t)(1));
                DragQueryFileW(hdr, i, buffer.data(), size + 1);
                std::wstring tws(buffer.data());
                std::string path = "";
                names.push_back(std::string(tws.begin(), tws.end()));
            }
        }

        DragFinish(hdr);
	}
}