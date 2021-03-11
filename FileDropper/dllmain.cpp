#include "filedropper.h"

ex double init(HWND hWnd) {
    file_dropper::init(hWnd);
    SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)MsgProc);
    return 1.0;
}

ex double file_drop_count() {
    return 1.0 * file_dropper::count();
}

ex char* file_drop_get(double n) {
    return file_dropper::get((int)n);
}

ex double file_drop_flush() {
    file_dropper::flush();
    return 0.0;
}

ex const char* file_dropper_version() {
    return file_dropper::version();
}

// internal stuff

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DROPFILES: {
        file_dropper::handle(hWnd, msg, wParam, lParam);
        break;
    }
    default: {
        return CallWindowProc((WNDPROC)file_dropper::window_original, hWnd, msg, wParam, lParam);
    }
    }

    return (LRESULT)0;
}