#include "TeamCenterITK.h"

int ITK_user_main(int argc, char **argv)
{
	tag_t user = NULL_TAG;
	int err = 0;
    //const char cUserId =;
	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;

	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");
	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		
	    SA_find_user2("installuser", &user);
		AOM_refresh(user, true);
		SA_set_user_status(user,1);
		AOM_refresh(user, false);
		cout << "User status udpated successfully";
	   AOM_save_without_extensions(user);
	}

	error(loginStatus);
	return 0;

}