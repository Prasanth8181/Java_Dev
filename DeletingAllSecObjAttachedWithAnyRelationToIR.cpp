#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItemId = ITK_ask_cli_argument("-i=");
	char *objectType = NULL;
	//const char *ch = "PDF";
	tag_t tItemTag,tPdf, tObjTypeTag = NULLTAG;
	tag_t *tRevisionList,*tSecondaryList = NULLTAG;
	int iNoOfRevisions, secondaryRelationshipCount= 0;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_find_item("000127",&tItemTag);
		//AE_find_datasettype2("PDF", &tDSType);
		ITEM_list_all_revs(tItemTag,&iNoOfRevisions,&tRevisionList);
		
		for (int i = 0; i < iNoOfRevisions; i++)
		{
			GRM_list_secondary_objects_only(tRevisionList[i], NULLTAG, &secondaryRelationshipCount, &tSecondaryList);    //NULLTAG means all relation types
			 
			//AE_find_all_datasets2();
			for (int j = 0; j < secondaryRelationshipCount; j++)
			{
				AOM_ask_value_string(tSecondaryList[j], "object_type", &objectType);
				cout <<"["<<objectType << "]\n";
				//AE_find_datasettype2(objectType,&tObjTypeTag);
				if (tc_strcmp(objectType,"PDF")==0)
				{
					cout << "Inside equal\n";
					AOM_delete_from_parent(tSecondaryList[j], tRevisionList[i]);
				}
				
			}
			AOM_save_without_extensions(tRevisionList[i]);
		}
		
	}
	error(loginStatus);
	return 0;
}