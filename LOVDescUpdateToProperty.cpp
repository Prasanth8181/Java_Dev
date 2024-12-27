#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;

	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");

	tag_t item = NULLTAG;
	tag_t lovTag = NULLTAG;
	char *lovDesc = NULL;
	tag_t *itemRevsions = NULLTAG;
	int itemRevCount=0;
	int lovDescriptions = 0;

	char **display_values = NULL;
	int noOFDesc = 0;
	logical* isNull;
	logical* isEmpty;
	map<char, char> mp;
	LOV_usage_t usageTag;
	int noOfValues = 0;
	logical* isNull1;
	logical* isEmpty2;
	char **values = NULL;
	char * InfoValue = NULL;
	

	//int count;
	


	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		
		cout << "Entry into the login Success" << "\n";
		ITEM_find_item("000100", &item);
		ITEM_list_all_revs(item, &itemRevCount,&itemRevsions);
		//cout << *itemRevCount;
		//count = (*itemRevCount);
		cout << itemRevCount << "\n";
		for (int i = 0; i < itemRevCount; i++)
		{
			cout << "Inside the for loop\n";
		}
		AOM_ask_lov(item, "a2ServiceHistoryInfo",&lovTag);
		LOV_ask_disp_value_descriptions(lovTag,&noOFDesc, &display_values,&isNull,&isEmpty);
		LOV_ask_disp_values(lovTag,&usageTag,&noOfValues, &isNull1,&isEmpty2,&values);
		for (int i = 0; i < noOFDesc; i++)
		{
			cout << display_values[i]<< "|" << values[i]<< "\n" <<endl;
			char* test = values[i];
			mp[test] = display_values[i];
		}
		AOM_ask_value_string(item, "a2ServiceHistoryInfo", &InfoValue);
		cout << InfoValue;
		cout << mp[*InfoValue];

		//AOM_set_value_string();
	}
	//error(loginStatus);
	return 0;
}