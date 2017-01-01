#include <Windows.h>
#include "MyWindow.h"
#include "MyWindowListener.h"

class DummyLisenter : public MyWindowListener {
public:
	void beat() {
		int x = 0;
	}
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
	MyWindow window(hInst, 800, 480, "Game");
	DummyLisenter listener;
	window.show(30, nShowCmd, listener);
	return 0;
}
