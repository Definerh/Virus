//#include <windows.h>


//#include <stdlib.h>
//#include <stdio.h>
//
//void ComputerStart(char *pathName)
//{
//	//找到系统的启动项
//	char *szSubKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//	HKEY hKey;
//
//	//打开注册表启动项
//	int k = RegOpenKeyExA(HKEY_CURRENT_USER, szSubKey, 0, KEY_ALL_ACCESS, &hKey);
//	if (k == ERROR_SUCCESS)
//	{
//		//添加一个子Key,并设置值，MyStart为启动项名称，自定义设置；
//		RegSetValueEx(hKey, "MyStart", 0, REG_SZ, (BYTE *)pathName, strlen(pathName));
//		//关闭注册表
//		RegCloseKey(hKey);
//		printf("设置成功\n");
//	}
//	else
//	{
//		printf("设置失败  error:%d\n", k);
//	}
//}
//
//int main()
//{
//	char pathName[MAX_PATH];//文件名字最大260个字符  MAX_PATH  260
//	GetCurrentDirectory(MAX_PATH, pathName);//设置字符集为多字节字符集  获取当前文件路径
//	sprintf(pathName, "%s\\", pathName);
//	strcat(pathName, "shell.exe");//找到需要开机自启动的程序
//	ComputerStart(pathName);
//	system("pause");
//	return 0;
//}
#include <windows.h>
//设置当前程序开机启动
#include <tchar.h>
void AutoPowerOn()
{
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";


	//1、找到系统的启动项
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS) ///打开启动项
	{
		//2、得到本程序自身的全路径
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);


		//3、判断注册表项是否已经存在
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, NULL, _T("GISRestart"), RRF_RT_REG_SZ, 0, strDir, &nLength);


		//4、已经存在
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			//5、添加一个子Key,并设置值，"GISRestart"是应用程序名字（不加后缀.exe）
			RegSetValueEx(hKey, _T("GISRestart"), 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));


			//6、关闭注册表
			RegCloseKey(hKey);
		}
	}
}


//取消当前程序开机启动
void CanclePowerOn()
{
	HKEY hKey;
	//std::string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";


	//1、找到系统的启动项
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
	                 &hKey) == ERROR_SUCCESS)
	{
		//2、删除值
		RegDeleteValue(hKey, _T("GISRestart"));


		//3、关闭注册表
		RegCloseKey(hKey);
	}
}

int main()
{
	return 0;
}