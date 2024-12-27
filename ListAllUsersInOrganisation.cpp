#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;
	int result = 0;
	char *user_id = NULL;
	char *userName = NULL;
	tag_t *usersList = NULLTAG;
	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");
	tag_t queryTag = NULLTAG;
	const char *queryName = "10_List_All_The_Users_In_Organisation";
	int userId = 0;
	int username = 0;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		cout << "Executing the query" << "\n";
		QRY_find2(queryName,&queryTag);
		QRY_execute(queryTag,NULL,NULL,NULL, &result,&usersList);
		cout << "The no of the user's are" << result << "\n";
		for (int i = 0; i < result; i++)
		{
			
			userId=SA_ask_user_identifier2(usersList[i],&user_id);
			username=SA_ask_os_user_name2(usersList[i], &userName);
			cout << "USER ID[" << user_id << "] - USER OS NAME[" << userName << "]" <<"\n"<<endl;
			//SA_ASK_ExtentUser
		}
	}
	error(userId);
	error(username);
	error(loginStatus);
	return 0;
}