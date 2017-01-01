#include <Windows.h>
#include "MyWindow.h"
#include "WglDisplay.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {
	MyWindow window(hInst, 800, 480, "Game");
	WglDisplay display(window.hDC());
	Game game(display);

	window.show(30, game);
	return 0;
}
