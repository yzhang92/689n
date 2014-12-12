#include <stdio.h>
#include <string.h>

int StrToInt(char *str) {
	char cur;
	int i = 0;
	int number = 0;
	int unit = 1;

	while ((cur = str[i]) != '\0') {
		if (cur < 48 || cur >57) {
			return 0;
		}
		i++;
	}

	while (--i >= 0) {
		number += (str[i] - 48) * unit;
		unit *= 10;
	}

	return number;
}