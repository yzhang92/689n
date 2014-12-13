# include <stdio.h>
# include <string.h>
# include <winsock.h>

char **StrToArray(char * str) {

	char **str_arr;

	int str_len = strlen(str);

	int count = 0;
	int i = 0;
	if (strlen(str) == 0) return NULL;

	while ((str[i] != '\0'))  {
		if (str[i] == ' ') count++;
		i++;
	}
	count++;
	/* create string arrry to store them */
	str_arr = (char **)malloc(count * sizeof(char *));

	int char_count = 0;
	i = 0;
	int j = 0;
	while (j < count)  {
		char_count = 0;
		while (str[i] != ' ' && str[i] != '\0') {
			char_count++;
			i++;
		}
		str_arr[j] = (char *)malloc((char_count + 1) * sizeof(char));
		str_arr[j][char_count] = '\0';
		j++;
		i++;
	}
	/* copy the recieve message to the string array */
	i = 0;
	j = 0;
	int k = 0;
	while (j < count) {
		while (k < strlen(str_arr[j])) {
			str_arr[j][k] = str[i];
			i++;
			k++;
		}
		k = 0;
		i += 1;
		j++;

	}

	return str_arr;

}