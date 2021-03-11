#include "filedropper.h"

namespace file_dropper {
    LONG_PTR window_original;
    std::vector<std::string> names;

    void init(HWND hWnd, bool set_ptr) {
        window_original = GetWindowLongPtr(hWnd, GWLP_WNDPROC);
        DragAcceptFiles(hWnd, true);
        if (set_ptr) {
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)handle);
        }
    }
    
	const char* version() {
		return __DRAGO_FILE_DROPPER;
	}
    
	int count() {
		//return names.size();
        return 0;
	}
    
	char* get(int n) {
		std::string path = names.at(n);
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
            int size = DragQueryFileW(hdr, i, NULL, 0);
            if (size > 0) {
                buffer.resize(size + 1);
                DragQueryFileW(hdr, i, buffer.data(), size + 1);
                std::string path = "";
                wchar_t* data = buffer.data();
                // i hate this part very much
                for (unsigned int j = 0; j < buffer.size(); j++) {
                    path += *(data + j);
                }
                path += '\0';
                names.push_back(path);
            }
        }

        DragFinish(hdr);
	}
}