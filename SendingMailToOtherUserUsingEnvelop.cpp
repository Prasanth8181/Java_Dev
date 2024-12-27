#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem = ITK_ask_cli_argument("-i=");
	const char *Subject= "HELLO SAMPLE ITK";
	const char *comments = "This is the sample mail from the ITK using Envelop";
	tag_t tEnvelop = NULLTAG,tReceiver = NULLTAG,tCCReceiver = NULLTAG,ItemRevision = NULLTAG;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_find_rev("000143","C",&ItemRevision);
		SA_find_user2("kumar",&tReceiver);
		SA_find_user2("infodba", &tCCReceiver);
		MAIL_create_envelope(Subject, comments,&tEnvelop);
		MAIL_add_envelope_receiver(tEnvelop, tReceiver);
		MAIL_add_envelope_cc_receiver(tEnvelop, tCCReceiver);
		FL_insert(tEnvelop, ItemRevision,0);
		MAIL_send_envelope(tEnvelop);
	}
	return 0;
}