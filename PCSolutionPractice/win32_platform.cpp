#pragma once

#include <windows.h>
#include <vector>
#include <iostream>

#include "utils.h"

enum {
	EXIT,
	GAME,
	SETTINGS,
	QUEUE
};

int state = 1;

void* buffer;
int buffer_w, buffer_h, buffer_size;
BITMAPINFO buffer_bmi;



LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			state = EXIT;
		} break;
		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			buffer_w = rect.right - rect.left;
			buffer_h = rect.bottom - rect.top;
			buffer_size = buffer_w * buffer_h * sizeof(unsigned int);

			buffer = realloc(buffer, buffer_size);
			memset(buffer, 0, buffer_size);

			buffer_bmi.bmiHeader.biSize = sizeof(buffer_bmi.bmiHeader);
			buffer_bmi.bmiHeader.biWidth = buffer_w;
			buffer_bmi.bmiHeader.biHeight = buffer_h;
			buffer_bmi.bmiHeader.biPlanes = 1;
			buffer_bmi.bmiHeader.biBitCount = sizeof(unsigned int) * 8;
			buffer_bmi.bmiHeader.biCompression = BI_RGB;

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
	HDC hdc = GetDC(window);

	// Game Loop
	while (state != EXIT) {
		// input
		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// simulate


		//render
		//memset(buffer, 0, buffer_size);

		unsigned int* pixel = (unsigned int*)buffer;

		for (int x = 0; x < buffer_w; ++x) {
			for (int y = 0; y < buffer_h; ++y) {
				drawPixel(buffer, buffer_w, x, y, x);
				//*pixel++ = 0x00ff00;
			}
		}

		StretchDIBits(hdc, 0, 0, buffer_w, buffer_h, 0, 0, buffer_w, buffer_h, buffer, &buffer_bmi, DIB_RGB_COLORS, SRCCOPY);
	}

}