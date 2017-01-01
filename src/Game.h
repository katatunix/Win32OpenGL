#pragma once

#include "MyWindowListener.h"
#include "WglDisplay.h"

class Game : public MyWindowListener {
public:
	Game(WglDisplay& display) : m_display(display) {

	}

	bool beat() {
		m_display.swapBuffers();
		return true;
	}

private:
	WglDisplay& m_display;
};
