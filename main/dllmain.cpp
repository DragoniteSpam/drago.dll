#include "drago.h"
#include "FileDropper/filedropper.h"

ex double drago_init(HWND hWnd, double close) {
    file_dropper::init(hWnd);
    window_original = GetWindowLongPtr(hWnd, GWLP_WNDPROC);
    window_status = WINDOW_NEVERMIND;
    disable_close = (close != 0.0);
    SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)MsgProc);
    return 1.0;
}

ex double drago_reset_status() {
    window_status = WINDOW_NEVERMIND;
    return 0.0;
}

ex double drago_fetch_status() {
    return window_status;
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

// versioning

ex const char* drago_version() {
    return __DRAGO_DDD_MAIN;
}

ex const char* file_dropper_version() {
    return file_dropper::version();
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
        file_dropper::handle(hWnd, msg, wParam, lParam);
        break;
    }
    default: {
        return CallWindowProc((WNDPROC)window_original, hWnd, msg, wParam, lParam);
    }
    }

    return (LRESULT)0;
}