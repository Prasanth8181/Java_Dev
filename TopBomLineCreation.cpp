#include "TeamCenterITK.h"

int ITK_user_main(int argc, char **argv)
{
	tag_t user = NULL_TAG;
	tag_t folder = NULL_TAG;
	tag_t item = NULL_TAG;
	tag_t itemRev = NULL_TAG;
	tag_t bomWindow = NULL_TAG;
	tag_t topBomLine = NULL_TAG;
	tag_t relationship_type = NULL_TAG;
	tag_t relation = NULL_TAG;
	tag_t childItem = NULL_TAG;
	tag_t childItemRev = NULL_TAG;
	tag_t ChildBOMLine = NULL_TAG;
	tag_t bv_tag = NULL_TAG;
	tag_t bvr_tag = NULL_TAG;
	tag_t default_view_type = NULL_TAG;


	if (ITK_init_module("infodba", "infodba", "dba") == ITK_ok)
	{
		//create  top bomline 
		cout << "Creating top bomline";
		SA_find_user2("infodba", &user);//it finds the user
		SA_ask_user_home_folder(user, &folder);//it finds the user home folder
		ITEM_find_item("000069",&childItem);
		ITEM_find_revision(childItem,"A", &childItemRev);
		ITEM_create_item("98765659", "ITK_ITEM", "Item", "B", &item, &itemRev);//creating item 
		FL_insert(folder, item,1);
		AOM_save_without_extensions(item);
		AOM_save_without_extensions(folder);
		BOM_create_window(&bomWindow);//bom window create
		PS_ask_default_view_type(&default_view_type);
		PS_create_bv_with_bvr("ITK_BV","BV", default_view_type,"ITK_BVR","BVR_DESC",true, itemRev, &bv_tag,&bvr_tag);
		BOM_set_window_top_line(bomWindow, item, itemRev, bv_tag, &topBomLine);
		//bom window save
		BOM_line_add(topBomLine, NULLTAG, childItemRev, NULLTAG, &ChildBOMLine);
		BOM_save_window(bomWindow);
		//BOM_close_window(bomWindow);
		
		cout << "Top bom line[" << topBomLine << "]";
	}
	else
	{
		cout << "kindly provide valid credentials";
	}
	return 0;

}