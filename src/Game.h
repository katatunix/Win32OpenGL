#pragma once

#include "MyWindowListener.h"
#include "WglDisplay.h"
#include "gl2.h"

class Game : public MyWindowListener {
public:
	Game(WglDisplay& display) : m_display(display) {
		glClearColor(1.0, 0.0, 1.0, 1.0);
	}

	bool beat() {
		glClear(GL_COLOR_BUFFER_BIT);

		m_display.swapBuffers();
		return true;
	}

private:
	WglDisplay& m_display;
};
