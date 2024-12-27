#include "TeamCenterITK.h";

int ITK_user_main(int argc, char **argv)
{
	const char* USERNAME = ITK_ask_cli_argument("-u=");
	const char* PASSWORD = ITK_ask_cli_argument("-p=");
	const char* GROUP = ITK_ask_cli_argument("-g=");
	const char* cItem = ITK_ask_cli_argument("-i=");
	const char* cPreferenceName = ITK_ask_cli_argument("-pn=");
	char *cPreferenceValue = NULL;
	tag_t tItem = NULLTAG,tBomWindow1 = NULLTAG,tItem1 = NULLTAG,tItemRev1 = NULLTAG, tDefaultViewType1 = NULLTAG, topBomLine1=NULLTAG;
	tag_t tBomWindow2 = NULLTAG, tItem2 = NULLTAG, tItemRev2 = NULLTAG, tDefaultViewType2 = NULLTAG, topBomLine2 = NULLTAG;
	int bomlineChildCount = 0, bomlineChildCount2 = 0;;
	tag_t *bv1List = NULLTAG;
	tag_t *bv2List = NULLTAG;
	tag_t bomCompare = NULLTAG;
	int mode = NULL;

	int loginStatus = ITK_init_module(USERNAME, PASSWORD, GROUP);
	if (loginStatus == ITK_ok)
	{
		//BOM-LINE1
		BOM_create_window(&tBomWindow1);
		ITEM_find_item("000143",&tItem1);
		ITEM_find_revision(tItem1,"B",&tItemRev1);
		ITEM_list_bom_views(tItem1, &bomlineChildCount, &bv1List);
		PS_ask_default_view_type(&tDefaultViewType1);
		BOM_set_window_top_line(tBomWindow1, tItem1, tItemRev1, tDefaultViewType1,&topBomLine1);
		//BOM-LINE1
		//BOM-LINE2
		BOM_create_window(&tBomWindow2);
		ITEM_find_item("000087", &tItem2);
		ITEM_find_revision(tItem2, "A", &tItemRev2);
		ITEM_list_bom_views(tItem2, &bomlineChildCount2, &bv2List);
		PS_ask_default_view_type(&tDefaultViewType2);
		BOM_set_window_top_line(tBomWindow2, tItem2, tItemRev2, tDefaultViewType2, &topBomLine2);
		//BOM-LINE2
		BOM_compare_create(&bomCompare);
		BOM_compare_ask_output_mode(bomCompare,&mode);
		cout << "Mode Name " << mode;
		BOM_compare(topBomLine1, topBomLine2, mode,4);
	}
	return 0;
}