#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem = ITK_ask_cli_argument("-i=");
	tag_t tItem = NULLTAG , newProcess = NULLTAG;
	tag_t releaseStatus = NULLTAG;
	tag_t RelStat = NULLTAG;
	int attachmentCount = 1;
	tag_t *tItemRevList = NULLTAG;
	int attachment_types[1];
    int iItemRevCount = 0;
	tag_t attachments[1];

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		
		RELSTAT_create_release_status("Finished", &releaseStatus);
		ITEM_find_item("000086",&tItem);
		ITEM_list_all_revs(tItem,&iItemRevCount,&tItemRevList);
		AOM_save_without_extensions(releaseStatus);
		
		for (int i = 0; i < iItemRevCount; i++)
		{
			attachments[0] = tItemRevList[i];
			attachment_types[0] = EPM_target_attachment;
			RELSTAT_add_release_status(releaseStatus,1, attachments,true);
			EPM_create_process("Process", "The item is under the processing", releaseStatus, attachmentCount, attachments, attachment_types, &newProcess);
		}
	}
	return 0;
}