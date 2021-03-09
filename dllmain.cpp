#include "drago.h"
#include "spriteatlas.h"

// not everything in here is used

// exported stuff

ex double init(HWND hWnd, double close) {
    window_original = GetWindowLongPtr(hWnd, GWLP_WNDPROC);
    window_status = WINDOW_NEVERMIND;
    disable_close = (close != 0.0);
    SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)MsgProc);
    DragAcceptFiles(hWnd, true);
    return 1.0;
}

// command line usage goes this: hh.exe ms-its:<file>.chm::<page>.htm
// apparently for shellexecutea you don't need the ms-its:: part
ex double help(const char* file, const char* where) {
    // because why would string concatenation be easy?
    /*char options[255];
    sprintf(options, "%s::%s.htm", file, where);*/
    //return 1.0 * (int)(ShellExecuteA(NULL, "open", "hh.exe", options, NULL, 1));
    return 0.0;
}

ex double copy(const char* source, const char* destination) {
    std::ifstream in(source);
    std::ofstream out(destination);
    out << in.rdbuf();
    out.close();
    in.close();

    return 0.0;
}

ex double process(const char* filename, const char* verb) {
    SHELLEXECUTEINFO info{};
    info.cbSize = sizeof(SHELLEXECUTEINFO);
    info.fMask = SEE_MASK_NOCLOSEPROCESS;
    info.lpVerb = (LPCWSTR)verb;
    info.lpFile = (LPCWSTR)filename;
    info.nShow = SW_SHOW;

    if (!ShellExecuteEx(&info)) {
        return -1.0;
    }

    double id = 1.0 * ((int)info.hProcess);
    process_map[id] = info;
    return id;
}

ex double process_complete(double id) {
    if (process_map.find(id) != process_map.end()) {
        if (WaitForSingleObject(process_map[id].hProcess, 0) == WAIT_OBJECT_0) {
            process_map.erase(id);
            return 1.0;
        }
    }
    return 0.0;
}

ex double kill(double id) {
    if (process_map.find(id) != process_map.end()) {
        HANDLE handle = OpenProcess(PROCESS_TERMINATE, false, (int)process_map[id].hProcess);
        if (TerminateProcess(handle, 0)) {
            CloseHandle(handle);
            return 1.0;
        }
        else {
            std::cout << "Unable to terminate: " << id << std::endl;
        }
    }
    else {
        std::cout << "Not found: " << id << std::endl;
    }
    return 0.0;
}

ex double open(const char* filename) {
    return process(filename, "open");
}

ex double edit(const char* filename) {
    return process(filename, "edit");
}

ex double reset_status() {
    window_status = WINDOW_NEVERMIND;
    return 0.0;
}

ex double fetch_status() {
    return window_status;
}

ex double file_drop_count() {
    return 1.0 * file_drop_names.size();
}

ex char* file_drop_get(double n) {
    std::string path = file_drop_names.at((int)n);
    char* cstr = new char[path.size() + 1];
    strcpy_s(cstr, path.size() + 1, path.c_str());
    return cstr;
}

ex double file_drop_flush() {
    file_drop_names.clear();
    return 0.0;
}

ex double pack_textures(int* sprite_data, double length) {
    return sprite_atlas::pack(sprite_data, ((int)length) >> 3);
}

// internal stuff

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE: {
        if (disable_close) {
            window_status = WINDOW_CLOSE;
        }
        else {
            return CallWindowProc((WNDPROC)window_original, hWnd, msg, wParam, lParam);
        }
        break;
    }
    case WM_DROPFILES: {
        HDROP hdr = ((HDROP)wParam);

        file_drop_flush();
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
                file_drop_names.push_back(path);
            }
        }

        DragFinish(hdr);
        break;
    }
    default: {
        return CallWindowProc((WNDPROC)window_original, hWnd, msg, wParam, lParam);
    }
    }

    return (LRESULT)0;
}