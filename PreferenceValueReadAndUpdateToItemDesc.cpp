#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem= ITK_ask_cli_argument("-i=");
	const char* cPreferenceName= ITK_ask_cli_argument("-pn=");
	char *cPreferenceValue = NULL;
	tag_t tItem = NULLTAG;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_find_item(cItem, &tItem);
		PREF_ask_char_value(cPreferenceName, 0, &cPreferenceValue);
		cout << cPreferenceValue;
		AOM_set_value_string(tItem,"object_desc", cPreferenceValue);
		AOM_save_without_extensions(tItem);
	}
	return 0;
}