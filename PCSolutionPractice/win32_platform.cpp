#include <windows.h>


enum {
	EXIT,
	GAME,
	SETTINGS,
	QUEUE
};
int state = 1;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			state = EXIT;
		} break;
		default: {
			result = DefWindowProc(hwnd, uMsg, wparam, lParam);
		}
	}
	return result;

}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	WNDCLASS w_class = {};
	w_class.style = CS_HREDRAW | CS_VREDRAW;
	w_class.lpszClassName = "Solution Practice";
	w_class.lpfnWndProc = window_callback;

	RegisterClass(&w_class);

	HWND window = CreateWindow(
		w_class.lpszClassName,
		":3",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		0,
		0,
		hInstance,
		0
		);

	// Game Loop
	while (state != EXIT) {
		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

}