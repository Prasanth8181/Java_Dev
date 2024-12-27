#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	tag_t queryTag = NULLTAG;
	

	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;
	tag_t *
	const char *userID[1];
	int result = 0;
	userID[0] = "kumar";

	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");
	const char *queryName = "34_ListAllDatasetsByUserID";

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		QRY_find2(queryName, &queryTag);
		QRY_execute(queryTag, 1, (char **) userID, NULL, &result, &Dataser);
		//cout << "THE NO OF DATASETS FETCHED FOR THE USER " << USERNAME << "[" << count << "]" << endl;

	}
	error(loginStatus);
	return 0;
}