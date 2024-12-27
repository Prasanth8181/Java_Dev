#include "TeamCenterITK.h"
int ITK_user_main(int argc, char **argv)
{

	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;

	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_find_items_by_user();
	}
	return 0;
}

