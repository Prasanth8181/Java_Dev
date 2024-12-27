#include "TeamCenterITK.h";
#define DLLAPI _declspec(dllexport) // using this for compailing purpose.
#define error4 (EMH_USER_error_base +4)
METHOD_id_t method_id;
extern "C"
{
	extern DLLAPI int DLL_register_callbacks();
	extern DLLAPI int PLM_execute_callbacks1(int *decisison, va_list argv);
	extern DLLAPI int set_property_IRMF(int *decision, va_list argv);

	extern DLLAPI int DLL_register_callbacks()
	{
		CUSTOM_register_exit("TeamCenterITK","USER_init_module", (CUSTOM_EXIT_ftn_t)PLM_execute_callbacks1);
	}
	extern DLLAPI int PLM_execute_callbacks1(int *decisison, va_list argv)
	{
		*decisison = ALL_CUSTOMIZATIONS;
		cout << "\n Welcome to DLL Regestration process \n";
		cout << "\n  Login Sucessfull \n ";
		METHOD_find_method("ItemRevision", "ITEM_create_from_rev", &method_id);
		METHOD_add_action(method_id, METHOD_post_action_type, (METHOD_function_t)set_property_IRMF, NULL);
	}
	extern DLLAPI int set_property_IRMF(int *decision, va_list argv)
	{
		tag_t tPrimaryObject = NULLTAG;
		tag_t tRelationType = NULLTAG;
		tag_t* tSecondaryList = NULLTAG;
		char* cValue = NULL;
		int iCount = 0;
		GRM_relation_t* gSecondaryList;
		tPrimaryObject = va_arg(argv, tag_t);

		error(GRM_find_relation_type("IMAN_master_form_rev", &tRelationType));
		error(GRM_list_secondary_objects_only(tPrimaryObject, tRelationType, &iCount, &tSecondaryList));

		if (iCount)
		{
			for (int i = 0; i < iCount; i++)
			{
				error(AOM_refresh(tSecondaryList[i], true));
				error(AOM_set_value_string(tSecondaryList[i], "object_desc", "UPDATE"));
				error(AOM_save_without_extensions(tSecondaryList[i]));
				error(AOM_refresh(tSecondaryList[i], false));
				error(AOM_ask_value_string(tPrimaryObject, "object_name", &cValue));
			}
			return ITK_ok;
		}
		else
		{
			EMH_store_error_s1(EMH_severity_error, error4, cValue);
			return error4;
		}



	}
}