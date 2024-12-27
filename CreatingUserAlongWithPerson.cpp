#include "TeamCenterITK.h"

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;
	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");
	tag_t user = NULLTAG;
	 
	const char* personName= "BVRM";
	tag_t personTag = NULLTAG;

	if (ITK_init_module(USERNAME, PASSWORD, GROUP) == ITK_ok)
	{
		SA_create_person2(personName, &personTag);
		AOM_save_without_extensions(personTag);
		error(SA_create_user2("IZNN", personName, "IZNN" , &user));
		AOM_save_without_extensions(user);
	}
	return 0;
}