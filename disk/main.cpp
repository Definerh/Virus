#include <windows.h>

int main() {
	system("diskpart");
//	system("list disk");
	system("select disk 0");
	system("offline disk");
}