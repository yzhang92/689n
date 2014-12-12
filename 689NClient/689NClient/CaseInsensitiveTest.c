#include <string.h>

char *CaseInsensitiveTest(char * str) {
	int len = strlen(str);
	char *re = malloc(len + 1);
	re[len] = '\0';
	for (int i = 0; i < len; i++) {
		if (str[i] > 64 && str[i] < 91) {
			re[i] = str[i] +  32;
		}
		else {
			re[i] = str[i];
		}
	}
	return re;
}