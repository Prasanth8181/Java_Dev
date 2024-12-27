#include "TeamCenterITK.h";
int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItemId = ITK_ask_cli_argument("-i=");
	tag_t *items = NULLTAG;
	int intnoOfItems = 0;
	date_t creationDate;
	tag_t owningUser = NULL;
	char *userId = NULL;
	char *dateFormat = NULL;
	char *dateInString = NULL;
	int M=0, D=0, Y=0 , H=0 , M=0, S=0;
	int date = 0;

	time_t timestamp = time(NULL);
	struct tm datetime = *localtime(&timestamp);
	char output[50];

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_extent(&intnoOfItems,&items);
		for (int i = 0; i < intnoOfItems; i++)
		{
			strftime(output, 50, "%d", &datetime);
			//cout << "Current day is [" << output << "]";
			AOM_ask_value_date(items[i],"creation_date",&creationDate);
			DATE_date_to_string(creationDate,"%d-%b-%Y %H:%M:%S", &dateInString);
			error(AOM_ask_value_tag(items[i],"owning_user", &owningUser));
			DATE_get_internal_date_string_format(&dateFormat);
			AOM_ask_value_string(owningUser,"user_id",&userId);
			cout << "Owning User " << userId <<endl;
			cout << dateFormat << endl;
			DATE_string_to_date(dateInString,"%d-%b-%Y %H:%M:%S",&M,&D,&Y,&H,&M,&S);
			
			if ((char*)D== output)
			{
				cout << "same day successful" << endl;
			}
			
		}
	}
	else
	{
		cout << "Kindly check the user credentials";
	}
	return 0;
}