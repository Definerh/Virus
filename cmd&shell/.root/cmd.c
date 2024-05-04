#include <windows.h>

int main(int argc, char *argv[]) {
	while (!kbhit())
		MessageBox(0, "A Computer Virus", "Little Bear", 0);
}




