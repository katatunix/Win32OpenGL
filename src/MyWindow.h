#pragma once

#include <stdio.h>
#include <Windows.h>
#include "MyWindowListener.h"

class MyWindow {

public:
	MyWindow(HINSTANCE hInst, int width, int height, const char* title) {
		WNDCLASSEX wClass;
		ZeroMemory(&wClass, sizeof(WNDCLASSEX));
		wClass.cbClsExtra = NULL;
		wClass.cbSize = sizeof(WNDCLASSEX);
		wClass.cbWndExtra = NULL;
		wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wClass.hIcon = NULL;
		wClass.hIconSm = NULL;
		wClass.hInstance = hInst;
		wClass.lpfnWndProc = (WNDPROC)internalWindProc;
		wClass.lpszClassName = "Window Class";
		wClass.lpszMenuName = NULL;
		wClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClassEx(&wClass);

		const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		const int CX_FRAME = SM_CXFIXEDFRAME;
		const int CY_FRAME = SM_CYFIXEDFRAME;
		const int DW_STYLE = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;
		const int windowWidth = width + GetSystemMetrics(CX_FRAME) * 2;
		const int windowHeight = height + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(CY_FRAME) * 2;

		m_hWnd = CreateWindowEx(NULL,
			"Window Class",
			title,
			DW_STYLE,
			(screenWidth - windowWidth) / 2,
			(screenHeight - windowHeight) / 2,
			windowWidth,
			windowHeight,
			NULL,
			NULL,
			hInst,
			NULL
		);

		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
		m_hDC = GetDC(m_hWnd);
	}

	HDC hDC() {
		return m_hDC;
	}

	void show(int fps, int nShowCmd, MyWindowListener& listener) {
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		unsigned long last = GetTickCount();
		const unsigned long avai = 1000 / fps;

		ShowWindow(m_hWnd, nShowCmd);
		while (true) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				auto cur = GetTickCount();
				auto duration = cur - last;
				if (duration < avai) {
					Sleep(avai - duration);
				}
				last = GetTickCount();
				listener.beat();
			}
		}
	}

	~MyWindow() {
		ReleaseDC(m_hWnd, m_hDC);
		DestroyWindow(m_hWnd);
	}

private:
	static LRESULT CALLBACK internalWindProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		MyWindow* myWindow = (MyWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		return myWindow->windProc(hWnd, msg, wParam, lParam);
	}

	LRESULT CALLBACK windProc(HWND hWin, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		}
		return DefWindowProc(hWin, msg, wParam, lParam);
	}

	HWND m_hWnd;
	HDC m_hDC;
};
