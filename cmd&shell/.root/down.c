#include <windows.h>

void HideWindow()
{
	HWND hwnd = GetForegroundWindow();
	if (hwnd)
	{
		ShowWindow(hwnd, SW_HIDE);
	}
}

int main()
{
	HideWindow();
	system("pause");
}