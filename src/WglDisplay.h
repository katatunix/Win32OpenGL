#pragma once

#include <stdio.h>
#include <Windows.h>

class WglDisplay {

public:
	WglDisplay(HDC hDC) : m_hDC(hDC) {
		PIXELFORMATDESCRIPTOR pfd =						// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			16,											// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			16,											// 16Bit Z-Buffer (Depth Buffer)  
			0,											// No Stencil Buffer
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};
		auto pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		SetPixelFormat(m_hDC, pixelFormat, &pfd);
		m_hRC = wglCreateContext(m_hDC);
		makeCurrent();
	}

	~WglDisplay() {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);
	}

	void makeCurrent() {
		wglMakeCurrent(m_hDC, m_hRC);
	}

	void swapBuffers() {
		SwapBuffers(m_hDC);
	}

private:
	HDC m_hDC;
	HGLRC m_hRC;

};
