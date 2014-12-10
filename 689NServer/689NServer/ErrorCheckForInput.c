# include <stdio.h>
#include <stdlib.h>

int ErrorCheckForInput(int port, char *filename, int timeGap) {
	FILE *file;

	if (port <= 0 || port > 65535) {
		return 1;
	}
	if ((file = fopen(filename, "r")) == NULL) {
		return 1;
	}
	if (timeGap <= 0 || timeGap > 20) {
		return 1;
	}
	return 0;
}