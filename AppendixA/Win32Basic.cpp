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
	// First we must describe the characteristics of the window by filling out a WNDCLASS structure
	WNDCLASS wc;

	wc.style					= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra			= 0;
	wc.cbWndExtra			= 0;
	wc.hInstance			= instanceHandle;
	wc.hIcon					= LoadIcon(0, IDI_SHIELD);
	wc.hCursor				= LoadCursor(0, IDC_HAND);
	wc.hbrBackground	= (HBRUSH) GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= L"DxWndClass";

	// Next, register this WNDCLASS instance (wc) with Windows so we can create a window based on it
	if(!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass instance FAILED", 0, 0);
		return false;
	}

	// Create a window based on our registered WNDClASS instance
	ghMainWnd = CreateWindow(
		L"DxWndClass",				// Registered WNDCLASS instance to use
		L"Win32Basic",				// window title
		WS_OVERLAPPEDWINDOW,	//style flags
		CW_USEDEFAULT,				// x-coordinate
		CW_USEDEFAULT,				// y-coordinate
		CW_USEDEFAULT,				// width
		CW_USEDEFAULT,				// height
		0,										// parent window (we have none)
		0,										// menu handle (we have none)
		instanceHandle,				// instance of our application
		0);										// extra creation parameters

	// Show our newly created window
	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

int Run()
{
	MSG msg = {0};

	BOOL bRet = 1;
	while (msg.message != WM_QUIT)
	{
		// PeekMessage check to see if there are messages, If there is a message then process it
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Else do animation/game stuff
		else
		{

		}
	}

	return (int)msg.wParam;
}

// We never call this function explicitly, Windows calls it when it needs to process a message for a window. Thus CALLBACK
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Handle some specific messages. If we handle a message, we should return 0
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			MessageBox(0, L"Hello, World", L"Hello", MB_OK);
		return 0;
		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				DestroyWindow(ghMainWnd);
		return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
		case WM_CLOSE:
			if(MessageBox(0, L"Would you like to quit?", L"Are you sure?", MB_YESNO | MB_ICONEXCLAMATION ) == IDYES)
			{
				DestroyWindow(ghMainWnd);
			}
		return 0;
	}
	// Forward any other messages we did not handle (above) to the default window procedure
	return DefWindowProc(hWnd, msg, wParam, lParam);
}