# include <stdio.h>

int StrToInt(char *str);
int InputLoggerFile(char *message);

int Switching(char ** para_arr, char *dataFileName) {

	int req_num = StrToInt(para_arr[0]);

	/* build the tree */

	switch (req_num) {

	case 1:
		/* if (AlreadyExist(para_arr, tree) == 0) return 0; */
		/* send back result */
	case 2:
		/* if (AlreadyExist(para_arr, tree) == 1) return 0; */
		/* insert entry*/
	case 3:
		/* if (AlreadyExist(para_arr, tree) == 0) return 0 */
		/* deleting entry */
	case 4:
		/* return most requested record */
	case 5:
		/* return least requested record */
	case 6:
		/* if (CodeSame() == 0) return 0;*/
		/* terminate server ;*/
	
	default:
		return 0;
	}

	/* update the tree and put data into database */
	return 1;
}