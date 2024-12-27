#include "TeamCenterITK.h";
int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItemId = ITK_ask_cli_argument("-i=");
	tag_t tWindow,tRootItem,tRootItemRevision,tViewType,tBVTag, tBVRTag,tTopBomLine,tParent1Item,tParent1ItemRevision, tParent2Item, tParent2ItemRevision, parent1BOMline, parent2BOMline = NULLTAG;
	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		//BOM_line_ask_all_child_lines
		ITEM_find_item("000135",&tRootItem);
		ITEM_find_revision(tRootItem,"A",&tRootItemRevision);
		ITEM_find_item("000133", &tParent1Item);
		ITEM_find_revision(tParent1Item, "A", &tParent1ItemRevision);
		ITEM_find_item("000134", &tParent2Item);
		ITEM_find_revision(tParent2Item, "A", &tParent2ItemRevision);

		BOM_create_window(&tWindow);
		PS_ask_default_view_type(&tViewType);
		PS_create_bv_with_bvr("ITK_CUSTOM_BOM","Custom bom for test", tViewType, "ITK_CUSTOM_BOM-BVR", "Custom bom for test-BVR",false, tRootItemRevision,&tBVTag,&tBVRTag);
		
		BOM_set_window_top_line(tWindow, tRootItem, tRootItemRevision, tBVTag, &tTopBomLine);
		BOM_line_add(tTopBomLine, NULLTAG, tParent1ItemRevision, NULLTAG,&parent1BOMline);
		BOM_save_window(tWindow);
		BOM_line_add(parent1BOMline, NULLTAG, tParent2ItemRevision, NULLTAG, &parent2BOMline);
		BOM_save_window(tWindow);

	}
	else
	{
		cout << "Kindly check the user credentials";
	}
	return 0;
}