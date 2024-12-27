#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem = ITK_ask_cli_argument("-i=");
	const char* cPreferenceName = ITK_ask_cli_argument("-pn=");
	char *cPreferenceValue = NULL;
	int numOfEmails = 0;
	tag_t tUser, tMailBox = NULLTAG;
	tag_t *tMailTags = NULLTAG;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		SA_find_user2(USERNAME,&tUser);
		SA_ask_user_mailbox(tUser,&tMailBox);
		AOM_ask_value_tags(tMailBox,"contents", &numOfEmails, &tMailTags);
		for (int i = 0; i < numOfEmails; i++)
		{
			AOM_delete_from_parent(tMailTags[i], tMailBox);
			AOM_save_without_extensions(tMailBox);
		}
	}
	return 0;
}