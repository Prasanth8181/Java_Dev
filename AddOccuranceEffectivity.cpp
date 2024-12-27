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
	tag_t childBomLine1 = NULLTAG;
	tag_t childBomLine2 = NULLTAG;
	tag_t occuranceEffectivity1 = NULLTAG;
	tag_t occuranceEffectivity2 = NULLTAG;

	tag_t parentItem = NULLTAG;
	tag_t parentItemRevision = NULLTAG;
	tag_t childItem1 = NULLTAG;
	tag_t childItemRevision1 = NULLTAG;
	tag_t childItem2 = NULLTAG;
	tag_t childItemRevision2 = NULLTAG;
	//int var = NULL;
	//date configurations
	const char *startDate = "01-Aug-2024 00:00:59";
	const char *endDate = "30-Aug-2024 00:00:59";
	date_t startDateReturn = NULLDATE;
	date_t endDateReturn = NULLDATE;
	logical isDateValid;
	date_t start_end_values[2];


	int loginStatus=ITK_init_module(USERNAME,PASSWORD,GROUP);
	if (loginStatus == ITK_ok)
	{
		//Date creation
		DATE_string_to_date_t(((char*)startDate), &isDateValid, &startDateReturn);
		start_end_values[0] = startDateReturn;
		DATE_string_to_date_t(((char*)endDate), &isDateValid, &endDateReturn);
		start_end_values[1] = endDateReturn;
		//Date Creation

		ITEM_find_item("000143",&parentItem);
		ITEM_find_revision(parentItem,"B",&parentItemRevision);
		ITEM_find_item("000142", &childItem1);
		ITEM_find_revision(childItem1, "C", &childItemRevision1);
		ITEM_find_item("000141", &childItem2);
		ITEM_find_revision(childItem2, "B", &childItemRevision2);
		PS_ask_default_view_type(&viewType);
		PS_create_bv_with_bvr("OCC_EFF","Occurance Effectivity", viewType,"ITK BVR","BOM VIEW REVISION",false, parentItemRevision,&tBV,&tBVR);
		BOM_create_window(&windowTag);
		BOM_set_window_top_line(windowTag, parentItem, parentItemRevision, tBV, &topBomLine);
		//BOM_save_window(windowTag);
		BOM_line_add(topBomLine, NULLTAG, childItemRevision1, NULLTAG, &childBomLine1);
		BOM_line_add(topBomLine, NULLTAG, childItemRevision2, NULLTAG, &childBomLine2);
		BOM_save_window(windowTag);
	    error(BOM_create_occurrence_effectivity(childBomLine1,"1122", parentItem, parentItemRevision,NULL,2, start_end_values, EFFECTIVITY_closed,false, &occuranceEffectivity1));
		//AOM_save_without_extensions(occuranceEffectivity1);
		error(BOM_create_occurrence_effectivity(childBomLine2, "100", parentItem, parentItemRevision, "11-100", 0, NULL, EFFECTIVITY_closed, false, &occuranceEffectivity2));
		//AOM_save_without_extensions(occuranceEffectivity1);
		//BOM_save_window(windowTag);
	}
	return 0;

}