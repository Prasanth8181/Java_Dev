#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem = ITK_ask_cli_argument("-i=");
	int iNoOfRevisions,iNoOfReleaseStatuses= 0;
	tag_t *tRevisionsList,*tReleaseStatusObjects = NULLTAG;
	tag_t tItem = NULLTAG;

	char *release_status, *releaseStatusName = NULL;
	date_t release_date = {0};
	date_t recentReleasedDate = { 0 };
	date_t dLatestReleaseDate=NULLDATE;
	tag_t latest_released_revision = NULLTAG;
	int dateResult = 0;
	int count = 0;
	char *revValue = NULL;
	


	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_find_item(cItem, &tItem);
		ITEM_list_all_revs(tItem, &iNoOfRevisions,&tRevisionsList);
		for (int i = 0; i < iNoOfRevisions; i++)
		{
			AOM_ask_value_tags(tRevisionsList[i],"release_status_list",&iNoOfReleaseStatuses,&tReleaseStatusObjects);
			for (int j = 0; j < iNoOfReleaseStatuses; j++)
			{
				AOM_ask_value_string(tReleaseStatusObjects[j],"name",&releaseStatusName);
				if (strcmp(releaseStatusName, "TCM Released") == 0)
				{
					//DATE_date_to_string();
					AOM_ask_value_date(tRevisionsList[i], "date_released", &release_date);
					if(count == 0)
					{
						dLatestReleaseDate = release_date;
						count++;
					}
					POM_compare_dates(release_date, dLatestReleaseDate, &dateResult);
					if(dateResult==1)
					{
						recentReleasedDate = release_date;
						latest_released_revision = tRevisionsList[i];
					}
					
				}
			}
		}
		AOM_ask_value_string(latest_released_revision, "item_revision_id", &revValue);
		cout << "Latest released revision-karim bhai " << revValue <<endl;
		AOM_save_without_extensions(tItem);
		
	}
	return 0;
}