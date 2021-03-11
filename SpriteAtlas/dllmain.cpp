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

ex double pack_textures(int* sprite_data, double length) {
    return sprite_atlas::pack(sprite_data, ((int)length) >> 2);
}