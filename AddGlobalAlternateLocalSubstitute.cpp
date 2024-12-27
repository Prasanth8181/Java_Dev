#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	tag_t bomWindow = NULL_TAG;
	tag_t default_view_type = NULL_TAG;
	tag_t bv_tag = NULL_TAG;
	tag_t bvr_tag = NULL_TAG;
	tag_t parentItem = NULL_TAG;
	tag_t parentItemRevision = NULL_TAG;//topBomLine
	tag_t topBomLine = NULL_TAG;
	tag_t ChildBOMLine1 = NULLTAG;
	tag_t ChildBOMLine2 = NULLTAG;
	tag_t childItemRev1 = NULLTAG;
	tag_t childItemRev2 = NULLTAG;
	tag_t globalAlternate[1];
	tag_t localSubstitute = NULLTAG;
	tag_t childItem1 = NULLTAG;
	tag_t global = NULLTAG;
	tag_t substitute = NULLTAG;
	tag_t substituteRev = NULLTAG;
	tag_t substituteResult = NULLTAG;
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
		
		ITEM_find_item("000091",&parentItem);
		ITEM_find_item("000083", &childItem1);
		ITEM_find_item("000085", &global);
		ITEM_find_item("000090", &substitute);

		ITEM_find_rev("000091","A",&parentItemRevision);
		ITEM_find_rev("000083", "A", &childItemRev1);
		ITEM_find_rev("000084", "A", &childItemRev2);
		ITEM_find_rev("000084", "A", &childItemRev2);
		ITEM_find_rev("000090", "A", &substituteRev);

		globalAlternate[0] = global;
		PS_create_bv_with_bvr("ITK_BV", "BV", default_view_type, "ITK_BVR", "BVR_DESC", false, parentItemRevision, &bv_tag, &bvr_tag);
		BOM_set_window_top_line(bomWindow, parentItem, parentItemRevision, bv_tag, &topBomLine);
		BOM_line_add(topBomLine, NULLTAG, childItemRev1, NULLTAG, &ChildBOMLine1);
		BOM_line_add(topBomLine, NULLTAG, childItemRev2, NULLTAG, &ChildBOMLine2);
			
		ITEM_add_related_global_alternates(childItem1,1,globalAlternate);
		BOM_line_add_substitute(ChildBOMLine2, substitute, substituteRev,NULLTAG, &substituteResult);
		AOM_save_without_extensions(substituteResult);
		AOM_save_without_extensions(*globalAlternate);
	
		BOM_save_window(bomWindow);
		
	}
	error(loginStatus);
	return 0;
}