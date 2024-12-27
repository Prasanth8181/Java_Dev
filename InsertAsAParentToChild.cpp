#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	tag_t bomWindow = NULL_TAG;
	tag_t default_view_type = NULL_TAG;
	tag_t viewType = NULLTAG;
	tag_t bv_tag = NULL_TAG;
	tag_t bvr_tag = NULL_TAG;
	tag_t parentItem = NULL_TAG;
	tag_t parentItemRevision = NULL_TAG;//topBomLine
	tag_t topBomLine = NULL_TAG;
	tag_t ChildBOMLine1 = NULLTAG;
	tag_t ChildBOMLine2 = NULLTAG;
	tag_t childItemRev1 = NULLTAG;
	tag_t childItemRev2 = NULLTAG;
	tag_t tSubChildRev = NULLTAG;
	tag_t bomLineArray[1];

	const char* USERNAME = NULL;
	const char* PASSWORD = NULL;
	const char* GROUP = NULL;
	USERNAME = ITK_ask_cli_argument("-u=");
	PASSWORD = ITK_ask_cli_argument("-p=");
	GROUP = ITK_ask_cli_argument("-g=");

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		cout << "Creating top bomline";
		BOM_create_window(&bomWindow);//bom window create
		PS_ask_default_view_type(&default_view_type);//getting the view type
		PS_ask_default_view_type(&viewType);//getting the view type

		ITEM_find_item("000136", &parentItem);
		ITEM_ask_latest_rev(parentItem, &parentItemRevision);

		ITEM_find_rev("000137", "A", &childItemRev1);
		ITEM_find_rev("000138", "A", &childItemRev2);
		ITEM_find_rev("000139", "A", &tSubChildRev);
	
		PS_create_bv_with_bvr("ITK_BV", "BV", default_view_type, "ITK_BVR", "BVR_DESC", false, parentItemRevision, &bv_tag, &bvr_tag);
		BOM_set_window_top_line(bomWindow, parentItem, parentItemRevision, bv_tag, &topBomLine);

		BOM_line_add(topBomLine, NULLTAG, childItemRev1, NULLTAG, &ChildBOMLine1);
		BOM_line_add(topBomLine, NULLTAG, childItemRev2, NULLTAG, &ChildBOMLine2);
		//bomLineArray[0] = ChildBOMLine1;
	    bomLineArray[0] = ChildBOMLine2;
		BOM_save_window(bomWindow);
		//BOM_line_insert_level(1, bomLineArray, tSubChildRev, bomWindow);
		BOM_save_window(bomWindow);

	}
	error(loginStatus);
	return 0;
}