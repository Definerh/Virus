//#include <windows.h>


//#include <stdlib.h>
//#include <stdio.h>
//
//void ComputerStart(char *pathName)
//{
//	//�ҵ�ϵͳ��������
//	char *szSubKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//	HKEY hKey;
//
//	//��ע���������
//	int k = RegOpenKeyExA(HKEY_CURRENT_USER, szSubKey, 0, KEY_ALL_ACCESS, &hKey);
//	if (k == ERROR_SUCCESS)
//	{
//		//���һ����Key,������ֵ��MyStartΪ���������ƣ��Զ������ã�
//		RegSetValueEx(hKey, "MyStart", 0, REG_SZ, (BYTE *)pathName, strlen(pathName));
//		//�ر�ע���
//		RegCloseKey(hKey);
//		printf("���óɹ�\n");
//	}
//	else
//	{
//		printf("����ʧ��  error:%d\n", k);
//	}
//}
//
//int main()
//{
//	char pathName[MAX_PATH];//�ļ��������260���ַ�  MAX_PATH  260
//	GetCurrentDirectory(MAX_PATH, pathName);//�����ַ���Ϊ���ֽ��ַ���  ��ȡ��ǰ�ļ�·��
//	sprintf(pathName, "%s\\", pathName);
//	strcat(pathName, "shell.exe");//�ҵ���Ҫ�����������ĳ���
//	ComputerStart(pathName);
//	system("pause");
//	return 0;
//}
#include <windows.h>
//���õ�ǰ���򿪻�����
#include <tchar.h>
void AutoPowerOn()
{
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";


	//1���ҵ�ϵͳ��������
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS) ///��������
	{
		//2���õ������������ȫ·��
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);


		//3���ж�ע������Ƿ��Ѿ�����
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("GISRestart"), RRF_RT_REG_SZ, 0, strDir, &nLength);


		//4���Ѿ�����
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			//5�����һ����Key,������ֵ��"GISRestart"��Ӧ�ó������֣����Ӻ�׺.exe��
			RegSetValueEx(hKey, _T("GISRestart"), 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));


			//6���ر�ע���
			RegCloseKey(hKey);
		}
	}
}


//ȡ����ǰ���򿪻�����
void CanclePowerOn()
{
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";


	//1���ҵ�ϵͳ��������
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS)
	{
		//2��ɾ��ֵ
		RegDeleteValue(hKey, _T("GISRestart"));


		//3���ر�ע���
		RegCloseKey(hKey);
	}
}

int main()
{
	return 0;
}