#include <windows.h>

void HideWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}
}

int main(int argc, const char *argv[]) {
	HideWindow();
	ShellExecuteA(0, "open", "shell.exe", 0, 0, 0);
}
