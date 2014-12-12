#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **SplitRecvMessage(char *recvMessage) {

	char **str_arr;

	int str_len = strlen(recvMessage);

	int count = 0;
	int i = 0;

	/* calculate the number of command line parameter */
	while ((recvMessage[i] != '$') || (recvMessage[i + 1] != '$') || (recvMessage[i + 2] != '$'))  {
		if (recvMessage[i] == '$' && recvMessage[i + 1] == '$') count++;
		i++;
	}
	count++;
	/* create string arrry to store them */
	str_arr = (char **)malloc(count * sizeof(char *));

	/* calculte the length of each string and assign them to the string arrary*/
	int char_count;
	i = 0;
	int j = 0;
	while ((recvMessage[i] != '$') || (recvMessage[i + 1] != '$') || (recvMessage[i + 2] != '$'))  {
		char_count = 1;
		while ((recvMessage[i + 1] != '$') || (recvMessage[i + 2] != '$')) {
			char_count++;
			i++;
		}
		str_arr[j] = (char *)malloc((char_count + 1) * sizeof(char));
		str_arr[j][char_count] = '\0';
		j++;
		if ((i + 3) < (str_len - 1)) i += 3;
		else i++;
	}
	/* copy the recieve message to the string array */
	int sum = j;
	i = 0;
	j = 0;
	int k = 0;
	while (j < sum) {

		while (k < strlen(str_arr[j])) {
			str_arr[j][k] = recvMessage[i];
			i++;
			k++;
		}
		k = 0;
		i += 2;
		j++;
	}

	return str_arr;

}

