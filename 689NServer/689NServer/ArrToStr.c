# include <stdio.h>
# include <string.h>
# include <winsock.h>

char *ArrToStr(char **str_arr) {
	if (str_arr == NULL) return NULL;

	int numbOfArr = sizeof(str_arr) / sizeof(char *);
	int len = 0;
	for (int i = 0; i < numbOfArr; i++) {
		len += strlen(str_arr[i]);
		len += 1;
	}
	printf("%d\n", len);
	char *str = malloc(len);
	str[len] = '\0';
	for (int i = 0; i < numbOfArr; i++) {
		if (i == 0) strcpy(str, str_arr[0]);
		else strcat(str, str_arr[i]);
		if (i != (numbOfArr - 1)) strcat(str, " ");
	}
	return str;
}