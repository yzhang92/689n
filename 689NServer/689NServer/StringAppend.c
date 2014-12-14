#include <string.h>
#include <stdlib.h>

char *StringAppend(char *str1, char *str2) {

	char *newString;
	if (str1 == NULL && str2 == NULL) return NULL;
	if (str1 == NULL) return str2;
	if (str2 == NULL) return str1;

	if ((newString = malloc(strlen(str1) + strlen(str2) + 1)) != NULL){
		newString[0] = '\0';
		strcat(newString, str1);
		strcat(newString, str2);
		return newString;
	}
	else
		return NULL;
}