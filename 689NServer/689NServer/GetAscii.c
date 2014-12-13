# include <stdio.h>
#include <string.h>

int GetAscii(char *str) {
	int ascii = 0;
	if (str == NULL) return 0;
	for (int i = 0; i < strlen(str); i++) {
		ascii += str[i];
	}
	return ascii;
}