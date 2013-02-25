#include <Windows.h>

// The main window handle; this is used to identify a created window
HWND ghMainWnd = 0;

bool InitWindowsApp(HINSTANCE instanceHandle, int show);
int Run();
// Handles events our window receives
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	if(!InitWindowsApp(hInstance, nShowCmd))
		return 0;

	// Loop until WM_QUIT message is received
	return Run();
}

bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{

	return true;
}

int Run()
{
	return 0;
}