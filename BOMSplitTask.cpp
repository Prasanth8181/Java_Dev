#include "TeamCenterITK.h";

int getChild(tag_t tBOMLINE)
{
	int iCountOfChilds = 0;
	tag_t *tListOfAllChilds = NULLTAG;
	char *cparent_id = NULL, *cChildId = NULL,*quantity=NULL;
	tag_t tparent = NULLTAG;
	tparent = tBOMLINE;
	int allSubChildLines = BOM_line_ask_all_child_lines(tBOMLINE, &iCountOfChilds, &tListOfAllChilds);
	if (allSubChildLines == ITK_ok)
	{
		if (iCountOfChilds != 0)
		{
			AOM_ask_value_string(tparent, "bl_item_item_id", &cparent_id);
			
			for (int i = 0; i < iCountOfChilds; i++)
			{
				AOM_ask_value_string(tListOfAllChilds[i], "bl_item_item_id", &cChildId);
				cout << "Parent ID [" << cparent_id << "] and childs in BOM are " << cChildId << endl;
				getChild(tListOfAllChilds[i]);

			}
		}
		else
		{
			cout << "----Final BOM----";
			AOM_ask_value_string(tparent, "bl_item_item_id", &cparent_id);
			cout << "End parent/child ID  [" << cparent_id << "]" << endl;
			AOM_ask_value_string(tparent, "bl_quantity", &quantity);
			if (tc_strcmp(quantity, "20") == 0)
			{
				BOM_line_split_occurrence("10", tBOMLINE);
			}
			
		}
	}
	else
	{
		cout << "Failed to get the child lines";
	}
	return 0;
}
int ITK_user_main(int argc, char **argv)
{
	int iFail = NULL;
	int iNoOfBOMViews = 0;
	tag_t tParentItem = NULLTAG, tParentItemRevision = NULLTAG, twindow = NULLTAG, tTopBomView = NULLTAG;
	tag_t *tBOMViewList = NULLTAG;
	// Obtain command-line arguments
	char* USERID = ITK_ask_cli_argument("-u=");
	char* PASSWORD = ITK_ask_cli_argument("-p=");
	char* GROUP = ITK_ask_cli_argument("-g=");
	char *item_id = ITK_ask_cli_argument("-i=");

	iFail = ITK_init_module(USERID, PASSWORD, GROUP);
	if (iFail == ITK_ok)
	{
		cout << "Login Successful \n";
		                      //Getting the ITEM ID from the Command prompt
		ITEM_find_item(item_id, &tParentItem);                              //Using item id fetching the ITEM TAG
		ITEM_find_rev(item_id, "A", &tParentItemRevision);                  //Fetching the item revision
		ITEM_list_bom_views(tParentItem, &iNoOfBOMViews, &tBOMViewList);      //Fetching the BOM Views  from the parent ITEM    
		for (int i = 0; i < iNoOfBOMViews; i++)
		{
			BOM_create_window(&twindow);                                    //creating the BOM window
			BOM_set_window_top_line(twindow, tParentItem, tParentItemRevision, tBOMViewList[i], &tTopBomView);//Setting the TOP line of the BOM WINDOW for each bom view present inside the root item
			getChild(tTopBomView);                                                                           //fetching the childs for the parent item present in root item
		}

	}
	else
	{
		cout << "Kindly enter the valid credentials";
	}
	BOM_save_window(twindow);
	return 0;

}
