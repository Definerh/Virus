#include <windows.h>
#include <Windows.h>
#include <winternl.h>
#include <unistd.h>
#include <tchar.h>
#include <cstring>
#include <iostream>

int main() {
	bool flat = CopyFile (_T("C:\\Users\\张杨\\Documents\\我的数据源\\小熊\\日常\\Virus\\c++\\bsod\\bsod.exe"),
	                      _T("C:\\Users\\张杨\\Desktop\\bsod.exe"),
	                      true);
	std::cout << GetLastError() << " ";
	std::cout << ERROR_FILE_NOT_FOUND << " " << MAX_PATH << " " << ERROR_ACCESS_DENIED << " " << ERROR_ENCRYPTION_FAILED ;
	return flat;
}