#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char*  GROUP = ITK_ask_cli_argument("-g=");
	tag_t windowTag = NULLTAG;
	tag_t viewType = NULLTAG;
	tag_t tBV = NULLTAG;
	tag_t tBVR = NULLTAG;
	tag_t topBomLine = NULLTAG;
	tag_t child1AsParent = NULLTAG;
	tag_t childBomLine1 = NULLTAG;
	tag_t childBomLine2 = NULLTAG;

	
	tag_t parentItem = NULLTAG;
	tag_t parentItemRevision = NULLTAG;
	tag_t childItem1 = NULLTAG;
	tag_t childItemRevision1 = NULLTAG;
	tag_t childItem2 = NULLTAG;
	tag_t childItemRevision2 = NULLTAG;
	tag_t childItem3 = NULLTAG;
	tag_t childItemRevision3 = NULLTAG;



	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		ITEM_find_item("000121", &parentItem);
		ITEM_find_revision(parentItem, "A", &parentItemRevision);
		ITEM_find_item("000122", &childItem1);
		ITEM_find_revision(childItem1, "A", &childItemRevision1);
		ITEM_find_item("000123", &childItem2);
		ITEM_find_revision(childItem2, "A", &childItemRevision2);
		ITEM_find_item("000124", &childItem3);
		ITEM_find_revision(childItem3, "A", &childItemRevision3);

		PS_ask_default_view_type(&viewType);
		PS_create_bv_with_bvr("OCC_EFF", "Occurance Effectivity", viewType, "ITK BVR", "BOM VIEW REVISION", false, parentItemRevision, &tBV, &tBVR);
		BOM_create_window(&windowTag);
		BOM_set_window_top_line(windowTag, parentItem, parentItemRevision, tBV, &topBomLine);
		BOM_line_add(topBomLine, childItem1, childItemRevision1, NULLTAG, &childBomLine1);
		BOM_line_add(topBomLine, childItem2, childItemRevision2, NULLTAG, &childBomLine2);
		BOM_save_window(windowTag);
		BOM_line_insert_level(1, &childBomLine2, childItemRevision3, viewType);
		//AOM_save_without_extensions(occuranceEffectivity1);
		BOM_save_window(viewType);
	}
	return 0;

}