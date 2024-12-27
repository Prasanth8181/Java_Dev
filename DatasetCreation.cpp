#include "TeamCenterITK.h"

int ITK_user_main(int argc, char **argv)
{
	tag_t  new_dataset = NULL_TAG;
	tag_t  output_dataset = NULL_TAG;
	tag_t relationship_type = NULL_TAG;
	tag_t rev_tag = NULL_TAG;
	tag_t item = NULL_TAG;
	tag_t user_data = NULL_TAG;
	tag_t relationObject = NULL_TAG;


	//tag_t  rev = NULL_TAG;
	if (ITK_init_module("infodba","infodba","dba")==ITK_ok)
	{
		cout << "Inside the main function";
		AE_find_datasettype2("Text", &new_dataset);
		GRM_find_relation_type("IMAN_specification", &relationship_type);//to fetch the relation, we are using this api	
		ITEM_find_item("000069", &item);
		
		ITEM_find_revision(item,"A", &rev_tag);
		
		AE_create_dataset_with_id(new_dataset,"text","Specification dataset for the text","1165","A", &output_dataset);
		
		GRM_create_relation(rev_tag, new_dataset,relationship_type, NULLTAG, &relationObject);//It's going to attach it with the some relation
		
		GRM_save_relation(relationObject);
	}
	else
	{
		cout << "kindly provide valid credentials";
	}
	return 0;
}