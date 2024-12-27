#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char*PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char *cProjId= "112233",*cProjectName="TEST", *cProjectDesc= "TEST";
	int gropMemCount = 0;
	tag_t *gropMemList = NULLTAG;
	tag_t tProject, tUser = NULLTAG;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		PROJ_create_project(cProjId, cProjectName, cProjectDesc, &tProject);
		//PROJ_find
		SA_find_user2("kumar",&tUser);
		SA_find_all_groupmember_by_user(tUser, false, &gropMemCount, &gropMemList);
		for (int i = 0; i < gropMemCount; i++)
		{
			PROJ_add_members(tProject,1, &gropMemList[i]);
		}
		AOM_save_without_extensions(tProject);
	}
	error(loginStatus);
	return 0;
}