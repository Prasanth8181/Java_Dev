#include "TeamCenterITK.h"

int ITK_user_main(int argc, char **argv)
{
	tag_t dataset = NULL_TAG;
	tag_t relation = NULL_TAG;
	tag_t primaryObject = NULL_TAG;
	tag_t *secondaryObject = NULL_TAG;
	tag_t item = NULL_TAG;
	tag_t item_rev = NULL_TAG;
	int count = 0;
	if (ITK_init_module("infodba", "infodba", "dba") == ITK_ok)
	{
		cout << "Entry into the login main \n";
		AE_find_dataset2("HELLOWORLD", &dataset);
		AOM_refresh(dataset, true);//check out the dataset object
		AOM_set_value_string(dataset, "object_desc", "This is the description from the ITK");//changes the object_desc value fo the dataset
		AOM_save_without_extensions(dataset);
		AOM_refresh(dataset, false);//check In the dataset object
		cout << "Finished!";
	}
	return 0;
}