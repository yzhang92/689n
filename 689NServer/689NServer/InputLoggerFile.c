#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG "log.txt"

int InputLoggerFile(char *message) {

	FILE *file;

	time_t current_time = time(NULL);
	struct tm *calendar_time; 

	if ((file = fopen(LOG, "a")) == NULL) {
		printf("error\n");
	};

	if ((calendar_time= localtime(&current_time)) == NULL) {
		printf("Error occured in loggerfile");
		return 0;
	}


	printf("%d/%d/%d %d:%d  %s\n", calendar_time->tm_mon + 1, calendar_time->tm_mday,
		calendar_time->tm_year + 1900, calendar_time->tm_hour, calendar_time->tm_min, message);

	fprintf(file, "%d/%d/%d %d:%d  %s\n", calendar_time->tm_mon + 1, calendar_time->tm_mday,
		calendar_time->tm_year + 1900, calendar_time->tm_hour, calendar_time->tm_min, message);

	fclose(file);

	return 1;
}
