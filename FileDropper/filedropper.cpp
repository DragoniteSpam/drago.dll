#include "filedropper.h"

namespace file_dropper {
    LONG_PTR window_original;
    std::vector<std::wstring> names;

    void init(HWND hWnd) {
        window_original = GetWindowLongPtr(hWnd, GWLP_WNDPROC);
        DragAcceptFiles(hWnd, true);
    }
    
	const char* version() {
		return __DRAGO_FILE_DROPPER;
	}
    
	int count() {
		return (int)names.size();
	}
    
	char* get(int n) {
		std::wstring path(names.at(n));
		wchar_t* cstr = new wchar_t[path.size() + 1];
        wcscpy_s(cstr, path.size() + 1, path.c_str());
		return (char*)cstr;
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
                std::wstring path(buffer.data());
                names.push_back(std::wstring(path.begin(), path.end()));
            }
        }

        DragFinish(hdr);
	}
}