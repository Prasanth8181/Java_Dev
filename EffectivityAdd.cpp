#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	//int status = ITK_ok;
	tag_t releaseStatus = NULLTAG;
	tag_t endItem = NULLTAG;
	tag_t effectivity = NULLTAG;
	tag_t parentItem = NULLTAG;
	int no_of_dates = 2;
	date_t start_end_values[2];
	const char *startDate = "01-Aug-2024 00:00:59";
	const char *endDate = "30-Aug-2024 00:00:59";
	logical isDateValid;
	date_t startDateReturn = NULLDATE;
	date_t endDateReturn = NULLDATE;
	tag_t wfProcess = NULLTAG;
	tag_t itemRev = NULLTAG;
	tag_t attachments[1];
	int attachment_types[1];
	tag_t newProcess = NULLTAG;

	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;

	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if(loginStatus==ITK_ok)
	{
		DATE_string_to_date_t(((char*)startDate), &isDateValid,&startDateReturn);
		start_end_values[0] = startDateReturn;
		DATE_string_to_date_t(((char*)endDate), &isDateValid, &endDateReturn);
		start_end_values[1] = endDateReturn;
		EPM_find_status_type("TCM Released", &releaseStatus);
		//ITEM_find_item("000079", &parentItem);
		
		ITEM_find_rev("000081", "A", &itemRev);
		attachments[0] = itemRev;
		attachment_types[0] = EPM_target_attachment;

		EPM_find_process_template("TCM Release Process", &wfProcess);
		EPM_create_process("TCM Release Process","TCM Release Process", wfProcess,1, attachments, attachment_types,&newProcess);//initiating the workflow
		AOM_save_with_extensions(newProcess);
		//
		WSOM_effectivity_create_with_dates(releaseStatus, attachments[0], no_of_dates, start_end_values, WSOM_open_ended_status_e(EFFECTIVITY_closed),&effectivity);
	    AOM_save_with_extensions(effectivity);
	}
	error(loginStatus);
	/*else
	{
		cout << "User credentials invalid";

	}*/
	return 0;
}