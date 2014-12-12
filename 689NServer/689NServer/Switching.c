# include <stdio.h>

int StrToInt(char *);
int InputLoggerFile(char *);
void SendBackServerRespond(int, char const *);

int Switching(char ** para_arr, char *dataFileName, int clnclock) {

	int req_num = StrToInt(para_arr[0]);

	/* build the tree */

	switch (req_num) {

	case 1:
		SendBackServerRespond(clnclock,"Test: get case 1");
		/* if (AlreadyExist(para_arr, tree) == 0) return 0; */
		/* send back result */
		break;
	case 2:
		SendBackServerRespond(clnclock,"Test: get case 2");

		/* if (AlreadyExist(para_arr, tree) == 1) return 0; */
		/* insert entry*/
		break;

	case 3:
		SendBackServerRespond(clnclock,"Test: get case 3");

		/* if (AlreadyExist(para_arr, tree) == 0) return 0 */
		/* deleting entry */
		break;

	case 4: 
		SendBackServerRespond(clnclock, "Test: get case 4");

		/* return most requested record */
		break;

	case 5:
		SendBackServerRespond(clnclock, "Test: get case 5");

		/* return least requested record */
		break;

	case 6:
		SendBackServerRespond(clnclock, "Test: get case 6");

		/* if (CodeSame() == 0) return 0;*/
		/* terminate server ;*/
		break;

	
	default:
		return 0;
	}

	/* update the tree and put data into database */
	return 1;
}