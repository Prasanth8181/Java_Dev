#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem = ITK_ask_cli_argument("-i=");
	const char* cPreferenceName = ITK_ask_cli_argument("-pn=");
	tag_t findType = NULLTAG;
	tag_t createInput,bo = NULLTAG;
	const char * objName = "object_name";
	const char *displayValues[1];
	displayValues[0] = "FINISHED";

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		TCTYPE_find_type("A2Bike","A2Bike",&findType);
		TCTYPE_construct_create_input(findType,&createInput);
		TCTYPE_set_create_display_value(createInput,(char*)objName,1, displayValues);
		TCTYPE_create_object(createInput, &bo);
		AOM_save_without_extensions(bo);
		//TCTYPE_create_object();
	}
	return 0;
}