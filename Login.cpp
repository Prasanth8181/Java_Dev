#include "TeamCenterITK.h"


int ITK_user_main(int argc, char **argv)
{
	tag_t  item = NULL_TAG;
	tag_t  rev = NULL_TAG;


	if (ITK_init_module("infodba", "infodba", "dba") == ITK_ok)
	{
		cout << "Inside validation success";//comment
		ITEM_create_item("00001", "Test11", "Item", "A", &item, &rev);//API to create the item
		AOM_save_without_extensions(item);//API to save the values inside the database
	}
	return 0;
}


